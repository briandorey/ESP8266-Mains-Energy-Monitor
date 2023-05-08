#include "HttpRequests.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>
#include <Ticker.h>
#include "Time.h" 

//#define debug

const char *ssid = "yourWiFissid";
const char *password = "yourWiFipassword";
MDNSResponder mdns;
ESP8266WebServer server(80);

// pin locations
const int ELECTRIC_METER_PIN = 12;
const int GAS_METER_PIN = 13;
const int SDA_PIN = 4;
const int SCL_PIN = 5;
const int READY_PIN = 1;
//const int LED_PIN = 14;




// I2C addresses

const uint8_t FRAM_I2C_ADDRESS = 0x50;
const uint8_t FRAM_START_ADDRESS = 0x10;

// Global variables

uint32_t GasReading = 0; // Gas Meter Reading
uint32_t ElectricReading = 0; // Electric Meter Reading

uint8_t readBuffer1[4] = { 0, 0, 0, 0 }; // used to store temporary buffer for gas meter reading
uint8_t readBuffer2[4] = { 0, 0, 0, 0 }; // used to store temporary buffer for electric meter reading

float  MainsCurrent = 0.0;
float  AvgMainsCurrent = 0.0;
float  MaxMainsCurrent = 0.0;

float  MainsCurrentArray[60];

int ArrayPosition = 0;

//power meter variables:
unsigned long energy = 0;
unsigned long new_millis = 0;
unsigned long old_millis = 0;
unsigned long myoldmillis = 0;

// Variables used for the Setup
int PULSE_PER_KW=3600;  //int PULSE_PER_KW=0; you have to know your meter pulse numbers here.
unsigned long total_energy_consumed = 0;

// interrupts flags
char doSaveFRAM = 0;

// Timer Tickers
Ticker UploadTicker;

//-----------------------------------------------------server----------------------------------
void RequestHome() {
  char temp[900];

  static char MainsCurrentStr[15];
  dtostrf(MainsCurrent, 7, 3, MainsCurrentStr);

  static char AvgMainsCurrentStr[15];
  dtostrf(AvgMainsCurrent, 7, 3, AvgMainsCurrentStr);

  static char MaxMainsCurrentStr[15];
  dtostrf(MaxMainsCurrent, 7, 3, MaxMainsCurrentStr);

  snprintf(temp, 900,

    "<html><head><meta http-equiv='refresh' content='5' /><title>Home Power Monitor</title><link href='https://fonts.googleapis.com/css?family=Roboto:400,300,500' rel='stylesheet' type='text/css'><style>body{background:#ddd;background:linear-gradient(to bottom,#d3f8ff 0%,#fff 100%);font-family:'Roboto',sans-serif;color:#333;padding:100px}h1{font-size:42px;font-weight:300}p{font-size:18px;font-weight:400;color:#000}b{font-weight:500;color:#666}#l{position:absolute;bottom:30px;right:30px;color:#666}</style></head><body><h1>Meter Readings</h1><p><b>Gas:</b> <span>%d</p><p><b>Electricity:</b> <span>%d</span></p><h1>Mains Power</h1><p><b>Mains Current:</b> <span>%s</span></p><p><b>Average Current over last Minute:</b> <span>%s</span></p><p><b>Max Current over last Minute:</b> <span>%s</span></p><a id=\"l\" href=\"/updatemeters\">Settings</a></body></html>" ,GasReading, ElectricReading, MainsCurrentStr, AvgMainsCurrentStr, MaxMainsCurrentStr
                          );
  server.send(200, "text/html", temp);
}

void RequestXMLFeed() {
  char temp[500];

  static char MainsCurrentStr[15];
  dtostrf(MainsCurrent, 7, 3, MainsCurrentStr);

  static char AvgMainsCurrentStr[15];
  dtostrf(AvgMainsCurrent, 7, 3, AvgMainsCurrentStr);

  static char MaxMainsCurrentStr[15];
  dtostrf(MaxMainsCurrent, 7, 3, MaxMainsCurrentStr);

  snprintf(temp, 500,

    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
      \n<vales>\
        \n<gasmeter>%d</gasmeter>\
        \n<electricmeter>%d</electricmeter>\
        \n<mainscurrent>%s</mainscurrent>\
        \n<mainscurrentavg>%s</mainscurrentavg>\
        \n<mainscurrentmax>%s</mainscurrentmax>\
      \n</vales>",
    GasReading, ElectricReading, MainsCurrentStr, AvgMainsCurrentStr, MaxMainsCurrentStr
    );
  server.send(200, "text/html", temp);
}

void RequestSettingsPage(){
  char temp[500];

  snprintf(temp, 500,

    "<HTML><HEAD><TITLE>Mains Monitor - Set Gas Meter</TITLE></HEAD><BODY><h1>Update Meter Values</h1>\
    <form action = \"/setgasmeter\" method = \"post\">\
    Gas Meter Value : <input name = \"gasreading\" value = \"%d\">\
    <button>Set Gas Meter</button>\
    </form>\
    <form action = \"/setelectricmeter\" method = \"post\">\
    Electric Meter Value : <input name = \"electricreading\" value = \"%d\">\
    <button>Set Electric Meter</button>\
    </form></BODY></HTML>",
    GasReading, ElectricReading
    );
  server.send(200, "text/html", temp);
}

void RequestUpdateGasSettings(void){  
  if (server.arg(0).length() > 1 && isValidNumber(server.arg(0))) {
    GasReading = atol(server.arg(0).c_str());
    char temp[50];
    snprintf(temp, 50,
      "gas updated to %d", GasReading
      );
    server.send(200, "text/plain", temp);

    doSaveFRAM = 1;
  }
  else {
    server.send(200, "text/plain", "Update failed");
  }
  
}

void RequestUpdateElectricSettings(void) {
  if (server.arg(0).length() > 1 && isValidNumber(server.arg(0))) {
    ElectricReading = atol(server.arg(0).c_str());
    char temp[50];
    snprintf(temp, 50,
      "electric updated to %d", ElectricReading
      );
    server.send(200, "text/plain", temp);

    doSaveFRAM = 1;
  }
  else {
    server.send(200, "text/plain", "Update failed");
  }
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}

//-------------------------------------------------------server end-----------------------------------------------------------
void setup(void) {
  #ifdef debug
    Serial.begin(115200);
  #endif

   

  // set array values to 0
    for (int x = 0; x < 60; x++){
      MainsCurrentArray[x] = 0;
    }

  // set up the pin direction
  pinMode(ELECTRIC_METER_PIN, INPUT);
  pinMode(GAS_METER_PIN, INPUT);
  pinMode(READY_PIN, INPUT);
  
  // attach interrupts
  
  attachInterrupt(digitalPinToInterrupt(ELECTRIC_METER_PIN), ElectricMeter_Triggered, RISING);
  attachInterrupt(digitalPinToInterrupt(GAS_METER_PIN), GasMeter_Triggered, RISING);

  // initialise I2C devices
  Wire.begin(SDA_PIN, SCL_PIN);
  // load the counter values from FRAM
  LoadFromFRAM();

  // Connect to Wifi  
  WiFi.begin(ssid, password);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    #ifdef debug
    Serial.print(".");
    #endif
    
  }

  #ifdef debug
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  #endif

  if (mdns.begin("esp8266", WiFi.localIP())) {
  #ifdef debug
  Serial.println("MDNS responder started");
  #endif
    
  }

  // set up web server responses

  server.on("/", RequestHome);
  server.on("/xmlfeed", RequestXMLFeed);
  server.on("/updatemeters", RequestSettingsPage);
  server.on("/setgasmeter", RequestUpdateGasSettings);
  server.on("/setelectricmeter", RequestUpdateElectricSettings);
  server.on("/isok", []() {
    server.send(200, "text/plain", "ok");
  });

  server.onNotFound(handleNotFound);
  server.begin();

  #ifdef debug
  Serial.println("HTTP server started");
  #endif
  

  // start timer
  UploadTicker.attach(60.0, UploadData);
}
//---------------------------------------------------------end of setup-------------------------------------------
void loop(void) {
  mdns.update();
  server.handleClient();
  CalculateCurrent();


  


  if (doSaveFRAM == 1) {
    SaveToFRAM();     //------------------------------------------------------------
    doSaveFRAM = 0;  // reset flag
  }
  
}

//-------------------------------end loop------------------------------

IRAM_ATTR void ElectricMeter_Triggered(void){
  
  // Calculate instantaneous power consumption
 // A 250ms delay is used to clean the signal but limits Max power to 18KW
 
 
 if (millis() > (new_millis+250))
  { 
   // Save the time to filter noise 
   myoldmillis = millis();
   ElectricReading += 1;
    doSaveFRAM = 1; // set flag so FRAM will save on next program loop
   
   // Calculate Instant Energy consumption
   
   new_millis = (millis());
   unsigned long ime = (new_millis-old_millis);
   //------------------------------------------
   unsigned long multiplier = (1000000/ime);
   float ratio = ((float)3600/PULSE_PER_KW);
   unsigned long power = (multiplier*ratio);
   
   
   //------------------------------------------
   if (power < 20000)
     {
       energy = power;
     }
   old_millis = new_millis;
  }
}

IRAM_ATTR void GasMeter_Triggered(void){
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200)
  {
    GasReading += 1;
    doSaveFRAM = 1; // set flag so FRAM will save on next program loop
  }
  last_interrupt_time = interrupt_time;
   //save to FRAM //-------------------------------------------------------
}

void CalculateCurrent(void){
  
  float watt_per_pulse = ((float)1000/PULSE_PER_KW);
  total_energy_consumed = (ElectricReading*watt_per_pulse);  //total_energy_consumed = (total_energy*watt_per_pulse);
  char tot_energy[9];
  sprintf(tot_energy, "%06dWh", total_energy_consumed);

  char instant_energy[8];
  sprintf(instant_energy, "%06dWh", energy);
  MainsCurrent = energy;  

  if (MainsCurrent > MaxMainsCurrent) {
      MaxMainsCurrent = MainsCurrent;
    }

    MainsCurrentArray[ArrayPosition] = MainsCurrent;
    ArrayPosition += 1;
    if (ArrayPosition >= 60) {
      ArrayPosition = 0;
    }
}


void UploadData(void){
  // average the last 60 samples
  AvgMainsCurrent = 0;

  for (int x = 0; x < 60; x++){
    AvgMainsCurrent += MainsCurrentArray[x];
  }

  AvgMainsCurrent = AvgMainsCurrent / 60;

  // upload data to the web server

  MaxMainsCurrent = 0;
}

void SaveToFRAM(void){
  /*
  * Save the Gas and Electric meter readings to the FRAM
  */

  Wire.beginTransmission(FRAM_I2C_ADDRESS);

  Wire.write(FRAM_START_ADDRESS);
  Wire.write(lowByte(GasReading));
  Wire.write(lowByte(GasReading >> 8));
  Wire.write(lowByte(GasReading >> 16));
  Wire.write(lowByte(GasReading >> 24));
  Wire.write(lowByte(ElectricReading));
  Wire.write(lowByte(ElectricReading >> 8));
  Wire.write(lowByte(ElectricReading >> 16));
  Wire.write(lowByte(ElectricReading >> 24));

  Wire.endTransmission();
}

void LoadFromFRAM(void){
  Wire.beginTransmission(FRAM_I2C_ADDRESS);
  Wire.write(FRAM_START_ADDRESS);
  Wire.endTransmission();
  Wire.requestFrom(0x50, 8);

  readBuffer1[0] = Wire.read();
  readBuffer1[1] = Wire.read();
  readBuffer1[2] = Wire.read();
  readBuffer1[3] = Wire.read();

  readBuffer2[0] = Wire.read();
  readBuffer2[1] = Wire.read();
  readBuffer2[2] = Wire.read();
  readBuffer2[3] = Wire.read();

  GasReading = readBuffer1[3];
  GasReading = (GasReading << 8) | readBuffer1[2];
  GasReading = (GasReading << 8) | readBuffer1[1];
  GasReading = (GasReading << 8) | readBuffer1[0];

  ElectricReading = readBuffer2[3];
  ElectricReading = (ElectricReading << 8) | readBuffer2[2];
  ElectricReading = (ElectricReading << 8) | readBuffer2[1];
  ElectricReading = (ElectricReading << 8) | readBuffer2[0];
}

boolean isValidNumber(String str) {
  for (byte i = 0; i<str.length(); i++)
  {
    if (isDigit(str.charAt(i))) return true;
  }
  return false;
}

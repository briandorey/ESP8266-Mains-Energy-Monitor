# ESP8266 Mains Energy Monitor
ESP8266 Mains Energy Monitor for gas and electric meter monitoring code and PCB files.

The **PCB files** are in Diptrace format.

The **firmware** folder contains the firmware for the ESP8266 module and has been compiled on Visual Studio 2015 using Visual Micro from [http://www.visualmicro.com](http://www.visualmicro.com)

The hardware profile used to upload to the ESP8266 module was set as:

Hardware: Generic ESP8266 Module, Platform=esp8266, Package=esp8266

The **Case** folder contains design files for the plastic case which was machined from 20mm thick plastic sheet.

The **RaspberryPi** folder contains a python script which is run from a cron job to read the data from the ESP8266 and upload via a querystring to an online database

More details about this project are on my blog at [http://www.briandorey.com](http://www.briandorey.com)


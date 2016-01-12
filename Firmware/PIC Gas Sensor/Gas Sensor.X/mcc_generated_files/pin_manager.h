/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB® Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC12F1822
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set C1INPos aliases
#define C1INPos_TRIS               TRISA0
#define C1INPos_LAT                LATA0
#define C1INPos_PORT               RA0
#define C1INPos_WPU                WPUA0
#define C1INPos_ANS                ANSA0
#define C1INPos_SetHigh()    do { LATA0 = 1; } while(0)
#define C1INPos_SetLow()   do { LATA0 = 0; } while(0)
#define C1INPos_Toggle()   do { LATA0 = ~LATA0; } while(0)
#define C1INPos_GetValue()         RA0
#define C1INPos_SetDigitalInput()    do { TRISA0 = 1; } while(0)
#define C1INPos_SetDigitalOutput()   do { TRISA0 = 0; } while(0)

#define C1INPos_SetPullup()    do { WPUA0 = 1; } while(0)
#define C1INPos_ResetPullup()   do { WPUA0 = 0; } while(0)
#define C1INPos_SetAnalogMode()   do { ANSA0 = 1; } while(0)
#define C1INPos_SetDigitalMode()   do { ANSA0 = 0; } while(0)
// get/set C1OUT aliases
#define C1OUT_TRIS               TRISA2
#define C1OUT_LAT                LATA2
#define C1OUT_PORT               RA2
#define C1OUT_WPU                WPUA2
#define C1OUT_ANS                ANSA2
#define C1OUT_SetHigh()    do { LATA2 = 1; } while(0)
#define C1OUT_SetLow()   do { LATA2 = 0; } while(0)
#define C1OUT_Toggle()   do { LATA2 = ~LATA2; } while(0)
#define C1OUT_GetValue()         RA2
#define C1OUT_SetDigitalInput()    do { TRISA2 = 1; } while(0)
#define C1OUT_SetDigitalOutput()   do { TRISA2 = 0; } while(0)

#define C1OUT_SetPullup()    do { WPUA2 = 1; } while(0)
#define C1OUT_ResetPullup()   do { WPUA2 = 0; } while(0)
#define C1OUT_SetAnalogMode()   do { ANSA2 = 1; } while(0)
#define C1OUT_SetDigitalMode()   do { ANSA2 = 0; } while(0)
// get/set C1IN1Neg aliases
#define C1IN1Neg_TRIS               TRISA4
#define C1IN1Neg_LAT                LATA4
#define C1IN1Neg_PORT               RA4
#define C1IN1Neg_WPU                WPUA4
#define C1IN1Neg_ANS                ANSA4
#define C1IN1Neg_SetHigh()    do { LATA4 = 1; } while(0)
#define C1IN1Neg_SetLow()   do { LATA4 = 0; } while(0)
#define C1IN1Neg_Toggle()   do { LATA4 = ~LATA4; } while(0)
#define C1IN1Neg_GetValue()         RA4
#define C1IN1Neg_SetDigitalInput()    do { TRISA4 = 1; } while(0)
#define C1IN1Neg_SetDigitalOutput()   do { TRISA4 = 0; } while(0)

#define C1IN1Neg_SetPullup()    do { WPUA4 = 1; } while(0)
#define C1IN1Neg_ResetPullup()   do { WPUA4 = 0; } while(0)
#define C1IN1Neg_SetAnalogMode()   do { ANSA4 = 1; } while(0)
#define C1IN1Neg_SetDigitalMode()   do { ANSA4 = 0; } while(0)
// get/set IO_LED aliases
#define IO_LED_TRIS               TRISA5
#define IO_LED_LAT                LATA5
#define IO_LED_PORT               RA5
#define IO_LED_WPU                WPUA5
#define IO_LED_SetHigh()    do { LATA5 = 1; } while(0)
#define IO_LED_SetLow()   do { LATA5 = 0; } while(0)
#define IO_LED_Toggle()   do { LATA5 = ~LATA5; } while(0)
#define IO_LED_GetValue()         RA5
#define IO_LED_SetDigitalInput()    do { TRISA5 = 1; } while(0)
#define IO_LED_SetDigitalOutput()   do { TRISA5 = 0; } while(0)

#define IO_LED_SetPullup()    do { WPUA5 = 1; } while(0)
#define IO_LED_ResetPullup()   do { WPUA5 = 0; } while(0)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize(void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);

#endif // PIN_MANAGER_H
/**
 End of File
 */
/**
  CMP1 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    cmp1.h

  @Summary
    This is the generated header file for the CMP1 driver using MPLAB® Code Configurator

  @Description
    This header file provides APIs for driver for CMP1.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC12F1822
        Driver Version    :  2.00
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

#ifndef _CMP1_H
#define _CMP1_H

/**
  Section: Included Files
 */

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

    /**
      Section: CMP1 APIs
     */

    /**
      @Summary
        Initializes the CMP1

      @Description
        This routine initializes the CMP1.
        This routine must be called before any other CMP1 routine is called.
        This routine should only be called once during system initialization.

      @Preconditions
        None

      @Param
        None

      @Returns
        None

      @Comment
    

      @Example
        <code>
        CMP1_Initialize();
        </code>
     */
    void CMP1_Initialize(void);

    /**
      @Summary
        Gets the CMP1 output status.

      @Description
        This routine gets the CMP1 output status.

      @Preconditions
        The CMP1 initializer routine should be called
        prior to use this routine.

      @Param
        None

      @Returns
        high  - if the CMP1 output is high.
        low   - if the CMP1 output is low.

      @Example
        <code>
        #define LED_On  LATAbits.LATA0=1
        #define LED_Off LATAbits.LATA0=0

        CMP1_Initialize()

        while(1)
        {
            if(CMP1_GetOutputStatus())
            {
                LED_On;
            }
            else
            {
                 LED_Off;
            }
        }
        </code>
     */
    bool CMP1_GetOutputStatus(void);

    /**
      @Summary
        Implements ISR

      @Description
        This routine is used to implement the ISR for the interrupt-driven
        implementations.

      @Returns
        None

      @Param
        None
     */
    void CMP1_ISR(void);


#ifdef __cplusplus  // Provide C++ Compatibility

}

#endif

#endif // _CMP1_H
/**
 End of File
 */


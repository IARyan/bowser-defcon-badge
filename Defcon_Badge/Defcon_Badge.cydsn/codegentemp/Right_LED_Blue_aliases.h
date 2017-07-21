/*******************************************************************************
* File Name: Right_LED_Blue.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Right_LED_Blue_ALIASES_H) /* Pins Right_LED_Blue_ALIASES_H */
#define CY_PINS_Right_LED_Blue_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Right_LED_Blue_0			(Right_LED_Blue__0__PC)
#define Right_LED_Blue_0_PS		(Right_LED_Blue__0__PS)
#define Right_LED_Blue_0_PC		(Right_LED_Blue__0__PC)
#define Right_LED_Blue_0_DR		(Right_LED_Blue__0__DR)
#define Right_LED_Blue_0_SHIFT	(Right_LED_Blue__0__SHIFT)
#define Right_LED_Blue_0_INTR	((uint16)((uint16)0x0003u << (Right_LED_Blue__0__SHIFT*2u)))

#define Right_LED_Blue_INTR_ALL	 ((uint16)(Right_LED_Blue_0_INTR))


#endif /* End Pins Right_LED_Blue_ALIASES_H */


/* [] END OF FILE */

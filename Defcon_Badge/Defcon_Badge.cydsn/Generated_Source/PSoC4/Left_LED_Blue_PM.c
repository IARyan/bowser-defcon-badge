/*******************************************************************************
* File Name: Left_LED_Blue.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Left_LED_Blue.h"

static Left_LED_Blue_BACKUP_STRUCT  Left_LED_Blue_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Left_LED_Blue_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Left_LED_Blue_SUT.c usage_Left_LED_Blue_Sleep_Wakeup
*******************************************************************************/
void Left_LED_Blue_Sleep(void)
{
    #if defined(Left_LED_Blue__PC)
        Left_LED_Blue_backup.pcState = Left_LED_Blue_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Left_LED_Blue_backup.usbState = Left_LED_Blue_CR1_REG;
            Left_LED_Blue_USB_POWER_REG |= Left_LED_Blue_USBIO_ENTER_SLEEP;
            Left_LED_Blue_CR1_REG &= Left_LED_Blue_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Left_LED_Blue__SIO)
        Left_LED_Blue_backup.sioState = Left_LED_Blue_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Left_LED_Blue_SIO_REG &= (uint32)(~Left_LED_Blue_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Left_LED_Blue_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Left_LED_Blue_Sleep() for an example usage.
*******************************************************************************/
void Left_LED_Blue_Wakeup(void)
{
    #if defined(Left_LED_Blue__PC)
        Left_LED_Blue_PC = Left_LED_Blue_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Left_LED_Blue_USB_POWER_REG &= Left_LED_Blue_USBIO_EXIT_SLEEP_PH1;
            Left_LED_Blue_CR1_REG = Left_LED_Blue_backup.usbState;
            Left_LED_Blue_USB_POWER_REG &= Left_LED_Blue_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Left_LED_Blue__SIO)
        Left_LED_Blue_SIO_REG = Left_LED_Blue_backup.sioState;
    #endif
}


/* [] END OF FILE */

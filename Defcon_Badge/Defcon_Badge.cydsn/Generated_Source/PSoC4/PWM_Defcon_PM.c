/*******************************************************************************
* File Name: PWM_Defcon_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_Defcon.h"

static PWM_Defcon_backupStruct PWM_Defcon_backup;


/*******************************************************************************
* Function Name: PWM_Defcon_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Defcon_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Defcon_SaveConfig(void) 
{

    #if(!PWM_Defcon_UsingFixedFunction)
        #if(!PWM_Defcon_PWMModeIsCenterAligned)
            PWM_Defcon_backup.PWMPeriod = PWM_Defcon_ReadPeriod();
        #endif /* (!PWM_Defcon_PWMModeIsCenterAligned) */
        PWM_Defcon_backup.PWMUdb = PWM_Defcon_ReadCounter();
        #if (PWM_Defcon_UseStatus)
            PWM_Defcon_backup.InterruptMaskValue = PWM_Defcon_STATUS_MASK;
        #endif /* (PWM_Defcon_UseStatus) */

        #if(PWM_Defcon_DeadBandMode == PWM_Defcon__B_PWM__DBM_256_CLOCKS || \
            PWM_Defcon_DeadBandMode == PWM_Defcon__B_PWM__DBM_2_4_CLOCKS)
            PWM_Defcon_backup.PWMdeadBandValue = PWM_Defcon_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_Defcon_KillModeMinTime)
             PWM_Defcon_backup.PWMKillCounterPeriod = PWM_Defcon_ReadKillTime();
        #endif /* (PWM_Defcon_KillModeMinTime) */

        #if(PWM_Defcon_UseControl)
            PWM_Defcon_backup.PWMControlRegister = PWM_Defcon_ReadControlRegister();
        #endif /* (PWM_Defcon_UseControl) */
    #endif  /* (!PWM_Defcon_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Defcon_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Defcon_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Defcon_RestoreConfig(void) 
{
        #if(!PWM_Defcon_UsingFixedFunction)
            #if(!PWM_Defcon_PWMModeIsCenterAligned)
                PWM_Defcon_WritePeriod(PWM_Defcon_backup.PWMPeriod);
            #endif /* (!PWM_Defcon_PWMModeIsCenterAligned) */

            PWM_Defcon_WriteCounter(PWM_Defcon_backup.PWMUdb);

            #if (PWM_Defcon_UseStatus)
                PWM_Defcon_STATUS_MASK = PWM_Defcon_backup.InterruptMaskValue;
            #endif /* (PWM_Defcon_UseStatus) */

            #if(PWM_Defcon_DeadBandMode == PWM_Defcon__B_PWM__DBM_256_CLOCKS || \
                PWM_Defcon_DeadBandMode == PWM_Defcon__B_PWM__DBM_2_4_CLOCKS)
                PWM_Defcon_WriteDeadTime(PWM_Defcon_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_Defcon_KillModeMinTime)
                PWM_Defcon_WriteKillTime(PWM_Defcon_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Defcon_KillModeMinTime) */

            #if(PWM_Defcon_UseControl)
                PWM_Defcon_WriteControlRegister(PWM_Defcon_backup.PWMControlRegister);
            #endif /* (PWM_Defcon_UseControl) */
        #endif  /* (!PWM_Defcon_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Defcon_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Defcon_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Defcon_Sleep(void) 
{
    #if(PWM_Defcon_UseControl)
        if(PWM_Defcon_CTRL_ENABLE == (PWM_Defcon_CONTROL & PWM_Defcon_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Defcon_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Defcon_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Defcon_UseControl) */

    /* Stop component */
    PWM_Defcon_Stop();

    /* Save registers configuration */
    PWM_Defcon_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Defcon_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_Defcon_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Defcon_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Defcon_RestoreConfig();

    if(PWM_Defcon_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Defcon_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */

/*******************************************************************************
* File Name: Right_LED_Red.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Right_LED_Red_H) /* Pins Right_LED_Red_H */
#define CY_PINS_Right_LED_Red_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Right_LED_Red_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Right_LED_Red_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Right_LED_Red_Read(void);
void    Right_LED_Red_Write(uint8 value);
uint8   Right_LED_Red_ReadDataReg(void);
#if defined(Right_LED_Red__PC) || (CY_PSOC4_4200L) 
    void    Right_LED_Red_SetDriveMode(uint8 mode);
#endif
void    Right_LED_Red_SetInterruptMode(uint16 position, uint16 mode);
uint8   Right_LED_Red_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Right_LED_Red_Sleep(void); 
void Right_LED_Red_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Right_LED_Red__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Right_LED_Red_DRIVE_MODE_BITS        (3)
    #define Right_LED_Red_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Right_LED_Red_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Right_LED_Red_SetDriveMode() function.
         *  @{
         */
        #define Right_LED_Red_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Right_LED_Red_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Right_LED_Red_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Right_LED_Red_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Right_LED_Red_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Right_LED_Red_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Right_LED_Red_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Right_LED_Red_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Right_LED_Red_MASK               Right_LED_Red__MASK
#define Right_LED_Red_SHIFT              Right_LED_Red__SHIFT
#define Right_LED_Red_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Right_LED_Red_SetInterruptMode() function.
     *  @{
     */
        #define Right_LED_Red_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Right_LED_Red_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Right_LED_Red_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Right_LED_Red_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Right_LED_Red__SIO)
    #define Right_LED_Red_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Right_LED_Red__PC) && (CY_PSOC4_4200L)
    #define Right_LED_Red_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Right_LED_Red_USBIO_DISABLE              ((uint32)(~Right_LED_Red_USBIO_ENABLE))
    #define Right_LED_Red_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Right_LED_Red_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Right_LED_Red_USBIO_ENTER_SLEEP          ((uint32)((1u << Right_LED_Red_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Right_LED_Red_USBIO_SUSPEND_DEL_SHIFT)))
    #define Right_LED_Red_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Right_LED_Red_USBIO_SUSPEND_SHIFT)))
    #define Right_LED_Red_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Right_LED_Red_USBIO_SUSPEND_DEL_SHIFT)))
    #define Right_LED_Red_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Right_LED_Red__PC)
    /* Port Configuration */
    #define Right_LED_Red_PC                 (* (reg32 *) Right_LED_Red__PC)
#endif
/* Pin State */
#define Right_LED_Red_PS                     (* (reg32 *) Right_LED_Red__PS)
/* Data Register */
#define Right_LED_Red_DR                     (* (reg32 *) Right_LED_Red__DR)
/* Input Buffer Disable Override */
#define Right_LED_Red_INP_DIS                (* (reg32 *) Right_LED_Red__PC2)

/* Interrupt configuration Registers */
#define Right_LED_Red_INTCFG                 (* (reg32 *) Right_LED_Red__INTCFG)
#define Right_LED_Red_INTSTAT                (* (reg32 *) Right_LED_Red__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Right_LED_Red_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Right_LED_Red__SIO)
    #define Right_LED_Red_SIO_REG            (* (reg32 *) Right_LED_Red__SIO)
#endif /* (Right_LED_Red__SIO_CFG) */

/* USBIO registers */
#if !defined(Right_LED_Red__PC) && (CY_PSOC4_4200L)
    #define Right_LED_Red_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Right_LED_Red_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Right_LED_Red_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Right_LED_Red_DRIVE_MODE_SHIFT       (0x00u)
#define Right_LED_Red_DRIVE_MODE_MASK        (0x07u << Right_LED_Red_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Right_LED_Red_H */


/* [] END OF FILE */

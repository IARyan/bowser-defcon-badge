/*******************************************************************************
* File Name: Board_LED.h  
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

#if !defined(CY_PINS_Board_LED_H) /* Pins Board_LED_H */
#define CY_PINS_Board_LED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Board_LED_aliases.h"


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
} Board_LED_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Board_LED_Read(void);
void    Board_LED_Write(uint8 value);
uint8   Board_LED_ReadDataReg(void);
#if defined(Board_LED__PC) || (CY_PSOC4_4200L) 
    void    Board_LED_SetDriveMode(uint8 mode);
#endif
void    Board_LED_SetInterruptMode(uint16 position, uint16 mode);
uint8   Board_LED_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Board_LED_Sleep(void); 
void Board_LED_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Board_LED__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Board_LED_DRIVE_MODE_BITS        (3)
    #define Board_LED_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Board_LED_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Board_LED_SetDriveMode() function.
         *  @{
         */
        #define Board_LED_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Board_LED_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Board_LED_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Board_LED_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Board_LED_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Board_LED_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Board_LED_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Board_LED_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Board_LED_MASK               Board_LED__MASK
#define Board_LED_SHIFT              Board_LED__SHIFT
#define Board_LED_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Board_LED_SetInterruptMode() function.
     *  @{
     */
        #define Board_LED_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Board_LED_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Board_LED_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Board_LED_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Board_LED__SIO)
    #define Board_LED_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Board_LED__PC) && (CY_PSOC4_4200L)
    #define Board_LED_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Board_LED_USBIO_DISABLE              ((uint32)(~Board_LED_USBIO_ENABLE))
    #define Board_LED_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Board_LED_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Board_LED_USBIO_ENTER_SLEEP          ((uint32)((1u << Board_LED_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Board_LED_USBIO_SUSPEND_DEL_SHIFT)))
    #define Board_LED_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Board_LED_USBIO_SUSPEND_SHIFT)))
    #define Board_LED_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Board_LED_USBIO_SUSPEND_DEL_SHIFT)))
    #define Board_LED_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Board_LED__PC)
    /* Port Configuration */
    #define Board_LED_PC                 (* (reg32 *) Board_LED__PC)
#endif
/* Pin State */
#define Board_LED_PS                     (* (reg32 *) Board_LED__PS)
/* Data Register */
#define Board_LED_DR                     (* (reg32 *) Board_LED__DR)
/* Input Buffer Disable Override */
#define Board_LED_INP_DIS                (* (reg32 *) Board_LED__PC2)

/* Interrupt configuration Registers */
#define Board_LED_INTCFG                 (* (reg32 *) Board_LED__INTCFG)
#define Board_LED_INTSTAT                (* (reg32 *) Board_LED__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Board_LED_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Board_LED__SIO)
    #define Board_LED_SIO_REG            (* (reg32 *) Board_LED__SIO)
#endif /* (Board_LED__SIO_CFG) */

/* USBIO registers */
#if !defined(Board_LED__PC) && (CY_PSOC4_4200L)
    #define Board_LED_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Board_LED_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Board_LED_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Board_LED_DRIVE_MODE_SHIFT       (0x00u)
#define Board_LED_DRIVE_MODE_MASK        (0x07u << Board_LED_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Board_LED_H */


/* [] END OF FILE */

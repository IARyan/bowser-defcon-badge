/*******************************************************************************
* File Name: SWL.h  
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

#if !defined(CY_PINS_SWL_H) /* Pins SWL_H */
#define CY_PINS_SWL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SWL_aliases.h"


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
} SWL_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SWL_Read(void);
void    SWL_Write(uint8 value);
uint8   SWL_ReadDataReg(void);
#if defined(SWL__PC) || (CY_PSOC4_4200L) 
    void    SWL_SetDriveMode(uint8 mode);
#endif
void    SWL_SetInterruptMode(uint16 position, uint16 mode);
uint8   SWL_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SWL_Sleep(void); 
void SWL_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SWL__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SWL_DRIVE_MODE_BITS        (3)
    #define SWL_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SWL_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SWL_SetDriveMode() function.
         *  @{
         */
        #define SWL_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SWL_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SWL_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SWL_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SWL_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SWL_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SWL_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SWL_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SWL_MASK               SWL__MASK
#define SWL_SHIFT              SWL__SHIFT
#define SWL_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SWL_SetInterruptMode() function.
     *  @{
     */
        #define SWL_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SWL_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SWL_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SWL_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SWL__SIO)
    #define SWL_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SWL__PC) && (CY_PSOC4_4200L)
    #define SWL_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SWL_USBIO_DISABLE              ((uint32)(~SWL_USBIO_ENABLE))
    #define SWL_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SWL_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SWL_USBIO_ENTER_SLEEP          ((uint32)((1u << SWL_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SWL_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWL_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SWL_USBIO_SUSPEND_SHIFT)))
    #define SWL_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SWL_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWL_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SWL__PC)
    /* Port Configuration */
    #define SWL_PC                 (* (reg32 *) SWL__PC)
#endif
/* Pin State */
#define SWL_PS                     (* (reg32 *) SWL__PS)
/* Data Register */
#define SWL_DR                     (* (reg32 *) SWL__DR)
/* Input Buffer Disable Override */
#define SWL_INP_DIS                (* (reg32 *) SWL__PC2)

/* Interrupt configuration Registers */
#define SWL_INTCFG                 (* (reg32 *) SWL__INTCFG)
#define SWL_INTSTAT                (* (reg32 *) SWL__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SWL_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SWL__SIO)
    #define SWL_SIO_REG            (* (reg32 *) SWL__SIO)
#endif /* (SWL__SIO_CFG) */

/* USBIO registers */
#if !defined(SWL__PC) && (CY_PSOC4_4200L)
    #define SWL_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SWL_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SWL_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SWL_DRIVE_MODE_SHIFT       (0x00u)
#define SWL_DRIVE_MODE_MASK        (0x07u << SWL_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SWL_H */


/* [] END OF FILE */

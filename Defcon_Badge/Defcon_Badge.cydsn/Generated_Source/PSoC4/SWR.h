/*******************************************************************************
* File Name: SWR.h  
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

#if !defined(CY_PINS_SWR_H) /* Pins SWR_H */
#define CY_PINS_SWR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SWR_aliases.h"


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
} SWR_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SWR_Read(void);
void    SWR_Write(uint8 value);
uint8   SWR_ReadDataReg(void);
#if defined(SWR__PC) || (CY_PSOC4_4200L) 
    void    SWR_SetDriveMode(uint8 mode);
#endif
void    SWR_SetInterruptMode(uint16 position, uint16 mode);
uint8   SWR_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SWR_Sleep(void); 
void SWR_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SWR__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SWR_DRIVE_MODE_BITS        (3)
    #define SWR_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SWR_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SWR_SetDriveMode() function.
         *  @{
         */
        #define SWR_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SWR_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SWR_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SWR_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SWR_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SWR_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SWR_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SWR_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SWR_MASK               SWR__MASK
#define SWR_SHIFT              SWR__SHIFT
#define SWR_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SWR_SetInterruptMode() function.
     *  @{
     */
        #define SWR_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SWR_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SWR_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SWR_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SWR__SIO)
    #define SWR_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SWR__PC) && (CY_PSOC4_4200L)
    #define SWR_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SWR_USBIO_DISABLE              ((uint32)(~SWR_USBIO_ENABLE))
    #define SWR_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SWR_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SWR_USBIO_ENTER_SLEEP          ((uint32)((1u << SWR_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SWR_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWR_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SWR_USBIO_SUSPEND_SHIFT)))
    #define SWR_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SWR_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWR_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SWR__PC)
    /* Port Configuration */
    #define SWR_PC                 (* (reg32 *) SWR__PC)
#endif
/* Pin State */
#define SWR_PS                     (* (reg32 *) SWR__PS)
/* Data Register */
#define SWR_DR                     (* (reg32 *) SWR__DR)
/* Input Buffer Disable Override */
#define SWR_INP_DIS                (* (reg32 *) SWR__PC2)

/* Interrupt configuration Registers */
#define SWR_INTCFG                 (* (reg32 *) SWR__INTCFG)
#define SWR_INTSTAT                (* (reg32 *) SWR__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SWR_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SWR__SIO)
    #define SWR_SIO_REG            (* (reg32 *) SWR__SIO)
#endif /* (SWR__SIO_CFG) */

/* USBIO registers */
#if !defined(SWR__PC) && (CY_PSOC4_4200L)
    #define SWR_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SWR_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SWR_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SWR_DRIVE_MODE_SHIFT       (0x00u)
#define SWR_DRIVE_MODE_MASK        (0x07u << SWR_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SWR_H */


/* [] END OF FILE */

#ifndef __DEVICE_H
#define __DEVICE_H

/**
  \brief  Structure type to access the System Timer (SysTick).
 */
typedef struct
{
  __IOM uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __IOM uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  __IOM uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  __IM  uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} MCU_SysTick_Type;

/* SysTick Control / Status Register Definitions */
#define MCU_SysTick_CTRL_COUNTFLAG_Pos         16U /*!< SysTick CTRL: COUNTFLAG Position */
#define MCU_SysTick_CTRL_COUNTFLAG_Msk         (1UL << MCU_SysTick_CTRL_COUNTFLAG_Pos) /*!< SysTick CTRL: COUNTFLAG Mask */

#define MCU_SysTick_CTRL_CLKSOURCE_Pos          2U /*!< SysTick CTRL: CLKSOURCE Position */
#define MCU_SysTick_CTRL_CLKSOURCE_Msk         (1UL << MCU_SysTick_CTRL_CLKSOURCE_Pos)            /*!< SysTick CTRL: CLKSOURCE Mask */

#define MCU_SysTick_CTRL_TICKINT_Pos            1U                                            /*!< SysTick CTRL: TICKINT Position */
#define MCU_SysTick_CTRL_TICKINT_Msk           (1UL << MCU_SysTick_CTRL_TICKINT_Pos)              /*!< SysTick CTRL: TICKINT Mask */

#define MCU_SysTick_CTRL_ENABLE_Pos             0U                                            /*!< SysTick CTRL: ENABLE Position */
#define MCU_SysTick_CTRL_ENABLE_Msk            (1UL /*<< MCU_SysTick_CTRL_ENABLE_Pos*/)           /*!< SysTick CTRL: ENABLE Mask */

/* SysTick Reload Register Definitions */
#define MCU_SysTick_LOAD_RELOAD_Pos             0U                                            /*!< SysTick LOAD: RELOAD Position */
#define MCU_SysTick_LOAD_RELOAD_Msk            (0xFFFFFFUL /*<< MCU_SysTick_LOAD_RELOAD_Pos*/)    /*!< SysTick LOAD: RELOAD Mask */

/* SysTick Current Register Definitions */
#define MCU_SysTick_VAL_CURRENT_Pos             0U                                            /*!< SysTick VAL: CURRENT Position */
#define MCU_SysTick_VAL_CURRENT_Msk            (0xFFFFFFUL /*<< MCU_SysTick_VAL_CURRENT_Pos*/)    /*!< SysTick VAL: CURRENT Mask */

/* SysTick Calibration Register Definitions */
#define MCU_SysTick_CALIB_NOREF_Pos            31U                                            /*!< SysTick CALIB: NOREF Position */
#define MCU_SysTick_CALIB_NOREF_Msk            (1UL << MCU_SysTick_CALIB_NOREF_Pos)               /*!< SysTick CALIB: NOREF Mask */

#define MCU_SysTick_CALIB_SKEW_Pos             30U                                            /*!< SysTick CALIB: SKEW Position */
#define MCU_SysTick_CALIB_SKEW_Msk             (1UL << MCU_SysTick_CALIB_SKEW_Pos)                /*!< SysTick CALIB: SKEW Mask */

#define MCU_SysTick_CALIB_TENMS_Pos             0U                                            /*!< SysTick CALIB: TENMS Position */
#define MCU_SysTick_CALIB_TENMS_Msk            (0xFFFFFFUL /*<< MCU_SysTick_CALIB_TENMS_Pos*/)    /*!< SysTick CALIB: TENMS Mask */

/*@} end of group MCU_SysTick */

/**
  \ingroup    MCU core_register
  \defgroup   MCU core_base     Core Definitions
  \brief      Definitions for base addresses, unions, and structures.
  @{
 */

/* Memory mapping of Cortex-M0+ Hardware */
#define MCU_SCS_BASE     (0xE000E000UL) /*!< System Control Space Base Address */
#define MCU_SysTick_BASE (MCU_SCS_BASE +  0x0010UL) /*!< SysTick Base Address */
#define MCU_SysTick      ((MCU_SysTick_Type *) MCU_SysTick_BASE) /*!< SysTick configuration struct */

/*!
 * @}
 */ /* end of group Cortex_Core_Configuration */


/** SIM - Register Layout Typedef */
typedef struct {
  __IO uint32_t SOPT1;                             /**< System Options Register 1, offset: 0x0 */
  __IO uint32_t SOPT1CFG;                          /**< SOPT1 Configuration Register, offset: 0x4 */
       uint8_t RESERVED_0[4092];
  __IO uint32_t SOPT2;                             /**< System Options Register 2, offset: 0x1004 */
       uint8_t RESERVED_1[4];
  __IO uint32_t SOPT4;                             /**< System Options Register 4, offset: 0x100C */
  __IO uint32_t SOPT5;                             /**< System Options Register 5, offset: 0x1010 */
       uint8_t RESERVED_2[4];
  __IO uint32_t SOPT7;                             /**< System Options Register 7, offset: 0x1018 */
       uint8_t RESERVED_3[8];
  __I  uint32_t SDID;                              /**< System Device Identification Register, offset: 0x1024 */
       uint8_t RESERVED_4[12];
  __IO uint32_t SCGC4;                             /**< System Clock Gating Control Register 4, offset: 0x1034 */
  __IO uint32_t SCGC5;                             /**< System Clock Gating Control Register 5, offset: 0x1038 */
  __IO uint32_t SCGC6;                             /**< System Clock Gating Control Register 6, offset: 0x103C */
  __IO uint32_t SCGC7;                             /**< System Clock Gating Control Register 7, offset: 0x1040 */
  __IO uint32_t CLKDIV1;                           /**< System Clock Divider Register 1, offset: 0x1044 */
       uint8_t RESERVED_5[4];
  __IO uint32_t FCFG1;                             /**< Flash Configuration Register 1, offset: 0x104C */
  __I  uint32_t FCFG2;                             /**< Flash Configuration Register 2, offset: 0x1050 */
       uint8_t RESERVED_6[4];
  __I  uint32_t UIDMH;                             /**< Unique Identification Register Mid-High, offset: 0x1058 */
  __I  uint32_t UIDML;                             /**< Unique Identification Register Mid Low, offset: 0x105C */
  __I  uint32_t UIDL;                              /**< Unique Identification Register Low, offset: 0x1060 */
       uint8_t RESERVED_7[156];
  __IO uint32_t COPC;                              /**< COP Control Register, offset: 0x1100 */
  __O  uint32_t SRVCOP;                            /**< Service COP, offset: 0x1104 */
} MCU_SIM_Type;

#define MCU_SIM_SCGC5_MCU_PORTA_MASK                     (0x200U)
#define MCU_SIM_SCGC5_MCU_PORTA_SHIFT                    (9U)
#define MCU_SIM_SCGC5_PORTA(x)                       (((uint32_t)(((uint32_t)(x)) << MCU_SIM_SCGC5_MCU_PORTA_SHIFT)) & MCU_SIM_SCGC5_MCU_PORTA_MASK)
#define MCU_SIM_SCGC5_MCU_PORTB_MASK                     (0x400U)
#define MCU_SIM_SCGC5_MCU_PORTB_SHIFT                    (10U)
#define MCU_SIM_SCGC5_PORTB(x)                       (((uint32_t)(((uint32_t)(x)) << MCU_SIM_SCGC5_MCU_PORTB_SHIFT)) & MCU_SIM_SCGC5_MCU_PORTB_MASK)
#define MCU_SIM_SCGC5_MCU_PORTC_MASK                     (0x800U)
#define MCU_SIM_SCGC5_MCU_PORTC_SHIFT                    (11U)
#define MCU_SIM_SCGC5_PORTC(x)                       (((uint32_t)(((uint32_t)(x)) << MCU_SIM_SCGC5_MCU_PORTC_SHIFT)) & MCU_SIM_SCGC5_MCU_PORTC_MASK)
#define MCU_SIM_SCGC5_MCU_PORTD_MASK                     (0x1000U)
#define MCU_SIM_SCGC5_MCU_PORTD_SHIFT                    (12U)
#define MCU_SIM_SCGC5_PORTD(x)                       (((uint32_t)(((uint32_t)(x)) << MCU_SIM_SCGC5_MCU_PORTD_SHIFT)) & MCU_SIM_SCGC5_MCU_PORTD_MASK)
#define MCU_SIM_SCGC5_MCU_PORTE_MASK                     (0x2000U)
#define MCU_SIM_SCGC5_MCU_PORTE_SHIFT                    (13U)
#define MCU_SIM_SCGC5_PORTE(x)                       (((uint32_t)(((uint32_t)(x)) << MCU_SIM_SCGC5_MCU_PORTE_SHIFT)) & MCU_SIM_SCGC5_MCU_PORTE_MASK)
#define MCU_SIM_SCGC5_SLCD_MASK                      (0x80000U)
#define MCU_SIM_SCGC5_SLCD_SHIFT                     (19U)
#define MCU_SIM_SCGC5_SLCD(x)                        (((uint32_t)(((uint32_t)(x)) << MCU_SIM_SCGC5_SLCD_SHIFT)) & MCU_SIM_SCGC5_SLCD_MASK)

/*!
 * @}
 */ /* end of group SIM_Register_Masks */


/* SIM - Peripheral instance base addresses */
/** Peripheral SIM base address */
#define MCU_SIM_BASE                                 (0x40047000u)
/** Peripheral SIM base pointer */
#define MCU_SIM                                      ((MCU_SIM_Type *)MCU_SIM_BASE)
/** Array initializer of SIM peripheral base addresses */
#define MCU_SIM_BASE_ADDRS                           { MCU_SIM_BASE }
/** Array initializer of SIM peripheral base pointers */
#define MCU_SIM_BASE_PTRS                            { MCU_SIM }

/*!
 * @}
 */ /* end of group SIM_Peripheral_Access_Layer */

 ///////////////////////////////////////////////////////////////////////////////////////////////////
 /*!
 * @addtogroup MCU_PORT_Peripheral_Access_Layer PORT Peripheral Access Layer
 * @{
 */

/** PORT - Register Layout Typedef */
typedef struct {
  __IO uint32_t PCR[32];                           /**< Pin Control Register n, array offset: 0x0, array step: 0x4 */
  __O  uint32_t GPCLR;                             /**< Global Pin Control Low Register, offset: 0x80 */
  __O  uint32_t GPCHR;                             /**< Global Pin Control High Register, offset: 0x84 */
       uint8_t RESERVED_0[24];
  __IO uint32_t ISFR;                              /**< Interrupt Status Flag Register, offset: 0xA0 */
} MCU_PORT_Type;

/* ----------------------------------------------------------------------------
   -- PORT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCU_PORT_Register_Masks PORT Register Masks
 * @{
 */

/*! @name PCR - Pin Control Register n */
#define MCU_PORT_PCR_PS_MASK                         (0x1U)
#define MCU_PORT_PCR_PS_SHIFT                        (0U)
#define MCU_PORT_PCR_PS(x)                           (((uint32_t)(((uint32_t)(x)) << MCU_PORT_PCR_PS_SHIFT)) & MCU_PORT_PCR_PS_MASK)
#define MCU_PORT_PCR_PE_MASK                         (0x2U)
#define MCU_PORT_PCR_PE_SHIFT                        (1U)
#define MCU_PORT_PCR_PE(x)                           (((uint32_t)(((uint32_t)(x)) << MCU_PORT_PCR_PE_SHIFT)) & MCU_PORT_PCR_PE_MASK)
#define MCU_PORT_PCR_SRE_MASK                        (0x4U)
#define MCU_PORT_PCR_SRE_SHIFT                       (2U)
#define MCU_PORT_PCR_SRE(x)                          (((uint32_t)(((uint32_t)(x)) << MCU_PORT_PCR_SRE_SHIFT)) & MCU_PORT_PCR_SRE_MASK)
#define MCU_PORT_PCR_PFE_MASK                        (0x10U)
#define MCU_PORT_PCR_PFE_SHIFT                       (4U)
#define MCU_PORT_PCR_PFE(x)                          (((uint32_t)(((uint32_t)(x)) << MCU_PORT_PCR_PFE_SHIFT)) & MCU_PORT_PCR_PFE_MASK)
#define MCU_PORT_PCR_DSE_MASK                        (0x40U)
#define MCU_PORT_PCR_DSE_SHIFT                       (6U)
#define MCU_PORT_PCR_DSE(x)                          (((uint32_t)(((uint32_t)(x)) << MCU_PORT_PCR_DSE_SHIFT)) & MCU_PORT_PCR_DSE_MASK)
#define MCU_PORT_PCR_MUX_MASK                        (0x700U)
#define MCU_PORT_PCR_MUX_SHIFT                       (8U)
#define MCU_PORT_PCR_MUX(x)                          (((uint32_t)(((uint32_t)(x)) << MCU_PORT_PCR_MUX_SHIFT)) & MCU_PORT_PCR_MUX_MASK)
#define MCU_PORT_PCR_IRQC_MASK                       (0xF0000U)
#define MCU_PORT_PCR_IRQC_SHIFT                      (16U)
#define MCU_PORT_PCR_IRQC(x)                         (((uint32_t)(((uint32_t)(x)) << MCU_PORT_PCR_IRQC_SHIFT)) & MCU_PORT_PCR_IRQC_MASK)
#define MCU_PORT_PCR_ISF_MASK                        (0x1000000U)
#define MCU_PORT_PCR_ISF_SHIFT                       (24U)
#define MCU_PORT_PCR_ISF(x)                          (((uint32_t)(((uint32_t)(x)) << MCU_PORT_PCR_ISF_SHIFT)) & MCU_PORT_PCR_ISF_MASK)

/* The count of MCU_PORT_PCR */
#define MCU_PORT_PCR_COUNT                           (32U)

/*! @name GPCLR - Global Pin Control Low Register */
#define MCU_PORT_GPCLR_GPWD_MASK                     (0xFFFFU)
#define MCU_PORT_GPCLR_GPWD_SHIFT                    (0U)
#define MCU_PORT_GPCLR_GPWD(x)                       (((uint32_t)(((uint32_t)(x)) << MCU_PORT_GPCLR_GPWD_SHIFT)) & MCU_PORT_GPCLR_GPWD_MASK)
#define MCU_PORT_GPCLR_GPWE_MASK                     (0xFFFF0000U)
#define MCU_PORT_GPCLR_GPWE_SHIFT                    (16U)
#define MCU_PORT_GPCLR_GPWE(x)                       (((uint32_t)(((uint32_t)(x)) << MCU_PORT_GPCLR_GPWE_SHIFT)) & MCU_PORT_GPCLR_GPWE_MASK)

/*! @name GPCHR - Global Pin Control High Register */
#define MCU_PORT_GPCHR_GPWD_MASK                     (0xFFFFU)
#define MCU_PORT_GPCHR_GPWD_SHIFT                    (0U)
#define MCU_PORT_GPCHR_GPWD(x)                       (((uint32_t)(((uint32_t)(x)) << MCU_PORT_GPCHR_GPWD_SHIFT)) & MCU_PORT_GPCHR_GPWD_MASK)
#define MCU_PORT_GPCHR_GPWE_MASK                     (0xFFFF0000U)
#define MCU_PORT_GPCHR_GPWE_SHIFT                    (16U)
#define MCU_PORT_GPCHR_GPWE(x)                       (((uint32_t)(((uint32_t)(x)) << MCU_PORT_GPCHR_GPWE_SHIFT)) & MCU_PORT_GPCHR_GPWE_MASK)

/*! @name ISFR - Interrupt Status Flag Register */
#define MCU_PORT_ISFR_ISF_MASK                       (0xFFFFFFFFU)
#define MCU_PORT_ISFR_ISF_SHIFT                      (0U)
#define MCU_PORT_ISFR_ISF(x)                         (((uint32_t)(((uint32_t)(x)) << MCU_PORT_ISFR_ISF_SHIFT)) & MCU_PORT_ISFR_ISF_MASK)


/*!
 * @}
 */ /* end of group MCU_PORT_Register_Masks */


/* PORT - Peripheral instance base addresses */
/** Peripheral PORTA base address */
#define MCU_PORTA_BASE                               (0x40049000u)
/** Peripheral PORTA base pointer */
#define MCU_PORTA                                    ((MCU_PORT_Type *)MCU_PORTA_BASE)
/** Peripheral PORTB base address */
#define MCU_PORTB_BASE                               (0x4004A000u)
/** Peripheral PORTB base pointer */
#define MCU_PORTB                                    ((MCU_PORT_Type *)MCU_PORTB_BASE)
/** Peripheral PORTC base address */
#define MCU_PORTC_BASE                               (0x4004B000u)
/** Peripheral PORTC base pointer */
#define MCU_PORTC                                    ((MCU_PORT_Type *)MCU_PORTC_BASE)
/** Peripheral PORTD base address */
#define MCU_PORTD_BASE                               (0x4004C000u)
/** Peripheral PORTD base pointer */
#define MCU_PORTD                                    ((MCU_PORT_Type *)MCU_PORTD_BASE)
/** Peripheral PORTE base address */
#define MCU_PORTE_BASE                               (0x4004D000u)
/** Peripheral PORTE base pointer */
#define MCU_PORTE                                    ((MCU_PORT_Type *)MCU_PORTE_BASE)
/** Array initializer of PORT peripheral base addresses */
#define MCU_PORT_BASE_ADDRS                          { MCU_PORTA_BASE, MCU_PORTB_BASE, MCU_PORTC_BASE, MCU_PORTD_BASE, MCU_PORTE_BASE }
/** Array initializer of PORT peripheral base pointers */
#define MCU_PORT_BASE_PTRS                           { MCU_PORTA, MCU_PORTB, MCU_PORTC, MCU_PORTD, MCU_PORTE }

/*!
 * @}
 */ /* end of group MCU_PORT_Peripheral_Access_Layer */
////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * @addtogroup MCU_GPIO_Peripheral_Access_Layer GPIO Peripheral Access Layer
 * @{
 */

/** GPIO - Register Layout Typedef */
typedef struct {
  __IO uint32_t PDOR;                              /**< Port Data Output Register, offset: 0x0 */
  __O  uint32_t PSOR;                              /**< Port Set Output Register, offset: 0x4 */
  __O  uint32_t PCOR;                              /**< Port Clear Output Register, offset: 0x8 */
  __O  uint32_t PTOR;                              /**< Port Toggle Output Register, offset: 0xC */
  __I  uint32_t PDIR;                              /**< Port Data Input Register, offset: 0x10 */
  __IO uint32_t PDDR;                              /**< Port Data Direction Register, offset: 0x14 */
} MCU_GPIO_Type;

/* ----------------------------------------------------------------------------
   -- GPIO Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCU_GPIO_Register_Masks GPIO Register Masks
 * @{
 */

/*! @name PDOR - Port Data Output Register */
#define MCU_GPIO_PDOR_PDO_MASK                       (0xFFFFFFFFU)
#define MCU_GPIO_PDOR_PDO_SHIFT                      (0U)
#define MCU_GPIO_PDOR_PDO(x)                         (((uint32_t)(((uint32_t)(x)) << MCU_GPIO_PDOR_PDO_SHIFT)) & MCU_GPIO_PDOR_PDO_MASK)

/*! @name PSOR - Port Set Output Register */
#define MCU_GPIO_PSOR_PTSO_MASK                      (0xFFFFFFFFU)
#define MCU_GPIO_PSOR_PTSO_SHIFT                     (0U)
#define MCU_GPIO_PSOR_PTSO(x)                        (((uint32_t)(((uint32_t)(x)) << MCU_GPIO_PSOR_PTSO_SHIFT)) & MCU_GPIO_PSOR_PTSO_MASK)

/*! @name PCOR - Port Clear Output Register */
#define MCU_GPIO_PCOR_PTCO_MASK                      (0xFFFFFFFFU)
#define MCU_GPIO_PCOR_PTCO_SHIFT                     (0U)
#define MCU_GPIO_PCOR_PTCO(x)                        (((uint32_t)(((uint32_t)(x)) << MCU_GPIO_PCOR_PTCO_SHIFT)) & MCU_GPIO_PCOR_PTCO_MASK)

/*! @name PTOR - Port Toggle Output Register */
#define MCU_GPIO_PTOR_PTTO_MASK                      (0xFFFFFFFFU)
#define MCU_GPIO_PTOR_PTTO_SHIFT                     (0U)
#define MCU_GPIO_PTOR_PTTO(x)                        (((uint32_t)(((uint32_t)(x)) << MCU_GPIO_PTOR_PTTO_SHIFT)) & MCU_GPIO_PTOR_PTTO_MASK)

/*! @name PDIR - Port Data Input Register */
#define MCU_GPIO_PDIR_PDI_MASK                       (0xFFFFFFFFU)
#define MCU_GPIO_PDIR_PDI_SHIFT                      (0U)
#define MCU_GPIO_PDIR_PDI(x)                         (((uint32_t)(((uint32_t)(x)) << MCU_GPIO_PDIR_PDI_SHIFT)) & MCU_GPIO_PDIR_PDI_MASK)

/*! @name PDDR - Port Data Direction Register */
#define MCU_GPIO_PDDR_PDD_MASK                       (0xFFFFFFFFU)
#define MCU_GPIO_PDDR_PDD_SHIFT                      (0U)
#define MCU_GPIO_PDDR_PDD(x)                         (((uint32_t)(((uint32_t)(x)) << MCU_GPIO_PDDR_PDD_SHIFT)) & MCU_GPIO_PDDR_PDD_MASK)


/*!
 * @}
 */ /* end of group MCU_GPIO_Register_Masks */


/* GPIO - Peripheral instance base addresses */
/** Peripheral MCU_GPIOA base address */
#define MCU_GPIOA_BASE                               (0x400FF000u)
/** Peripheral MCU_GPIOA base pointer */
#define MCU_GPIOA                                    ((MCU_GPIO_Type *)MCU_GPIOA_BASE)
/** Peripheral MCU_GPIOB base address */
#define MCU_GPIOB_BASE                               (0x400FF040u)
/** Peripheral MCU_GPIOB base pointer */
#define MCU_GPIOB                                    ((MCU_GPIO_Type *)MCU_GPIOB_BASE)
/** Peripheral MCU_GPIOC base address */
#define MCU_GPIOC_BASE                               (0x400FF080u)
/** Peripheral MCU_GPIOC base pointer */
#define MCU_GPIOC                                    ((MCU_GPIO_Type *)MCU_GPIOC_BASE)
/** Peripheral MCU_GPIOD base address */
#define MCU_GPIOD_BASE                               (0x400FF0C0u)
/** Peripheral MCU_GPIOD base pointer */
#define MCU_GPIOD                                    ((MCU_GPIO_Type *)MCU_GPIOD_BASE)
/** Peripheral MCU_GPIOE base address */
#define MCU_GPIOE_BASE                               (0x400FF100u)
/** Peripheral MCU_GPIOE base pointer */
#define MCU_GPIOE                                    ((MCU_GPIO_Type *)MCU_GPIOE_BASE)
/** Array initializer of GPIO peripheral base addresses */
#define MCU_GPIO_BASE_ADDRS                          { MCU_GPIOA_BASE, MCU_GPIOB_BASE, MCU_GPIOC_BASE, MCU_GPIOD_BASE, MCU_GPIOE_BASE }
/** Array initializer of GPIO peripheral base pointers */
#define MCU_GPIO_BASE_PTRS                           { MCU_GPIOA, MCU_GPIOB, MCU_GPIOC, MCU_GPIOD, MCU_GPIOE }

/*!
 * @}
 */ /* end of group MCU_GPIO_Peripheral_Access_Layer */


/* ----------------------------------------------------------------------------
   -- LED define
   ---------------------------------------------------------------------------- */
#define MCU_RED_LED_GPIO_REG            MCU_GPIOE
#define MCU_GREEN_LED_GPIO_REG          MCU_GPIOD
#define MCU_RED_LED_PORT_REG            MCU_PORTE
#define MCU_GREEN_LED_PORT_REG          MCU_PORTD
#define MCU_RED_LED_PIN_INDEX           29
#define MCU_GREEN_LED_PIN_INDEX         5

#endif /* __DEVICE_H */

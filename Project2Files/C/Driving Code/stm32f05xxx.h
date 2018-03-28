// stm32f05xxx low level header file
// Works with the stm32f0discovery board
// Not organized in any particular way, just as I found them useful
// No guarantees or claims of suitability,reliability or safety of any kind are implied or given
// All the values below were taken from the STM32F05xxx reference manual (RM0091)
// Also include macros for enabling and disabling global interrupts
// Written by Frank Duignan
// stm32f05xxx.h
//
// Get the latest version from eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery
// Changelog:
// 11/10/12: Changed USART1_TD1 to USART1_TDR and USART2_TD1 to USART2_TDR
// 27/10/12: Correct error where PORTF was called PORTE
// Define some bitmasks
#define BIT0 (1 << 0)
#define BIT1 (1 << 1)
#define BIT2 (1 << 2)
#define BIT3 (1 << 3)
#define BIT4 (1 << 4)
#define BIT5 (1 << 5)
#define BIT6 (1 << 6)
#define BIT7 (1 << 7)
#define BIT8 (1 << 8)
#define BIT9 (1 << 9)
#define BIT10 (1 << 10)
#define BIT11 (1 << 11)
#define BIT12 (1 << 12)
#define BIT13 (1 << 13)
#define BIT14 (1 << 14)
#define BIT15 (1 << 15)
#define BIT16 (1 << 16)
#define BIT17 (1 << 17)
#define BIT18 (1 << 18)
#define BIT19 (1 << 19)
#define BIT20 (1 << 20)
#define BIT21 (1 << 21)
#define BIT22 (1 << 22)
#define BIT23 (1 << 23)
#define BIT24 (1 << 24)
#define BIT25 (1 << 25)
#define BIT26 (1 << 26)
#define BIT27 (1 << 27)
#define BIT28 (1 << 28)
#define BIT29 (1 << 29)
#define BIT30 (1 << 30)
#define BIT31 (1 << 31)

// Macros to reduce typing later on
#define  REGISTER_32(ADDRESS) (*((volatile unsigned int *)(ADDRESS)))
#define  REGISTER_16(ADDRESS) (*((volatile unsigned int *)(ADDRESS)))
// Macros to enable/disable global interrupts
#define enable_interrupts() asm(" cpsie i ")
#define disable_interrupts() asm(" cpsid i ")

// Boundary addresses peripherals
// APB devices
#define TIM2_BASE 	0x40000000
#define TIM3_BASE 	0x40000400
#define TIM6_BASE 	0x40001000
#define TIM14_BASE 	0x40002000
#define RTC_BASE 	0x40002800
#define WWDG_BASE	0x40002c00
#define IWDG_BASE	0x40003000
#define SPI2_BASE	0x40003800
#define USART2_BASE	0x40004400
#define I2C1_BASE	0x40005400
#define I2C2_BASE	0x40005800
#define PWR_BASE	0x40007000
#define DAC_BASE	0x40007400
#define CEC_BASE	0x40007800
#define SYSCFG_BASE	0x40010000
#define EXTI_BASE	0x40010400
#define ADC_BASE	0x40012400
#define TIM1_BASE	0x40012C00
#define SPI1_BASE	0x40013000
#define USART1_BASE	0x40013800
#define TIM15_BASE	0x40014000
#define TIM16_BASE	0x40014400
#define TIM17_BASE	0x40014800
#define DBGMCU_BASE	0x40015800
// AHB1 devices
#define DMA_BASE	0x40020000
#define RCC_BASE	0x40021000
#define FLASH_BASE	0x40022000
#define CRC_BASE	0x40023000
#define TSC_BASE	0x40024000
// AHB2 devices
#define GPIOA_BASE	0x48000000
#define GPIOB_BASE	0x48000400
#define GPIOC_BASE	0x48000800
#define GPIOD_BASE	0x48000c00
#define GPIOF_BASE	0x48001400

// Core peripherals
#define STK_BASE	0xe000e010
#define SCB_BASE	0xe000ed00
#define NVIC_BASE 	0xe000e100
// Seems base addresses are split for some core peripherals
#define SCB_BASE2	0xe000e008
#define NVIC_BASE2	0xe000ef00 
#define FLASH_SIZE	REGISTER_16( 0x1ffff7cc )

// Option bytes - see reference manual for details.

#define OPTION_WORD0	REGISTER_32( 0x1ffff800 )
#define OPTION_WORD1	REGISTER_32( 0x1ffff804 )
#define OPTION_WORD2	REGISTER_32( 0x1ffff808 )

// RCC registers
#define RCC_CR 		REGISTER_32(RCC_BASE + 0)
#define RCC_CFGR	REGISTER_32(RCC_BASE + 4)
#define RCC_CIR		REGISTER_32(RCC_BASE + 8)
#define RCC_APB2RSTR	REGISTER_32(RCC_BASE + 0x0c)	
#define RCC_APB1RSTR	REGISTER_32(RCC_BASE + 0x10)	
#define RCC_AHBENR	REGISTER_32(RCC_BASE + 0x14)
#define RCC_APB2ENR	REGISTER_32(RCC_BASE + 0x18)
#define RCC_APB1ENR	REGISTER_32(RCC_BASE + 0x1c)
#define RCC_BDCR	REGISTER_32(RCC_BASE + 0x20)
#define RCC_CSR		REGISTER_32(RCC_BASE + 0x24)
#define RCC_AHBRSTR	REGISTER_32(RCC_BASE + 0x28)
#define RCC_CFGR2	REGISTER_32(RCC_BASE + 0x2c)
#define RCC_CFGR3	REGISTER_32(RCC_BASE + 0x30)
#define RCC_CR2		REGISTER_32(RCC_BASE + 0x34)


// GPIO registers 
// PORT A
#define GPIOA_MODER	REGISTER_32(GPIOA_BASE + 0)
#define GPIOA_OTYPER	REGISTER_32(GPIOA_BASE + 4)
#define GPIOA_OSPEEDR	REGISTER_32(GPIOA_BASE + 8)
#define GPIOA_PUPDR	REGISTER_32(GPIOA_BASE + 0x0c)
#define GPIOA_IDR	REGISTER_32(GPIOA_BASE + 0x10)
#define GPIOA_ODR	REGISTER_32(GPIOA_BASE + 0x14)
#define GPIOA_BSRR	REGISTER_32(GPIOA_BASE + 0x18)
#define GPIOA_LCKR	REGISTER_32(GPIOA_BASE + 0x1c)
#define GPIOA_AFRL	REGISTER_32(GPIOA_BASE + 0x20)
#define GPIOA_AFRH	REGISTER_32(GPIOA_BASE + 0x24)
#define GPIOA_BRR	REGISTER_32(GPIOA_BASE + 0x28)

// PORT B
#define GPIOB_MODER	REGISTER_32(GPIOB_BASE + 0)
#define GPIOB_OTYPER	REGISTER_32(GPIOB_BASE + 4)
#define GPIOB_OSPEEDR	REGISTER_32(GPIOB_BASE + 8)
#define GPIOB_PUPDR	REGISTER_32(GPIOB_BASE + 0x0c)
#define GPIOB_IDR	REGISTER_32(GPIOB_BASE + 0x10)
#define GPIOB_ODR	REGISTER_32(GPIOB_BASE + 0x14)
#define GPIOB_BSRR	REGISTER_32(GPIOB_BASE + 0x18)
#define GPIOB_LCKR	REGISTER_32(GPIOB_BASE + 0x1c)
#define GPIOB_AFRL	REGISTER_32(GPIOB_BASE + 0x20)
#define GPIOB_AFRH	REGISTER_32(GPIOB_BASE + 0x24)
#define GPIOB_BRR	REGISTER_32(GPIOB_BASE + 0x28)

// PORT C
#define GPIOC_MODER	REGISTER_32(GPIOC_BASE + 0)
#define GPIOC_OTYPER	REGISTER_32(GPIOC_BASE + 4)
#define GPIOC_OSPEEDR	REGISTER_32(GPIOC_BASE + 8)
#define GPIOC_PUPDR	REGISTER_32(GPIOC_BASE + 0x0c)
#define GPIOC_IDR	REGISTER_32(GPIOC_BASE + 0x10)
#define GPIOC_ODR	REGISTER_32(GPIOC_BASE + 0x14)
#define GPIOC_BSRR	REGISTER_32(GPIOC_BASE + 0x18)
#define GPIOC_LCKR	REGISTER_32(GPIOC_BASE + 0x1c)
#define GPIOC_AFRL	REGISTER_32(GPIOC_BASE + 0x20)
#define GPIOC_AFRH	REGISTER_32(GPIOC_BASE + 0x24)
#define GPIOC_BRR	REGISTER_32(GPIOC_BASE + 0x28)

// PORT D
#define GPIOD_MODER	REGISTER_32(GPIOD_BASE + 0)
#define GPIOD_OTYPER	REGISTER_32(GPIOD_BASE + 4)
#define GPIOD_OSPEEDR	REGISTER_32(GPIOD_BASE + 8)
#define GPIOD_PUPDR	REGISTER_32(GPIOD_BASE + 0x0c)
#define GPIOD_IDR	REGISTER_32(GPIOD_BASE + 0x10)
#define GPIOD_ODR	REGISTER_32(GPIOD_BASE + 0x14)
#define GPIOD_BSRR	REGISTER_32(GPIOD_BASE + 0x18)
#define GPIOD_LCKR	REGISTER_32(GPIOD_BASE + 0x1c)
#define GPIOD_AFRL	REGISTER_32(GPIOD_BASE + 0x20)
#define GPIOD_AFRH	REGISTER_32(GPIOD_BASE + 0x24)
#define GPIOD_BRR	REGISTER_32(GPIOD_BASE + 0x28)

// PORT F
#define GPIOF_MODER	REGISTER_32(GPIOF_BASE + 0)
#define GPIOF_OTYPER	REGISTER_32(GPIOF_BASE + 4)
#define GPIOF_OSPEEDR	REGISTER_32(GPIOF_BASE + 8)
#define GPIOF_PUPDR	REGISTER_32(GPIOF_BASE + 0x0c)
#define GPIOF_IDR	REGISTER_32(GPIOF_BASE + 0x10)
#define GPIOF_ODR	REGISTER_32(GPIOF_BASE + 0x14)
#define GPIOF_BSRR	REGISTER_32(GPIOF_BASE + 0x18)
#define GPIOF_LCKR	REGISTER_32(GPIOF_BASE + 0x1c)
#define GPIOF_AFRL	REGISTER_32(GPIOF_BASE + 0x20)
#define GPIOF_AFRH	REGISTER_32(GPIOF_BASE + 0x24)
#define GPIOF_BRR	REGISTER_32(GPIOF_BASE + 0x28)


// Timer 1
#define TIM1_CR1	REGISTER_16(TIM1_BASE + 0)
#define TIM1_CR2	REGISTER_16(TIM1_BASE + 4)
#define TIM1_CR2	REGISTER_16(TIM1_BASE + 4)
#define TIM1_SMCR	REGISTER_16(TIM1_BASE + 8)
#define TIM1_DIER	REGISTER_16(TIM1_BASE + 0x0c)
#define TIM1_SR		REGISTER_16(TIM1_BASE + 0x10)
#define TIM1_EGR	REGISTER_16(TIM1_BASE + 0x14)
#define TIM1_CCMR1	REGISTER_16(TIM1_BASE + 0x18)
#define TIM1_CCMR2	REGISTER_16(TIM1_BASE + 0x1c)
#define TIM1_CCER	REGISTER_16(TIM1_BASE + 0x20)
#define TIM1_CNT	REGISTER_16(TIM1_BASE + 0x24)
#define TIM1_PSC	REGISTER_16(TIM1_BASE + 0x28)
#define TIM1_ARR	REGISTER_16(TIM1_BASE + 0x2c)
#define TIM1_RCR	REGISTER_16(TIM1_BASE + 0x30)
#define TIM1_CCR1	REGISTER_16(TIM1_BASE + 0x34)
#define TIM1_CCR2	REGISTER_16(TIM1_BASE + 0x38)
#define TIM1_CCR3	REGISTER_16(TIM1_BASE + 0x3c)
#define TIM1_CCR4	REGISTER_16(TIM1_BASE + 0x40)
#define TIM1_BDTR	REGISTER_16(TIM1_BASE + 0x44)
#define TIM1_DCR	REGISTER_16(TIM1_BASE + 0x48)
#define TIM1_DMAR	REGISTER_16(TIM1_BASE + 0x4c)

// Timer 2
#define TIM2_CR1	REGISTER_32(TIM2_BASE + 0)
#define TIM2_CR2	REGISTER_32(TIM2_BASE + 4)
#define TIM2_SMCR	REGISTER_32(TIM2_BASE + 8)
#define TIM2_DIER	REGISTER_32(TIM2_BASE + 0x0c)
#define TIM2_SR		REGISTER_32(TIM2_BASE + 0x10)
#define TIM2_EGR	REGISTER_32(TIM2_BASE + 0x14)
#define TIM2_CCMR1	REGISTER_32(TIM2_BASE + 0X18)
#define TIM2_CCMR2	REGISTER_32(TIM2_BASE + 0X1c)
#define TIM2_CCER	REGISTER_32(TIM2_BASE + 0X20)
#define TIM2_CNT	REGISTER_32(TIM2_BASE + 0X24)
#define TIM2_PSC	REGISTER_32(TIM2_BASE + 0X28)
#define TIM2_ARR	REGISTER_32(TIM2_BASE + 0X2c)
#define TIM2_CCR1	REGISTER_32(TIM2_BASE + 0X34)
#define TIM2_CCR2	REGISTER_32(TIM2_BASE + 0X38)
#define TIM2_CCR3	REGISTER_32(TIM2_BASE + 0X3c)
#define TIM2_CCR4	REGISTER_32(TIM2_BASE + 0X40)
#define TIM2_DCR	REGISTER_32(TIM2_BASE + 0X48)
#define TIM2_DMAR	REGISTER_32(TIM2_BASE + 0X4c)

// Timer 3
#define TIM3_CR1	REGISTER_32(TIM3_BASE + 0)
#define TIM3_CR2	REGISTER_32(TIM3_BASE + 4)
#define TIM3_SMCR	REGISTER_32(TIM3_BASE + 8)
#define TIM3_DIER	REGISTER_32(TIM3_BASE + 0x0c)
#define TIM3_SR		REGISTER_32(TIM3_BASE + 0x10)
#define TIM3_EGR	REGISTER_32(TIM3_BASE + 0x14)
#define TIM3_CCMR1	REGISTER_32(TIM3_BASE + 0X18)
#define TIM3_CCMR2	REGISTER_32(TIM3_BASE + 0X1c)
#define TIM3_CCER	REGISTER_32(TIM3_BASE + 0X20)
#define TIM3_CNT	REGISTER_32(TIM3_BASE + 0X24)
#define TIM3_PSC	REGISTER_32(TIM3_BASE + 0X28)
#define TIM3_ARR	REGISTER_32(TIM3_BASE + 0X2c)
#define TIM3_CCR1	REGISTER_32(TIM3_BASE + 0X34)
#define TIM3_CCR2	REGISTER_32(TIM3_BASE + 0X38)
#define TIM3_CCR3	REGISTER_32(TIM3_BASE + 0X3c)
#define TIM3_CCR4	REGISTER_32(TIM3_BASE + 0X40)
#define TIM3_DCR	REGISTER_32(TIM3_BASE + 0X48)
#define TIM3_DMAR	REGISTER_32(TIM3_BASE + 0X4c)

// Timer 6
#define TIM6_CR1	REGISTER_32(TIM6_BASE + 0)
#define TIM6_CR2	REGISTER_32(TIM6_BASE + 4)
#define TIM6_DIER	REGISTER_32(TIM6_BASE + 0x0c)
#define TIM6_SR		REGISTER_32(TIM6_BASE + 0x10)
#define TIM6_EGR	REGISTER_32(TIM6_BASE + 0x14)
#define TIM6_CNT	REGISTER_32(TIM6_BASE + 0x24)
#define TIM6_PSC	REGISTER_32(TIM6_BASE + 0x28)
#define TIM6_ARR	REGISTER_32(TIM6_BASE + 0x2c)

// Timer 14
#define TIM14_CR1	REGISTER_32(TIM14_BASE + 0)
#define TIM14_DIER1	REGISTER_32(TIM14_BASE + 0x0c)
#define TIM14_SR	REGISTER_32(TIM14_BASE + 0x10)
#define TIM14_EGR	REGISTER_32(TIM14_BASE + 0x14)
#define TIM14_CCMR1	REGISTER_32(TIM14_BASE + 0x18)
#define TIM14_CCER	REGISTER_32(TIM14_BASE + 0x20)
#define TIM14_CNT	REGISTER_32(TIM14_BASE + 0x24)
#define TIM14_PSC	REGISTER_32(TIM14_BASE + 0x28)
#define TIM14_ARR	REGISTER_32(TIM14_BASE + 0x2c)
#define TIM14_CCR1	REGISTER_32(TIM14_BASE + 0x34)
#define TIM14_OR	REGISTER_32(TIM14_BASE + 0x50)

// Timer 15
#define TIM15_CR1	REGISTER_32(TIM15_BASE + 0)
#define TIM15_CR2	REGISTER_32(TIM15_BASE + 4)
#define TIM15_SMCR	REGISTER_32(TIM15_BASE + 8)
#define TIM15_DIER	REGISTER_32(TIM15_BASE + 0x0c)
#define TIM15_SR	REGISTER_32(TIM15_BASE + 0x10)
#define TIM15_EGR	REGISTER_32(TIM15_BASE + 0x14)
#define TIM15_CCMR1	REGISTER_32(TIM15_BASE + 0x18)
#define TIM15_CCER	REGISTER_32(TIM15_BASE + 0x20)
#define TIM15_CNT	REGISTER_32(TIM15_BASE + 0x24)
#define TIM15_PSC	REGISTER_32(TIM15_BASE + 0x28)
#define TIM15_ARR	REGISTER_32(TIM15_BASE + 0x2c)
#define TIM15_RCR	REGISTER_32(TIM15_BASE + 0x30)
#define TIM15_CCR1	REGISTER_32(TIM15_BASE + 0x34)
#define TIM15_CCR2	REGISTER_32(TIM15_BASE + 0x38)
#define TIM15_BDTR	REGISTER_32(TIM15_BASE + 0x44)
#define TIM15_DCR	REGISTER_32(TIM15_BASE + 0x48)
#define TIM15_DMAR	REGISTER_32(TIM15_BASE + 0x4c)

// Timer 16
#define TIM16_CR1	REGISTER_32(TIM16_BASE + 0)
#define TIM16_CR2	REGISTER_32(TIM16_BASE + 4)
#define TIM16_DIER	REGISTER_32(TIM16_BASE + 0x0c)
#define TIM16_SR	REGISTER_32(TIM16_BASE + 0x10)
#define TIM16_EGR	REGISTER_32(TIM16_BASE + 0x14)
#define TIM16_CCMR1	REGISTER_32(TIM16_BASE + 0x18)
#define TIM16_CCER	REGISTER_32(TIM16_BASE + 0x20)
#define TIM16_CNT	REGISTER_32(TIM16_BASE + 0x24)
#define TIM16_PSC	REGISTER_32(TIM16_BASE + 0x28)
#define TIM16_ARR	REGISTER_32(TIM16_BASE + 0x2c)
#define TIM16_RCR	REGISTER_32(TIM16_BASE + 0x30)
#define TIM16_CCR1	REGISTER_32(TIM16_BASE + 0x34)
#define TIM16_BDTR	REGISTER_32(TIM16_BASE + 0x44)
#define TIM16_DCR	REGISTER_32(TIM16_BASE + 0x48)
#define TIM16_DMAR	REGISTER_32(TIM16_BASE + 0x4c)

// Timer 17
#define TIM17_CR1	REGISTER_32(TIM17_BASE + 0)
#define TIM17_CR2	REGISTER_32(TIM17_BASE + 4)
#define TIM17_DIER	REGISTER_32(TIM17_BASE + 0x0c)
#define TIM17_SR	REGISTER_32(TIM17_BASE + 0x10)
#define TIM17_EGR	REGISTER_32(TIM17_BASE + 0x14)
#define TIM17_CCMR1	REGISTER_32(TIM17_BASE + 0x18)
#define TIM17_CCER	REGISTER_32(TIM17_BASE + 0x20)
#define TIM17_CNT	REGISTER_32(TIM17_BASE + 0x24)
#define TIM17_PSC	REGISTER_32(TIM17_BASE + 0x28)
#define TIM17_ARR	REGISTER_32(TIM17_BASE + 0x2c)
#define TIM17_RCR	REGISTER_32(TIM17_BASE + 0x30)
#define TIM17_CCR1	REGISTER_32(TIM17_BASE + 0x34)
#define TIM17_BDTR	REGISTER_32(TIM17_BASE + 0x44)
#define TIM17_DCR	REGISTER_32(TIM17_BASE + 0x48)
#define TIM17_DMAR	REGISTER_32(TIM17_BASE + 0x4c)

// ADC
#define ADC_ISR		REGISTER_32(ADC_BASE + 0)
#define ADC_IER		REGISTER_32(ADC_BASE + 4)
#define ADC_CR		REGISTER_32(ADC_BASE + 8)
#define ADC_CFGR1	REGISTER_32(ADC_BASE + 0x0c)
#define ADC_CFGR2	REGISTER_32(ADC_BASE + 0x10)
#define ADC_SMPR	REGISTER_32(ADC_BASE + 0x14)
#define ADC_TR		REGISTER_32(ADC_BASE + 0x20)
#define ADC_CHSELR	REGISTER_32(ADC_BASE + 0x28)
#define ADC_DR		REGISTER_32(ADC_BASE + 0x40)
#define ADC_CCR		REGISTER_32(ADC_BASE + 0x308)

// DAC
#define DAC_CR		REGISTER_32(DAC_BASE + 0)
#define DAC_SWTRIGR	REGISTER_32(DAC_BASE + 4)
#define DAC_DHR12R1	REGISTER_32(DAC_BASE + 8)
#define DAC_DHR12L1	REGISTER_32(DAC_BASE + 0x0c)
#define DAC_DHR8R1	REGISTER_32(DAC_BASE + 0x10)
#define DAC_DOR1	REGISTER_32(DAC_BASE + 0x2c)
#define DAC_SR		REGISTER_32(DAC_BASE + 0x34)


// PWR 
#define PWR_CR		REGISTER_32(PWR_BASE + 0)
#define PWR_CSR		REGISTER_32(PWR_BASE + 4)

// SYS Config
#define SYSCFG_CFGR1	REGISTER_32(SYSCFG_BASE + 0)
#define SYSCFG_EXTICR1	REGISTER_32(SYSCFG_BASE + 8)
#define SYSCFG_EXTICR2	REGISTER_32(SYSCFG_BASE + 0x0c)
#define SYSCFG_EXTICR3	REGISTER_32(SYSCFG_BASE + 0x10)
#define SYSCFG_EXTICR4	REGISTER_32(SYSCFG_BASE + 0x14)
#define SYSCFG_CFGR2	REGISTER_32(SYSCFG_BASE + 0x18)

// CRC
#define CRC_DR 		REGISTER_32(CRC_BASE + 0)
#define CRC_IDR 	REGISTER_32(CRC_BASE + 4)
#define CRC_CR 		REGISTER_32(CRC_BASE + 8)
#define CRC_INIT 	REGISTER_32(CRC_BASE + 0x10)

// DMA

#define DMA_ISR 	REGISTER_32(DMA_BASE + 0)
#define DMA_IFCR 	REGISTER_32(DMA_BASE + 4)
#define DMA_CCR1 	REGISTER_32(DMA_BASE + 8)
#define DMA_CNDTR1	REGISTER_32(DMA_BASE + 0x0c)
#define DMA_CPAR1	REGISTER_32(DMA_BASE + 0x10)
#define DMA_CMAR1	REGISTER_32(DMA_BASE + 0x14)
#define DMA_CCR2	REGISTER_32(DMA_BASE + 0x1c)
#define DMA_CNDTR2	REGISTER_32(DMA_BASE + 0x20)
#define DMA_CPAR2	REGISTER_32(DMA_BASE + 0x24)
#define DMA_CMAR2	REGISTER_32(DMA_BASE + 0x28)
#define DMA_CCR3	REGISTER_32(DMA_BASE + 0x30)
#define DMA_CNDTR3	REGISTER_32(DMA_BASE + 0x34)
#define DMA_CPAR3	REGISTER_32(DMA_BASE + 0x38)
#define DMA_CMAR3	REGISTER_32(DMA_BASE + 0x3c)
#define DMA_CCR4	REGISTER_32(DMA_BASE + 0x44)
#define DMA_CNDTR4	REGISTER_32(DMA_BASE + 0x48)
#define DMA_CPAR4	REGISTER_32(DMA_BASE + 0x4c)
#define DMA_CMAR4	REGISTER_32(DMA_BASE + 0x50)
#define DMA_CCR5	REGISTER_32(DMA_BASE + 0x58)
#define DMA_CNDTR5	REGISTER_32(DMA_BASE + 0x5c)
#define DMA_CPAR5	REGISTER_32(DMA_BASE + 0x60)
#define DMA_CMAR5	REGISTER_32(DMA_BASE + 0x64)

// COMP (in same address area as syscfg)
#define COMP_CSR	REGISTER_32(SYSCFG_BASE + 0x1c)

// USART1

#define USART1_CR1	REGISTER_32(USART1_BASE + 0)
#define USART1_CR2	REGISTER_32(USART1_BASE + 4)
#define USART1_CR3	REGISTER_32(USART1_BASE + 8)
#define USART1_BRR	REGISTER_32(USART1_BASE + 0x0c)
#define USART1_GTBR	REGISTER_32(USART1_BASE + 0x10)
#define USART1_RTOR	REGISTER_32(USART1_BASE + 0x14)
#define USART1_RQR	REGISTER_32(USART1_BASE + 0x18)
#define USART1_ISR	REGISTER_32(USART1_BASE + 0x1c)
#define USART1_ICR	REGISTER_32(USART1_BASE + 0x20)
#define USART1_RDR	REGISTER_32(USART1_BASE + 0x24)
#define USART1_TDR	REGISTER_32(USART1_BASE + 0x28)

// USART2

#define USART2_CR1	REGISTER_32(USART2_BASE + 0)
#define USART2_CR2	REGISTER_32(USART2_BASE + 4)
#define USART2_CR3	REGISTER_32(USART2_BASE + 8)
#define USART2_BRR	REGISTER_32(USART2_BASE + 0x0c)
#define USART2_GTBR	REGISTER_32(USART2_BASE + 0x10)
#define USART2_RTOR	REGISTER_32(USART2_BASE + 0x14)
#define USART2_RQR	REGISTER_32(USART2_BASE + 0x18)
#define USART2_ISR	REGISTER_32(USART2_BASE + 0x1c)
#define USART2_ICR	REGISTER_32(USART2_BASE + 0x20)
#define USART2_RDR	REGISTER_32(USART2_BASE + 0x24)
#define USART2_TDR	REGISTER_32(USART2_BASE + 0x28)

// EXTI	
#define EXTI_IMR	REGISTER_32(EXTI_BASE + 0)
#define EXTI_EMR	REGISTER_32(EXTI_BASE + 4)
#define EXTI_RTSR	REGISTER_32(EXTI_BASE + 8)
#define EXTI_FTSR	REGISTER_32(EXTI_BASE + 0x0c)
#define EXTI_SWIER	REGISTER_32(EXTI_BASE + 0x10)
#define EXTI_PR		REGISTER_32(EXTI_BASE + 0x14)

// NVIC
#define ISER		REGISTER_32(NVIC_BASE + 0)
#define ICER		REGISTER_32(NVIC_BASE + 0x80)
#define ISPR		REGISTER_32(NVIC_BASE + 0x100)
#define ICPR		REGISTER_32(NVIC_BASE + 0x180)
#define IPR0		REGISTER_32(NVIC_BASE + 0x300)
#define IPR1		REGISTER_32(NVIC_BASE + 0x304)
#define IPR2		REGISTER_32(NVIC_BASE + 0x308)
#define IPR3		REGISTER_32(NVIC_BASE + 0x30c)
#define IPR4		REGISTER_32(NVIC_BASE + 0x310)
#define IPR5		REGISTER_32(NVIC_BASE + 0x314)
#define IPR6		REGISTER_32(NVIC_BASE + 0x318)
#define IPR7		REGISTER_32(NVIC_BASE + 0x31c)

// STK
#define STK_CSR		REGISTER_32(STK_BASE + 0)
#define STK_RVR		REGISTER_32(STK_BASE + 4)
#define STK_CVR		REGISTER_32(STK_BASE + 8)
#define STK_CALIB	REGISTER_32(STK_BASE + 0x0c)

// SCB_BASE
#define CPUID		REGISTER_32(SCB_BASE + 0)
#define ICSR		REGISTER_32(SCB_BASE + 4)
#define AIRCR		REGISTER_32(SCB_BASE + 0x0c)
#define SCR		REGISTER_32(SCB_BASE + 0x10)
#define CCR		REGISTER_32(SCB_BASE + 0x14)
#define SHPR2		REGISTER_32(SCB_BASE + 0x1c)
#define SHPR3		REGISTER_32(SCB_BASE + 0x20)

// I2C1
#define I2C1_CR1	REGISTER_32(I2C1_BASE + 0)
#define I2C1_CR2	REGISTER_32(I2C1_BASE + 4)
#define I2C1_OAR1	REGISTER_32(I2C1_BASE + 8)
#define I2C1_OAR2	REGISTER_32(I2C1_BASE + 0x0c)
#define I2C1_TIMINGR	REGISTER_32(I2C1_BASE + 0x10)
#define I2C1_TIMEOUTR	REGISTER_32(I2C1_BASE + 0x14)
#define I2C1_ISR	REGISTER_32(I2C1_BASE + 0x18)
#define I2C1_ICR	REGISTER_32(I2C1_BASE + 0x1c)
#define I2C1_PECR	REGISTER_32(I2C1_BASE + 0x20)
#define I2C1_RXDR	REGISTER_32(I2C1_BASE + 0x24)
#define I2C1_TXDR	REGISTER_32(I2C1_BASE + 0x28)

// I2C2
#define I2C2_CR1	REGISTER_32(I2C2_BASE + 0)
#define I2C2_CR2	REGISTER_32(I2C2_BASE + 4)
#define I2C2_OAR1	REGISTER_32(I2C2_BASE + 8)
#define I2C2_OAR2	REGISTER_32(I2C2_BASE + 0x0c)
#define I2C2_TIMINGR	REGISTER_32(I2C2_BASE + 0x10)
#define I2C2_TIMEOUTR	REGISTER_32(I2C2_BASE + 0x14)
#define I2C2_ISR	REGISTER_32(I2C2_BASE + 0x18)
#define I2C2_ICR	REGISTER_32(I2C2_BASE + 0x1c)
#define I2C2_PECR	REGISTER_32(I2C2_BASE + 0x20)
#define I2C2_RXDR	REGISTER_32(I2C2_BASE + 0x24)
#define I2C2_TXDR	REGISTER_32(I2C2_BASE + 0x28)

// RTC
#define RTC_TR		REGISTER_32(RTC_BASE + 0)
#define RTC_DR		REGISTER_32(RTC_BASE + 4)
#define RTC_CR		REGISTER_32(RTC_BASE + 8)
#define RTC_ISR		REGISTER_32(RTC_BASE + 0x0c)
#define RTC_PRER	REGISTER_32(RTC_BASE + 0x10)
#define RTC_ALRMAR	REGISTER_32(RTC_BASE + 0x1c)
#define RTC_WPR		REGISTER_32(RTC_BASE + 0x24)
#define RTC_SSR		REGISTER_32(RTC_BASE + 0x28)
#define RTC_SHIFTR	REGISTER_32(RTC_BASE + 0x2c)
#define RTC_TSTR	REGISTER_32(RTC_BASE + 0x30)
#define RTC_TSDR	REGISTER_32(RTC_BASE + 0x34)
#define RTC_TSSSR	REGISTER_32(RTC_BASE + 0x38)
#define RTC_CALR	REGISTER_32(RTC_BASE + 0x3c)
#define RTC_TAFCR	REGISTER_32(RTC_BASE + 0x40)
#define RTC_ALRMASSR	REGISTER_32(RTC_BASE + 0x44)
#define RTC_BKP0R	REGISTER_32(RTC_BASE + 0x50)
#define RTC_BKP1R	REGISTER_32(RTC_BASE + 0x54)
#define RTC_BKP2R	REGISTER_32(RTC_BASE + 0x58)
#define RTC_BKP3R	REGISTER_32(RTC_BASE + 0x5c)
#define RTC_BKP4R	REGISTER_32(RTC_BASE + 0x60)

// IWDG
#define IWDG_KR		REGISTER_32(IWDG_BASE + 0)
#define IWDG_PR		REGISTER_32(IWDG_BASE + 4)
#define IWDG_RLR	REGISTER_32(IWDG_BASE + 8)
#define IWDG_SR		REGISTER_32(IWDG_BASE + 0x0c)
#define IWDG_WINR	REGISTER_32(IWDG_BASE + 0x10)

// WWDG
#define WWDG_CR		REGISTER_32(WWDG_BASE + 0)
#define WWDG_CFR	REGISTER_32(WWDG_BASE + 4)
#define WWDG_SR		REGISTER_32(WWDG_BASE + 8)

// SPI1
#define SPI1_CR1	REGISTER_32(SPI1_BASE + 0)
#define SPI1_CR2	REGISTER_32(SPI1_BASE + 4)
#define SPI1_SR		REGISTER_32(SPI1_BASE + 8)
#define SPI1_DR		REGISTER_32(SPI1_BASE + 0x0c)
#define SPI1_CRCPR	REGISTER_32(SPI1_BASE + 0x10)
#define SPI1_RXCRCR	REGISTER_32(SPI1_BASE + 0x14)
#define SPI1_TXCRCR	REGISTER_32(SPI1_BASE + 0x18)
#define SPI1_I2SCFGR	REGISTER_32(SPI1_BASE + 0x1c)
#define SPI1_I2SPR	REGISTER_32(SPI1_BASE + 0x20)

// SPI2
#define SPI2_CR1	REGISTER_32(SPI2_BASE + 0)
#define SPI2_CR2	REGISTER_32(SPI2_BASE + 4)
#define SPI2_SR		REGISTER_32(SPI2_BASE + 8)
#define SPI2_DR		REGISTER_32(SPI2_BASE + 0x0c)
#define SPI2_CRCPR	REGISTER_32(SPI2_BASE + 0x10)
#define SPI2_RXCRCR	REGISTER_32(SPI2_BASE + 0x14)
#define SPI2_TXCRCR	REGISTER_32(SPI2_BASE + 0x18)
#define SPI2_I2SCFGR	REGISTER_32(SPI2_BASE + 0x1c)
#define SPI2_I2SPR	REGISTER_32(SPI2_BASE + 0x20)

// TSC
#define TS_CR 		REGISTER_32(TSC_BASE + 0)
#define TSC_IER		REGISTER_32(TSC_BASE + 4)
#define TSC_ICR		REGISTER_32(TSC_BASE + 8)
#define TSC_ISR		REGISTER_32(TSC_BASE + 0x0c)
#define TSC_IOHCR	REGISTER_32(TSC_BASE + 0x10)
#define TSC_IOASCR	REGISTER_32(TSC_BASE + 0x18)
#define TSC_IOSCR	REGISTER_32(TSC_BASE + 0x20)
#define TSC_IOCCR	REGISTER_32(TSC_BASE + 0x28)
#define TSC_IOGCSR	REGISTER_32(TSC_BASE + 0x30)
#define TSC_IOG1CR	REGISTER_32(TSC_BASE + 0x34)
#define TSC_IOG2CR	REGISTER_32(TSC_BASE + 0x38)
#define TSC_IOG3CR	REGISTER_32(TSC_BASE + 0x3c)
#define TSC_IOG4CR	REGISTER_32(TSC_BASE + 0x40)
#define TSC_IOG5CR	REGISTER_32(TSC_BASE + 0x44)
#define TSC_IOG6CR	REGISTER_32(TSC_BASE + 0x48)

// HDMI
#define CEC_CR		REGISTER_32(HDMI_BASE + 0)
#define CEC_CFGR	REGISTER_32(HDMI_BASE + 4)
#define CEC_TXDR	REGISTER_32(HDMI_BASE + 8)
#define CEC_RXDR	REGISTER_32(HDMI_BASE + 0x0c)
#define CEC_ISR		REGISTER_32(HDMI_BASE + 0x10)
#define CEC_IER		REGISTER_32(HDMI_BASE + 0x14)

// DBG
#define DBGMCU_IDCODE	REGISTER_32(DBG_BASE + 0)
#define DBGMCU_CR	REGISTER_32(DBG_BASE + 4)
#define DBGMCU_APB1_FZ	REGISTER_32(DBG_BASE + 8)
#define DBGMCU_APB2_FZ	REGISTER_32(DBG_BASE + 0x0c)


// FLASH

#define FLASH_ACR	REGISTER_32(FLASH_BASE + 0)
#define FLASH_KEYR	REGISTER_32(FLASH_BASE + 4)
#define FLASH_OPTKEYR	REGISTER_32(FLASH_BASE + 8)
#define FLASH_SR	REGISTER_32(FLASH_BASE + 0x0c)
#define FLASH_CR	REGISTER_32(FLASH_BASE + 0x10)
#define FLASH_AR	REGISTER_32(FLASH_BASE + 0x14)
#define FLASH_OBR	REGISTER_32(FLASH_BASE + 0x1c)
#define FLASH_WRPR	REGISTER_32(FLASH_BASE + 0x20)
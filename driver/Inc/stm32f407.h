/*
 * stm32f407.h
 *
 *  Created on: Aug 26, 2025
 *      Author: JAYARAJ
 */

#ifndef INC_STM32F407_H_
#define INC_STM32F407_H_
#include <stdint.h>
#define __vo         volatile
/****processor specific details *****************************************************/
/*
 * ARM Cortex Mx processor NVIC ISERx register addresses
 * Refer arm cortex m4 reference manual
 */
#define NVIC_ISER0         ((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1         ((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2         ((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3         ((__vo uint32_t*)0xE000E10C)

/*
 * ARM Cortex Mx processor NVIC ICERx register addresses
 * Refer arm Cortex m4 reference manual
 */
#define NVIC_ICER0         ((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1         ((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2         ((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3         ((__vo uint32_t*)0xE000E18C)

/*
 * ARM Cortex Mx Processor Priority Register Address Calculation
 */
#define NVIC_PR_BASE_ADDR   ((__vo uint32_t*)0xE000E400)

#define NO_PR_BITS_IMPLEMENTED   4
/*Base address of Flash and SRAM memories*/

#define FLASH_BASEADDR               0x08000000U
#define SRAM1_BASEADDR               0x20000000U
#define SRAM2_BASEADDR               0x2001C000U
#define ROM                          0x1FFF0000U
#define SRAM                         SRAM1_BASEADDR


/*Base address of AHBx and APBx bus*/

#define PERIPH_BASE                  0x40000000U
#define APB1PERIPH_BASE              PERIPH_BASE
#define APB2PERIPH_BASE              0x40010000U
#define AHB1PERIPH_BASE              0x40020000U
#define AHB2PERIPH_BASE              0x50000000U

/*
 * Base addresses of peripherals which are hanging on AHB1 bus
 *
*/

#define GPIOA_BASEADDR              (AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASEADDR              (AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASEADDR              (AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASEADDR              (AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASEADDR              (AHB1PERIPH_BASE + 0x1000)

#define RCC_BASEADDR                (AHB1PERIPH_BASE + 0x3800)

/*
 * Base addresses of peripherals which are hanging on APB1 bus
 *
*/
#define I2C1_BASEADDR               (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASEADDR               (APB1PERIPH_BASE + 0x5800)
#define I2C3_BASEADDR               (APB1PERIPH_BASE + 0x5C00)


#define SPI2_BASEADDR               (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASEADDR               (APB1PERIPH_BASE + 0x3C00)


#define USART2_BASEADDR             (APB1PERIPH_BASE + 0x4400)
#define USART3_BASEADDR             (APB1PERIPH_BASE + 0x4800)
#define UART4_BASEADDR              (APB1PERIPH_BASE + 0x4C00)
#define UART5_BASEADDR              (APB1PERIPH_BASE + 0x5000)


/*
 * Base addresses of peripherals which are hanging on APB2 bus
 *
*/

#define SPI1_BASEADDR               (APB2PERIPH_BASE + 0x3000)


#define USART1_BASEADDR             (APB2PERIPH_BASE + 0x1000)
#define USART6_BASEADDR             (APB2PERIPH_BASE + 0x1400)


#define EXTI_BASEADDR               (APB2PERIPH_BASE + 0x3C00)
#define SYSCFG_BASEADDR             (APB2PERIPH_BASE + 0x3800)

/***********************peripheral register definition structures****************************/

typedef struct{
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];/*AFR[0] GPIO alternate function low register, AF[1]: GPIO alternate function high register*/

}GPIO_RegDef_t;

typedef struct{
	__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTR;
	uint32_t     RESERVED0;
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	uint32_t RESERVED1[2];
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
	uint32_t     RESERVED2;
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	uint32_t RESERVED3[2];
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t AHB3LPENR;
	uint32_t     RESERVED4;
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	uint32_t RESERVED5[2];
	__vo uint32_t  RCC_BDCR;
	__vo uint32_t RCC_CSR;
	uint32_t RESERVED6[2];
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;


}RCC_RegDef_t;

/*
 * EXTI peripheral register definition
 */

typedef struct{
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;
}EXTI_RegDef_t;

/*
 * SYSCFG peripheral register definition
 */
typedef struct{
	__vo uint32_t  MEMRMP;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR[4];
	uint32_t RESERVED1[2];
	__vo uint32_t CMPCR;
	uint32_t RESERVED2[2];
	__vo uint32_t CFGR;
}SYSCFG_RegDef_t;

/*
 * I2c peripheral register definition
 */

typedef struct{
	__vo uint32_t  CR1;
	__vo uint32_t  CR2;
	__vo uint32_t  OAR1;
	__vo uint32_t  OAR2;
	__vo uint32_t  DR;
	__vo uint32_t  SR1;
	__vo uint32_t  SR2;
	__vo uint32_t  CCR;
	__vo uint32_t  TRISE;
	__vo uint32_t  FLTR;


}I2C_RegDef_t;

/*
 * USART peripheral register definition
 */
typedef struct{
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t BRR;
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t CR3;
	__vo uint32_t GTPR;
}USART_RegDef_t;
/*
 * Peripheral definitions (Peripheral base address typecasted to xxx_RegDef_t
 */

#define GPIOA                        ((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB                        ((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC                        ((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD                        ((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE                        ((GPIO_RegDef_t *)GPIOE_BASEADDR)

#define RCC                          ((RCC_RegDef_t *)RCC_BASEADDR)
#define EXTI                         ((EXTI_RegDef_t *)EXTI_BASEADDR)
#define SYSCFG                       ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)


#define I2C1                         ((I2C_RegDef_t *)I2C1_BASEADDR)
#define I2C2                         ((I2C_RegDef_t *)I2C2_BASEADDR)
#define I2C3                         ((I2C_RegDef_t *)I2C3_BASEADDR)



#define USART1                       ((USART_RegDef_t*)USART1_BASEADDR)
#define USART2                        ((USART_RegDef_t*)USART2_BASEADDR)
#define USART3                        ((USART_RegDef_t*)USART3_BASEADDR)
#define UART4                        ((USART_RegDef_t*)UART4_BASEADDR)
#define UART5                        ((USART_RegDef_t*)UART5_BASEADDR)
#define USART6  			         ((USART_RegDef_t*)USART6_BASEADDR)
/*
 * Clock Enable Macros for GPIOx peripheral
 */
#define GPIOA_PCLK_EN()               (RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()               (RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()               (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()               (RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()               (RCC->AHB1ENR |= (1 << 4))


/*
 * Clock Enable Macros for I2Cx peripheral
 */

#define I2C1_PCLK_EN()                 (RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()                 (RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()                 (RCC->APB1ENR |= (1 << 23))


/*
 * Clock Enable Macros for SPIx peripheral
 */
#define SPI1_PCLK_EN()                 (RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()                 (RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()                 (RCC->APB1ENR |= (1 << 15))

/*
 * Clock Enable Macros for USARTx peripheral
 */
#define USART1_PCLK_EN()               (RCC->APB2ENR |= (1 << 4))

#define USART2_PCLK_EN()               (RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN()               (RCC->APB1ENR |= (1 << 18))

#define UART4_PCLK_EN()                (RCC->APB1ENR |= (1 << 19))
#define UART5_PCLK_EN()                (RCC->APB1ENR |= (1 << 20))

#define USART6_PCLK_EN()               (RCC->APB2ENR |= (1 << 5))

/*
 * Clock Enable Macros for SYSCFG peripheral
 */
#define SYSCFG_PCLK_EN()              (RCC->APB2ENR |= (1 << 14))

/*
 * Clock Disable Macros for GPIOx peripheral
 */
#define GPIOA_PCLK_DI()               (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()               (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()               (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()               (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()               (RCC->AHB1ENR &= ~(1 << 4))


/*
 * Clock Disable Macros for I2Cx peripheral
 */

#define I2C1_PCLK_DI()                 (RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()                 (RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()                 (RCC->APB1ENR &= ~(1 << 23))


/*
 * Clock Disable Macros for SPIx peripheral
 */
#define SPI1_PCLK_DI()                 (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()                 (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()                 (RCC->APB1ENR &= ~(1 << 15))

/*
 * Clock Disable Macros for USARTx peripheral
 */
#define USART1_PCLK_DI()               (RCC->APB2ENR &= ~(1 << 4))

#define USART2_PCLK_DI()               (RCC->APB1ENR &= ~(1 << 17))
#define USART3_PCLK_DI()               (RCC->APB1ENR &= ~(1 << 18))

#define UART4_PCLK_DI()                (RCC->APB1ENR &= ~(1 << 19))
#define UART5_PCLK_DI()                (RCC->APB1ENR &= ~(1 << 20))

#define USART6_PCLK_DI()               (RCC->APB2ENR &= ~(1 << 5))

/*
 * Clock Disable Macros for SYSCFG peripheral
 */
#define SYSCFG_PCLK_DI()               (RCC->APB2ENR &= ~(1 << 14))

/*
 * GPIO register reset
 */
#define GPIOA_REG_RESET()              do{(RCC->AHB1RSTR |= 1 << 0) ;(RCC->AHB1RSTR &= ~(1 << 0));}while(0)
#define GPIOB_REG_RESET()              do{(RCC->AHB1RSTR |= 1 << 1) ;(RCC->AHB1RSTR &= ~(1 << 1));}while(0)
#define GPIOC_REG_RESET()              do{(RCC->AHB1RSTR |= 1 << 2) ;(RCC->AHB1RSTR &= ~(1 << 2));}while(0)
#define GPIOD_REG_RESET()              do{(RCC->AHB1RSTR |= 1 << 3) ;(RCC->AHB1RSTR &= ~(1 << 3));}while(0)
#define GPIOE_REG_RESET()              do{(RCC->AHB1RSTR |= 1 << 4) ;(RCC->AHB1RSTR &= ~(1 << 4));}while(0)


/*
 * I2C Register Reset
 */
#define I2C1_REG_RESET()               do{(RCC->APB1RSTR |= 1 << 21);(RCC->APB2RSTR &=~(1<<21));}while(0)
#define I2C2_REG_RESET()               do{(RCC->APB1RSTR |= 1 << 22);(RCC->APB1RSTR &=~(1<<22));}while(0)
#define I2C3_REG_RESET()               do{(RCC->APB1RSTR |= 1 << 23);(RCC->APB1RSTR &=~(1<<23));}while(0)


/*
 * USART register reset
 */
#define USART2_REG_RESET()              do{(RCC->APB1RSTR |= 1 << 17) ;(RCC->APB1RSTR &= ~(1 << 17));}while(0)
#define USART3_REG_RESET()              do{(RCC->APB1RSTR |= 1 << 18) ;(RCC->APB1RSTR &= ~(1 << 18));}while(0)
#define USART4_REG_RESET()              do{(RCC->APB1RSTR |= 1 << 19) ;(RCC->APB1RSTR &= ~(1 << 19));}while(0)
#define USART5_REG_RESET()              do{(RCC->APB1RSTR |= 1 << 20) ;(RCC->APB1RSTR &= ~(1 << 20));}while(0)

#define USART1_REG_RESET()              do{(RCC->APB2RSTR |= 1 << 4) ;(RCC->APB2RSTR &= ~(1 << 4));}while(0)
#define USART6_REG_RESET()              do{(RCC->APB2RSTR |= 1 << 5) ;(RCC->APB2RSTR &= ~(1 << 5));}while(0)

/*
 * This macro returns a code(between 0 to 7) for a given GPIO base address(x)
 */
#define GPIO_BASEADDR_TO_CODE(x)       ((x == GPIOA)?0:\
		                                (x == GPIOB)?1:\
		                                (x == GPIOC)?2:\
		                                (x == GPIOD)?3:\
		                                (x == GPIOE)?4:0)



/*
 * IRQ Numbers of STM32F407x MCU
 *
 */
#define IRQ_NO_EXTI0         6
#define IRQ_NO_EXTI1         7
#define IRQ_NO_EXTI2         8
#define IRQ_NO_EXTI3         9
#define IRQ_NO_EXTI4         10
#define IRQ_NO_EXTI9_5       23
#define IRQ_NO_EXTI15_10     40
/*
 * General Usage Macros
 */
#define  ENABLE                        1
#define  DISABLE                       0
#define  SET                           1
#define  RESET                         0
#define  GPIO_PIN_SET                  1
#define  GPIO_PIN_RESET                0
#define  FLAG_SET                      1
#define  FLAG_RESET                    0

/******************************************************************************************
 *Bit position definitions of I2C peripheral
 ******************************************************************************************/
/*
 * Bit position definitions I2C_CR1
 */
#define I2C_CR1_PE						0
#define I2C_CR1_NOSTRETCH  				7
#define I2C_CR1_START 					8
#define I2C_CR1_STOP  				 	9
#define I2C_CR1_ACK 				 	10
#define I2C_CR1_SWRST  				 	15

/*
 * Bit position definitions I2C_CR2
 */
#define I2C_CR2_FREQ				 	0
#define I2C_CR2_ITERREN				 	8
#define I2C_CR2_ITEVTEN				 	9
#define I2C_CR2_ITBUFEN 			    10

/*
 * Bit position definitions I2C_OAR1
 */
#define I2C_OAR1_ADD0    				 0
#define I2C_OAR1_ADD71 				 	 1
#define I2C_OAR1_ADD98  			 	 8
#define I2C_OAR1_ADDMODE   			 	15

/*
 * Bit position definitions I2C_SR1
 */

#define I2C_SR1_SB 					 	0
#define I2C_SR1_ADDR 				 	1
#define I2C_SR1_BTF 					2
#define I2C_SR1_ADD10 					3
#define I2C_SR1_STOPF 					4
#define I2C_SR1_RXNE 					6
#define I2C_SR1_TXE 					7
#define I2C_SR1_BERR 					8
#define I2C_SR1_ARLO 					9
#define I2C_SR1_AF 					 	10
#define I2C_SR1_OVR 					11
#define I2C_SR1_TIMEOUT 				14

/*
 * Bit position definitions I2C_SR2
 */
#define I2C_SR2_MSL						0
#define I2C_SR2_BUSY 					1
#define I2C_SR2_TRA 					2
#define I2C_SR2_GENCALL 				4
#define I2C_SR2_DUALF 					7

/*
 * Bit position definitions I2C_CCR
 */
#define I2C_CCR_CCR 					 0
#define I2C_CCR_DUTY 					14
#define I2C_CCR_FS  				 	15


/******************************************************************************************
 *Bit position definitions of USART peripheral
 ******************************************************************************************/

/*
 * Bit position definitions USART_CR1
 */
#define USART_CR1_SBK					0
#define USART_CR1_RWU 					1
#define USART_CR1_RE  					2
#define USART_CR1_TE 					3
#define USART_CR1_IDLEIE 				4
#define USART_CR1_RXNEIE  				5
#define USART_CR1_TCIE					6
#define USART_CR1_TXEIE					7
#define USART_CR1_PEIE 					8
#define USART_CR1_PS 					9
#define USART_CR1_PCE 					10
#define USART_CR1_WAKE  				11
#define USART_CR1_M 					12
#define USART_CR1_UE 					13
#define USART_CR1_OVER8  				15



/*
 * Bit position definitions USART_CR2
 */
#define USART_CR2_ADD   				0
#define USART_CR2_LBDL   				5
#define USART_CR2_LBDIE  				6
#define USART_CR2_LBCL   				8
#define USART_CR2_CPHA   				9
#define USART_CR2_CPOL   				10
#define USART_CR2_STOP   				12
#define USART_CR2_LINEN   				14


/*
 * Bit position definitions USART_CR3
 */
#define USART_CR3_EIE   				0
#define USART_CR3_IREN   				1
#define USART_CR3_IRLP  				2
#define USART_CR3_HDSEL   				3
#define USART_CR3_NACK   				4
#define USART_CR3_SCEN   				5
#define USART_CR3_DMAR  				6
#define USART_CR3_DMAT   				7
#define USART_CR3_RTSE   				8
#define USART_CR3_CTSE   				9
#define USART_CR3_CTSIE   				10
#define USART_CR3_ONEBIT   				11

/*
 * Bit position definitions USART_SR
 */

#define USART_SR_PE        				0
#define USART_SR_FE        				1
#define USART_SR_NE        				2
#define USART_SR_ORE       				3
#define USART_SR_IDLE       			4
#define USART_SR_RXNE        			5
#define USART_SR_TC        				6
#define USART_SR_TXE        			7
#define USART_SR_LBD        			8
#define USART_SR_CTS        			9
#include "stm32f407_gpio_driver.h"
#include "stm32f407_i2c_driver.h"
#include "stm32f407_rcc_driver.h"
#include "stm32f407_usart_driver.h"
#endif /* INC_STM32F407_H_ */

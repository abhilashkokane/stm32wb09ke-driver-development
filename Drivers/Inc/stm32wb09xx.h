#ifndef INC_STM32WB09XX_H_
#define INC_STM32WB09XX_H_

#include <stdint.h>

#define __vo volatile

// 1. Base address of Flash and SRAM memories

#define FLASH_BASEADDR		0x10040000U			// flash base address found in memory map
#define ROM_BASEADDR		0x10000000U 		// SYSTEM_MEMORY_BASE address
#define SRAM0_BASEADDR		0x20000000U			// SRAM0 base address
#define SRAM1_BASEADDR		0x20004000U			// SRAM1 base address
#define SRAM2_BASEADDR		0x20008000U			// SRAM2 base address
#define SRAM3_BASEADDR		0x2000C000U			// SRAM3 base address
#define SRAM				SRAM0_BASEADDR


// 2. Base address of Peripheral bus APBx and AHBx - (AHB0, APB0, APB1, APB2)
#define PERIPH_BASE			0x40000000U
#define AHB0PERIPH_BASE		0x48000000U
#define APB0PERIPH_BASE		PERIPH_BASE
#define APB1PERIPH_BASE		0x41000000U
#define APB2PERIPH_BASE		0x60000000U

// 3. Define base address of peripherals hanging on AHB0 bus - (GPIOA, GPIOB)
// GPIO base address = AHB0 base address + offset
// Offset is found in RM memory map. 0x0000 is there because it is the first peri on AHB0

#define GPIOA_BASEADDR 		0x48000000U
#define GPIOB_BASEADDR		0x48100000U
#define RCC_BASEADDR		0x48400000U

// 4. Define base address of peripherals hanging on APB1 bus - (I2C1, SPI3, USART)

#define I2C1_BASEADDR		0x41000000U
#define SPI3_BASEADDR		0x41007000U
#define USART_BASEADDR		0x41004000U


/******************** Peripheral Registers Definition Structures **************************/
/*
 * GPIO ------>
 * Use proper sequence from the register map
 *
 * */


typedef struct
{
	__vo uint32_t MODER;		// GPIO port mode register : Add offset = 0x00
	__vo uint32_t OTYPER;		// GPIO port output type register : Add offset = 0x04
	__vo uint32_t OSPEEDR;		// and so on......
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t BRR;
	__vo uint32_t AFR[2];		// AFR[0] : GPIO low register, AFR[1] : GPIO high register
} GPIO_RegDef_t;				// GPIO Register definitions


typedef struct
{
	__vo uint32_t CR;
	uint32_t RESERVED0;
	__vo uint32_t CFGR;
	__vo uint32_t CSSWCR;
	uint32_t RESERVED1;
	__vo uint32_t CIER;
	__vo uint32_t CIFR;
	__vo uint32_t CSCMDR;
	uint32_t RESERVED2;
	__vo uint32_t AHBRSTR;
	__vo uint32_t APB0RSTR;
	__vo uint32_t APB1RSTR;
	uint32_t RESERVED3;
	__vo uint32_t APB2RSTR;
	uint32_t RESERVED4;
	__vo uint32_t AHBENR;
	__vo uint32_t APB0ENR;
	__vo uint32_t APB1ENR;
	uint32_t RESERVED5;
	__vo uint32_t APB2ENR;
	uint32_t RESERVED6;
	__vo uint32_t CSR;
	__vo uint32_t RFSWHSECR;
	__vo uint32_t RFHSECR;
} RCC_RegDef_t;

/*
 * ---------------------------- SPI ------------------------------------------->
 *
 * */

typedef struct {
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t CRCOR;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;
	__vo uint32_t I2SCFGR;
	__vo uint32_t I2SPR;
} SPI_RegDef_t;




/*
 * Peripheral Definitions (Peripheral base type-casted to xxx_RegDef_t
*/

#define GPIOA	((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB	((GPIO_RegDef_t*)GPIOB_BASEADDR)

#define RCC		((RCC_RegDef_t*)RCC_BASEADDR)

/*
 * Peripheral Definitions (Peripheral base type-casted to xxx_RegDef_t
*/

#define SPI3	((SPI_RegDef_t*)SPI3_BASEADDR)



/*
 * Clock Enable macros for GPIOx peripherals
 * */

#define GPIOA_PCLK_EN()	(RCC -> AHBENR |= (1 << 2))	// 2nd bit is enabled
#define GPIOB_PCLK_EN()	(RCC -> AHBENR |= (1 << 3)) // 3rd bit is use for enable for GPIOB port

/*
 * Clock Enable macros for I2C peripheral
 * */

#define I2C1_PCLK_EN()	(RCC -> APB1ENR |= (1 << 21))

/*
 * Clock Enable macros for SPI peripheral
 * */

#define SPI3_PCLK_EN()	(RCC -> APB1ENR |= (1 << 14))


/*
 * Clock Enable macros for USART peripheral
 * */

#define USART_PCLK_EN()	(RCC -> APB1ENR |= (1 << 10))


/*
 * Clock Disable macros for GPIOx peripherals
 * */

#define GPIOA_PCLK_DI()	(RCC -> AHBENR &= ~(1 << 2))	// 2nd bit is disabled/clear
#define GPIOB_PCLK_DI()	(RCC -> AHBENR &= ~(1 << 2))


/*
 * Clock Disable macros for I2C peripheral
 * */

#define I2C1_PCLK_DI()	(RCC -> APB1ENR &= ~(1 << 21))

/*
 * Clock Disable macros for SPI peripheral
 * */

#define SPI3_PCLK_DI()	(RCC -> APB1ENR &= ~(1 << 14))


/*
 * Clock Disable macros for USART peripheral
 * */

#define USART_PCLK_DI()	(RCC -> APB1ENR &= ~(1 << 10))


/*
 * Macros to reset GPIOx Peripherals
 * */

#define GPIOA_REG_RESET()		do{ (RCC -> AHBRSTR |= (1 << 2)); ((RCC -> AHBRSTR &= ~(1 << 2))); }while(0)
#define GPIOB_REG_RESET()		do{ (RCC -> AHBRSTR |= (1 << 3)); ((RCC -> AHBRSTR &= ~(1 << 3))); }while(0)


/*
 * Some Generic macros
 * */

#define ENABLE			1
#define DISABLE			0
#define SET				ENABLE
#define RESET			DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET
#define FLAG_RESET		RESET
#define FLAG_SET		SET

/******************************************************
 * Bit position definitions of SPI peripheral		  *
 * ****************************************************
 */

/*
 * SPI control register 1 (SPIx_CR1)
 *
 */
#define SPI_CR1_CPHA		0
#define SPI_CR1_CPOL		1
#define SPI_CR1_MSTR		2
#define SPI_CR1_BR			3
#define SPI_CR1_SPE			6
#define SPI_CR1_LSBFIRST	7
#define SPI_CR1_SSI			8
#define SPI_CR1_SSM			9
#define SPI_CR1_RXONLY		10
#define SPI_CR1_CRCL		11
#define SPI_CR1_CRCNEXT		12
#define SPI_CR1_CRCEN		13
#define SPI_CR1_BIDIOE		14
#define SPI_CR1_BIDIMODE	15


/*
 * SPI control register 2 (SPIx_CR2)
 *
 */
#define SPI_CR2_RXDMAEN		0
#define SPI_CR2_TXDMAEN		1
#define SPI_CR2_SSOE		2
#define SPI_CR2_NSSP		3
#define SPI_CR2_FRF			4
#define SPI_CR2_ERRIE		5
#define SPI_CR2_RXNEIE		6
#define SPI_CR2_TXNEIE		7
#define SPI_CR2_DS			8
#define SPI_CR2_FRXTH		12
#define SPI_CR2_LDMA_RX		13
#define SPI_CR2_LDMA_TX		14
#define SPI_CR2_RESERVED	15



/*
 * SPI status register (SPIx_SR)
 *
 */
#define SPI_SR_RXNE			0
#define SPI_SR_TXE			1
#define SPI_SR_CHSIDE		2
#define SPI_SR_UDR			3
#define SPI_SR_CRCERR		4
#define SPI_SR_MODF			5
#define SPI_SR_OVR			6
#define SPI_SR_BSY			7
#define SPI_SR_FRE			8
#define SPI_SR_FRLVL		9
#define SPI_SR_FTLVL		11






#include "stm32wb09xx_gpio_driver.h"
#include "stm32wb09xx_spi_driver.h"

#endif /* INC_STM32WB09XX_H_ */

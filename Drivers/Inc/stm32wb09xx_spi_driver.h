/*
 * stm32wb09xx_spi_driver.h
 *
 *  Created on: Dec 3, 2025
 *      Author: Abhilash
 */

#ifndef INC_STM32WB09XX_SPI_DRIVER_H_
#define INC_STM32WB09XX_SPI_DRIVER_H_

#include "stm32wb09xx.h"

/*
 * Configuration structure of SPIx Peripheral
 */

typedef struct
{
	uint8_t SPI_DeviceMode;			/* @Device mode */
	uint8_t SPI_BusConfig;			/* @SPI_BusConfig */
	uint8_t SPI_SclkSpeed;			/* @SPI_SclkSpeed */
	uint8_t SPI_DFF;				/* @SPI_DFF */
	uint8_t SPI_CPOL;				/* @SPI_CPOL */
	uint8_t SPI_CPHA;				/* @SPI_CPHA */
	uint8_t SPI_SSM;				/* @SPI_SSM */
} SPI_Config_t;


/*
 * This is a handle structure for a SPIx Peripheral
 */

typedef struct
{
	SPI_RegDef_t *pSPIx;		// This holds the base address of the SPIx. x : 0,1,2
	SPI_Config_t SPIConfig;		// This holds SPIx pin config settings
} SPI_Handle_t;


/*----- Every Bit is present in SPI control register 1 (SPIx_CR1) except DFF in SPIx_CR2 -----*/


/*
 * @Device mode
 * Bit 2 MSTR: Master selection
 * Master or slave
 */

#define SPI_DEVICE_MODE_MASTER	1
#define SPI_DEVICE_MODE_SLAVE	0	1


/*
 * @SPI_BusConfig
 * Simplex, Half duplex or duplex
 * - SPI_BUS_CONFIG_FD : Full duplex
 * - SPI_BUS_CONFIG_HD : Half duplex
 * - SPI_BUS_CONFIG_S_TXONLY : Simplex Tx only
 * - SPI_BUS_CONFIG_RXONLY : Simplex Rx only

 	BIDIMODE: Bidirectional data mode enable
	0: 2-line unidirectional data mode selected - Full duplex
	1: 1-line bidirectional data mode selected	- half duplex

	BIDIOE: Output enable in bidirectional mode
	0: Output disabled (receive-only mode)
	1: Output enabled (transmit-only mode)

	When simplex is used, use this bit as 1.
	 RXONLY: Receive only mode enabled - Simplex
	 0: Full duplex (Transmit and receive)
	 1: Output disabled (Receive-only mode)
 */

#define SPI_BUS_CONFIG_FD					1
#define SPI_BUS_CONFIG_HD					2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY		3


/*
 * @SPI_DFF	@SPI control register 1 (SPIx_CR1)
 *  BR[2:0]: Baud rate control
	000: fPCLK/2
	001: fPCLK/4
	010: fPCLK/8
	011: fPCLK/16
	100: fPCLK/32
	101: fPCLK/64
	110: fPCLK/128
	111: fPCLK/256
 */
#define SPI_SCLK_SPEED_DIV2			0
#define SPI_SCLK_SPEED_DIV4			1
#define SPI_SCLK_SPEED_DIV8			2
#define SPI_SCLK_SPEED_DIV16		3
#define SPI_SCLK_SPEED_DIV32		4
#define SPI_SCLK_SPEED_DIV64		5
#define SPI_SCLK_SPEED_DIV128		6
#define SPI_SCLK_SPEED_DIV256		7



/*
 * @SPI_DFF
 * This is present in SPI control register 2 (SPIx_CR2)
 * DS [3:0]: Data size
	0111: 8-bit
	1111: 16-bit
 */
#define SPI_DFF_8bit	0
#define SPI_DFF_16bit	1

/*
 * @SPI_CPOL : Clock Polarity
 	0: CK to 0 when idle
	1: CK to 1 when idle
 */

#define SPI_CPOL_HIGH	1
#define SPI_CPOL_LOW	0

/*
 * @SPI_CPHA : Clock Phase
	0: The first clock transition is the first data capture edge
	1: The second clock transition is the first data capture edge
 */

#define SPI_CPHA_HIGH	1
#define SPI_CPHA_LOW	0


/*
 * @SPI_SSM : Software slave management
	0: Software slave management disabled
	1: Software slave management enabled
 */

#define SPI_SSM_EN	0
#define SPI_SSM_DI	1


/*
 * SPI related status flag definitions
 */

#define SPI_RXNE_FLAG					(0 << SPI_SR_RXNE)
#define SPI_TXE_FLAG					(1 << SPI_SR_TXE)
#define SPI_CHANNEL_SIDE_FLAG			(2 << SPI_SR_CHSIDE)
#define SPI_UNDERRUN_FLAG				(2 << SPI_SR_UDR)
#define SPI_CRCERR						(2 << SPI_SR_CRCERR)
#define SPI_MODE_FAULT_FLAG				(2 << SPI_SR_MODF)
#define SPI_OVERRUN_FLAG				(2 << SPI_SR_OVR)
#define SPI_BUSY_FLAG					(2 << SPI_SR_BSY)
#define SPI_FRAME_FORMAT_ERROR_FLAG		(2 << SPI_SR_FRE)
#define SPI_FRLVL						(2 << SPI_SR_FRLVL)
#define SPI_FTLVL						(2 << SPI_SR_FTLVL)










/***********************************************************************************************************************
 * 										API supported by this driver
 ***********************************************************************************************************************
 */


/*
 * SPI Peripheral Clock Setup
 */

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);



/*
 * SPI Init and De-init
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);



/*
 * SPI Data Send and receive
 */

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);


/*
 * Interrupt Configuration and ISR handling
 *
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);


/*
 * Other Peripheral Control APIs
 */

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);




#endif /* INC_STM32WB09XX_SPI_DRIVER_H_ */

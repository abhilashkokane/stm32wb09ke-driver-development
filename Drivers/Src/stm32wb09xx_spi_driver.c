/*
 * stm32wb09xx_spi_driver.c
 *
 *  Created on: Dec 3, 2025
 *      Author: Abhilash
 */


#include "stm32wb09xx_spi_driver.h"

/*****************************************************************
* @fn			- SPI_PeriClockControl
*
* @brief		- Only 1 SPI is available
*
* @param[i] 	-
*
* @param[i] 	-
*
* @return		-	none
*
* @Note			-	none
 */

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if (EnorDi == ENABLE){
		if (pSPIx == SPI3){
			SPI3_PCLK_EN();
		}
	} else {
		if (pSPIx == SPI3){
			SPI3_PCLK_DI();
		}
	}
}


/*****************************************************************
* @fn			- SPI Init
*
* @brief		-
*
* @param[i] 	-
*
* @param[i] 	-
*
* @return		-
*
* @Note			-
 */

void SPI_Init(SPI_Handle_t *pSPIHandle)
{

	// Enable the clock
	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

	// Configure SPI_CR1 register
	uint32_t tempReg = 0;

	// Configure SPI_CR2 register
	uint32_t tempReg2 = 0;

	// 1. Configure the Device mode
	tempReg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;	// 2nd bit is device mode

	// 2. Configure the Bus config
	if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD){

		//BIDI mode should be cleared
		tempReg &= ~(1 << SPI_CR1_BIDIMODE);		//15th bit is BIDI MODE

	}else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD){

		// BIDI mode should be set
		tempReg |= ~(1 << SPI_CR1_BIDIMODE);		//15th bit is BIDI MODE

	}else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY){

		// BIDI mode should be cleared
		tempReg &= ~(1 << SPI_CR1_BIDIMODE);		//15th bit is BIDI MODE
		// RXONLY bit must be set
		tempReg &= ~(1 << SPI_CR1_RXONLY);		//10th bit is RXONLYs
	}

	// 3. Configure the SPI clock (baud rate)
	tempReg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;

	// 4. Configure the DFF in tempReg 2
	tempReg2 |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR2_DS;

	// 5. Configure the SPI_CPOL
	tempReg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;

	// 6. Configure the SPI_CPHA
	tempReg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;

	// Now set all these values to CR1 and CR2 register
	pSPIHandle->pSPIx->CR1 = tempReg;
	pSPIHandle->pSPIx->CR2 = tempReg2;

}


/*****************************************************************
* @fn			- SPI De Init
*
* @brief		-
*
* @param[i] 	-
*
* @param[i] 	-
*
* @return		-
*
* @Note			-
 */

void SPI_DeInit(SPI_RegDef_t *pSPIx);


/*****************************************************************
* @fn			- SPI Send data
*
* @brief		-
*
* @param[i] 	-
*
* @param[i] 	-
*
* @return		-
*
* @Note			- This is blocking call
 */

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName){
	if(pSPIx->SR & FlagName){
		return FLAG_SET;
	}
	return FLAG_RESET;
}

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len){

	while(Len > 0){
		//1. Wait until TXE is set
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);

		if((pSPIx->CR1 & (1 << SPI_CR2_DS))){
			//16 bit DFF
			//1. load the data into DR
			pSPIx->DR = *((uint16_t*)pTxBuffer);
			Len--;
			Len--;
			(uint16_t*)pTxBuffer++;
		} else {

			// 8bit DFF

			pSPIx->DR = *((uint8_t*)pTxBuffer);
			Len--;
			pTxBuffer++;
		}
	}


}




/*****************************************************************
* @fn			- SPI Receive data
*
* @brief		-
*
* @param[i] 	-
*
* @param[i] 	-
*
* @return		-
*
* @Note			-
 */

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);



/*****************************************************************
* @fn			- SPI Peripheral Control
*
* @brief		-
*
* @param[i] 	-
*
* @param[i] 	-
*
* @return		-
*
* @Note			-
 */


void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi){

	if (EnorDi == ENABLE) {
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	} else {
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}













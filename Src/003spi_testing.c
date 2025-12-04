/*
 * 003spi_testing.c
 *
 *  Created on: Dec 3, 2025
 *      Author: Abhilash
 */

#include "stm32wb09xx.h"
#include <string.h>

/*
 * Alt Funx Mode 3
 * PA8 --> MISO
 * PA11 --> MOSI
 * PA3 --> SCLK
 * NSS --> PA9
 */

void SPI3_GPIOInits(void){

	GPIO_Handle_t SPIPins;
	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAFMode = 3;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdCtrl = GPIO_PIN_NO_PUPD;

	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_11;
	GPIO_Init(&SPIPins);

	//MISO - not used
	//	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
	//	GPIO_Init(&SPIPins);

	//NSS - not used
	//	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	//	GPIO_Init(&SPIPins);
}

void SPI3_Inits(void){

	SPI_Handle_t SPI3Handle;

	SPI3Handle.pSPIx = SPI3;
	SPI3Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI3Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI3Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;
	SPI3Handle.SPIConfig.SPI_DFF = SPI_DFF_8bit;
	SPI3Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI3Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI3Handle.SPIConfig.SPI_SSM = SPI_SSM_EN;

	SPI_Init(&SPI3Handle);
}


int main(void){

	char user_data[] = "Hello World";

	// Initialize the GPIO pins to behave as SPI3 pins
	SPI3_GPIOInits();

	// Initialize the SPI3 peripheral parameters
	SPI3_Inits();

	// Enable the SPI3 peripheral
	SPI_PeripheralControl(SPI3, ENABLE);

	// Send the 8 bit data
	SPI_SendData(SPI3, (uint8_t*)user_data, strlen(user_data));

	while(1);

	return 0;
}

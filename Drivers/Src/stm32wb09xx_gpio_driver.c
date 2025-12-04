#include "stm32wb09xx_gpio_driver.h"

/*****************************************************************
* @fn			- GPIO_PeriClockControl
*
* @brief		- This will enable or disable the peripheral clock of the given GPIO port.
*
* @param[i] 	- Base address of the gpio peripheral
*
* @param[i] 	- ENABLE or DISABLE macros, created in MCU header file stm32wb09xx.h
*
* @return		- none
*
* @Note			- none
 */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if (EnorDi == ENABLE){
		if (pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		} else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
	} else {
		if (pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		} else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}
	}
}


/*****************************************************************
* @fn			- GPIO_Init
*
* @brief		- Initialize the port and pin
*
* @param[i] 	- Base address of the gpio peripheral
*
* @param[i] 	-
*
* @return		- none
*
* @Note			- none
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	/*
	1. configure the mode of gpio pin [7.4.1 GPIOA port mode register (GPIOA_MODER)]
		 - There are 4 modes :
			00 as 0: Input mode
			01 as 1: output mode
			10 as 2: Alternate function mode
			11 as 3: Analog mode
		 - These macros are defined in gpio driver header file since it is gpio driver specific
	2. configure the speed : not using bcoz speed option not available
	3. configure the pull up/pull down
	4. configure the output type
	5. configure the alt funx
	*/


	//Enable the peripheral clock
	GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

	uint32_t temp = 0;

	// 1. Configure the mode of the gpio pin ->

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG) // checks condition for non interrupt mode
	{
		// non interrupt mode (0 to 3)
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clearing the bit
		pGPIOHandle->pGPIOx->MODER |= temp; 	// setting the bit

	} else
	{
		// this part will code later for interrupt mode
	}

	// 2. Configure the pull up pull down mode
	temp = 0;
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdCtrl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->PUPDR |= temp;


	// 3. Configure the output type
	temp = 0;
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER |= temp;


	// 4. Configure the alt funx mode
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		uint32_t temp1, temp2;

		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &=  ~(0xF << (4 * temp2)); // clearing
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAFMode << (4 * temp2));
	}

	else
	{
		// later..
	}
}

/*****************************************************************
* @fn			- GPIO_DeInit
*
* @brief		- De-initialize the port and pin
*
* @param[i] 	- Making it reset state
*
* @param[i] 	-
*
* @return		- none
*
* @Note			- none
 */


void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if (pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	} else if (pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	} else {
		if (pGPIOx == GPIOA)
		{
			GPIOA_REG_RESET();
		} else if (pGPIOx == GPIOB)
		{
			GPIOB_REG_RESET();
		}
	}
}


/*
 * Data read and write
 * 1. uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
 * 	- uint8_t is the return data type either 0 or 1 will be returned
 * 	- Takes 2 arguments. one for base address and other pin number
 *
 * 2. uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
 *  - Port is of 16pins. Hence return type will be uint16_t
 *  - The fnx will return content of data registers
 *
 * 3. GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
 *  - Nothing is returned
 *  - Value is for pin set or reset
 */

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return value;
}


uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)(pGPIOx->IDR);
	return value;
}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if (Value == GPIO_PIN_SET)
	{
		// write 1 to the output data register at the bit field corresponding the pin
		pGPIOx->ODR |= (1 << PinNumber);
	} else
	{
		// write 0
		pGPIOx->ODR &= ~(1 << PinNumber);
	}
}


void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value;
}



void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1 << PinNumber);
}

/*
 * Interrupt Configuration and ISR handling
 *
 */
 void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi){}
 void GPIO_IRQHandling(uint8_t PinNumber){}


#ifndef INC_STM32WB09XX_GPIO_DRIVER_H_
#define INC_STM32WB09XX_GPIO_DRIVER_H_

#include "stm32wb09xx.h"



typedef struct
{
	uint8_t GPIO_PinNumber;				/*possible values from @GPIO_PIN_NUMBERS*/
	uint8_t GPIO_PinMode;				/*possible values from @GPIO_PIN_MODES*/
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPuPdCtrl;			/*possible values from @GPIO_PULL_PULL_CONFIG*/
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAFMode;
} GPIO_PinConfig_t;


/*
 * This is a handle structure for a GPIO pin
 */

typedef struct
{
	GPIO_RegDef_t *pGPIOx;				// This holds the base address of the GPIO port to which the pin belongs. x : A,B
	GPIO_PinConfig_t GPIO_PinConfig;	// This holds GPIO pin config settings
} GPIO_Handle_t;


/*
 * 1. @GPIO_PIN_NUMBERS
 */
#define GPIO_PIN_NO_0	0
#define GPIO_PIN_NO_1	1
#define GPIO_PIN_NO_2	2
#define GPIO_PIN_NO_3	3
#define GPIO_PIN_NO_4	4
#define GPIO_PIN_NO_5	5
#define GPIO_PIN_NO_6	6
#define GPIO_PIN_NO_7	7
#define GPIO_PIN_NO_8	8
#define GPIO_PIN_NO_9	9
#define GPIO_PIN_NO_10	10
#define GPIO_PIN_NO_11	11
#define GPIO_PIN_NO_12	12
#define GPIO_PIN_NO_13	13
#define GPIO_PIN_NO_14	14
#define GPIO_PIN_NO_15	15


/*
 * 2. @GPIO_PIN_MODES
 * GPIO pin possible modes
 *  - There are 4 modes :
		00 as 0: Input mode
		01 as 1: output mode
		10 as 2: Alternate function mode
		11 as 3: Analog mode
 */
#define GPIO_MODE_IN		0
#define GPIO_MODE_OUT		1
#define GPIO_MODE_ALTFN		2
#define GPIO_MODE_ANALOG	3
#define GPIO_MODE_IT_FT		4	// interrupt falling edge
#define GPIO_MODE_IT_RT		5	// interrupt rising edge
#define GPIO_MODE_IT_RFT	6	// interrupt rising falling edge trigger


/*
 * @GPIO_PULL_PULL_CONFIG
 * GPIO pin possible output types
 * GPIO port output type register (GPIOA_OTYPER)
	0: Output push-pull (reset state)
	1: Output open-drain
 */
#define GPIO_OP_TYPE_PP		0
#define GPIO_OP_TYPE_OD		1


/*
 * GPIO Pin pull up pull down configuration macros
 *  00: No pull-up, pull-down
	01: Pull-up
	10: Pull-down
 * */
#define GPIO_PIN_NO_PUPD	0
#define GPIO_PIN_PU			1
#define GPIO_PIN_PD			3




/***********************************************************************************************************************
 * 										API supported by this driver
 ***********************************************************************************************************************
 */

/*
 * Peripheral Clock setup
 * GPIO_PeriClockControl(): - This will enable or disable the peripheral clock of given GPIO base address.
 * 							- Takes 2 arguments.
 * 							- First is pointer to the base address (GPIO_RegDef_t *pGPIOx).
 * 							- Second to enable or disable (uint8_t EnorDi).
 * 							- Two macros are created in MCU header file stm32wb09xx.h
 */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);


/*
 * Init and De-init
 * Init: Initialize the port and pin
 * De-init: Deinitialize the registers of the given peripheral. Making it reset or reset state
 */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle);


void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);


/*
 * Interrupt Configuration and ISR handling
 *
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);


#endif /* INC_STM32WB09XX_GPIO_DRIVER_H_ */

################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/stm32wb09xx_gpio_driver.c \
../Drivers/Src/stm32wb09xx_spi_driver.c 

OBJS += \
./Drivers/Src/stm32wb09xx_gpio_driver.o \
./Drivers/Src/stm32wb09xx_spi_driver.o 

C_DEPS += \
./Drivers/Src/stm32wb09xx_gpio_driver.d \
./Drivers/Src/stm32wb09xx_spi_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/%.o Drivers/Src/%.su Drivers/Src/%.cyclo: ../Drivers/Src/%.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32WB0 -DSTM32 -DSTM32WB09KEVx -DNUCLEO_WB09KE -c -I../Inc -I"D:/Embedded_Course/STM32WB09xx_Drivers/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-Src

clean-Drivers-2f-Src:
	-$(RM) ./Drivers/Src/stm32wb09xx_gpio_driver.cyclo ./Drivers/Src/stm32wb09xx_gpio_driver.d ./Drivers/Src/stm32wb09xx_gpio_driver.o ./Drivers/Src/stm32wb09xx_gpio_driver.su ./Drivers/Src/stm32wb09xx_spi_driver.cyclo ./Drivers/Src/stm32wb09xx_spi_driver.d ./Drivers/Src/stm32wb09xx_spi_driver.o ./Drivers/Src/stm32wb09xx_spi_driver.su

.PHONY: clean-Drivers-2f-Src


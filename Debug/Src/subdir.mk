################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/003spi_testing.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/003spi_testing.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/003spi_testing.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32WB0 -DSTM32 -DSTM32WB09KEVx -DNUCLEO_WB09KE -c -I../Inc -I"D:/Embedded_Course/STM32WB09xx_Drivers/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/003spi_testing.cyclo ./Src/003spi_testing.d ./Src/003spi_testing.o ./Src/003spi_testing.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src


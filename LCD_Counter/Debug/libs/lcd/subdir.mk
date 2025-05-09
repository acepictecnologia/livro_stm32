################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libs/lcd/LCD16X02_4B.c 

OBJS += \
./libs/lcd/LCD16X02_4B.o 

C_DEPS += \
./libs/lcd/LCD16X02_4B.d 


# Each subdirectory must supply rules for building sources it contributes
libs/lcd/%.o libs/lcd/%.su libs/lcd/%.cyclo: ../libs/lcd/%.c libs/lcd/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/STM32_book/LCD_Counter/libs/lcd" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-libs-2f-lcd

clean-libs-2f-lcd:
	-$(RM) ./libs/lcd/LCD16X02_4B.cyclo ./libs/lcd/LCD16X02_4B.d ./libs/lcd/LCD16X02_4B.o ./libs/lcd/LCD16X02_4B.su

.PHONY: clean-libs-2f-lcd


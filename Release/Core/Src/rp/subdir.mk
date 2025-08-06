################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../Core/Src/rp/RP.cc 

CC_DEPS += \
./Core/Src/rp/RP.d 

OBJS += \
./Core/Src/rp/RP.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/rp/%.o Core/Src/rp/%.su Core/Src/rp/%.cyclo: ../Core/Src/rp/%.cc Core/Src/rp/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-rp

clean-Core-2f-Src-2f-rp:
	-$(RM) ./Core/Src/rp/RP.cyclo ./Core/Src/rp/RP.d ./Core/Src/rp/RP.o ./Core/Src/rp/RP.su

.PHONY: clean-Core-2f-Src-2f-rp


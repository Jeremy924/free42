################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../Core/Src/rp/NumberEntry.cc \
../Core/Src/rp/RP.cc \
../Core/Src/rp/SimpleMenu.cc 

CC_DEPS += \
./Core/Src/rp/NumberEntry.d \
./Core/Src/rp/RP.d \
./Core/Src/rp/SimpleMenu.d 

OBJS += \
./Core/Src/rp/NumberEntry.o \
./Core/Src/rp/RP.o \
./Core/Src/rp/SimpleMenu.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/rp/%.o Core/Src/rp/%.su Core/Src/rp/%.cyclo: ../Core/Src/rp/%.cc Core/Src/rp/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DDEBUG -DDECIMAL_GLOBAL_EXCEPTION_FLAGS=1 -DDECIMAL_GLOBAL_ROUNDING=1 -DDECIMAL_GLOBAL_ROUNDING_ACCESS_FUNCTIONS=1 -DDECIMAL_GLOBAL_EXCEPTION_FLAGS_ACCESS_FUNCTIONS=1 -DDECIMAL_CALL_BY_REFERENCE=1 -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I"C:/Users/Jerem/STM32CubeIDE/rp42-workspace/Free42/Core/Inc/rp" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jerem/OneDrive/Documents/career/my_projects/stm-workspace/Free42/Core/Inc/IntelDecimal" -I"C:/Users/Jerem/OneDrive/Documents/career/my_projects/stm-workspace/Free42/Core/Inc/Free42" -Ofast -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-rp

clean-Core-2f-Src-2f-rp:
	-$(RM) ./Core/Src/rp/NumberEntry.cyclo ./Core/Src/rp/NumberEntry.d ./Core/Src/rp/NumberEntry.o ./Core/Src/rp/NumberEntry.su ./Core/Src/rp/RP.cyclo ./Core/Src/rp/RP.d ./Core/Src/rp/RP.o ./Core/Src/rp/RP.su ./Core/Src/rp/SimpleMenu.cyclo ./Core/Src/rp/SimpleMenu.d ./Core/Src/rp/SimpleMenu.o ./Core/Src/rp/SimpleMenu.su

.PHONY: clean-Core-2f-Src-2f-rp


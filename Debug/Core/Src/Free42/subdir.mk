################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../Core/Src/Free42/core_commands1.cc \
../Core/Src/Free42/core_commands2.cc \
../Core/Src/Free42/core_commands3.cc \
../Core/Src/Free42/core_commands4.cc \
../Core/Src/Free42/core_commands5.cc \
../Core/Src/Free42/core_commands6.cc \
../Core/Src/Free42/core_commands7.cc \
../Core/Src/Free42/core_display.cc \
../Core/Src/Free42/core_globals.cc \
../Core/Src/Free42/core_helpers.cc \
../Core/Src/Free42/core_keydown.cc \
../Core/Src/Free42/core_linalg1.cc \
../Core/Src/Free42/core_linalg2.cc \
../Core/Src/Free42/core_main.cc \
../Core/Src/Free42/core_math1.cc \
../Core/Src/Free42/core_math2.cc \
../Core/Src/Free42/core_phloat.cc \
../Core/Src/Free42/core_sto_rcl.cc \
../Core/Src/Free42/core_tables.cc \
../Core/Src/Free42/core_variables.cc \
../Core/Src/Free42/shell_main.cc \
../Core/Src/Free42/shell_spool.cc 

CC_DEPS += \
./Core/Src/Free42/core_commands1.d \
./Core/Src/Free42/core_commands2.d \
./Core/Src/Free42/core_commands3.d \
./Core/Src/Free42/core_commands4.d \
./Core/Src/Free42/core_commands5.d \
./Core/Src/Free42/core_commands6.d \
./Core/Src/Free42/core_commands7.d \
./Core/Src/Free42/core_display.d \
./Core/Src/Free42/core_globals.d \
./Core/Src/Free42/core_helpers.d \
./Core/Src/Free42/core_keydown.d \
./Core/Src/Free42/core_linalg1.d \
./Core/Src/Free42/core_linalg2.d \
./Core/Src/Free42/core_main.d \
./Core/Src/Free42/core_math1.d \
./Core/Src/Free42/core_math2.d \
./Core/Src/Free42/core_phloat.d \
./Core/Src/Free42/core_sto_rcl.d \
./Core/Src/Free42/core_tables.d \
./Core/Src/Free42/core_variables.d \
./Core/Src/Free42/shell_main.d \
./Core/Src/Free42/shell_spool.d 

OBJS += \
./Core/Src/Free42/core_commands1.o \
./Core/Src/Free42/core_commands2.o \
./Core/Src/Free42/core_commands3.o \
./Core/Src/Free42/core_commands4.o \
./Core/Src/Free42/core_commands5.o \
./Core/Src/Free42/core_commands6.o \
./Core/Src/Free42/core_commands7.o \
./Core/Src/Free42/core_display.o \
./Core/Src/Free42/core_globals.o \
./Core/Src/Free42/core_helpers.o \
./Core/Src/Free42/core_keydown.o \
./Core/Src/Free42/core_linalg1.o \
./Core/Src/Free42/core_linalg2.o \
./Core/Src/Free42/core_main.o \
./Core/Src/Free42/core_math1.o \
./Core/Src/Free42/core_math2.o \
./Core/Src/Free42/core_phloat.o \
./Core/Src/Free42/core_sto_rcl.o \
./Core/Src/Free42/core_tables.o \
./Core/Src/Free42/core_variables.o \
./Core/Src/Free42/shell_main.o \
./Core/Src/Free42/shell_spool.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Free42/%.o Core/Src/Free42/%.su Core/Src/Free42/%.cyclo: ../Core/Src/Free42/%.cc Core/Src/Free42/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -DDEBUG -DDECIMAL_GLOBAL_EXCEPTION_FLAGS=1 -DDECIMAL_GLOBAL_ROUNDING=1 -DDECIMAL_GLOBAL_ROUNDING_ACCESS_FUNCTIONS=1 -DDECIMAL_GLOBAL_EXCEPTION_FLAGS_ACCESS_FUNCTIONS=1 -DDECIMAL_CALL_BY_REFERENCE=1 -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Jerem/OneDrive/Documents/career/my_projects/stm-workspace/Free42/Core/Inc/IntelDecimal" -I"C:/Users/Jerem/OneDrive/Documents/career/my_projects/stm-workspace/Free42/Core/Inc/Free42" -Oz -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Free42

clean-Core-2f-Src-2f-Free42:
	-$(RM) ./Core/Src/Free42/core_commands1.cyclo ./Core/Src/Free42/core_commands1.d ./Core/Src/Free42/core_commands1.o ./Core/Src/Free42/core_commands1.su ./Core/Src/Free42/core_commands2.cyclo ./Core/Src/Free42/core_commands2.d ./Core/Src/Free42/core_commands2.o ./Core/Src/Free42/core_commands2.su ./Core/Src/Free42/core_commands3.cyclo ./Core/Src/Free42/core_commands3.d ./Core/Src/Free42/core_commands3.o ./Core/Src/Free42/core_commands3.su ./Core/Src/Free42/core_commands4.cyclo ./Core/Src/Free42/core_commands4.d ./Core/Src/Free42/core_commands4.o ./Core/Src/Free42/core_commands4.su ./Core/Src/Free42/core_commands5.cyclo ./Core/Src/Free42/core_commands5.d ./Core/Src/Free42/core_commands5.o ./Core/Src/Free42/core_commands5.su ./Core/Src/Free42/core_commands6.cyclo ./Core/Src/Free42/core_commands6.d ./Core/Src/Free42/core_commands6.o ./Core/Src/Free42/core_commands6.su ./Core/Src/Free42/core_commands7.cyclo ./Core/Src/Free42/core_commands7.d ./Core/Src/Free42/core_commands7.o ./Core/Src/Free42/core_commands7.su ./Core/Src/Free42/core_display.cyclo ./Core/Src/Free42/core_display.d ./Core/Src/Free42/core_display.o ./Core/Src/Free42/core_display.su ./Core/Src/Free42/core_globals.cyclo ./Core/Src/Free42/core_globals.d ./Core/Src/Free42/core_globals.o ./Core/Src/Free42/core_globals.su ./Core/Src/Free42/core_helpers.cyclo ./Core/Src/Free42/core_helpers.d ./Core/Src/Free42/core_helpers.o ./Core/Src/Free42/core_helpers.su ./Core/Src/Free42/core_keydown.cyclo ./Core/Src/Free42/core_keydown.d ./Core/Src/Free42/core_keydown.o ./Core/Src/Free42/core_keydown.su ./Core/Src/Free42/core_linalg1.cyclo ./Core/Src/Free42/core_linalg1.d ./Core/Src/Free42/core_linalg1.o ./Core/Src/Free42/core_linalg1.su ./Core/Src/Free42/core_linalg2.cyclo ./Core/Src/Free42/core_linalg2.d ./Core/Src/Free42/core_linalg2.o ./Core/Src/Free42/core_linalg2.su ./Core/Src/Free42/core_main.cyclo ./Core/Src/Free42/core_main.d ./Core/Src/Free42/core_main.o ./Core/Src/Free42/core_main.su ./Core/Src/Free42/core_math1.cyclo ./Core/Src/Free42/core_math1.d ./Core/Src/Free42/core_math1.o ./Core/Src/Free42/core_math1.su ./Core/Src/Free42/core_math2.cyclo ./Core/Src/Free42/core_math2.d ./Core/Src/Free42/core_math2.o ./Core/Src/Free42/core_math2.su ./Core/Src/Free42/core_phloat.cyclo ./Core/Src/Free42/core_phloat.d ./Core/Src/Free42/core_phloat.o ./Core/Src/Free42/core_phloat.su ./Core/Src/Free42/core_sto_rcl.cyclo ./Core/Src/Free42/core_sto_rcl.d ./Core/Src/Free42/core_sto_rcl.o ./Core/Src/Free42/core_sto_rcl.su ./Core/Src/Free42/core_tables.cyclo ./Core/Src/Free42/core_tables.d ./Core/Src/Free42/core_tables.o ./Core/Src/Free42/core_tables.su ./Core/Src/Free42/core_variables.cyclo ./Core/Src/Free42/core_variables.d ./Core/Src/Free42/core_variables.o ./Core/Src/Free42/core_variables.su ./Core/Src/Free42/shell_main.cyclo ./Core/Src/Free42/shell_main.d ./Core/Src/Free42/shell_main.o ./Core/Src/Free42/shell_main.su ./Core/Src/Free42/shell_spool.cyclo ./Core/Src/Free42/shell_spool.d ./Core/Src/Free42/shell_spool.o ./Core/Src/Free42/shell_spool.su

.PHONY: clean-Core-2f-Src-2f-Free42


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/mydrivers/Src/stm32f401xe_adc.c \
../Core/mydrivers/Src/stm32f401xe_dma.c \
../Core/mydrivers/Src/stm32f401xe_gpio.c \
../Core/mydrivers/Src/stm32f401xe_i2c.c \
../Core/mydrivers/Src/stm32f401xe_iwdg.c \
../Core/mydrivers/Src/stm32f401xe_pwr.c \
../Core/mydrivers/Src/stm32f401xe_rcc.c \
../Core/mydrivers/Src/stm32f401xe_rtc.c \
../Core/mydrivers/Src/stm32f401xe_spi.c \
../Core/mydrivers/Src/stm32f401xe_systick.c \
../Core/mydrivers/Src/stm32f401xe_tim.c \
../Core/mydrivers/Src/stm32f401xe_usart.c \
../Core/mydrivers/Src/stm32f401xe_wwdg.c 

OBJS += \
./Core/mydrivers/Src/stm32f401xe_adc.o \
./Core/mydrivers/Src/stm32f401xe_dma.o \
./Core/mydrivers/Src/stm32f401xe_gpio.o \
./Core/mydrivers/Src/stm32f401xe_i2c.o \
./Core/mydrivers/Src/stm32f401xe_iwdg.o \
./Core/mydrivers/Src/stm32f401xe_pwr.o \
./Core/mydrivers/Src/stm32f401xe_rcc.o \
./Core/mydrivers/Src/stm32f401xe_rtc.o \
./Core/mydrivers/Src/stm32f401xe_spi.o \
./Core/mydrivers/Src/stm32f401xe_systick.o \
./Core/mydrivers/Src/stm32f401xe_tim.o \
./Core/mydrivers/Src/stm32f401xe_usart.o \
./Core/mydrivers/Src/stm32f401xe_wwdg.o 

C_DEPS += \
./Core/mydrivers/Src/stm32f401xe_adc.d \
./Core/mydrivers/Src/stm32f401xe_dma.d \
./Core/mydrivers/Src/stm32f401xe_gpio.d \
./Core/mydrivers/Src/stm32f401xe_i2c.d \
./Core/mydrivers/Src/stm32f401xe_iwdg.d \
./Core/mydrivers/Src/stm32f401xe_pwr.d \
./Core/mydrivers/Src/stm32f401xe_rcc.d \
./Core/mydrivers/Src/stm32f401xe_rtc.d \
./Core/mydrivers/Src/stm32f401xe_spi.d \
./Core/mydrivers/Src/stm32f401xe_systick.d \
./Core/mydrivers/Src/stm32f401xe_tim.d \
./Core/mydrivers/Src/stm32f401xe_usart.d \
./Core/mydrivers/Src/stm32f401xe_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
Core/mydrivers/Src/%.o: ../Core/mydrivers/Src/%.c Core/mydrivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Core/devices/Inc -I../Core/examples/Inc -I../Core/mydrivers/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


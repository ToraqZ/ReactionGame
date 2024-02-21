################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/React_game/game.c 

OBJS += \
./Core/React_game/game.o 

C_DEPS += \
./Core/React_game/game.d 


# Each subdirectory must supply rules for building sources it contributes
Core/React_game/%.o Core/React_game/%.su Core/React_game/%.cyclo: ../Core/React_game/%.c Core/React_game/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Cossu/OneDrive/Bureau/ReactionGame/Drivers/MAX7219-master" -I"C:/Users/Cossu/OneDrive/Bureau/ReactionGame/Core/React_game" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-React_game

clean-Core-2f-React_game:
	-$(RM) ./Core/React_game/game.cyclo ./Core/React_game/game.d ./Core/React_game/game.o ./Core/React_game/game.su

.PHONY: clean-Core-2f-React_game


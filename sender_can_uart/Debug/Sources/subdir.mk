################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Application.c \
../Sources/CAN1_Events.c \
../Sources/Events.c \
../Sources/Timer1_Events.c \
../Sources/UART2_Events.c \
../Sources/main.c 

OBJS += \
./Sources/Application.o \
./Sources/CAN1_Events.o \
./Sources/Events.o \
./Sources/Timer1_Events.o \
./Sources/UART2_Events.o \
./Sources/main.o 

C_DEPS += \
./Sources/Application.d \
./Sources/CAN1_Events.d \
./Sources/Events.d \
./Sources/Timer1_Events.d \
./Sources/UART2_Events.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/alejandro/workspace.kds.k70/sender_can_uart/Static_Code/PDD" -I"/home/alejandro/workspace.kds.k70/sender_can_uart/Static_Code/IO_Map" -I"/home/alejandro/workspace.kds.k70/sender_can_uart/Sources" -I"/home/alejandro/workspace.kds.k70/sender_can_uart/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



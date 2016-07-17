################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/AS1.c \
../Generated_Code/CAN1.c \
../Generated_Code/CAN_RxBuff.c \
../Generated_Code/CS1.c \
../Generated_Code/CS2.c \
../Generated_Code/Cpu.c \
../Generated_Code/GREENLED.c \
../Generated_Code/KSDK1.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/TU1.c \
../Generated_Code/UART_RxBuff.c \
../Generated_Code/Vectors.c 

OBJS += \
./Generated_Code/AS1.o \
./Generated_Code/CAN1.o \
./Generated_Code/CAN_RxBuff.o \
./Generated_Code/CS1.o \
./Generated_Code/CS2.o \
./Generated_Code/Cpu.o \
./Generated_Code/GREENLED.o \
./Generated_Code/KSDK1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/TU1.o \
./Generated_Code/UART_RxBuff.o \
./Generated_Code/Vectors.o 

C_DEPS += \
./Generated_Code/AS1.d \
./Generated_Code/CAN1.d \
./Generated_Code/CAN_RxBuff.d \
./Generated_Code/CS1.d \
./Generated_Code/CS2.d \
./Generated_Code/Cpu.d \
./Generated_Code/GREENLED.d \
./Generated_Code/KSDK1.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/TU1.d \
./Generated_Code/UART_RxBuff.d \
./Generated_Code/Vectors.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/alejandro/workspace.kds.k70/sender_can_uart/Static_Code/PDD" -I"/home/alejandro/workspace.kds.k70/sender_can_uart/Static_Code/IO_Map" -I"/home/alejandro/workspace.kds.k70/sender_can_uart/Sources" -I"/home/alejandro/workspace.kds.k70/sender_can_uart/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



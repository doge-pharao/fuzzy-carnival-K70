################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Application.c \
../Sources/Events.c \
../Sources/can_events.c \
../Sources/main.c \
../Sources/timer_events.c \
../Sources/uart_events.c 

OBJS += \
./Sources/Application.o \
./Sources/Events.o \
./Sources/can_events.o \
./Sources/main.o \
./Sources/timer_events.o \
./Sources/uart_events.o 

C_DEPS += \
./Sources/Application.d \
./Sources/Events.d \
./Sources/can_events.d \
./Sources/main.d \
./Sources/timer_events.d \
./Sources/uart_events.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/alejandro/workspace.kds.k70/hello_world/Static_Code/PDD" -I"/home/alejandro/workspace.kds.k70/hello_world/Static_Code/IO_Map" -I"/home/alejandro/workspace.kds.k70/hello_world/Sources" -I"/home/alejandro/workspace.kds.k70/hello_world/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



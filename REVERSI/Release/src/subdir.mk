################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/REVERSI.c \
../src/funciones_R.c \
../src/inteligencia_cpu.c \
../src/juego_R.c 

OBJS += \
./src/REVERSI.o \
./src/funciones_R.o \
./src/inteligencia_cpu.o \
./src/juego_R.o 

C_DEPS += \
./src/REVERSI.d \
./src/funciones_R.d \
./src/inteligencia_cpu.d \
./src/juego_R.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



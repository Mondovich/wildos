################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/common.o \
../src/kernel.o \
../src/monitor.o 

CPP_SRCS += \
../src/common.cpp \
../src/kernel.cpp \
../src/monitor.cpp 

ASM_SRCS += \
../src/loader.asm 

OBJS += \
./src/common.o \
./src/kernel.o \
./src/loader.o \
./src/monitor.o 

CPP_DEPS += \
./src/common.d \
./src/kernel.d \
./src/monitor.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	i686-elf-g++.exe -O2 -g -Wall -c -Wextra -nostdlib -nostartfiles -nodefaultlibs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	nasm -f elf -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



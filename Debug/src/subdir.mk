################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Instruction.cpp \
../src/Memory.cpp \
../src/Register.cpp \
../src/UserInterface.cpp \
../src/main.cpp 

OBJS += \
./src/Instruction.o \
./src/Memory.o \
./src/Register.o \
./src/UserInterface.o \
./src/main.o 

CPP_DEPS += \
./src/Instruction.d \
./src/Memory.d \
./src/Register.d \
./src/UserInterface.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/ygcho/Desktop/dev/workspace_mars/ARMv6m_Simulator/inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



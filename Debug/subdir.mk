################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Router.cpp \
../freader.cpp \
../main.cpp \
../regex.cpp 

O_SRCS += \
../freader.o \
../main.o 

OBJS += \
./Router.o \
./freader.o \
./main.o \
./regex.o 

CPP_DEPS += \
./Router.d \
./freader.d \
./main.d \
./regex.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Application.cpp \
../BodyModels.cpp \
../CelestialBody.cpp \
../GUIModel.cpp \
../main.cpp 

OBJS += \
./Application.o \
./BodyModels.o \
./CelestialBody.o \
./GUIModel.o \
./main.o 

CPP_DEPS += \
./Application.d \
./BodyModels.d \
./CelestialBody.d \
./GUIModel.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/irrlicht -I/home/daniele/Documenti/C++Libraries/json-develop/include -I/home/daniele/Documenti/C++Libraries -I/usr/include/freetype2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



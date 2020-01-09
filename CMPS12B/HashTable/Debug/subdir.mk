################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/edywang/Documents/GitHub/CMPS12B/HashTable/Dictionary.c \
/Users/edywang/Documents/GitHub/CMPS12B/HashTable/DictionaryClient.c 

OBJS += \
./Dictionary.o \
./DictionaryClient.o 

C_DEPS += \
./Dictionary.d \
./DictionaryClient.d 


# Each subdirectory must supply rules for building sources it contributes
Dictionary.o: /Users/edywang/Documents/GitHub/CMPS12B/HashTable/Dictionary.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

DictionaryClient.o: /Users/edywang/Documents/GitHub/CMPS12B/HashTable/DictionaryClient.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



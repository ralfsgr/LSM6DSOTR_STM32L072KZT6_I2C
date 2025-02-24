################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32L0xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := LSM6DSOTR_STM32L072KZT6_I2C
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
LSM6DSOTR_STM32L072KZT6_I2C.elf \

MAP_FILES += \
LSM6DSOTR_STM32L072KZT6_I2C.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
LSM6DSOTR_STM32L072KZT6_I2C.list \

OBJCOPY_HEX += \
LSM6DSOTR_STM32L072KZT6_I2C.hex \

OBJCOPY_BIN += \
LSM6DSOTR_STM32L072KZT6_I2C.bin \


# All Target
all: main-build

# Main-build Target
main-build: LSM6DSOTR_STM32L072KZT6_I2C.elf secondary-outputs

# Tool invocations
LSM6DSOTR_STM32L072KZT6_I2C.elf LSM6DSOTR_STM32L072KZT6_I2C.map: $(OBJS) $(USER_OBJS) C:\Workspace\STM32CubeIDE\downloads_from_gitlab\LSM6DSOTR_STM32L072KZT6_I2C\LSM6DSOTR_STM32L072KZT6_I2C\STM32L072KZTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "LSM6DSOTR_STM32L072KZT6_I2C.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"C:\Workspace\STM32CubeIDE\downloads_from_gitlab\LSM6DSOTR_STM32L072KZT6_I2C\LSM6DSOTR_STM32L072KZT6_I2C\STM32L072KZTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="LSM6DSOTR_STM32L072KZT6_I2C.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

LSM6DSOTR_STM32L072KZT6_I2C.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "LSM6DSOTR_STM32L072KZT6_I2C.list"
	@echo 'Finished building: $@'
	@echo ' '

LSM6DSOTR_STM32L072KZT6_I2C.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "LSM6DSOTR_STM32L072KZT6_I2C.hex"
	@echo 'Finished building: $@'
	@echo ' '

LSM6DSOTR_STM32L072KZT6_I2C.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "LSM6DSOTR_STM32L072KZT6_I2C.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) LSM6DSOTR_STM32L072KZT6_I2C.bin LSM6DSOTR_STM32L072KZT6_I2C.elf LSM6DSOTR_STM32L072KZT6_I2C.hex LSM6DSOTR_STM32L072KZT6_I2C.list LSM6DSOTR_STM32L072KZT6_I2C.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets

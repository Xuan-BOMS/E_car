################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
system/%.o: ../system/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/Code_sourse/mspm0_sdk_2_05_01_00/examples/rtos/LP_MSPM0G3507/drivers/empty_freertos/Fuckti" -I"D:/Code_sourse/mspm0_sdk_2_05_01_00/examples/rtos/LP_MSPM0G3507/drivers/empty_freertos/Fuckti/Debug" -I"D:/Code_sourse/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"D:/Code_sourse/mspm0_sdk_2_05_01_00/source" -gdwarf-3 -MMD -MP -MF"system/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



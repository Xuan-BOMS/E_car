################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/Code_sourse/mspm0_sdk_2_05_01_00/examples/rtos/LP_MSPM0G3507/drivers/empty_freertos/Fuckti" -I"D:/Code_sourse/mspm0_sdk_2_05_01_00/examples/rtos/LP_MSPM0G3507/drivers/empty_freertos/Fuckti/Debug" -I"D:/Code_sourse/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"D:/Code_sourse/mspm0_sdk_2_05_01_00/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1019371055: ../empty.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"D:/ti/ccs2020/ccs/utils/sysconfig_1.24.0/sysconfig_cli.bat" --script "D:/Code_sourse/mspm0_sdk_2_05_01_00/examples/rtos/LP_MSPM0G3507/drivers/empty_freertos/Fuckti/empty.syscfg" -o "." -s "D:/Code_sourse/mspm0_sdk_2_05_01_00/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-1019371055 ../empty.syscfg
device.opt: build-1019371055
device.cmd.genlibs: build-1019371055
ti_msp_dl_config.c: build-1019371055
ti_msp_dl_config.h: build-1019371055
Event.dot: build-1019371055

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/Code_sourse/mspm0_sdk_2_05_01_00/examples/rtos/LP_MSPM0G3507/drivers/empty_freertos/Fuckti" -I"D:/Code_sourse/mspm0_sdk_2_05_01_00/examples/rtos/LP_MSPM0G3507/drivers/empty_freertos/Fuckti/Debug" -I"D:/Code_sourse/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"D:/Code_sourse/mspm0_sdk_2_05_01_00/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: D:/Code_sourse/mspm0_sdk_2_05_01_00/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/Code_sourse/mspm0_sdk_2_05_01_00/examples/rtos/LP_MSPM0G3507/drivers/empty_freertos/Fuckti" -I"D:/Code_sourse/mspm0_sdk_2_05_01_00/examples/rtos/LP_MSPM0G3507/drivers/empty_freertos/Fuckti/Debug" -I"D:/Code_sourse/mspm0_sdk_2_05_01_00/source/third_party/CMSIS/Core/Include" -I"D:/Code_sourse/mspm0_sdk_2_05_01_00/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



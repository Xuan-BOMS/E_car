################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS

GEN_OPTS__FLAG := @"./device.opt" 
GEN_CMDS__FLAG := -Wl,-l"./device_linker.cmd" 

ORDERED_OBJS += \
"./empty.o" \
"./ti_msp_dl_config.o" \
"./startup_mspm0g350x_ticlang.o" \
"./HWT101/hwt101.o" \
"./OLED/oled.o" \
"./State/Buzzer.o" \
"./State/Key.o" \
"./State/LED.o" \
"./State/task.o" \
"./classic/Encoder.o" \
"./classic/Gray.o" \
"./classic/Motor_tb.o" \
"./classic/Tracking.o" \
"./classic/chassis.o" \
"./classic/motorDK.o" \
"./gimbal/ZDT_drive.o" \
"./gimbal/gimbal.o" \
"./iar/startup_mspm0g350x_iar.o" \
"./system/PID.o" \
"./system/PWM.o" \
"./system/Timer.o" \
"./system/max_min.o" \
"./time/time.o" \
"./vision/vision.o" \
"../gcc/device_linker.lds" \
"../ticlang/device_linker.cmd" \
$(GEN_CMDS__FLAG) \
-Wl,-ldevice.cmd.genlibs \
-Wl,-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include EIDE/build/empty_LP_MSPM0G3507_nortos_keil/subdir_vars.mk
-include HWT101/subdir_vars.mk
-include OLED/subdir_vars.mk
-include State/subdir_vars.mk
-include classic/subdir_vars.mk
-include gcc/subdir_vars.mk
-include gimbal/subdir_vars.mk
-include iar/subdir_vars.mk
-include system/subdir_vars.mk
-include ticlang/subdir_vars.mk
-include time/subdir_vars.mk
-include vision/subdir_vars.mk
-include subdir_rules.mk
-include EIDE/build/empty_LP_MSPM0G3507_nortos_keil/subdir_rules.mk
-include HWT101/subdir_rules.mk
-include OLED/subdir_rules.mk
-include State/subdir_rules.mk
-include classic/subdir_rules.mk
-include gcc/subdir_rules.mk
-include gimbal/subdir_rules.mk
-include iar/subdir_rules.mk
-include system/subdir_rules.mk
-include ticlang/subdir_rules.mk
-include time/subdir_rules.mk
-include vision/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Fuckti.out 

EXE_OUTPUTS__QUOTED += \
"Fuckti.out" 


# All Target
all: $(OBJS) $(CMD_SRCS) $(LDS_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "Fuckti.out"

# Tool invocations
Fuckti.out: $(OBJS) $(CMD_SRCS) $(LDS_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"D:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -gdwarf-3 -Wl,-m"Fuckti.map" -Wl,-i"D:/Code_sourse/mspm0_sdk_2_05_01_00/source" -Wl,-i"D:/Code_sourse/mspm0_sdk_2_05_01_00/examples/rtos/LP_MSPM0G3507/drivers/empty_freertos/Fuckti" -Wl,-i"D:/Code_sourse/mspm0_sdk_2_05_01_00/examples/rtos/LP_MSPM0G3507/drivers/empty_freertos/Fuckti/Debug/syscfg" -Wl,-i"D:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/lib" -Wl,--diag_wrap=off -Wl,--display_error_number -Wl,--warn_sections -Wl,--xml_link_info="Fuckti_linkInfo.xml" -Wl,--rom_model -o "Fuckti.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "empty.o" "ti_msp_dl_config.o" "startup_mspm0g350x_ticlang.o" "HWT101\hwt101.o" "OLED\oled.o" "State\Buzzer.o" "State\Key.o" "State\LED.o" "State\task.o" "classic\Encoder.o" "classic\Gray.o" "classic\Motor_tb.o" "classic\Tracking.o" "classic\chassis.o" "classic\motorDK.o" "gimbal\ZDT_drive.o" "gimbal\gimbal.o" "iar\startup_mspm0g350x_iar.o" "system\PID.o" "system\PWM.o" "system\Timer.o" "system\max_min.o" "time\time.o" "vision\vision.o" 
	-$(RM) "empty.d" "ti_msp_dl_config.d" "startup_mspm0g350x_ticlang.d" "HWT101\hwt101.d" "OLED\oled.d" "State\Buzzer.d" "State\Key.d" "State\LED.d" "State\task.d" "classic\Encoder.d" "classic\Gray.d" "classic\Motor_tb.d" "classic\Tracking.d" "classic\chassis.d" "classic\motorDK.d" "gimbal\ZDT_drive.d" "gimbal\gimbal.d" "iar\startup_mspm0g350x_iar.d" "system\PID.d" "system\PWM.d" "system\Timer.d" "system\max_min.d" "time\time.d" "vision\vision.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets


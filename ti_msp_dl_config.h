/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for MOTOR */
#define MOTOR_INST                                                         TIMA0
#define MOTOR_INST_IRQHandler                                   TIMA0_IRQHandler
#define MOTOR_INST_INT_IRQN                                     (TIMA0_INT_IRQn)
#define MOTOR_INST_CLK_FREQ                                             32000000
/* GPIO defines for channel 0 */
#define GPIO_MOTOR_C0_PORT                                                 GPIOA
#define GPIO_MOTOR_C0_PIN                                          DL_GPIO_PIN_8
#define GPIO_MOTOR_C0_IOMUX                                      (IOMUX_PINCM19)
#define GPIO_MOTOR_C0_IOMUX_FUNC                     IOMUX_PINCM19_PF_TIMA0_CCP0
#define GPIO_MOTOR_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_MOTOR_C1_PORT                                                 GPIOA
#define GPIO_MOTOR_C1_PIN                                          DL_GPIO_PIN_9
#define GPIO_MOTOR_C1_IOMUX                                      (IOMUX_PINCM20)
#define GPIO_MOTOR_C1_IOMUX_FUNC                     IOMUX_PINCM20_PF_TIMA0_CCP1
#define GPIO_MOTOR_C1_IDX                                    DL_TIMER_CC_1_INDEX



/* Defines for TIMER_gimbal */
#define TIMER_gimbal_INST                                                (TIMA1)
#define TIMER_gimbal_INST_IRQHandler                            TIMA1_IRQHandler
#define TIMER_gimbal_INST_INT_IRQN                              (TIMA1_INT_IRQn)
#define TIMER_gimbal_INST_LOAD_VALUE                                      (199U)
/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMG8)
#define TIMER_0_INST_IRQHandler                                 TIMG8_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMG8_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                          (3199U)



/* Defines for UART_1 */
#define UART_1_INST                                                        UART1
#define UART_1_INST_FREQUENCY                                            4000000
#define UART_1_INST_IRQHandler                                  UART1_IRQHandler
#define UART_1_INST_INT_IRQN                                      UART1_INT_IRQn
#define GPIO_UART_1_RX_PORT                                                GPIOB
#define GPIO_UART_1_TX_PORT                                                GPIOB
#define GPIO_UART_1_RX_PIN                                         DL_GPIO_PIN_5
#define GPIO_UART_1_TX_PIN                                         DL_GPIO_PIN_4
#define GPIO_UART_1_IOMUX_RX                                     (IOMUX_PINCM18)
#define GPIO_UART_1_IOMUX_TX                                     (IOMUX_PINCM17)
#define GPIO_UART_1_IOMUX_RX_FUNC                      IOMUX_PINCM18_PF_UART1_RX
#define GPIO_UART_1_IOMUX_TX_FUNC                      IOMUX_PINCM17_PF_UART1_TX
#define UART_1_BAUD_RATE                                                (115200)
#define UART_1_IBRD_4_MHZ_115200_BAUD                                        (2)
#define UART_1_FBRD_4_MHZ_115200_BAUD                                       (11)
/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_FREQUENCY                                            4000000
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_31
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_28
#define GPIO_UART_0_IOMUX_RX                                      (IOMUX_PINCM6)
#define GPIO_UART_0_IOMUX_TX                                      (IOMUX_PINCM3)
#define GPIO_UART_0_IOMUX_RX_FUNC                       IOMUX_PINCM6_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                       IOMUX_PINCM3_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_4_MHZ_115200_BAUD                                        (2)
#define UART_0_FBRD_4_MHZ_115200_BAUD                                       (11)
/* Defines for UART_2 */
#define UART_2_INST                                                        UART3
#define UART_2_INST_FREQUENCY                                            4000000
#define UART_2_INST_IRQHandler                                  UART3_IRQHandler
#define UART_2_INST_INT_IRQN                                      UART3_INT_IRQn
#define GPIO_UART_2_RX_PORT                                                GPIOB
#define GPIO_UART_2_TX_PORT                                                GPIOB
#define GPIO_UART_2_RX_PIN                                        DL_GPIO_PIN_13
#define GPIO_UART_2_TX_PIN                                        DL_GPIO_PIN_12
#define GPIO_UART_2_IOMUX_RX                                     (IOMUX_PINCM30)
#define GPIO_UART_2_IOMUX_TX                                     (IOMUX_PINCM29)
#define GPIO_UART_2_IOMUX_RX_FUNC                      IOMUX_PINCM30_PF_UART3_RX
#define GPIO_UART_2_IOMUX_TX_FUNC                      IOMUX_PINCM29_PF_UART3_TX
#define UART_2_BAUD_RATE                                                (115200)
#define UART_2_IBRD_4_MHZ_115200_BAUD                                        (2)
#define UART_2_FBRD_4_MHZ_115200_BAUD                                       (11)





/* Port definition for Pin Group GPIO_Buzzer */
#define GPIO_Buzzer_PORT                                                 (GPIOA)

/* Defines for PIN_A27: GPIOA.27 with pinCMx 60 on package pin 31 */
#define GPIO_Buzzer_PIN_A27_PIN                                 (DL_GPIO_PIN_27)
#define GPIO_Buzzer_PIN_A27_IOMUX                                (IOMUX_PINCM60)
/* Defines for LED1: GPIOA.26 with pinCMx 59 on package pin 30 */
#define GPIO_LED_LED1_PORT                                               (GPIOA)
#define GPIO_LED_LED1_PIN                                       (DL_GPIO_PIN_26)
#define GPIO_LED_LED1_IOMUX                                      (IOMUX_PINCM59)
/* Defines for LED2: GPIOA.24 with pinCMx 54 on package pin 25 */
#define GPIO_LED_LED2_PORT                                               (GPIOA)
#define GPIO_LED_LED2_PIN                                       (DL_GPIO_PIN_24)
#define GPIO_LED_LED2_IOMUX                                      (IOMUX_PINCM54)
/* Defines for LED3: GPIOB.24 with pinCMx 52 on package pin 23 */
#define GPIO_LED_LED3_PORT                                               (GPIOB)
#define GPIO_LED_LED3_PIN                                       (DL_GPIO_PIN_24)
#define GPIO_LED_LED3_IOMUX                                      (IOMUX_PINCM52)
/* Defines for KEY1: GPIOB.0 with pinCMx 12 on package pin 47 */
#define GPIO_KEY_KEY1_PORT                                               (GPIOB)
#define GPIO_KEY_KEY1_PIN                                        (DL_GPIO_PIN_0)
#define GPIO_KEY_KEY1_IOMUX                                      (IOMUX_PINCM12)
/* Defines for KEY2: GPIOB.1 with pinCMx 13 on package pin 48 */
#define GPIO_KEY_KEY2_PORT                                               (GPIOB)
#define GPIO_KEY_KEY2_PIN                                        (DL_GPIO_PIN_1)
#define GPIO_KEY_KEY2_IOMUX                                      (IOMUX_PINCM13)
/* Defines for KEY3: GPIOA.7 with pinCMx 14 on package pin 49 */
#define GPIO_KEY_KEY3_PORT                                               (GPIOA)
#define GPIO_KEY_KEY3_PIN                                        (DL_GPIO_PIN_7)
#define GPIO_KEY_KEY3_IOMUX                                      (IOMUX_PINCM14)
/* Defines for KEY4: GPIOA.18 with pinCMx 40 on package pin 11 */
#define GPIO_KEY_KEY4_PORT                                               (GPIOA)
#define GPIO_KEY_KEY4_PIN                                       (DL_GPIO_PIN_18)
#define GPIO_KEY_KEY4_IOMUX                                      (IOMUX_PINCM40)
/* Defines for PIN_1: GPIOB.23 with pinCMx 51 on package pin 22 */
#define GPIO_Gray_PIN_1_PORT                                             (GPIOB)
#define GPIO_Gray_PIN_1_PIN                                     (DL_GPIO_PIN_23)
#define GPIO_Gray_PIN_1_IOMUX                                    (IOMUX_PINCM51)
/* Defines for PIN_2: GPIOA.30 with pinCMx 5 on package pin 37 */
#define GPIO_Gray_PIN_2_PORT                                             (GPIOA)
#define GPIO_Gray_PIN_2_PIN                                     (DL_GPIO_PIN_30)
#define GPIO_Gray_PIN_2_IOMUX                                     (IOMUX_PINCM5)
/* Defines for PIN_3: GPIOB.27 with pinCMx 58 on package pin 29 */
#define GPIO_Gray_PIN_3_PORT                                             (GPIOB)
#define GPIO_Gray_PIN_3_PIN                                     (DL_GPIO_PIN_27)
#define GPIO_Gray_PIN_3_IOMUX                                    (IOMUX_PINCM58)
/* Defines for PIN_4: GPIOB.21 with pinCMx 49 on package pin 20 */
#define GPIO_Gray_PIN_4_PORT                                             (GPIOB)
#define GPIO_Gray_PIN_4_PIN                                     (DL_GPIO_PIN_21)
#define GPIO_Gray_PIN_4_IOMUX                                    (IOMUX_PINCM49)
/* Defines for PIN_5: GPIOA.29 with pinCMx 4 on package pin 36 */
#define GPIO_Gray_PIN_5_PORT                                             (GPIOA)
#define GPIO_Gray_PIN_5_PIN                                     (DL_GPIO_PIN_29)
#define GPIO_Gray_PIN_5_IOMUX                                     (IOMUX_PINCM4)
/* Defines for AIN_2: GPIOA.25 with pinCMx 55 on package pin 26 */
#define GPIO_MOTOR_DIR_AIN_2_PORT                                        (GPIOA)
#define GPIO_MOTOR_DIR_AIN_2_PIN                                (DL_GPIO_PIN_25)
#define GPIO_MOTOR_DIR_AIN_2_IOMUX                               (IOMUX_PINCM55)
/* Defines for AIN_1: GPIOB.25 with pinCMx 56 on package pin 27 */
#define GPIO_MOTOR_DIR_AIN_1_PORT                                        (GPIOB)
#define GPIO_MOTOR_DIR_AIN_1_PIN                                (DL_GPIO_PIN_25)
#define GPIO_MOTOR_DIR_AIN_1_IOMUX                               (IOMUX_PINCM56)
/* Defines for STBY: GPIOB.20 with pinCMx 48 on package pin 19 */
#define GPIO_MOTOR_DIR_STBY_PORT                                         (GPIOB)
#define GPIO_MOTOR_DIR_STBY_PIN                                 (DL_GPIO_PIN_20)
#define GPIO_MOTOR_DIR_STBY_IOMUX                                (IOMUX_PINCM48)
/* Defines for BIN_1: GPIOA.14 with pinCMx 36 on package pin 7 */
#define GPIO_MOTOR_DIR_BIN_1_PORT                                        (GPIOA)
#define GPIO_MOTOR_DIR_BIN_1_PIN                                (DL_GPIO_PIN_14)
#define GPIO_MOTOR_DIR_BIN_1_IOMUX                               (IOMUX_PINCM36)
/* Defines for BIN_2: GPIOB.17 with pinCMx 43 on package pin 14 */
#define GPIO_MOTOR_DIR_BIN_2_PORT                                        (GPIOB)
#define GPIO_MOTOR_DIR_BIN_2_PIN                                (DL_GPIO_PIN_17)
#define GPIO_MOTOR_DIR_BIN_2_IOMUX                               (IOMUX_PINCM43)
/* Port definition for Pin Group GPIO_ENCODERA */
#define GPIO_ENCODERA_PORT                                               (GPIOA)

/* Defines for PIN_A_1: GPIOA.1 with pinCMx 2 on package pin 34 */
#define GPIO_ENCODERA_PIN_A_1_PIN                                (DL_GPIO_PIN_1)
#define GPIO_ENCODERA_PIN_A_1_IOMUX                               (IOMUX_PINCM2)
/* Defines for PIN_A_2: GPIOA.0 with pinCMx 1 on package pin 33 */
#define GPIO_ENCODERA_PIN_A_2_PIN                                (DL_GPIO_PIN_0)
#define GPIO_ENCODERA_PIN_A_2_IOMUX                               (IOMUX_PINCM1)
/* Port definition for Pin Group GPIO_ENCODERB */
#define GPIO_ENCODERB_PORT                                               (GPIOB)

/* Defines for PIN_B_1: GPIOB.15 with pinCMx 32 on package pin 3 */
#define GPIO_ENCODERB_PIN_B_1_PIN                               (DL_GPIO_PIN_15)
#define GPIO_ENCODERB_PIN_B_1_IOMUX                              (IOMUX_PINCM32)
/* Defines for PIN_B_2: GPIOB.16 with pinCMx 33 on package pin 4 */
#define GPIO_ENCODERB_PIN_B_2_PIN                               (DL_GPIO_PIN_16)
#define GPIO_ENCODERB_PIN_B_2_IOMUX                              (IOMUX_PINCM33)
/* Port definition for Pin Group GPIO_OLED */
#define GPIO_OLED_PORT                                                   (GPIOA)

/* Defines for SCL: GPIOA.17 with pinCMx 39 on package pin 10 */
#define GPIO_OLED_SCL_PIN                                       (DL_GPIO_PIN_17)
#define GPIO_OLED_SCL_IOMUX                                      (IOMUX_PINCM39)
/* Defines for SDA: GPIOA.16 with pinCMx 38 on package pin 9 */
#define GPIO_OLED_SDA_PIN                                       (DL_GPIO_PIN_16)
#define GPIO_OLED_SDA_IOMUX                                      (IOMUX_PINCM38)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_MOTOR_init(void);
void SYSCFG_DL_TIMER_gimbal_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_UART_1_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_UART_2_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */

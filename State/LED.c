#include "LED.h"

void LED1_Toggle(void) {
    // 切换LED1状态
    DL_GPIO_togglePins(GPIO_LED_LED1_PORT, GPIO_LED_LED1_PIN);
}

void LED2_Toggle(void) {
    // 切换LED2状态
    DL_GPIO_togglePins(GPIO_LED_LED2_PORT, GPIO_LED_LED2_PIN);
}

void LED3_Toggle(void) {
    // 切换LED3状态
    DL_GPIO_togglePins(GPIO_LED_LED3_PORT, GPIO_LED_LED3_PIN);
}

void LED1_On(void) {
    // 打开LED1
    DL_GPIO_setPins(GPIO_LED_LED1_PORT, GPIO_LED_LED1_PIN);
}
void LED2_On(void) {
    // 打开LED2
    DL_GPIO_setPins(GPIO_LED_LED2_PORT, GPIO_LED_LED2_PIN);
}

void LED3_On(void) {
    // 打开LED3
    DL_GPIO_setPins(GPIO_LED_LED3_PORT, GPIO_LED_LED3_PIN);
}
void LED1_Off(void) {
    // 关闭LED1
    DL_GPIO_clearPins(GPIO_LED_LED1_PORT, GPIO_LED_LED1_PIN);
}
void LED2_Off(void) {
    // 关闭LED2
    DL_GPIO_clearPins(GPIO_LED_LED2_PORT, GPIO_LED_LED2_PIN);
}
void LED3_Off(void) {
    // 关闭LED3
    DL_GPIO_clearPins(GPIO_LED_LED3_PORT, GPIO_LED_LED3_PIN);
}
void LED_ALL_OFF(void) {
    // 关闭所有LED
    DL_GPIO_clearPins(GPIO_LED_LED1_PORT, GPIO_LED_LED1_PIN);
    DL_GPIO_clearPins(GPIO_LED_LED2_PORT, GPIO_LED_LED2_PIN);
    DL_GPIO_clearPins(GPIO_LED_LED3_PORT, GPIO_LED_LED3_PIN);
}
#include "Laser.h"

void Laser_ON(void) {
    DL_GPIO_setPins(GPIO_Laser_PORT, GPIO_Laser_PIN_0_PIN);
}

void Laser_OFF(void) {
    DL_GPIO_clearPins(GPIO_Laser_PORT, GPIO_Laser_PIN_0_PIN);
}

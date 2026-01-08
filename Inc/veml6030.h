#ifndef VEML6030_H
#define VEML6030_H

#include "stm32f407_i2c_driver.h"

#define VEML6030_I2C_ADDR     0x48

float VEML6030_ReadLux(I2C_Handle_t *pI2CHandle);

#endif

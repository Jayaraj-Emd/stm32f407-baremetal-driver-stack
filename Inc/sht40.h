#ifndef SHT40_H
#define SHT40_H

#include "stm32f407_i2c_driver.h"

#define SHT40_I2C_ADDR      0x44

typedef struct
{
    float temperature;
    float humidity;
} SHT40_Data_t;

typedef enum
{
    SHT40_OK = 0,
    SHT40_CRC_TEMP_ERROR,
    SHT40_CRC_HUM_ERROR
} SHT40_Status_t;

void SHT40_Init(I2C_Handle_t *pI2CHandle);
SHT40_Status_t SHT40_ReadData(I2C_Handle_t *pI2CHandle,
                              SHT40_Data_t *data);


#endif

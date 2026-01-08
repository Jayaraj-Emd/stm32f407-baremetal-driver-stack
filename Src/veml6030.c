#include "veml6030.h"

#define VEML6030_REG_CONF     0x00
#define VEML6030_REG_ALS      0x04

static void VEML6030_Write16(I2C_Handle_t *pI2CHandle, uint8_t reg, uint16_t value)
{
    uint8_t tx[3];
    tx[0] = reg;
    tx[1] = value & 0xFF;
    tx[2] = (value >> 8) & 0xFF;

    I2C_MasterSendData(pI2CHandle, tx, 3, VEML6030_I2C_ADDR, I2C_DISABLE_SR);
}

static uint16_t VEML6030_Read16(I2C_Handle_t *pI2CHandle, uint8_t reg)
{
    uint8_t rx[2];

    I2C_MasterSendData(pI2CHandle, &reg, 1, VEML6030_I2C_ADDR, I2C_ENABLE_SR);
    I2C_MasterReceiveData(pI2CHandle, rx, 2, VEML6030_I2C_ADDR, I2C_DISABLE_SR);

    return (rx[1] << 8) | rx[0];
}

float VEML6030_ReadLux(I2C_Handle_t *pI2CHandle)
{

    VEML6030_Write16(pI2CHandle, VEML6030_REG_CONF, 0x0000);
    for(volatile uint32_t i = 0; i < 50000; i++);
    uint16_t raw = VEML6030_Read16(pI2CHandle, VEML6030_REG_ALS);
    return raw * 0.0576f;
}

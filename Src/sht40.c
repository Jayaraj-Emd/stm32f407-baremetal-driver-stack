#include "sht40.h"

#define SHT40_CMD_MEASURE_HIGH_PREC  0xFD
void Delay_ms(uint32_t ms)
{
    for(uint32_t i = 0 ; i < ms * 4000 ; i++);
}

static uint8_t SHT40_CalcCRC(uint8_t *data, uint8_t len)
{
    uint8_t crc = 0xFF;

    for (uint8_t i = 0; i < len; i++)
    {
        crc ^= data[i];
        for (uint8_t bit = 0; bit < 8; bit++)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x31;
            else
                crc <<= 1;
        }
    }
    return crc;
}

SHT40_Status_t SHT40_ReadData(I2C_Handle_t *pI2CHandle,
                              SHT40_Data_t *data)
{
    uint8_t cmd = 0xFD;   // High precision
    uint8_t rx[6];
    uint16_t rawT, rawH;

    I2C_MasterSendData(pI2CHandle,
                       &cmd,
                       1,
                       SHT40_I2C_ADDR,
                       I2C_DISABLE_SR);

    Delay_ms(20);

    I2C_MasterReceiveData(pI2CHandle,
                          rx,
                          6,
                          SHT40_I2C_ADDR,
                          I2C_DISABLE_SR);

    if (SHT40_CalcCRC(&rx[0], 2) != rx[2])
        return SHT40_CRC_TEMP_ERROR;

    if (SHT40_CalcCRC(&rx[3], 2) != rx[5])
        return SHT40_CRC_HUM_ERROR;

    rawT = (rx[0] << 8) | rx[1];
    rawH = (rx[3] << 8) | rx[4];

    data->temperature = -45.0f + (175.0f * rawT / 65535.0f);
    data->humidity    = -6.0f  + (125.0f * rawH / 65535.0f);

    return SHT40_OK;
}

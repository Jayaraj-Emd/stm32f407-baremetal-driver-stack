/*
 * 001_i2c_testing.c
 *
 * Created on: Oct 18, 2025
 * Author: JAI
 */

#include <string.h>
#include "stm32f407.h"
#include <stdio.h>
/* I2C addresses */
#define MY_ADDR     0x61
#define SLAVE_ADDR  0x44   // SHT40 address

I2C_Handle_t I2C1Handle;

/* Simple delay */
void Delay_ms(uint32_t ms)
{
    for(uint32_t i = 0; i < ms; i++)
        for(uint32_t j = 0; j < 16000; j++);
}

/*
 * PB6 -> SCL
 * PB7 -> SDA
 */
void I2C1_GPIOInits(void)
{
    GPIO_Handle_t I2CPins;

    I2CPins.pGPIOx = GPIOB;
    I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUTPUT_TYPE_OD;
    I2CPins.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_PIN_PULL_UP;
    I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
    I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OUTPUT_SPEED_FAST;

    /* SCL */
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
    GPIO_Init(&I2CPins);

    /* SDA */
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
    GPIO_Init(&I2CPins);
}

void I2C1_Inits(void)
{
    I2C1Handle.pI2Cx = I2C1;
    I2C1Handle.I2C_Config.I2C_AckControl = I2C_ACK_ENABLE;
    I2C1Handle.I2C_Config.I2C_DeviceAddress = MY_ADDR;
    I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
    I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;

    I2C_Init(&I2C1Handle);
}

void GPIO_ButtonInit(void)
{
    GPIO_Handle_t GPIOBtn;

    GPIOBtn.pGPIOx = GPIOA;
    GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OUTPUT_SPEED_FAST;
    GPIOBtn.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_PIN_NO_PUPD;

    GPIO_Init(&GPIOBtn);
}

/* Read temperature & humidity from SHT40 */
void SHT40_ReadData(float *temperature, float *humidity)
{
    uint8_t cmd = 0xFD;   // High precision measurement
    uint8_t rx[6];
    uint16_t rawT, rawH;

    /* Send measurement command */
    I2C_MasterSendData(&I2C1Handle,
                       &cmd,
                       1,
                       SLAVE_ADDR,
                       I2C_ENABLE_SR);

    /* Wait for conversion */
    Delay_ms(20);

    /* Read 6 bytes */
    I2C_MasterReceiveData(&I2C1Handle,
                          rx,
                          6,
                          SLAVE_ADDR,
                          I2C_DISABLE_SR);

    rawT = (rx[0] << 8) | rx[1];
    rawH = (rx[3] << 8) | rx[4];

    *temperature = -45.0f + (175.0f * rawT / 65535.0f);
    *humidity    = -6.0f  + (125.0f * rawH / 65535.0f);
}

int main(void)
{
    float temperature, humidity;

    GPIO_ButtonInit();
    I2C1_GPIOInits();
    I2C1_Inits();

    /* Enable I2C peripheral */
    I2C_PeripheralControl(I2C1, ENABLE);

    /* ACK enabled after PE = 1 */
    I2C_ManageAcking(I2C1, I2C_ACK_ENABLE);

    while(1)
    {
    	printf("hello\n\r");
        SHT40_ReadData(&temperature, &humidity);
        Delay_ms(500);
    }
}

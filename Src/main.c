#include <stdio.h>
#include <string.h>

#include "stm32f407.h"
#include "stm32f407_gpio_driver.h"
#include "stm32f407_i2c_driver.h"
#include "stm32f407_usart_driver.h"

#include "sht40.h"
#include "veml6030.h"

I2C_Handle_t   I2C1Handle;
USART_Handle_t USART2Handle;


void delay(void)
{
    for(uint32_t i = 0 ; i < 1000000 ; i++);
}

void I2C1_GPIOInits(void)
{
    GPIO_Handle_t I2CPins;

    GPIO_PeriClockControl(GPIOB, ENABLE);

    I2CPins.pGPIOx = GPIOB;
    I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4; // AF4
    I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUTPUT_TYPE_OD;
    I2CPins.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_PIN_PULL_UP;
    I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OUTPUT_SPEED_FAST;

    // SCL
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
    GPIO_Init(&I2CPins);

    // SDA
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
    GPIO_Init(&I2CPins);
}

/*
 * USART2:
 * PA2 -> TX
 * PA3 -> RX
 */
void USART2_GPIOInits(void)
{
    GPIO_Handle_t USARTPins;

    GPIO_PeriClockControl(GPIOA, ENABLE);

    USARTPins.pGPIOx = GPIOA;
    USARTPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    USARTPins.GPIO_PinConfig.GPIO_PinAltFunMode = 7; // AF7
    USARTPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUTPUT_TYPE_PP;
    USARTPins.GPIO_PinConfig.GPIO_PinPupdControl = GPIO_PIN_PULL_UP;
    USARTPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OUTPUT_SPEED_FAST;

    USARTPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    GPIO_Init(&USARTPins);

    USARTPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
    GPIO_Init(&USARTPins);
}


void I2C1_Inits(void)
{
    I2C1Handle.pI2Cx = I2C1;
    I2C1Handle.I2C_Config.I2C_AckControl = I2C_ACK_ENABLE;
    I2C1Handle.I2C_Config.I2C_DeviceAddress = 0x61; // own address
    I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;
    I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;

    I2C_Init(&I2C1Handle);
}

void USART2_Inits(void)
{
    USART2Handle.pUSARTx = USART2;
    USART2Handle.USART_Config.USART_Mode = USART_MODE_ONLY_TX;
    USART2Handle.USART_Config.USART_Baud = USART_STD_BAUD_115200;
    USART2Handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
    USART2Handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
    USART2Handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
    USART2Handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;

    USART_Init(&USART2Handle);
}

void UART_Print(char *msg)
{
    USART_SendData(&USART2Handle, (uint8_t *)msg, strlen(msg));
}
int main(void)
{
    char uart_buf[120];
    SHT40_Data_t sht40_data;
    SHT40_Status_t sht40_status;
    float lux;
    USART2_GPIOInits();
    I2C1_GPIOInits();
    USART2_Inits();
    I2C1_Inits();
    USART_PeripheralControl(USART2, ENABLE);
    I2C_PeripheralControl(I2C1, ENABLE);
    I2C_ManageAcking(I2C1, I2C_ACK_ENABLE);

    UART_Print("SHT40 + VEML6030 application started\r\n");

    while(1)
    {
        sht40_status = SHT40_ReadData(&I2C1Handle, &sht40_data);
        lux = VEML6030_ReadLux(&I2C1Handle);
        if (sht40_status == SHT40_OK)
        {
            sprintf(uart_buf,
                    "Temp: %.2f C | Hum: %.2f %% | Lux: %.2f lx\r\n",
                    sht40_data.temperature,
                    sht40_data.humidity,
                    lux);
        }
        else if (sht40_status == SHT40_CRC_TEMP_ERROR)
        {
            sprintf(uart_buf,
                    "SHT40 ERROR: Temperature CRC failed | Lux: %.2f lx\r\n",
                    lux);
        }
        else if (sht40_status == SHT40_CRC_HUM_ERROR)
        {
            sprintf(uart_buf,
                    "SHT40 ERROR: Humidity CRC failed | Lux: %.2f lx\r\n",
                    lux);
        }
        else
        {
            sprintf(uart_buf,
                    "SHT40 ERROR: Unknown status | Lux: %.2f lx\r\n",
                    lux);
        }

        UART_Print(uart_buf);
        delay();
    }
}



#ifndef INC_STM32F407_I2C_DRIVER_H_
#define INC_STM32F407_I2C_DRIVER_H_

#include "stm32f407.h"

/*
 * Configuration structure for I2Cx peripheral
 */
typedef struct
{
    uint32_t I2C_SCLSpeed;
    uint8_t  I2C_DeviceAddress;
    uint8_t  I2C_AckControl;
    uint8_t  I2C_FMDutyCycle;
} I2C_Config_t;

/*
 * Handle structure for I2Cx peripheral
 * (kept minimal, as in your second code)
 */
typedef struct
{
    I2C_RegDef_t *pI2Cx;
    I2C_Config_t I2C_Config;
    uint8_t      TxRxState;
    uint32_t     RxSize;
} I2C_Handle_t;


/*
 * @I2C_SCLSpeed
 */
#define I2C_SCL_SPEED_SM     100000
#define I2C_SCL_SPEED_FM4K   400000
#define I2C_SCL_SPEED_FM2K   200000

/*
 * @I2C_AckControl
 */
#define I2C_ACK_ENABLE       1
#define I2C_ACK_DISABLE      0

/*
 * @I2C_FMDutyCycle
 */
#define I2C_FM_DUTY_2        0
#define I2C_FM_DUTY_16_9     1

/*
 * I2C related status flags definitions
 * (must match 1st driver)
 */
#define I2C_FLAG_TXE         (1 << I2C_SR1_TXE)
#define I2C_FLAG_RXNE        (1 << I2C_SR1_RXNE)
#define I2C_FLAG_SB          (1 << I2C_SR1_SB)
#define I2C_FLAG_ADDR        (1 << I2C_SR1_ADDR)
#define I2C_FLAG_ADD10       (1 << I2C_SR1_ADD10)
#define I2C_FLAG_STOPF       (1 << I2C_SR1_STOPF)
#define I2C_FLAG_BTF         (1 << I2C_SR1_BTF)
#define I2C_FLAG_BERR        (1 << I2C_SR1_BERR)
#define I2C_FLAG_AF          (1 << I2C_SR1_AF)
#define I2C_FLAG_OVR         (1 << I2C_SR1_OVR)
#define I2C_FLAG_TIMEOUT     (1 << I2C_SR1_TIMEOUT)

/*
 * Repeated START macros
 */
#define I2C_DISABLE_SR       RESET
#define I2C_ENABLE_SR        SET


#define I2C_READY        0
#define I2C_BUSY_IN_RX   1
#define I2C_BUSY_IN_TX   2


/******************************************************************************************
 * APIs supported by this driver
 ******************************************************************************************/

/*
 * Peripheral Clock setup
 */
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);

/*
 * Init and De-init
 */
void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);

/*
 * Other Peripheral Control APIs
 */
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx , uint32_t FlagName);
void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);

/*
 * Data Send and Receive
 */
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,
                        uint8_t *pTxBuffer,
                        uint32_t Len,
                        uint8_t SlaveAddr,
                        uint8_t Sr);

void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle,uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr,uint8_t Sr);

#endif /* INC_STM32F407_I2C_DRIVER_H_ */

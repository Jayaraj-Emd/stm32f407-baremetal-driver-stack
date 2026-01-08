

#ifndef INC_STM32F407_GPIO_DRIVER_H_
#define INC_STM32F407_GPIO_DRIVER_H_

#include <stm32f407.h>

typedef struct{
	uint8_t GPIO_PinNumber;             /*@GPIO PIN NUMBERS*/
	uint8_t GPIO_PinMode;               /*@GPIO_PIN_MODES*/
	uint8_t GPIO_PinSpeed;              /*@GPIO_OUTPUT_PIN_SPEEDS*/
	uint8_t GPIO_PinPupdControl;        /*@GPIO_PUPD_CONFIG*/
	uint8_t GPIO_PinOPType;             /*Possible values @GPIO_OUTPUT_TYPES*/
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;
typedef struct{
	GPIO_RegDef_t *pGPIOx; /*this holds the base address of the PORT*/
	GPIO_PinConfig_t GPIO_PinConfig;

}GPIO_Handle_t;

/*
 * GPIO Possible Modes
 * @GPIO_PIN_MODES
 */
#define GPIO_MODE_IN                    0
#define GPIO_MODE_OUT                   1
#define GPIO_MODE_ALTFN                 2
#define GPIO_MODE_ANALOG                3
/*
 * some possible Interrupt modes while GPIO in INPUT mode
 *
 * */
#define GPIO_MODE_IT_FT                 4  // Falling edge
#define GPIO_MODE_IT_RT                 5  // Raising edge
#define GPIO_MODE_IT_RFT                6  //Raising and falling edge trigger

/*
 * GPIO Possible output types
 * @GPIO_OUTPUT_TYPES
 */
#define GPIO_OUTPUT_TYPE_PP             0
#define GPIO_OUTPUT_TYPE_OD             1

/*
 * @GPIO_OUTPUT_PIN_SPEEDS
 * GPIO possible output SPEEDs
 */
#define GPIO_OUTPUT_SPEED_LOW           0
#define GPIO_OUTPUT_SPEED_MEDIUM        1
#define GPIO_OUTPUT_SPEED_FAST          2
#define GPIO_OUTPUT_SPEED_HIGH          3

/*
 * GPIO possible pull-up and pull-down configuration
 * @GPIO_PUPD_CONFIG
 */
#define GPIO_PIN_NO_PUPD                0
#define GPIO_PIN_PULL_UP                1
#define GPIO_PIN_PULL_DOWN              2

/*
 * @GPIO PIN NUMBERS
 */
#define GPIO_PIN_NO_0                   0
#define GPIO_PIN_NO_1                   1
#define GPIO_PIN_NO_2                   2
#define GPIO_PIN_NO_3                   3
#define GPIO_PIN_NO_4                   4
#define GPIO_PIN_NO_5                   5
#define GPIO_PIN_NO_6                   6
#define GPIO_PIN_NO_7                   7
#define GPIO_PIN_NO_8                   8
#define GPIO_PIN_NO_9                   9
#define GPIO_PIN_NO_10                  10
#define GPIO_PIN_NO_11                  11
#define GPIO_PIN_NO_12                  12
#define GPIO_PIN_NO_13                  13
#define GPIO_PIN_NO_14                  14
#define GPIO_PIN_NO_15                  15

/*
 * APIs supported by this driver
 */
/*
 * Peripheral Clock setup
 */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);
/*
 * Init and De-init
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);


/*
 * Data read and write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

#endif /* INC_STM32F407_GPIO_DRIVER_H_ */

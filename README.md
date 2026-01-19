
STM32F407 Bare-Metal Driver Stack

---------------------------------------------------------------
Overview
---------------------------------------------------------------
This repository contains a bare-metal firmware driver stack
developed for the STM32F407 Cortex-M4 microcontroller.
The project is implemented without STM32 HAL or CubeMX-
generated code and focuses on register-level peripheral
control, protocol correctness, and modular firmware design.

Custom GPIO, I2C, and USART drivers are implemented from
scratch. An application layer is built on top of these drivers
to interface environmental sensors over I2C and transmit
processed sensor data to a PC terminal using UART.

---------------------------------------------------------------
Hardware Platform
---------------------------------------------------------------
MCU   : STM32F407VG (Cortex-M4 with FPU)
Board : STM32F407 Discovery

Sensors:
- SHT40  Temperature and Humidity Sensor (I2C)
- VEML6030 Ambient Light Sensor (I2C)

Communication Interfaces:
- I2C  (Master mode)
- UART (Telemetry output)

---------------------------------------------------------------
Key Features
---------------------------------------------------------------
- Fully bare-metal GPIO, I2C, and USART drivers
- No STM32 HAL, LL, or CubeMX-generated code
- Blocking I2C master implementation
- Correct handling of START, STOP, and Repeated START
- ACK / NACK management as per STM32 reference manual
- CRC-8 validation for SHT40 sensor data
  - Polynomial     : 0x31
  - Initial Value  : 0xFF
- Error-aware application logic with CRC status reporting
- Floating-point sensor computation using hardware FPU
- UART logging with float formatting enabled
- Clear separation between driver and application layers
- Clean, modular, and extensible firmware design

---------------------------------------------------------------
Driver Architecture
---------------------------------------------------------------

GPIO Driver
- Input, output, and alternate-function modes
- Configurable output type and speed
- Pull-up and pull-down control
- Register-level configuration

I2C Driver
- Master-mode operation
- START, STOP, and Repeated START handling
- ACK and NACK management
- Blocking transmit and receive APIs
- Designed for strict sensor-level protocol correctness

USART Driver
- Configurable baud rate, word length, parity, and stop bits
- Blocking transmit and receive
- UART-based telemetry output

---------------------------------------------------------------
Sensor Integration
---------------------------------------------------------------

SHT40 – Temperature and Humidity Sensor
- High-precision measurement mode
- STOP condition enforced before conversion start
- CRC-8 validation for temperature and humidity data
- Status-based error reporting to application layer

VEML6030 – Ambient Light Sensor
- Register-based I2C communication
- Lux conversion using datasheet scaling factors
- Combined write and read transaction using Repeated START

---------------------------------------------------------------
Project Structure
---------------------------------------------------------------
```
stm32f407-baremetal-driver-stack/
├── Core/
│   ├── Src/
│   │   ├── main.c
│   │   ├── sht40.c
│   │   └── veml6030.c
│   └── Inc/
│       ├── main.h
│       ├── sht40.h
│       └── veml6030.h
│
├── driver/
│   ├── Inc/
│   │   ├── stm32f407_gpio_driver.h
│   │   ├── stm32f407_i2c_driver.h
│   │   └── stm32f407_usart_driver.h
│   └── Src/
│       ├── stm32f407_gpio_driver.c
│       ├── stm32f407_i2c_driver.c
│       └── stm32f407_usart_driver.c
│
├── Startup/
│   └── startup_stm32f407vgtx.s
│
├── STM32F407VGTX_FLASH.ld
├── README.md
└── .gitignore
```

---------------------------------------------------------------
UART Output Example
---------------------------------------------------------------
Temp: 26.45 C | Hum: 48.12 % | Lux: 123.40 lx

CRC Error Example:
SHT40 ERROR: Temperature CRC failed | Lux: 123.40 lx

---------------------------------------------------------------
Toolchain and Build Configuration
---------------------------------------------------------------
IDE        : STM32CubeIDE
Compiler   : ARM GCC
Build Type : Bare-metal (No RTOS)
FPU        : FPv4-SP-D16 (Hard ABI)

Printf Float Support:
-u _printf_float

Linker Script:
Custom STM32F407 memory layout

---------------------------------------------------------------
How to Build and Run
---------------------------------------------------------------
1. Open the project in STM32CubeIDE
2. Enable FPU (FPv4-SP-D16, Hard ABI)
3. Enable float formatting for printf
4. Build the project
5. Flash to STM32F407 Discovery board
6. Monitor UART output at 115200 baud

---------------------------------------------------------------

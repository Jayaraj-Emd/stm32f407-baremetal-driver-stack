# stm32f407-baremetal-driver-stack

Bare-metal driver stack for the STM32F407 microcontroller providing:
- GPIO driver
- I2C driver (SHT40, VEML6030 sensor interfaces with CRC checks)
- USART driver for UART telemetry

---

## Table of contents
- [Features](#features)
- [Repository structure](#repository-structure)
- [Hardware](#hardware)
- [Quick start (build & flash)](#quick-start-build--flash)
- [Usage example](#usage-example)
- [Driver API highlights](#driver-api-highlights)
- [Development notes](#development-notes)
- [Contributing](#contributing)
- [License](#license)

---

## Features
- Minimal, readable, bare-metal drivers for peripherals common to STM32 projects: GPIO, I2C, USART
- Sensor examples and verified reads for SHT40 (temperature & humidity) and VEML6030 (ambient light)
- Example application demonstrating periodic sensor reads and UART telemetry in `Src/main.c`

## Repository structure
- `driver/` — low-level peripheral drivers (headers in `driver/Inc`, sources in `driver/Src`)
- `Src/` — application code and sensor drivers (`main.c`, `sht40.c`, `veml6030.c`)
- `Inc/` — public headers used by the application
- `Startup/` — startup files and vector table
- Linker scripts: `STM32F407VGTX_FLASH.ld`, `STM32F407VGTX_RAM.ld`

## Hardware
- MCU: STM32F407VGTx (Cortex-M4)
- Example sensors used:
  - SHT40 (I2C)
  - VEML6030 (I2C)
- Default pin mappings used by the example (`Src/main.c`):
  - I2C1: PB6 (SCL), PB7 (SDA)
  - USART2: PA2 (TX), PA3 (RX)

## Quick start (build & flash)
Prerequisites:
- ARM toolchain (e.g., `arm-none-eabi-gcc`)
- OpenOCD or ST-Link utilities (`st-flash`, `openocd`) for flashing

Example (one-off) build using `arm-none-eabi-gcc`:

```sh
# create build dir
mkdir -p build

# compile and link (adjust flags as needed)
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -TSTM32F407VGTX_FLASH.ld \
  Src/*.c driver/Src/*.c Startup/*.s \
  -IInc -Idriver/Inc \
  -Os -ffunction-sections -fdata-sections -Wl,--gc-sections \
  -o build/firmware.elf

# create binary
arm-none-eabi-objcopy -O binary build/firmware.elf build/firmware.bin

# flash (example using st-flash)
st-flash write build/firmware.bin 0x8000000
```

Notes:
- You can also import this project into STM32CubeIDE or Keil and configure a project using the provided startup and linker scripts.
- If you prefer `openocd`, use an appropriate `openocd` command or a tool like `st-link`.

## Usage example
The example application in `Src/main.c` demonstrates how to:
1. Initialize GPIO pins for I2C and USART
2. Configure and enable I2C1 and USART2
3. Read sensor values and print telemetry via UART

Key lines to inspect for usage:
- `USART2_GPIOInits()`, `I2C1_GPIOInits()` — GPIO configuration
- `I2C1_Inits()`, `USART2_Inits()` — peripheral configuration
- `SHT40_ReadData(&I2C1Handle, &sht40_data)` and `VEML6030_ReadLux(&I2C1Handle)` — sensor reads

Example output (UART):
```
Temp: 23.45 C | Hum: 45.12 % | Lux: 123.45 lx
```

## Driver API highlights
- I2C:
  - `I2C_Init`, `I2C_PeripheralControl`, `I2C_MasterSendData`, `I2C_MasterReceiveData`
- USART:
  - `USART_Init`, `USART_SendData`, `USART_PeripheralControl`
- GPIO:
  - `GPIO_Init`, `GPIO_WriteToOutputPin`, `GPIO_ReadFromInputPin`

See header files in `driver/Inc` for full definitions and comments.

## Development notes
- This is a small, bare-metal codebase (no RTOS). Keep changes focused and test on hardware.
- Add unit tests as simple host-executable tests (e.g., harness in `tests/`) if you want CI-friendly checks; hardware integration tests should be run on a board.
- Consider adding a `Makefile` or CMake setup for repeatable builds.

## Contributing
- Open issues for bugs or feature requests
- Prefer small, focused PRs with clear descriptions and a test plan (hardware test steps or expected output logs)

## License
No license file is included in the repository. If you are the project owner, add a `LICENSE` (e.g., MIT) to make the terms explicit.

---

Maintainer: repository owner

If you'd like, I can also add a `CONTRIBUTING.md`, a `Makefile` for GCC builds, or a CI job that builds the firmware on each PR — tell me which you'd like next.

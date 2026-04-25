# STM32 Bare-Metal Interrupt & GPIO Driver

This repository contains bare-metal firmware for the **STM32F103CB (Cortex-M3)**. It demonstrates low-level hardware interaction by bypassing HAL and interacting directly with memory-mapped registers.

## 🛠️ Function Documentation

### 1. GPIO Driver (`gpio_drive.c`)
* **`init_GP(port, pin, dir, opt)`**: Initializes a GPIO pin by enabling the APB2 clock and configuring the CRL/CRH registers based on pin mapping (0-7 vs 8-15).
* **`W_GP(port, pin, state)`**: Writes to the Output Data Register (ODR) to set a pin HIGH or LOW.
* **`R_GP(port, pin)`**: Reads the Input Data Register (IDR) and masks the target pin to check its logic state.

### 2. Systick Timer (`systick.c`)
* **`systick_init()`**: Sets up the basic SysTick control and reload registers for simple timing.
* **`systick_inr_start()`**: Configures the SysTick timer to trigger a `SysTick_Handler` interrupt every 1ms (72,000 cycles at 72MHz).
* **`get_current_ms()`**: Returns the `msTicks` variable, which tracks elapsed time for debouncing and pattern timing.

### 3. Application Logic (`main.c`)
* **`EXTI0_IRQHandler()`**: An Interrupt Service Routine (ISR) that increments a pattern counter when a button is pressed on PA0, including a 50ms software debounce check.
* **`main()`**: Initializes peripherals, configures the NVIC for EXTI0, and runs a state machine to cycle LED patterns on PA10, PA11, and PA12.

## 🚀 Usage
1. Open the project in Keil uVision.
2. Connect your STM32 via ST-Link.
3. Flash the firmware to cycle through LED patterns using the on-board button.

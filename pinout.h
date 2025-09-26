#pragma once
// Pinbelegung für Waveshare ESP32-C6 LCD 1.47"

// --- LCD (ST7789 / SPI) ---
#define LCD_DIN    6   // IO6  - LCD DIN
#define LCD_CLK    7   // IO7  - LCD CLK
#define LCD_CS     14  // IO14 - LCD Chip Select
#define LCD_DC     15  // IO15 - Data/Command
#define LCD_RST    21  // IO21 - Reset
#define LCD_BL     22  // IO22 - Backlight (PWM möglich!!!)

// --- UART ---
#define UART_TX    17  // TXD
#define UART_RX    16  // RXD

// --- Besondere GPIOs laut Board-Pinout ---
#define PIN_BOOT   9   // IO9  - Boot/Download
#define PIN_RGB    8   // IO8  - On-board RGB LED
#define PIN_USB_N  12  // IO12 - USB D-
#define PIN_USB_P  13  // IO13 - USB D+

// --- Analog Inputs (ADC) ---
#define ADC_SENSOR_1  0   // USER_GPIO1 (IO0)
#define ADC_SENSOR_2  1   // USER_GPIO2 (IO1)
#define ADC_SENSOR_3  2   // USER_GPIO3 (IO2)
#define ADC_SENSOR_4  3   // USER_GPIO4 (IO3)

// --- Digital Inputs ---
#define DIGITAL_INPUT_1  18  // USER_GPIO6 (IO18)
#define DIGITAL_INPUT_2  19  // USER_GPIO7 (IO19)
#define DIGITAL_INPUT_3  20  // USER_GPIO8 (IO20)
#define DIGITAL_INPUT_4  23  // USER_GPIO9 (IO23)
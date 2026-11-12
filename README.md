# ESP32_C3_LCD_1in47

Arduino library for the **ESP32-C3 1.47-inch LCD board**. This library wraps the board-specific ST7789 display setup and onboard I/O-expander functions behind a small C++ interface.

> **Board-specific library:** This project targets the ESP32-C3 1.47-inch LCD hardware for which it was developed. It is not a generic ST7789 driver.

## Features

- Initializes the onboard 1.47-inch display panel through the board-specific configuration.
- Provides access to the graphics object through `gfx()` (Arduino_GFX API).
- Controls the LCD backlight.
- Selects the LCD and SD-card chip-select lines through the onboard I/O expander.
- Provides BOOT-button state reading.
- Exposes the I/O-expander helper functions declared in `io_extension.h`.

## Requirements

- ESP32-C3 1.47-inch LCD board
- Arduino IDE 2.x (or a compatible Arduino build environment)
- **Espressif Arduino-ESP32 board package 3.x**
- **GFX Library for Arduino** (`Arduino_GFX_Library`)

The ESP32 Arduino Core 3.x requirement is important: this library uses the ESP-IDF I2C master driver API provided through `driver/i2c_master.h`.

Install **GFX Library for Arduino** from the Arduino IDE Library Manager before compiling sketches that use this library. When installed through a compatible Library Manager, the `depends` metadata may also be used to identify this dependency.

## Installation (ZIP)

1. Download this repository as a ZIP (or download the ZIP attached to a GitHub Release).
2. In Arduino IDE, select **Sketch → Include Library → Add .ZIP Library…**.
3. Select the downloaded ZIP file.
4. Select the ESP32-C3 board from **Tools → Board** and make sure the Espressif Arduino-ESP32 3.x platform is installed.
5. Install **GFX Library for Arduino** from Library Manager if it is not already installed.

## Quick start

```cpp
#include <ESP32_C3_LCD_1in47.h>

ESP32_C3_LCD_1in47 display;

void setup()
{
  Serial.begin(115200);

  if (!display.begin())
  {
    Serial.printf("Display initialization failed. ESP error: %d\n",
                  (int)display.lastError());
    while (true)
    {
      delay(1000);
    }
  }

  Arduino_GFX *gfx = display.gfx();
  gfx->fillScreen(0x0000);
  gfx->setTextColor(0xFFFF);
  gfx->setTextSize(2);
  gfx->setCursor(10, 20);
  gfx->println("Hello, ESP32-C3!");
}

void loop()
{
  // Your application code
}
```

A matching sketch is available in [`examples/Basic`](examples/Basic/Basic.ino).

## Public API

The main class is `ESP32_C3_LCD_1in47`:

| Method | Description |
|---|---|
| `begin(brightness, speed)` | Initializes the I/O expander and LCD. Brightness is 0–100; SPI speed defaults to 80 MHz. |
| `gfx()` | Returns the underlying `Arduino_GFX*` graphics object. |
| `setBacklight(value)` | Sets backlight brightness from 0–100. |
| `beginSD(spi, cs, hz)` | Initializes the SPI interface for the SD card. |
| `selectLCD()` | Selects the LCD through the onboard I/O expander. |
| `selectSD()` | Selects the SD card through the onboard I/O expander. |
| `bootPressed()` | Returns `true` while the BOOT button is pressed. |
| `lastError()` | Returns the most recent ESP-IDF error code. |

For the lower-level I/O-expander functions, see `src/io_extension.h`.

## Compatibility and testing status

- Target architecture: `esp32` (including ESP32-C3).
- Required ESP32 Arduino Core family: 3.x.
- Required graphics dependency: GFX Library for Arduino.
- This repository has been packaged for Arduino library layout. A successful compile and on-device hardware test have **not** yet been claimed for this release. Please test with the exact board and report the board-package and graphics-library versions when opening an issue.

## License

MIT. See [LICENSE](LICENSE).

## GitHub

[ESP32_C3_LCD_1in47 – GitHub Repository](https://github.com/Ysrabyab/ESP32_C3_LCD_1in47)
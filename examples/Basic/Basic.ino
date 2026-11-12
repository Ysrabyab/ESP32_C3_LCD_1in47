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
  // Add your application code here.
}

# ESP32_C3_LCD_1in47

**ESP32-C3 1.47 inç LCD geliştirme kartı için Arduino kütüphanesi.**

---

# 🇹🇷 TÜRKÇE

## Merhaba!

Bu projeyi, ESP32-C3 1.47 inç LCD geliştirme kartını Arduino IDE üzerinden daha kolay kullanabilmek için hazırladım.

Amacım; ekranı başlatmak, arka ışığı kontrol etmek, SD kart arayüzünü kullanmak ve kart üzerindeki bazı donanım bileşenlerine erişmek için tekrar tekrar aynı kodları yazmak zorunda kalmamanız.

Kısacası, gerekli işlemleri tek bir kütüphane altında topladım. Böylece kendi projelerinize daha rahat odaklanabilirsiniz.

## Neler Yapabiliyor?

- 1.47 inç LCD ekranı başlatma.
- Ekrana grafik ve metin çizme.
- Ekran arka ışığının parlaklığını ayarlama.
- LCD ve SD kart arayüzleri arasında seçim yapma.
- SD kart SPI bağlantısını başlatma.
- Kart üzerindeki BOOT butonunun durumunu okuma.
- I/O genişletici üzerinden düşük seviyeli işlemler gerçekleştirme.

**Not:** Bu kütüphane genel amaçlı bütün ST7789 ekranlar için değil, ESP32-C3 1.47 inç LCD geliştirme kartının donanım yapısı için hazırlanmıştır.

## Gereksinimler

**Donanım**
- ESP32-C3 1.47 inç LCD geliştirme kartı.

**Yazılım**
- Arduino IDE 2.x
- Espressif Arduino-ESP32 Core 3.x
- GFX Library for Arduino (`Arduino_GFX_Library`)

Arduino-ESP32 Core 3.x kullanılması gerekiyor. Çünkü kütüphane ESP-IDF'nin yeni I2C master sürücüsünü kullanıyor.

## Kurulum

### Yöntem 1: ZIP dosyası ile kurulum (Önerilen)

En kolay yöntem bu. Git veya GitHub Desktop kurmanıza gerek yok.

1. Bu GitHub deposunu açın.
2. Yeşil **Code** butonuna tıklayın.
3. **Download ZIP** seçeneğini seçin.
4. İndirdiğiniz ZIP dosyasını bilgisayarınıza çıkarın.
5. Arduino IDE'yi açın.
6. **Sketch → Include Library → Add .ZIP Library...** yolunu izleyin.
7. İndirdiğiniz ZIP dosyasını seçin.

Kurulum tamamlandığında kütüphaneniz kullanıma hazır!

### Gerekli bağımlılıkların kurulması

Kütüphaneyi kullanmadan önce şu işlemleri de yapmanız gerekiyor:

1. Arduino IDE içerisindeki Library Manager bölümünü açın.
2. `GFX Library for Arduino` araması yapın.
3. Kütüphaneyi yükleyin.
4. Boards Manager üzerinden Espressif Arduino-ESP32 platformunun 3.x sürümünü yükleyin.
5. Uygun ESP32-C3 kartını seçin.

## İlk Deneme

Kurulumun başarılı olup olmadığını görmek için aşağıdaki örneği deneyebilirsiniz.

```cpp
#include <ESP32_C3_LCD_1in47.h>

ESP32_C3_LCD_1in47 display;

void setup()
{
    Serial.begin(115200);

    if (!display.begin())
    {
        Serial.printf(
            "Display initialization failed. ESP error: %d\n",
            (int)display.lastError()
        );

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
}
```

Ayrıca bu örneği proje içerisindeki şu dizinde de bulabilirsiniz:

`examples/Basic/Basic.ino`

## Kullanılabilir Fonksiyonlar

| Fonksiyon | Açıklama |
|---|---|
| `ESP32_C3_LCD_1in47()` | Ekran nesnesini oluşturur. Varsayılan dönüş değeri 4'tür. |
| `begin(brightness, speed)` | Ekranı ve I/O genişleticiyi başlatır. |
| `gfx()` | Arduino_GFX grafik nesnesini döndürür. |
| `setBacklight(value)` | Arka ışık parlaklığını ayarlar (0–100). |
| `beginSD(spi, cs, hz)` | SD kart SPI arayüzünü başlatır. |
| `selectLCD()` | LCD arayüzünü seçer. |
| `selectSD()` | SD kart arayüzünü seçer. |
| `bootPressed()` | BOOT butonunun durumunu okur. |
| `lastError()` | Son ESP-IDF hata kodunu döndürür. |

### Varsayılan Değerler

- Ekran parlaklığı: `100`
- SPI hızı: `80 MHz`
- SD kart CS pini: `GPIO 10`
- SD kart SPI frekansı: `1 MHz`
- Ekran dönüşü: `4`

I/O genişleticinin düşük seviyeli fonksiyonları için `src/io_extension.h` dosyasına göz atabilirsiniz.

## Sık Karşılaşılan Sorunlar

**Kütüphane zaten yüklü hatası**

Arduino IDE, bilgisayarınızda aynı isimli başka bir sürüm bulunduğunu söylüyorsa:

1. Arduino IDE'yi kapatın.
2. Arduino sketchbook klasörünüzdeki `libraries` dizinine gidin.
3. `ESP32_C3_LCD_1in47` klasörünü bulun.
4. Eski sürümü yedekleyin veya kaldırın.
5. Yeni ZIP dosyasını tekrar yükleyin.

**Arduino_GFX_Library bulunamadı hatası**

Library Manager üzerinden GFX Library for Arduino kütüphanesini yükleyin.

**ESP-IDF I2C sürücüsüyle ilgili hatalar**

Espressif Arduino-ESP32 Core sürümünüzün 3.x olduğundan emin olun.

**Ekran başlatılamıyor**

Doğru ESP32-C3 1.47 inç LCD kartını kullandığınızı ve uygun kart paketinin yüklü olduğunu kontrol edin.

## Proje Yapısı

```text
ESP32_C3_LCD_1in47/
│
├── examples/
│   └── Basic/
│       └── Basic.ino
│
├── src/
│   ├── ESP32_C3_LCD_1in47.h
│   ├── ESP32_C3_LCD_1in47.cpp
│   └── io_extension.h
│
├── library.properties
├── LICENSE
└── README.md
```

## Geliştirmeye Katkı

Bu projeyi geliştirmek için önerileriniz, hata bildirimleriniz ve katkılarınız benim için değerli.

Bir sorunla karşılaşırsanız veya geliştirilmesini istediğiniz bir özellik varsa GitHub üzerinden Issue açabilirsiniz.

## Lisans

Bu proje MIT Lisansı kapsamında yayımlanmıştır. Ayrıntılar için `LICENSE` dosyasına bakabilirsiniz.

---

# 🇬🇧 ENGLISH

## Hello!

I developed this library to make the ESP32-C3 1.47-inch LCD development board easier to use with Arduino IDE.

The goal is to avoid writing the same initialization and hardware control code repeatedly. The library brings together display initialization, backlight control, SD card interface management, and access to onboard hardware components.

This allows you to focus more on your own projects instead of dealing with repetitive setup code.

## Features

- Initialize the onboard 1.47-inch LCD.
- Draw graphics and text on the display.
- Control LCD backlight brightness.
- Select between LCD and SD card interfaces.
- Initialize the SD card SPI interface.
- Read the onboard BOOT button state.
- Access low-level I/O expander functions.

**Note:** This library is designed specifically for the ESP32-C3 1.47-inch LCD development board. It is not intended as a generic driver for all ST7789 displays.

## Requirements

**Hardware**
- ESP32-C3 1.47-inch LCD development board.

**Software**
- Arduino IDE 2.x
- Espressif Arduino-ESP32 Core 3.x
- GFX Library for Arduino (`Arduino_GFX_Library`)

Arduino-ESP32 Core 3.x is required because this library uses the newer ESP-IDF I2C master driver API.

## Installation

### Method 1: Install from ZIP (Recommended)

You don't need Git or GitHub Desktop to install this library.

1. Open this GitHub repository.
2. Click the green **Code** button.
3. Select **Download ZIP**.
4. Download and extract the ZIP archive.
5. Open Arduino IDE.
6. Navigate to **Sketch → Include Library → Add .ZIP Library...**
7. Select the downloaded ZIP archive.

That's it! The library is ready to use.

### Installing Dependencies

Before using the library:

1. Open Library Manager in Arduino IDE.
2. Search for `GFX Library for Arduino`.
3. Install the library.
4. Install Espressif Arduino-ESP32 Core 3.x through Boards Manager.
5. Select the appropriate ESP32-C3 board.

## Quick Start

Use the following example to test your installation.

```cpp
#include <ESP32_C3_LCD_1in47.h>

ESP32_C3_LCD_1in47 display;

void setup()
{
    Serial.begin(115200);

    if (!display.begin())
    {
        Serial.printf(
            "Display initialization failed. ESP error: %d\n",
            (int)display.lastError()
        );

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
}
```

You can also find this example in:

`examples/Basic/Basic.ino`

## Public API Reference

| Function | Description |
|---|---|
| `ESP32_C3_LCD_1in47()` | Creates the display object. Default rotation is 4. |
| `begin(brightness, speed)` | Initializes the display and I/O expander. |
| `gfx()` | Returns the Arduino_GFX graphics object. |
| `setBacklight(value)` | Sets backlight brightness (0–100). |
| `beginSD(spi, cs, hz)` | Initializes the SD card SPI interface. |
| `selectLCD()` | Selects the LCD interface. |
| `selectSD()` | Selects the SD card interface. |
| `bootPressed()` | Reads the onboard BOOT button state. |
| `lastError()` | Returns the most recent ESP-IDF error code. |

### Default Parameters

- Brightness: `100`
- SPI speed: `80 MHz`
- SD chip select: `GPIO 10`
- SD SPI frequency: `1 MHz`
- Display rotation: `4`

For low-level I/O expander functions, see `src/io_extension.h`.

## Troubleshooting

**Library is already installed**

If Arduino IDE reports that a different version of the library is already installed:

1. Close Arduino IDE.
2. Open your Arduino sketchbook's `libraries` directory.
3. Locate the `ESP32_C3_LCD_1in47` folder.
4. Back up or remove the old version.
5. Install the new ZIP archive again.

**Arduino_GFX_Library not found**

Install GFX Library for Arduino through Library Manager.

**ESP-IDF I2C driver errors**

Make sure you are using Espressif Arduino-ESP32 Core 3.x.

**Display initialization fails**

Check that you are using the intended ESP32-C3 1.47-inch LCD hardware and that the correct board platform is installed.

## Project Structure

```text
ESP32_C3_LCD_1in47/
│
├── examples/
│   └── Basic/
│       └── Basic.ino
│
├── src/
│   ├── ESP32_C3_LCD_1in47.h
│   ├── ESP32_C3_LCD_1in47.cpp
│   └── io_extension.h
│
├── library.properties
├── LICENSE
└── README.md
```

## Contributing

Suggestions, bug reports, and contributions are welcome.

If you encounter a problem or have an idea for improvement, feel free to open an Issue in this repository.

## License

This project is distributed under the MIT License. See the `LICENSE` file for details.

---

**Repository:** https://github.com/Ysrabyab/ESP32_C3_LCD_1in47

# GxEPD
A simple E-Paper display library with common base class and separate IO class for Arduino framework.

## For SPI e-paper 1.54" 3-color board from Waveshare (https://www.waveshare.com/wiki/1.54inch_e-Paper_Module_(B))

### important note :
### - these displays are for 3.3V supply and 3.3V data lines
### - never connect data lines directly to 5V Arduino data pins, you may use e.g. 4k7 series resistor
### - do not forget to connect GND

### Paged Drawing, Picture Loop for AVR
#### - This library uses paged drawing to cope with RAM restriction and missing single pixel update support
#### - Paged drawing is implemented using callbacks to callback functions in the user application code,
#### - the picture loop is internal to the display classes and calls the callback function as many times as needed,
#### - this is a different implementation compared to the picture loop in U8G2 (Oliver Kraus)
#### - see also https://github.com/olikraus/u8glib/wiki/tpictureloop


### The E-Paper display base class is a subclass of Adafruit_GFX, to have graphics and text rendering.

It needs up to 30kB available RAM to buffer the black/white image for the SPI displays.
ESP8266 or STM32 systems have just enough free RAM, e.g. Arduino Due, ESP8266 or STM32.
- Paged Drawing is available to cope with RAM restriction on AVR processors.

### Supporting Arduino Forum Topics:

- Waveshare e-paper displays with SPI: http://forum.arduino.cc/index.php?topic=487007.0
- Good Dispay ePaper for Arduino : https://forum.arduino.cc/index.php?topic=436411.0

Initial support is for E-Paper displays from Dalian Good Display Inc. with SPI:

The following classes can be used with Waveshare e-Paper displays:
- The GxGDEP015OC1 class can be used with Waveshare 1.54inch e-Paper SPI display.

Support for partial update and paged drawing (AVR, low RAM).
- To use on AVR (UNO, NANO) Arduino IDE 1.8.x is required (optimizing linker) for code space.

mapping suggestion from Waveshare SPI e-Paper to Wemos D1 mini:
- BUSY -> D2, RST -> D4, DC -> D3, CS -> D8, CLK -> D5, DIN -> D7, GND -> GND, 3.3V -> 3.3V

mapping suggestion from Waveshare SPI e-Paper to ESP8266 NodeMCU:
- BUSY -> D2, RST -> D4, DC -> D3, CS -> D8, CLK -> D5, DIN -> D7, GND -> GND, 3.3V -> 3.3V

mapping suggestion from Waveshare SPI e-Paper to generic ESP8266:
- BUSY -> GPIO4, RST -> GPIO2, DC -> GPIO0, CS -> GPIO15, CLK -> GPIO14, DIN -> GPIO13, GND -> GND, 3.3V -> 3.3V

mapping suggestion (by G6EJD) from Waveshare SPI e-Paper to ESP8266 Huzzah:
- BUSY -> 03, RST -> 15, DC -> 02, CS -> 00, CLK -> 14, DIN -> 13, GND -> GND, 3.3V -> 3.3V

new mapping suggestion for STM32F1, e.g. STM32F103C8T6 "BluePill"
- BUSY -> A1, RST -> A2, DC -> A3, CS-> A4, CLK -> A5, DIN -> A7

mapping example for AVR, UNO, NANO etc.:
- BUSY -> 7, RST -> 9, DC -> 8, C S-> 10, CLK -> 13, DIN -> 11

Added classes for Waveshare and Good Display black / white / red SPI e-Paper displays:
- GxGDEW0154Z04 1.54 inch 200 x 200 3 color SPI display

Added Support for multiple e-paper displays on one Arduino (with enough RAM, e.g. ESP32)

### Version 2.3.6
- fixes and cleanup
#### Version 2.3.5
- GxFont_GFX : Font Rendering Graphics Switch and Bridge Class
--------------------------------------------------------------------------------------------
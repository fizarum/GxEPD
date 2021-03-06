// GxFont_GFX_Example : example to show the use of additional fonts rendering these fonts
//
// Author : J-M Zingg
//
// Version : see library.properties
//
// License: GNU GENERAL PUBLIC LICENSE V3, see LICENSE
//
// Library: https://github.com/ZinggJM/GxEPD

// for use of additional fonts you need to enable these in file GxFont_GFX.h
// and install the library
//
// selection of the additional fonts is done by the following methods:
//
// void setFont(const uint8_t *font); // selects rendering and fonts from library U8G2_FOR_ADAFRUIT_GFX
//
// void setFreeFont(const GFXfont *f = NULL); // selects rendering and fonts from library GxFont_GFX_TFT_eSPI
// void void setTextFont(uint8_t font); // selects rendering and fonts from library GxFont_GFX_TFT_eSPI
//
// void setFont(uint8_t f); // selects rendering and fonts from library Adafruit_tfGFX
// (no additional fonts, as all are now part of Adafruit_GFX)
//
// void setFont(const GFXfont *f = NULL); // reverts back to Adafruit_GFX FreeFonts
// use setFont((void*)NULL); // to select Adafruit_GFX classic font
//
// these additions may not work with AVR Arduinos
//
// these additions are only partially tested; more tests and additions may follow

// Supporting Arduino Forum Topics:
// Waveshare e-paper displays with SPI: http://forum.arduino.cc/index.php?topic=487007.0
// Good Dispay ePaper for Arduino : https://forum.arduino.cc/index.php?topic=436411.0

// mapping suggestion from Waveshare SPI e-Paper to Wemos D1 mini
// BUSY -> D2, RST -> D4, DC -> D3, CS -> D8, CLK -> D5, DIN -> D7, GND -> GND, 3.3V -> 3.3V

// mapping suggestion from Waveshare SPI e-Paper to generic ESP8266
// BUSY -> GPIO4, RST -> GPIO2, DC -> GPIO0, CS -> GPIO15, CLK -> GPIO14, DIN -> GPIO13, GND -> GND, 3.3V -> 3.3V

// mapping suggestion for ESP32, e.g. LOLIN32, see .../variants/.../pins_arduino.h for your board
// NOTE: there are variants with different pins for SPI ! CHECK SPI PINS OF YOUR BOARD
// BUSY -> 4, RST -> 16, DC -> 17, CS -> SS(5), CLK -> SCK(18), DIN -> MOSI(23), GND -> GND, 3.3V -> 3.3V

// new mapping suggestion for STM32F1, e.g. STM32F103C8T6 "BluePill"
// BUSY -> A1, RST -> A2, DC -> A3, CS-> A4, CLK -> A5, DIN -> A7

// mapping suggestion for AVR, UNO, NANO etc.
// BUSY -> 7, RST -> 9, DC -> 8, CS-> 10, CLK -> 13, DIN -> 11

// include library, include base class, make path known
#include <GxEPD.h>

// select the display class to use, only one
//#include <GxGDEP015OC1/GxGDEP015OC1.cpp>    // 1.54" b/w
//#include <GxGDEW0154Z04/GxGDEW0154Z04.cpp>  // 1.54" b/w/r
//#include <GxGDE0213B1/GxGDE0213B1.cpp>      // 2.13" b/w
//#include <GxGDEW0213Z16/GxGDEW0213Z16.cpp>  // 2.13" b/w/r
//#include <GxGDEH029A1/GxGDEH029A1.cpp>      // 2.9" b/w
//#include <GxGDEW029Z10/GxGDEW029Z10.cpp>    // 2.9" b/w/r
//#include <GxGDEW027C44/GxGDEW027C44.cpp>    // 2.7" b/w/r
//#include <GxGDEW027W3/GxGDEW027W3.cpp>      // 2.7" b/w
#include <GxGDEW042T2/GxGDEW042T2.cpp>      // 4.2" b/w
//#include <GxGDEW042Z15/GxGDEW042Z15.cpp>    // 4.2" b/w/r
//#include <GxGDEW075T8/GxGDEW075T8.cpp>      // 7.5" b/w

#if !defined(_GxFont_GFX_TFT_eSPI_H_)
// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
//#include <Fonts/FreeMonoBold18pt7b.h>
//#include <Fonts/FreeMonoBold24pt7b.h>
#endif
#if defined(_ADAFRUIT_TF_GFX_H_)
#include <Fonts/Open_Sans_Bold_12pt.h>
#endif


#include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
#include <GxIO/GxIO.cpp>

#if defined(ESP8266)

// generic/common.h
//static const uint8_t SS    = 15;
//static const uint8_t MOSI  = 13;
//static const uint8_t MISO  = 12;
//static const uint8_t SCK   = 14;
// pins_arduino.h
//static const uint8_t D8   = 15;
//static const uint8_t D7   = 13;
//static const uint8_t D6   = 12;
//static const uint8_t D5   = 14;

// GxIO_SPI(SPIClass& spi, int8_t cs, int8_t dc, int8_t rst = -1, int8_t bl = -1);
GxIO_Class io(SPI, SS, 0, 2); // arbitrary selection of D3(=0), D4(=2), selected for default of GxEPD_Class
// GxGDEP015OC1(GxIO& io, uint8_t rst = 2, uint8_t busy = 4);
GxEPD_Class display(io); // default selection of D4(=2), D2(=4)

#elif defined(ESP32)

// pins_arduino.h, e.g. LOLIN32
//static const uint8_t SS    = 5;
//static const uint8_t MOSI  = 23;
//static const uint8_t MISO  = 19;
//static const uint8_t SCK   = 18;

// GxIO_SPI(SPIClass& spi, int8_t cs, int8_t dc, int8_t rst = -1, int8_t bl = -1);
GxIO_Class io(SPI, SS, 17, 16); // arbitrary selection of 17, 16
// GxGDEP015OC1(GxIO& io, uint8_t rst = D4, uint8_t busy = D2);
GxEPD_Class display(io, 16, 4); // arbitrary selection of (16), 4

#elif defined(ARDUINO_ARCH_SAMD)

// variant.h of MKR1000
//#define PIN_SPI_MISO  (10u)
//#define PIN_SPI_MOSI  (8u)
//#define PIN_SPI_SCK   (9u)
//#define PIN_SPI_SS    (24u) // should be 4?
// variant.h of MKRZERO
//#define PIN_SPI_MISO  (10u)
//#define PIN_SPI_MOSI  (8u)
//#define PIN_SPI_SCK   (9u)
//#define PIN_SPI_SS    (4u)

GxIO_Class io(SPI, 4, 7, 6);
GxEPD_Class display(io, 6, 5);

#elif defined(_BOARD_GENERIC_STM32F103C_H_)

// STM32 Boards (STM32duino.com)
// Generic STM32F103C series
// aka BluePill
// board.h
//#define BOARD_SPI1_NSS_PIN        PA4
//#define BOARD_SPI1_MOSI_PIN       PA7
//#define BOARD_SPI1_MISO_PIN       PA6
//#define BOARD_SPI1_SCK_PIN        PA5
//enum {
//    PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13,PA14,PA15,
//  PB0, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13,PB14,PB15,
//  PC13, PC14,PC15
//};
// variant.h
//static const uint8_t SS   = BOARD_SPI1_NSS_PIN;
//static const uint8_t SS1  = BOARD_SPI2_NSS_PIN;
//static const uint8_t MOSI = BOARD_SPI1_MOSI_PIN;
//static const uint8_t MISO = BOARD_SPI1_MISO_PIN;
//static const uint8_t SCK  = BOARD_SPI1_SCK_PIN;

// original mapping suggestion for STM32F1, e.g. STM32F103C8T6 "BluePill"
// BUSY -> A3, RST -> A9, DC -> A8, CS-> A4, CLK -> A5, DIN -> A7

// GxIO_SPI(SPIClass& spi, int8_t cs, int8_t dc, int8_t rst = -1, int8_t bl = -1);
//GxIO_Class io(SPI, SS, 8, 9);
// GxGDEP015OC1(GxIO& io, uint8_t rst = 9, uint8_t busy = 7);
//GxEPD_Class display(io, 9, 3);

// new mapping suggestion for STM32F1, e.g. STM32F103C8T6 "BluePill"
// BUSY -> A1, RST -> A2, DC -> A3, CS-> A4, CLK -> A5, DIN -> A7

// GxIO_SPI(SPIClass& spi, int8_t cs, int8_t dc, int8_t rst = -1, int8_t bl = -1);
GxIO_Class io(SPI, SS, 3, 2);
// GxGDEP015OC1(GxIO& io, uint8_t rst = 9, uint8_t busy = 7);
GxEPD_Class display(io, 2, 1);

#else

// pins_arduino.h, e.g. AVR
//#define PIN_SPI_SS    (10)
//#define PIN_SPI_MOSI  (11)
//#define PIN_SPI_MISO  (12)
//#define PIN_SPI_SCK   (13)

GxIO_Class io(SPI, SS, 8, 9); // arbitrary selection of 8, 9 selected for default of GxEPD_Class
GxEPD_Class display(io);

#endif


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");

  display.init();

  Serial.println("setup done");
}

void loop()
{
#if !defined(_ADAFRUIT_TF_GFX_H_) && !defined(_GxFont_GFX_TFT_eSPI_H_) && !defined(U8g2_for_Adafruit_GFX_h)
  showFont("FreeMonoBold12pt7b", &FreeMonoBold12pt7b);
#endif
#if defined(U8g2_for_Adafruit_GFX_h)
  showFont("u8g2_font_helvR14_tf", u8g2_font_helvR14_tf); // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
  delay(2000);
  showFont("u8g2_font_profont22_mr", u8g2_font_profont22_mr); // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
  delay(2000);
#endif
#if defined(_GxFont_GFX_TFT_eSPI_H_)
  showFreeFont("FreeMonoBold12pt7b", &FreeMonoBold12pt7b);
  delay(2000);
  //showFreeFont("NULL", NULL);
  showTextFont("Font 1", 1, 1);
  delay(2000);
  showTextFont("Font 1", 1, 2);
  delay(2000);
  showTextFont("Font 1", 1, 3);
  delay(2000);
  showTextFont("Font 2", 2, 1);
  delay(2000);
  showTextFont("Font 2", 2, 2);
  delay(2000);
  showTextFont("Font 2", 2, 3);
  delay(2000);
  showTextFont("Font 4", 4, 1);
  delay(2000);
  showTextFont("Font 4", 4, 2);
  delay(2000);
  showTextFont("Font 4", 4, 3);
#endif
#if defined(_ADAFRUIT_TF_GFX_H_)
  showFont("Open_Sans_Bold_12pt", OPENSANSBOLD_12);
#endif
  delay(10000);
}

void showFont(const char name[], const GFXfont* f)
{
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(f);
  display.setCursor(0, 0);
  display.println();
  display.println(name);
  display.println(" !\"#$%&'()*+,-./");
  display.println("0123456789:;<=>?");
  display.println("@ABCDEFGHIJKLMNO");
  display.println("PQRSTUVWXYZ[\\]^_");
#if defined(HAS_RED_COLOR)
  display.setTextColor(GxEPD_RED);
#endif
  display.println("`abcdefghijklmno");
  display.println("pqrstuvwxyz{|}~ ");
  display.update();
  delay(5000);
}

#if defined(U8g2_for_Adafruit_GFX_h)
void showFont(const char name[], const uint8_t *f)
{
  display.setRotation(0);
  display.fillScreen(GxEPD_WHITE);
  display.setFontMode(1);                   // use u8g2 transparent mode (this is default)
  display.setFontDirection(0);              // left to right (this is default)
  display.setForegroundColor(GxEPD_BLACK);  // apply Adafruit GFX color
  display.setBackgroundColor(GxEPD_WHITE);  // apply Adafruit GFX color
  display.setFont(f); // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
  uint16_t dy = display.getFontAscent() - display.getFontDescent();
  Serial.print("display.getFontAscent() returns "); Serial.println(display.getFontAscent());
  Serial.print("display.getFontDescent() returns "); Serial.println(display.getFontDescent());
  Serial.print("dy = "); Serial.println(dy);
  display.setCursor(0, 0);
  display.println();
  display.setCursor(0, display.getCursorY() + dy);
  display.println(name);
  display.setCursor(0, display.getCursorY() + dy);
  display.println(" !\"#$%&'()*+,-./");
  display.setCursor(0, display.getCursorY() + dy);
  display.println("0123456789:;<=>?");
  display.setCursor(0, display.getCursorY() + dy);
  display.println("@ABCDEFGHIJKLMNO");
  display.setCursor(0, display.getCursorY() + dy);
  display.println("PQRSTUVWXYZ[\\]^_");
  display.setCursor(0, display.getCursorY() + dy);
#if defined(HAS_RED_COLOR)
  display.setForegroundColor(GxEPD_RED);
#endif
  display.println("`abcdefghijklmno");
  display.setCursor(0, display.getCursorY() + dy);
  display.println("pqrstuvwxyz{|}~ ");
  display.setCursor(0, display.getCursorY() + dy);
  display.println("Umlaut ÄÖÜäéöü");
  display.setCursor(0, display.getCursorY() + dy);
  display.update();
}
#endif

#if defined(_ADAFRUIT_TF_GFX_H_)
void showFont(const char name[], uint8_t f)
{
  display.setRotation(0);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(f);
  display.setCursor(0, 0);
  display.println();
  display.println(name);
  display.println(" !\"#$%&'()*+,-./");
  display.println("0123456789:;<=>?");
  display.println("@ABCDEFGHIJKLMNO");
  display.println("PQRSTUVWXYZ[\\]^_");
#if defined(HAS_RED_COLOR)
  display.setTextColor(GxEPD_RED);
#endif
  display.println("`abcdefghijklmno");
  display.println("pqrstuvwxyz{|}~ ");
  display.update();
}
#endif

#if defined(_GxFont_GFX_TFT_eSPI_H_)
void showFreeFont(const char name[], const GFXfont* f)
{
  display.setRotation(0);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFreeFont(f);
  display.setCursor(0, 0);
  display.println();
  display.println(name);
  display.println(" !\"#$%&'()*+,-./");
  display.println("0123456789:;<=>?");
  display.println("@ABCDEFGHIJKLMNO");
  display.println("PQRSTUVWXYZ[\\]^_");
#if defined(HAS_RED_COLOR)
  display.setTextColor(GxEPD_RED);
#endif
  display.println("`abcdefghijklmno");
  display.println("pqrstuvwxyz{|}~ ");
  display.update();
}
void showTextFont(const char name[], uint8_t f, uint8_t size)
{
  display.setRotation(0);
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK, GxEPD_WHITE);
  display.setTextFont(f);
  display.setTextSize(size);
  display.setCursor(0, 0);
  display.println();
  display.println(name);
  display.println(" !\"#$%&'()*+,-./");
  display.println("0123456789:;<=>?");
  display.println("@ABCDEFGHIJKLMNO");
  display.println("PQRSTUVWXYZ[\\]^_");
#if defined(HAS_RED_COLOR)
  display.setTextColor(GxEPD_RED);
#endif
  display.println("`abcdefghijklmno");
  display.println("pqrstuvwxyz{|}~ ");
  display.update();
}
#endif




#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SdFat.h>
#include <Adafruit_SPIFlash.h>
#include <Adafruit_EPD.h>
#include <Adafruit_ImageReader.h>
#include <tiny32_v3.h>

// For the breakout board, you can use any 2 or 3 pins.
// These pins will also work for the 1.8" TFT shield.
#define TFT_CS 14
#define TFT_RST 15 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC 32
#define TFT_MOSI 26
#define TFT_SCLK 27

// For ST7735-based displays, we will use this call
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

tiny32_v3 mcu;

SdFat SD;                        // SD card filesystem
Adafruit_ImageReader reader(SD); // Image-reader object, pass in SD filesys

Adafruit_Image img; // An image loaded into RAM
int32_t width = 0,  // BMP image dimensions
    height = 0;

float p = 3.1415926;

void testlines(uint16_t color)
{
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawLine(0, 0, x, tft.height() - 1, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6)
  {
    tft.drawLine(0, 0, tft.width() - 1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawLine(tft.width() - 1, 0, x, tft.height() - 1, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6)
  {
    tft.drawLine(tft.width() - 1, 0, 0, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawLine(0, tft.height() - 1, x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6)
  {
    tft.drawLine(0, tft.height() - 1, tft.width() - 1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawLine(tft.width() - 1, tft.height() - 1, x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6)
  {
    tft.drawLine(tft.width() - 1, tft.height() - 1, 0, y, color);
    delay(0);
  }
}

void testdrawtext(char *text, uint16_t color)
{
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2)
{
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t y = 0; y < tft.height(); y += 5)
  {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x = 0; x < tft.width(); x += 5)
  {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color)
{
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6)
  {
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2)
{
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = tft.width() - 1; x > 6; x -= 6)
  {
    tft.fillRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color1);
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color)
{
  for (int16_t x = radius; x < tft.width(); x += radius * 2)
  {
    for (int16_t y = radius; y < tft.height(); y += radius * 2)
    {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color)
{
  for (int16_t x = 0; x < tft.width() + radius; x += radius * 2)
  {
    for (int16_t y = 0; y < tft.height() + radius; y += radius * 2)
    {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles()
{
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 0xF800;
  int t;
  int w = tft.width() / 2;
  int x = tft.height() - 1;
  int y = 0;
  int z = tft.width();
  for (t = 0; t <= 15; t++)
  {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x -= 4;
    y += 4;
    z -= 4;
    color += 100;
  }
}

void testroundrects()
{
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 100;
  int i;
  int t;
  for (t = 0; t <= 4; t += 1)
  {
    int x = 0;
    int y = 0;
    int w = tft.width() - 2;
    int h = tft.height() - 2;
    for (i = 0; i <= 16; i += 1)
    {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x += 2;
      y += 3;
      w -= 4;
      h -= 6;
      color += 1100;
    }
    color += 100;
  }
}

void tftPrintTest()
{
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_GREEN);
  tft.print(p, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ST77XX_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(" seconds.");
}

void mediabuttons()
{
  // play
  tft.fillScreen(ST77XX_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST77XX_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST77XX_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_GREEN);
}

void setup(void)
{
  Serial.begin(115200);
  Serial.print(F("Hello! ST77xx TFT Test"));
  tft.initR(INITR_BLACKTAB); // Init ST7735S chip, black tab
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);

  if (!SD.begin(5, SD_SCK_MHZ(25)))
  { // ESP32 requires 25 MHz limit
    Serial.println(F("SD begin() failed"));
    mcu.buzzer_beep(3);
    for (;;)
      ; // Fatal error, do not continue
  }

  ImageReturnCode stat; // Status from image-reading functions

  Serial.print(F("Loading [file].bmp to screen..."));

  tft.fillScreen(ST77XX_WHITE);
  tft.setRotation(3);
  // stat = reader.drawBMP("/cmu.bmp", tft, 0, 0);
  stat = reader.drawBMP("/tenergyin.bmp", tft, 0, 10);
  reader.printStatus(stat); // How'd we do?

  if (stat == 0)
  {
    mcu.buzzer_beep(2);
  }
  else
  {
    mcu.buzzer_beep(3);
  }
}

void loop()
{
}

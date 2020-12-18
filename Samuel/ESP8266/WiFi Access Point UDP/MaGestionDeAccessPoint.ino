#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_FeatherOLED.h>
#include "MaGestionDeAccessPoint.h"

Adafruit_FeatherOLED oled = Adafruit_FeatherOLED();
Adafruit_SSD1306 display = Adafruit_SSD1306();

void initialiseLaGestionDeAccessPoint()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();
  display.println("247-527!!!");
  display.setTextSize(1);  
  display.println("access point et UDP");
  display.display();
  display.setTextSize(1);
  delay(1000);
  display.clearDisplay();
}

void afficheErreur(void)
{
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("erreur");
  display.display();  
  while(1);
}

void afficheLeMessageRecu(unsigned char *Tampon, unsigned char Longueur)
{
unsigned char index;
  display.clearDisplay();
  display.setCursor(0,0);
  for (index = 0; index < Longueur; index++)
  {
    display.print(Tampon[index]);
  }
  display.display();
}

void afficheMessageAbsent(void)
{
  display.clearDisplay();
  display.setCursor(0,0);
  display.printf("AP: pas de message");
  display.display();
}

/* SparkFun WS2812 Breakout Board Example
  SparkFun Electronics
  date: July 25, 2013
  license: GNU GENERAL PUBLIC LICENSE
  
  Requires the Adafruit NeoPixel library. It's awesome, go get it.
  https://github.com/adafruit/Adafruit_NeoPixel
   
  Before uploading the code, make sure you adjust the two defines at the
  top of this sketch: PIN and LED_COUNT. Pin should be the Arduino pin
  you've got connected to the first pixel's DIN pin. By default it's
  set to Arduino pin 4. LED_COUNT should be the number of breakout boards
  you have linked up.
*/
#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"

#define PIN1 3
#define LED_COUNT1 21
#define PIN2 5
#define LED_COUNT2 21
#define PIN3 6
#define LED_COUNT3 22

// Create an instance of the Adafruit_NeoPixel class called "XPin", "YPin" and "ZPin".
// That'll be what we refer to from here on...
Adafruit_NeoPixel XPin = Adafruit_NeoPixel(LED_COUNT1, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel YPin = Adafruit_NeoPixel(LED_COUNT2, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ZPin = Adafruit_NeoPixel(LED_COUNT3, PIN3, NEO_GRB + NEO_KHZ800);
 
const int sensorPinX = A0; //Accelerometer x-axis to analog pin 0 
const int sensorPinY = A2; //Accelerometer y-axis to analog pin 2
const int sensorPinZ = A4; //Accelerometer z-axis to analog pin 4 

int analogValueX = 0;
int analogValueY = 0;
int analogValueZ = 0;

void setup()
{
  
  XPin.begin();  // Call this to start up the LED strip.
  YPin.begin();
  ZPin.begin();
  clearLEDs();   // This function, defined below, turns all LEDs off...

}

void loop()
{
   analogValueX = analogRead(sensorPinX);
   analogValueY = analogRead(sensorPinY);
   analogValueZ = analogRead(sensorPinZ);
   
   if (analogValueX > 500) //the value which is an average between no movement of the accelerometer and some change in position for the x-axis
   {   
        // A light shower of light sky blue
        // This will run the cascade from top->bottom i times
        for (int i=0; i<1; i++)
        {
          // First parameter is the color, second is direction, third is ms between falls
          cascade1(LIGHTSKYBLUE, TOP_DOWN, 25); 
        }
   }
   else
         {
           clearLEDs(); // Turn all LEDs off
         }
   if (analogValueY > 500) //the value which is an average between no movement of the accelerometer and some change in position for the y-axis
   {
          // A light shower of light sky blue
          // This will run the cascade from top->bottom i times
          for (int i=0; i<1; i++)
          {
            // First parameter is the color, second is direction, third is ms between falls
            cascade2(LIGHTSKYBLUE, TOP_DOWN, 25); 
          }
   }
   else
         {
           clearLEDs(); // Turn all LEDs off
         }
   if (analogValueZ > 500) //the value which is an average between no movement of the accelerometer and some change in position for the z-axis
   {
        // A light shower of light sky blue
        // This will run the cascade from top->bottom i times
        for (int i=0; i<1; i++)
        {
          // First parameter is the color, second is direction, third is ms between falls
          cascade3(LIGHTSKYBLUE, TOP_DOWN, 25); 
        }
   }
   else
         {
           clearLEDs(); // Turn all LEDs off
         }
}

// Cascades a single direction. One time.
void cascade1(unsigned long color, byte direction, byte wait)
{
  if (direction == TOP_DOWN)
  {
    for (int i=0; i<LED_COUNT1; i++)
    {
      clearLEDs();  // Turn off all LEDs
      XPin.setPixelColor(i, color);  // Set just this one
      XPin.show();
      delay(wait);
    }
  }
    else
  {
    for (int i=LED_COUNT1-1; i>=0; i--)
    {
      clearLEDs();
      XPin.setPixelColor(i, color);
      XPin.show();
      delay(wait);
    }
  }
}

void cascade2(unsigned long color, byte direction, byte wait)
{
  if (direction == TOP_DOWN)
  {
    for (int i=0; i<LED_COUNT2; i++)
    {
      clearLEDs();  // Turn off all LEDs
      YPin.setPixelColor(i, color);  // Set just this one
      YPin.show();
      delay(wait);
    }
  }
      else
  {
        for (int i=LED_COUNT2-1; i>=0; i--)
    {
      clearLEDs();
      YPin.setPixelColor(i, color);
      YPin.show();
      delay(wait);
    }
  }
}
  
 void cascade3(unsigned long color, byte direction, byte wait)
{
  if (direction == TOP_DOWN)
  {
    for (int i=0; i<LED_COUNT3; i++)
    {
      clearLEDs();
      ZPin.setPixelColor(i, color);
      ZPin.show();
      delay(wait);
    }
  }
  else{
    
   for (int i=LED_COUNT3-1; i>=0; i--)
    {
      clearLEDs();  // Turn off all LEDs
      ZPin.setPixelColor(i, color);  // Set just this one
      ZPin.show();
      delay(wait);
    }
  }
}

// Sets all LEDs to off, but DOES NOT update the display;
// call leds.show() to actually turn them off after this.
void clearLEDs()
{
  for (int i=0; i<LED_COUNT1; i++)
  {
    XPin.setPixelColor(i, 0);
  }
  for (int i=0; i<LED_COUNT2; i++)
  {
    YPin.setPixelColor(i, 0);
  }
  for (int i=0; i<LED_COUNT3; i++)
  {
    ZPin.setPixelColor(i, 0);
  }
}

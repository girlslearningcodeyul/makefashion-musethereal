#include <Adafruit_NeoPixel.h>
#include "WS2812_Definitions.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which PIN1 on the Arduino is connected to the NeoPixels1?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN1            3
#define PIN2            9
#define PIN3            10
#define PIN4            11


// How many NeoPixels1 are attached to the Arduino? 
//How many Neopixels1 do you want to chase (starting from the first in address 0). 
//How many do you want to burst from the end?
#define n 24 //total number of pixels1 on strand one +1
#define x 14   //number of pixels1 in colour lightskyblue to chase on strand one
#define y 4 //number of pixels1 in colour lightskyblue to burst on strand one
#define z 5 //number of pixels1 in colour fuscia to burst on strand one
#define nn 33 //total number of pixels1 on strand two +1
#define xx 23   //number of pixels1 in colour lightskyblue to chase on strand two
#define yy 4 //number of pixels1 in colour lightskyblue to burst on strand two
#define zz 5 //number of pixels1 in colour fuscia to burst on strand two
#define nnn 36 //total number of pixels1 on strand three +1
#define xxx 26   //number of pixels1 in colour lightskyblue to chase on strand three
#define yyy 4 //number of pixels1 in colour lightskyblue to burst on strand three
#define zzz 5 //number of pixels1 in colour fuscia to burst on strand three
#define nnnn 29 //total number of pixels4 on strand four +1
#define xxxx 18   //number of pixels4 in colour lightskyblue to chase on strand four
#define yyyy 4 //number of pixels4 in colour lightskyblue to burst on strand four
#define zzzz 5 //number of pixels4 in colour fuscia to burst on strand four

// When we setup the NeoPixel library, we tell it how many pixels1, and which PIN1 to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(n, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(nn, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3 = Adafruit_NeoPixel(nnn, PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels4 = Adafruit_NeoPixel(nnnn, PIN4, NEO_GRB + NEO_KHZ800);

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels1.begin(); // This initializes the NeoPixel library.
  pixels2.begin();
  pixels3.begin();
  pixels4.begin();
  clearLEDs();
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels1 minus one.
  for(int i1=0, i4=0; i1<x, i4<xxxx;i1++, i4++) //strands 1 and 4 are to execute at the same time
  {
    pixels1.setPixelColor(i1, LIGHTSKYBLUE);
    pixels4.setPixelColor(i4, LIGHTSKYBLUE);
    pixels1.show(); // This sends the updated pixel color to the hardware.
    pixels4.show();
    delay(50);
    clearLEDs();
  }

  for(int i1=n-y-z, i4=nnnn-yyyy-zzzz; i1<n-z, i4<nnnn-zzzz; i1++, i4++)
  {
    pixels1.setPixelColor(i1, LIGHTSKYBLUE);
    pixels4.setPixelColor(i4, LIGHTSKYBLUE);
    pixels1.show(); // This sends the updated pixel color to the hardware.
    pixels4.show();
    delay(20);
    clearLEDs();
  }

  for(int i1=n-z, i4=nnnn-zzzz; i1<n, i4<nnnn; i1++, i4++)
  {
    pixels1.setPixelColor(i1, FUCHSIA);
    pixels4.setPixelColor(i4, FUCHSIA);
    pixels1.show(); // This sends the updated pixel color to the hardware.
    pixels4.show();
    delay(20);
    clearLEDs();//remove this line if you want the chasing sequence to stay on
  }
    for(int i2=0; i2<xx; i2++) 
  {
    pixels2.setPixelColor(i2, LIGHTSKYBLUE);
    pixels2.show(); // This sends the updated pixel color to the hardware.
    delay(50);
    clearLEDs();
  }

  for(int i2=nn-yy-zz; i2<nn-zz; i2++)
  {
    pixels2.setPixelColor(i2, LIGHTSKYBLUE);
    pixels2.show(); // This sends the updated pixel color to the hardware.
    delay(20);
    clearLEDs();
  }

  for(int i2=nn-zz; i2<nn; i2++)
  {
    pixels2.setPixelColor(i2, FUCHSIA);
    pixels2.show(); // This sends the updated pixel color to the hardware.
    delay(20);
    clearLEDs();//remove this line if you want the chasing sequence to stay on
  }
  for(int i3=0; i3<xxx; i3++) 
  {
    pixels3.setPixelColor(i3, LIGHTSKYBLUE);
    pixels3.show(); // This sends the updated pixel color to the hardware.
    delay(50);
    clearLEDs();
  }

  for(int i3=nnn-yyy-zzz; i3<nnn-zzz; i3++)
  {
    pixels3.setPixelColor(i3, LIGHTSKYBLUE);
    pixels3.show(); // This sends the updated pixel color to the hardware.
    delay(20);
    clearLEDs();
  }

  for(int i3=nnn-zzz; i3<nnn; i3++)
  {
    pixels3.setPixelColor(i3, FUCHSIA);
    pixels3.show(); // This sends the updated pixel color to the hardware.
    delay(20);
    clearLEDs();//remove this line if you want the chasing sequence to stay on
  }

}

// Sets all LEDs to off, but DOES NOT update the display;
// call pixels.show() to actually turn them off after this.
void clearLEDs()
{
  for (int i1=0; i1<n; i1++)
  {
    pixels1.setPixelColor(i1, 0);
  }
  
      for (int i2=0; i2<nn; i2++)
  {
    pixels2.setPixelColor(i2, 0);
  }
  
    for (int i3=0; i3<nnn; i3++)
  {
    pixels3.setPixelColor(i3, 0);
  }
  
    for (int i4=0; i4<nnnn; i4++)
  {
    pixels4.setPixelColor(i4, 0);
  }
}


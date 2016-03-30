// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define ARRAY1PIN         6    
#define DRESSLEDARRAYLENGTH 13 //13 channels - 13 dress LEDs 
#define RED     0xFF0000
#define ORANGE  0xFF7000
#define YELLOW  0xFFFF00
#define GREEN   0x00FF00
#define CYAN    0x00FFFF
#define BLUE    0x0000FF
#define VIOLET  0x5000FF
#define PINK    0xFF00FF
#define WHITE   0xFFFFFF
#define NONE    0x000000
uint32_t currentColors [DRESSLEDARRAYLENGTH];
uint32_t targetColors [DRESSLEDARRAYLENGTH];
int stepMax = 15;   //The number of steps to do a fade across
int stepTime = 20;  //The number of milliseconds to pause at each step in the fade
bool readyToRead = true;
Adafruit_NeoPixel array1 = Adafruit_NeoPixel(DRESSLEDARRAYLENGTH, ARRAY1PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  array1.begin();

  //Initialize current color array to be blank
  for(int i = 0; i < DRESSLEDARRAYLENGTH; i++){
      currentColors[i] = 0x000000;
  }
}

void loop(){
  if(Serial.available() && Serial.peek() != -1 && readyToRead) {
      //We're processing, everything hold up
      readyToRead = false;
      
      //Read out data into target color array
      for(int i=0;i<DRESSLEDARRAYLENGTH;i++){
        char c = Serial.read();
        if (c == -1) {
          c = 'n';
        }
        targetColors[i] = convertToColor(c);
      }

      //Transition currentColors to targetColors
      uint32_t tempArray [DRESSLEDARRAYLENGTH];
      for(int i=1;i<stepMax+1;i++){
        for(int j=0;j<DRESSLEDARRAYLENGTH;j++){
          tempArray[j] = calculateTransitionColor(currentColors[j], targetColors[j], i, stepMax);
        }

        //Then show it briefly
        writeToArray(tempArray);
        delay(stepTime);
      }
      
      //Then assign the current array to what the target was (cause we are already there...right?)
      for(int i = 0; i < DRESSLEDARRAYLENGTH; i++){
        currentColors[i] = tempArray[i];
      }
      writeToArray(currentColors);

      //Ready to read again
      readyToRead = true;
      Serial.write('1'); //Write a 1 back onto the serial wire - the android app is waiting for this 'readyToTransmit' byte before it sends across the next color string
  }
}

uint32_t calculateTransitionColor(uint32_t currentColor, uint32_t targetColor, int stepNum, int stepMax) {
  uint8_t rcur = (currentColor & 0xFF0000) >> 16; //Mask and shift the current red level into a byte 
  uint8_t rtar = (targetColor & 0xFF0000) >> 16;  //Mask and shift the target red level into a byte
  uint8_t gcur = (currentColor & 0x00FF00) >> 8;  //Mask and shift the current green level into a byte
  uint8_t gtar = (targetColor & 0x00FF00) >> 8;   //Mask and shift the target red level into a byte
  uint8_t bcur = (currentColor & 0x0000FF);       //Mask the current blue level into a byte (no shift necessary as the bits are in the correct position)
  uint8_t btar = (targetColor & 0x0000FF);        //Mask and target blue level into a byte (no shift necessary as the bits are already in the correct position)
  
  int rstep = (rtar - rcur) / stepMax;            // calculate the red step size - leave as signed variable target to account for negative step.  ignore truncation errors cause DGAF...we are writing out the target color at the end anyways
  int gstep = (gtar - gcur) / stepMax;            // calculate the green step size - leave as signed variable target to account for negative step.  ignore truncation errors cause DGAF...we are writing out the target color at the end anyways
  int bstep = (btar - bcur) / stepMax;            // calculate the blue step size - leave as signed variable target to account for negative step.  ignore truncation errors cause DGAF...we are writing out the target color at the end anyways
  
  uint32_t rnow = rcur + rstep * stepNum;         // given the step number, the step size and a current color, calculate where we should be in the fade....
  uint32_t gnow = gcur + gstep * stepNum;
  uint32_t bnow = bcur + bstep * stepNum;
    
  uint32_t calc = 0x000000 + (rnow << 16) + (gnow << 8) + bnow;   // And recombine the RGBnow levels back into a single unsigned int that we can pass along as a color
  return calc;
}

void writeToArray(uint32_t arr[]) { 
  for (int i = 0; i < DRESSLEDARRAYLENGTH; i++) {
    array1.setPixelColor(i, arr[i]); 
  }

  array1.show();
}

//given a single character from the serial line, turn that into a numeric code representing to color
uint32_t convertToColor(char c) { 
  switch (c) {
    case 'r': return RED;
    case 'o': return ORANGE;
    case 'y': return YELLOW;
    case 'g': return GREEN;
    case 'c': return CYAN;
    case 'b': return BLUE;
    case 'v': return VIOLET;
    case 'p': return PINK;
    case 'w': return WHITE;
    default:  return NONE;
  }
}


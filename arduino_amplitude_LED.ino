// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library
 
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
 
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        3 // On Trinket or Gemma, suggest changing this to 1
 
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 24 // Popular NeoPixel ring size
 
// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
 
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  // put your setup code here, to run once:
  Serial.begin(9600);
 
}
 
void loop() {
 
  int a = analogRead(A0);
  Serial.println(a);
  int change = abs(797 - a); //change main line
  
  int sensitivity = 100.8;      // feel free to change htis variable to determine how sentiive it will be 
  
  if(change >= sensitivity){change = sensitivity;}
  //else(change <= 10){change = 10;}
  
  if(change <= sensitivity and change >= 10){
    int numactive = (change / 4.2) + 1;  //change this if you got change sensitivity, sensitivity / num of led 

    int r = 0; 
    int g = 0; 
    int b = 0; 

    if(change > 25 and change < 50)    { r = 100; g = change - (r * 0.20); b = 0;}
    if(change > 50 and change < 70)   { r = 0; g = 100; b = change - (g * 0.20);}
    if(change > 75)                   { r = change - (b * 0.20); g = 0; b=100;}
    if(change == sensitivity){r = 100; g = 100; b = 100;}
    
    for(int i=0; i<numactive; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();
    delay(2);
  }
  }
  else{
    for(int i=0; i<24; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();
    delay(2);
  }
  }
 
}

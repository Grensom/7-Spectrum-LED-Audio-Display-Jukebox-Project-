//Jukebox LED Show
//Designed by Gregory Ensom
//6.29.22
#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    90
#define resetPin 3
#define strobePin 4
#define outputPin A0
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

int BRIGHTNESS;

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

//==============================================================
//                  SETUP
//==============================================================
void setup() {
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(UncorrectedColor);

  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;

  pinMode(resetPin, OUTPUT);
  pinMode(strobePin, OUTPUT); 
}
//==============================================================
//                  LOOP
//==============================================================
void loop(){ 
  BRIGHTNESS = 50;
  FastLED.clear();
  uint8_t colorAdj = 75;
  //130 purply blue
  //75 yellowy red
  int reset;
  int strobe;
  int output;
  int bands[7];
  int randomNum1;
  int randomNum2;
  int randomNum3;
  int randomNum4;
  int randomNum5;
  int randomNum6;
  int randomNum7;
  int tubeLED1 = 0;
  int tubeLED2 = 0;
  int tubeLED3 = 0;
  int tubeLED4 = 0;
  int tubeLED5 = 0;
  int tubeLED6 = 0;
  int tubeLED7 = 0;
  int t1s = 90; //tube 1 start
  int t1e = 80; //tube 1 end
  int t2s = 68; //tube 2 start
  int t2e = 78; //tube 2 end
  int t3s = 66; //tube 3 start
  int t3e = 56; //tube 3 end
  int t4s = 44; //tube 4 start
  int t4e = 54; //tube 4 end
  int t5s = 42; //tube 5 start
  int t5e = 32; //tube 5 end
  int t6s = 20; //tube 6 start
  int t6e = 30; //tube 6 end
  int t7s = 18; //tube 7 start
  int t7e = 8; //tube 7 end
  while(true){
    //audio collection loop
    digitalWrite(resetPin, HIGH);
    digitalWrite(resetPin, LOW);
    //delayMicroseconds(75);
    for(int i = 0; i < 7; i++){
      digitalWrite(strobePin, LOW);
      delayMicroseconds(40);
      bands[i] = analogRead(outputPin);
      digitalWrite(strobePin, HIGH);
      delayMicroseconds(40);
    }
//    randomNum1 = random(t1e,t1s);90-80
//    randomNum2 = random(t2s,t2e);
//    randomNum3 = random(t3e,t3s);
//    randomNum4 = random(t4s,t4e);
//    randomNum5 = random(t5e,t5s);
//    randomNum6 = random(t6s,t6e);
//    randomNum7 = random(t7e,t7s);
    randomNum1 = map(bands[0], 0, 1023, t1s, t1e);
    randomNum2 = map(bands[1], 0, 1023, t2s, t2e);
    randomNum3 = map(bands[2], 0, 1023, t3s, t3e);
    randomNum4 = map(bands[3], 0, 1023, t4s, t4e);
    randomNum5 = map(bands[4], 0, 1023, t5s, t5e);
    randomNum6 = map(bands[5], 0, 1023, t6s, t6e);
    randomNum7 = map(bands[6], 0, 1023, t7s, t7e);
    tubeLED1 = LedShowDown(t1s,t1e,randomNum1, tubeLED1, BRIGHTNESS, colorAdj);
    tubeLED2 = LedShowUp(t2s,t2e,randomNum2, tubeLED2, BRIGHTNESS, colorAdj);
    tubeLED3 = LedShowDown(t3s,t3e,randomNum3, tubeLED3, BRIGHTNESS, colorAdj);//
    tubeLED4 = LedShowUp(t4s,t4e,randomNum4, tubeLED4, BRIGHTNESS, colorAdj);
    tubeLED5 = LedShowDown(t5s,t5e,randomNum5, tubeLED5, BRIGHTNESS, colorAdj);
    tubeLED6 = LedShowUp(t6s,t6e,randomNum6, tubeLED6, BRIGHTNESS, colorAdj);
    tubeLED7 = LedShowDown(t7s,t7e,randomNum7, tubeLED7, BRIGHTNESS, colorAdj);
    FastLED.show();
    delay(3);
//    colorAdj++;
//    if(colorAdj>250){
//      colorAdj = 0;
//    }
  }
}

int LedShowUp(int ts, int te, int randomNum, int tubeLED, int brightness, int colorAdjustment)
{
//  if((randomNum > ts+tubeLED)){
//        leds[ts+tubeLED] = ColorFromPalette(currentPalette, colorAdjustment+(tubeLED*5), brightness, currentBlending);
//        tubeLED++;
//  }
  if((randomNum > ts+tubeLED)){ //78 > 68, light up to 78
        for(int i=ts; i<=randomNum; i++){
          leds[i] = ColorFromPalette(currentPalette, colorAdjustment+(tubeLED*5), brightness, currentBlending);
          tubeLED = i-ts;
        }   
  }
  else if((randomNum < ts+tubeLED)){
    leds[ts+tubeLED] = CRGB::Black;
    tubeLED--;
  }
  else{}
  Serial.println(tubeLED);
  return tubeLED;
}

int LedShowDown(int ts, int te, int randomNum, int tubeLED, int brightness, int colorAdjustment)
{
//  if((randomNum < ts-tubeLED)){
//        leds[ts-tubeLED] = ColorFromPalette(currentPalette, colorAdjustment+(tubeLED*5), brightness, currentBlending);
//        tubeLED++;
//  }
  if((randomNum < ts-tubeLED)){ //80 < 90, light up to 80
        for(int i=ts; i>=randomNum; i--){
          leds[i] = ColorFromPalette(currentPalette, colorAdjustment+(tubeLED*5), brightness, currentBlending);
          tubeLED = ts-i;
        }   
  }
  else if((randomNum > ts-tubeLED)){;
    leds[ts-tubeLED] = CRGB::Black;
    tubeLED--;
  }
  else{}
  Serial.println(tubeLED);
  return tubeLED;
  
}

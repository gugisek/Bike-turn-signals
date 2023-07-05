#include <FastLED.h>
#define NUM_STRIPS 6 
#define NUM_LEDS_PER_STRIP 22
CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];
uint8_t gHue = 0;                           // rotating "base color" used by many of the patterns
uint8_t hue = 0;

const int buttonPinL = 3;
const int buttonPinR = 2;
const int powerBTN = 4;
const int stopBTN = 5;

int buttonStateL = 0;
int buttonStateR = 0;
int powerBTNstate = 0;
int stopBTNstate = 0;

int delayTurnLedAnim = 60;

int eo2 = 0;

unsigned long currentMillis = 0; 
unsigned long previousMillis = 0;

void setup() {
  // put your setup code here, to run once:
    //FastLED.addLeds<NEOPIXEL, 8>(leds[0], NUM_LEDS_PER_STRIP); //led strip front left
    FastLED.addLeds<NEOPIXEL, 9>(leds[1], 22); //led strip front
    FastLED.addLeds<NEOPIXEL, 10>(leds[2], 19); //led strip rear + stop

    pinMode(buttonPinL, INPUT);
    pinMode(buttonPinR, INPUT);
    pinMode(powerBTN, INPUT);
    pinMode(stopBTN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  buttonStateL = digitalRead(buttonPinL); 
  buttonStateR = digitalRead(buttonPinR);
  powerBTNstate = digitalRead(powerBTN);
  stopBTNstate= digitalRead(stopBTN);

  //awaryjne światła
  if(powerBTNstate == HIGH) {

    if (buttonStateL == LOW && buttonStateR == LOW) {
      fill_solid(leds[1], NUM_LEDS_PER_STRIP, CRGB::Black); // przod na czarno
      fill_solid(leds[2], NUM_LEDS_PER_STRIP, CRGB::Black); // tył na czarno

      leds[1][8] = CRGB::White;
      leds[1][9] = CRGB::White;
      leds[1][10] = CRGB::White;
      leds[1][11] = CRGB::White;

      leds[2][4] = CRGB::Red;
      leds[2][5] = CRGB::Red;
      leds[2][6] = CRGB::Red;

      FastLED.show();
      int dot_przod_lewy = 8;
      int dot_przod_prawy = 11;
      int dot_tyl_prawy = 6;
      int dot_tyl_lewy = 4;
      while (dot_przod_lewy <= 20) {

        stopBTNstate= digitalRead(stopBTN);
        if (stopBTNstate == HIGH) {
            leds[2][11] = CRGB::Red;
            leds[2][12] = CRGB::Red;
            leds[2][13] = CRGB::Red;
            leds[2][14] = CRGB::Red;
            leds[2][15] = CRGB::Red;
            leds[2][16] = CRGB::Red;
            leds[2][17] = CRGB::Red;
            leds[2][18] = CRGB::Red;
            leds[2][19] = CRGB::Red;
            FastLED.show();
        }else{
            leds[2][11] = CRGB::Black;
            leds[2][12] = CRGB::Black;
            leds[2][13] = CRGB::Black;
            leds[2][14] = CRGB::Black;
            leds[2][15] = CRGB::Black;
            leds[2][16] = CRGB::Black;
            leds[2][17] = CRGB::Black;
            leds[2][18] = CRGB::Black;
            leds[2][19] = CRGB::Black;
            FastLED.show();
        }

        leds[1][dot_przod_lewy] = 0xff6a00;
        leds[1][dot_przod_prawy] = 0xff6a00;
        leds[2][dot_tyl_prawy] = 0xff6a00;
        leds[2][dot_tyl_lewy] = 0xff6a00;

        leds[1][8] = CRGB::White;
        leds[1][9] = CRGB::White;
        leds[1][10] = CRGB::White;
        leds[1][11] = CRGB::White;

        leds[2][4] = CRGB::Red;
        leds[2][5] = CRGB::Red;
        leds[2][6] = CRGB::Red;
        if(dot_przod_prawy <=-6){
          dot_przod_prawy = -6;
        }else{
          dot_przod_prawy--;
        }
        if(dot_przod_lewy >=21){
          dot_przod_lewy = 21;
        }else{
          dot_przod_lewy++;
        }

        if(dot_tyl_prawy <=0){
          dot_tyl_prawy = -1;
        }else{
          dot_tyl_prawy--;
        }
        if(dot_tyl_lewy >=10){
          dot_tyl_lewy = 10;
        }else{
          dot_tyl_lewy++;
        }
        FastLED.show();
        currentMillis = previousMillis = millis();
        while(previousMillis + delayTurnLedAnim >= currentMillis){
          currentMillis = millis();
        }
    }
    }
    if(buttonStateR == HIGH) {


      if(eo2<=255) {
      eo2++;
      fill_rainbow(leds[1], NUM_LEDS_PER_STRIP, eo2, 10); 
      fill_rainbow(leds[2], NUM_LEDS_PER_STRIP, eo2, 10);      
      FastLED.show();
      currentMillis = previousMillis = millis();
        while(previousMillis + 2 >= currentMillis){
          currentMillis = millis();
        }
      }else {eo2=0;}
    }

    if(buttonStateL == HIGH) {
      int eo;
      eo=1;
      while(eo<=1024) {
      eo++;
      fill_rainbow(leds[0], NUM_LEDS_PER_STRIP, eo, 3);
      fill_rainbow(leds[1], NUM_LEDS_PER_STRIP, eo, 3); 
      fill_rainbow(leds[2], NUM_LEDS_PER_STRIP, eo, 3);      
      FastLED.show();
      }
    }
    
  }else{
    //światła dzienne
    //prawy kierunkowskaz
    if(buttonStateR == HIGH) {
      //punkt początkowy
      //przód
      leds[1][0] = CRGB::Black;
      leds[1][1] = CRGB::Black;
      leds[1][2] = CRGB::Black;
      leds[1][3] = CRGB::Black;
      leds[1][4] = CRGB::Black;
      leds[1][5] = CRGB::Black;
      leds[1][6] = CRGB::Black;
      leds[1][7] = CRGB::Black;
      leds[1][8] = CRGB::Black;
      leds[1][9] = CRGB::White;
      leds[1][10] = CRGB::White;

      leds[1][11] = CRGB::White;
      leds[1][12] = CRGB::White;
      leds[1][13] = CRGB::White;
      leds[1][14] = CRGB::White;
      leds[1][15] = CRGB::White;
      leds[1][16] = CRGB::White;
      leds[1][17] = CRGB::White;
      leds[1][18] = CRGB::White;
      leds[1][19] = CRGB::White;
      leds[1][20] = CRGB::White;
      leds[1][21] = CRGB::White;
      //tył
      leds[2][0] = CRGB::Black;
      leds[2][1] = CRGB::Black;
      leds[2][2] = CRGB::Black;
      leds[2][3] = CRGB::Black;
      leds[2][4] = CRGB::Black;
      leds[2][5] = CRGB::Red;
      leds[2][6] = CRGB::Red;
      leds[2][7] = CRGB::Red;
      leds[2][8] = CRGB::Red;
      leds[2][9] = CRGB::Red;
      leds[2][10] = CRGB::Red;
      FastLED.show();
      //animacja
      int dot_przod_prawy = 9;
      int dot_tyl_prawy = 5;
      while (dot_przod_prawy >= -2) {
        //przód animacja
        leds[1][dot_przod_prawy] = 0xff6a00;
        //tył animacja
        leds[2][dot_tyl_prawy] = 0xff6a00;
        leds[1][9] = CRGB::White;
        leds[2][5] = CRGB::Red;
        dot_przod_prawy--;
        if(dot_tyl_prawy <=0){
          dot_tyl_prawy = -1;
        }else{
          dot_tyl_prawy--;
        }
        FastLED.show();
        //włączenie światła stopu
        stopBTNstate= digitalRead(stopBTN);
        if (stopBTNstate == HIGH) {
            leds[2][11] = CRGB::Red;
            leds[2][12] = CRGB::Red;
            leds[2][13] = CRGB::Red;
            leds[2][14] = CRGB::Red;
            leds[2][15] = CRGB::Red;
            leds[2][16] = CRGB::Red;
            leds[2][17] = CRGB::Red;
            leds[2][18] = CRGB::Red;
            leds[2][19] = CRGB::Red;
            FastLED.show();
        }else{
            leds[2][11] = CRGB::Black;
            leds[2][12] = CRGB::Black;
            leds[2][13] = CRGB::Black;
            leds[2][14] = CRGB::Black;
            leds[2][15] = CRGB::Black;
            leds[2][16] = CRGB::Black;
            leds[2][17] = CRGB::Black;
            leds[2][18] = CRGB::Black;
            leds[2][19] = CRGB::Black;
            FastLED.show();
        }
        currentMillis = previousMillis = millis();
        while(previousMillis + delayTurnLedAnim >= currentMillis){
          currentMillis = millis();
        }
      }
      
    }
    //lewy kierunkowskaz
    if(buttonStateL == HIGH) {
      // fill_solid(leds[1], NUM_LEDS_PER_STRIP, CRGB::Black);
      // fill_solid(leds[0], NUM_LEDS_PER_STRIP, CRGB::White);

      leds[1][0] = CRGB::White;
      leds[1][1] = CRGB::White;
      leds[1][2] = CRGB::White;
      leds[1][3] = CRGB::White;
      leds[1][4] = CRGB::White;
      leds[1][5] = CRGB::White;
      leds[1][6] = CRGB::White;
      leds[1][7] = CRGB::White;
      leds[1][8] = CRGB::White;
      leds[1][9] = CRGB::White;
      leds[1][10] = CRGB::White;
      leds[1][11] = CRGB::Black;
      leds[1][12] = CRGB::Black;
      leds[1][13] = CRGB::Black;
      leds[1][14] = CRGB::Black;
      leds[1][15] = CRGB::Black;
      leds[1][16] = CRGB::Black;
      leds[1][17] = CRGB::Black;
      leds[1][18] = CRGB::Black;
      leds[1][19] = CRGB::Black;
      leds[1][20] = CRGB::Black;
      leds[1][21] = CRGB::Black;

      leds[2][0] = CRGB::Red;
      leds[2][1] = CRGB::Red;
      leds[2][2] = CRGB::Red;
      leds[2][3] = CRGB::Red;
      leds[2][4] = CRGB::Red;
      leds[2][5] = CRGB::Black;
      leds[2][6] = CRGB::Black;
      leds[2][7] = CRGB::Black;
      leds[2][8] = CRGB::Black;
      leds[2][9] = CRGB::Black;
      leds[2][10] = CRGB::Black;

      FastLED.show();
      int dot = -1;
      int dot_przod_lewy = 10;
      int dot_tyl_lewy = 5;

      while (dot_przod_lewy <= 21) {
        leds[1][dot_przod_lewy] = 0xff6a00;
        leds[2][dot_tyl_lewy] = 0xff6a00;
        leds[1][10] = CRGB::White;
        leds[2][5] = CRGB::Red;
        dot_przod_lewy++;
        // if(dot_przod_lewy >=12){
        //   dot_przod_lewy = 12;
        // }else{
        //   dot_przod_lewy++;
        // }
        if(dot_tyl_lewy >=10){
          dot_tyl_lewy = 10;
        }else{
          dot_tyl_lewy++;
        }
        FastLED.show();
              //włączenie światła stopu
      stopBTNstate= digitalRead(stopBTN);
      if (stopBTNstate == HIGH) {
          leds[2][11] = CRGB::Red;
          leds[2][12] = CRGB::Red;
          leds[2][13] = CRGB::Red;
          leds[2][14] = CRGB::Red;
          leds[2][15] = CRGB::Red;
          leds[2][16] = CRGB::Red;
          leds[2][17] = CRGB::Red;
          leds[2][18] = CRGB::Red;
          leds[2][19] = CRGB::Red;
          FastLED.show();
      }else{
          leds[2][11] = CRGB::Black;
          leds[2][12] = CRGB::Black;
          leds[2][13] = CRGB::Black;
          leds[2][14] = CRGB::Black;
          leds[2][15] = CRGB::Black;
          leds[2][16] = CRGB::Black;
          leds[2][17] = CRGB::Black;
          leds[2][18] = CRGB::Black;
          leds[2][19] = CRGB::Black;
          FastLED.show();
      }
        currentMillis = previousMillis = millis();
        while(previousMillis + delayTurnLedAnim >= currentMillis){
          currentMillis = millis();
        }
      }
    }
if (buttonStateL == LOW && buttonStateR == LOW) {
  //włączenie światła stopu
  if (stopBTNstate == HIGH) {
      leds[2][11] = CRGB::Red;
      leds[2][12] = CRGB::Red;
      leds[2][13] = CRGB::Red;
      leds[2][14] = CRGB::Red;
      leds[2][15] = CRGB::Red;
      leds[2][16] = CRGB::Red;
      leds[2][17] = CRGB::Red;
      leds[2][18] = CRGB::Red;
      leds[2][19] = CRGB::Red;
      FastLED.show();
  }else{
          leds[2][11] = CRGB::Black;
          leds[2][12] = CRGB::Black;
          leds[2][13] = CRGB::Black;
          leds[2][14] = CRGB::Black;
          leds[2][15] = CRGB::Black;
          leds[2][16] = CRGB::Black;
          leds[2][17] = CRGB::Black;
          leds[2][18] = CRGB::Black;
          leds[2][19] = CRGB::Black;
          FastLED.show();
      }

    //fill_solid(leds[0], NUM_LEDS_PER_STRIP, CRGB::White);
      fill_solid(leds[1], 22, CRGB::White);
      fill_solid(leds[2], 11, CRGB::Red);

      FastLED.show();
      
    }
  }
}

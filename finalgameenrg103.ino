#include <Adafruit_CircuitPlayground.h>
const byte rightPin = 5;
const byte leftPin = 4;
const byte switchPin = 7;
volatile bool intFlag = 0;
int score = 0;
int count = 0;
volatile bool state = 0;
int gameDelay = 30;

float midi[127];
int songMajor[6][2] = {
  {329, 50},
  {261, 50},
  {440, 50},
  {329, 50},
  {147, 200},
  {329, 100}
};
int songMinor[6][2] = {
  {300, 100},
  {294, 150},
  {261, 200},
  {300, 50},
  {294, 50},
  {261, 200}
};
int challenges[2] = {1, 2};
//l=left button, r=right button, a=shake s=sound c=light

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLDOWN);
  pinMode(leftPin, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(switchPin), startGame, CHANGE);

}

void loop() {
  //is switch on?
  if(intFlag){
    delay(5);
    state = digitalRead(switchPin);
    intFlag = 0;
  }
    if (!state){
      Serial.println("Round start!");
    for(int i = 0; i < 10; i++){
      //retrieve sensor values
      int randIndex = random(2);
      int randChallenge = challenges[randIndex];
      //Serial.println(randChallenge);
      //start delay here
      if(randChallenge == 1){
        Serial.println("Press the left button!");
        delay(gameDelay);
        bool leftButtonOn = digitalRead(leftPin);
        if(leftButtonOn){
          LEDoutput(0, 255);
          score += 1;
          count += 1;
        }
        else{
          LEDoutput(255, 0);
          score -= 1;
          count += 1;
        }
      }
      if(randChallenge == 2){
        Serial.println("Press the right button!");
        delay(gameDelay);
        bool rightButtonOn = digitalRead(rightPin);
        if(rightButtonOn){
          LEDoutput(0, 255);
          score += 1;
          count += 1;
        }
        else{
          LEDoutput(255, 0);
          score -= 1;
          count += 1;
        }

      }
    }
    Serial.println("game over! Your score is:");
    Serial.println(score);
    soundOutput(score);
    state = !state;
    }
    if (state){
      delay(5);
      score = 0;
      Serial.println("game quit");
    }
  }

//functions for outputs
void LEDoutput(int redval, int greenval){
  for(int i=0; i<10; i++){
    CircuitPlayground.setPixelColor(i, redval, greenval, 0);
  }
  delay(1000);
  CircuitPlayground.clearPixels();
}

void soundOutput(int score){
  if(score >= 5){
    Serial.println("Win");
    for(int i=0; i < 6; i++){
      //CircuitPlayground.playTone(songMajor[i][0], songMajor[i][1]);
    }
    delay(5000);
  }
  if(score < 5){
    Serial.println("Loose");
     for(int i=0; i < 6; i++){
      //CircuitPlayground.playTone(songMinor[i][0], songMinor[i][1]);
    }
    delay(5000);
  }
}

void startGame(){
  intFlag = 1;
}

#include <Adafruit_CircuitPlayground.h>
const byte rightPin = 5;
const byte leftPin = 4;
const byte switchPin = 7;
volatile bool intFlag = 0;
int score = 0;
int count = 0;
volatile bool state = 0;

float midi[127];
int songMajor[6][2] = {
  {64, 50},
  {71, 50},
  {69, 50},
  {67, 50},
  {60, 200},
  {64, 100}
};
int songMinor[6][2] = {
  {65, 100},
  {63, 100},
  {62, 200},
  {70, 50},
  {72, 50},
  {65, 100}
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
    if (!state){
      Serial.println("Round start");
    //for(int i = 0; i < 10; i++){
      //retrieve sensor values
      int randIndex = random(2);
      int randChallenge = challenges[randIndex];
      //Serial.println(randChallenge);
      //start delay here
      if(randChallenge == 1){
        Serial.println("Press the left button!");
        delay(5000);
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
        //Serial.println("Press the right button!");
        delay(5000);
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
      if(count > 10){
        Serial.println("game over! Your score is:");
        Serial.println(score);
        soundOutput(score);
        //continue;
      }
    //}
      
    }
    if (state){
      delay(5);
      score = 0;
      Serial.println("game quit");
    }
  }

}

//functions for outputs

void LEDoutput(int redval, int greenval){
  for(int i=0; i<10; i++){
    CircuitPlayground.setPixelColor(i, redval, greenval, 0);
  }
}

void soundOutput(int score){
  if(score >= 5){
    for(int i=0; i < sizeof(songMajor) / sizeof(songMajor[0]); i++){
      CircuitPlayground.playTone(midi[songMajor[i][0]], songMajor[i][1]);
    }
  }
  if(score < 5){
     for(int i=0; i < sizeof(songMinor) / sizeof(songMinor[0]); i++){
      CircuitPlayground.playTone(midi[songMinor[i][0]], songMinor[i][1]);
    }
  }
}

void startGame(){
  intFlag = 1;
}

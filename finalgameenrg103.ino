#include <Adafruit_CircuitPlayground.h>
const byte rightPin = 5;
const byte leftPin = 4;
const byte switchPin = 7;
volatile bool intFlag = 0;
int score = 0;
volatile bool state = 0;
 
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
    for(int i = 0; i < 10; i++){
      //retrieve sensor values
      bool leftButtonOn = digitalRead(leftPin);
      bool rightButtonOn = digitalRead(rightPin);
      int randIndex = random(2);
      int randChallenge = challenges[randIndex];
      //start delay here
      if(randChallenge == 1){
        if(leftButtonOn){
          LEDoutput(0, 255);
          score += 1;
        }
        else{
          LEDoutput(255, 0);
          score -= 1;
        }
      }
      if(randChallenge == 2){
        if(rightButtonOn){
          LEDoutput(0, 255);
          score += 1;
        }
        else{
          LEDoutput(255, 0);
          score -= 1;
        }

      }
    }
      
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
    //happy song!
  }
  if(score < 5){
    //play sad song!
  }
}

void startGame(){
  intFlag = 1;
}

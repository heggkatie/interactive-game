#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

//global variables
float tempF;
float tempThresh;
float soundLevel;
float soundThresh;

volatile int count = 0;
volatile bool switchFlag = true;  //switch on for gameplay
volatile bool AButtonFlag = false;
volatile bool BButtonFlag = false;
//David A. Mellis, Arduino
unsigned long lastDebounceDelay = 0; //the last time the pin was toggled
unsigned long debounceDelay = 50; //the debounce time
int lastDebounceTime;

int levelTime[5] = {10000,8000,5000,4000,3000};
int currentLevel = 0;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin(); 
  randomSeed(analogRead(0));
  pinMode(7, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(7), S_ISR, CHANGE); //used to pause the game
  tempF = CircuitPlayground.temperatureF();
  tempThresh = tempF + 5;
  soundLevel = CircuitPlayground.soundSensor();
  soundThresh = soundLevel + 10;
}

void loop() {
  rules();
  if (switchFlag) {
    level();
  } else {
    Serial.println("Game Paused");
    CircuitPlayground.setPixelColor(0, 0xE000FF);
    CircuitPlayground.setPixelColor(1, 0xE000FF);
    CircuitPlayground.setPixelColor(2, 0xE000FF);
    CircuitPlayground.setPixelColor(3, 0xE000FF);
    CircuitPlayground.setPixelColor(4, 0xE000FF);
    CircuitPlayground.setPixelColor(5, 0xE000FF);
    CircuitPlayground.setPixelColor(6, 0xE000FF);
    CircuitPlayground.setPixelColor(7, 0xE000FF);
    CircuitPlayground.setPixelColor(8, 0xE000FF);
    CircuitPlayground.setPixelColor(9, 0xE000FF);
  }
}

/*
- at the beginning, print the rules
  - blue = left button
  - green = right button
  - red = temperature increase
  - yellow = sound
  - bop it - maybe not (not very creative)
  - certain colors mean something
  - level up (level up sound and lights sillyy)
  - it can talk??
level 1 - 10 seconds - 10000 ms
level 2 - 8 seconds  -  8000 ms
level 3 - 5 seconds  -  5000 ms
level 4 - 4 second   -  4000 ms
level 5 - 3 seconds  -  3000 ms
*/

void rules() {
  Serial.println();
  Serial.println("There are 5 interactions per level, and 10 levels total.");
  Serial.println("The speed increases each level");
  Serial.println("Flipping the switch pauses the game, and is shown by the LEDs turning purple");
  Serial.println("blue = left button");
  Serial.println("green = right button");
  Serial.println("red = increase temperature");
  Serial.println("yellow = increase sound");
  Serial.println("Good Luck!");
}

void level() {
  int randNumber;
  // number from 0 - 3 chooses which color is shown, which needs to have the correct result
  
  // if you pass the level, it increases the level and prints that to the serial monitor
  for (int i = 0; i < 4; i++) {
    randNumber = random(3);
    switch(randNumber) {
      case 0:
        leftButton();
        break;
      case 1:
        rightButton();
        break;
      case 2:
        tempSensor();
        break;
      case 3:
        soundSensor();
        break;
    }
    /*if (randNumber() = userInput()) {
      i++;
    } else {
      Serial.println("Game Over");
    }*/
  }
}

void S_ISR() { //attach interrupt fuction
  unsigned long currentTime = millis();
  if ((currentTime - lastDebounceTime) > debounceDelay) { //checking if the difference between the current state and the last time it was switched is greater than the delay
    switchFlag = !switchFlag; //sets the switchFlag to true/false
    lastDebounceTime = currentTime; //saves the latest time of the switch to the current time
  }
}

void leftButton() {
  CircuitPlayground.setPixelColor(0, 0x0039FF);
   CircuitPlayground.setPixelColor(1, 0x0039FF);
   CircuitPlayground.setPixelColor(2, 0x0039FF);
   CircuitPlayground.setPixelColor(3, 0x0039FF);
   CircuitPlayground.setPixelColor(4, 0x0039FF);
   CircuitPlayground.setPixelColor(5, 0x0039FF);
   CircuitPlayground.setPixelColor(6, 0x0039FF);
   CircuitPlayground.setPixelColor(7, 0x0039FF);
   CircuitPlayground.setPixelColor(8, 0x0039FF);
   CircuitPlayground.setPixelColor(9, 0x0039FF);
  waitPress(AButtonFlag);
  delay(levelTime[4]);
}

void rightButton() {
  CircuitPlayground.setPixelColor(0, 0x21e624);
   CircuitPlayground.setPixelColor(1, 0x21e624);
   CircuitPlayground.setPixelColor(2, 0x21e624);
   CircuitPlayground.setPixelColor(3, 0x21e624);
   CircuitPlayground.setPixelColor(4, 0x21e624);
   CircuitPlayground.setPixelColor(5, 0x21e624);
   CircuitPlayground.setPixelColor(6, 0x21e624);
   CircuitPlayground.setPixelColor(7, 0x21e624);
   CircuitPlayground.setPixelColor(8, 0x21e624);
   CircuitPlayground.setPixelColor(9, 0x21e624);
  waitPress(BButtonFlag);
  delay(levelTime[4]);
}

void tempSensor() {
  CircuitPlayground.setPixelColor(0, 0xFF0000);
   CircuitPlayground.setPixelColor(1, 0xFF0000);
   CircuitPlayground.setPixelColor(2, 0xFF0000);
   CircuitPlayground.setPixelColor(3, 0xFF0000);
   CircuitPlayground.setPixelColor(4, 0xFF0000);
   CircuitPlayground.setPixelColor(5, 0xFF0000);
   CircuitPlayground.setPixelColor(6, 0xFF0000);
   CircuitPlayground.setPixelColor(7, 0xFF0000);
   CircuitPlayground.setPixelColor(8, 0xFF0000);
   CircuitPlayground.setPixelColor(9, 0xFF0000);
  waitTemp();
  delay(levelTime[4]);
}

void soundSensor() {
  CircuitPlayground.setPixelColor(0, 0xFFFD00);
   CircuitPlayground.setPixelColor(1, 0xFFFD00);
   CircuitPlayground.setPixelColor(2, 0xFFFD00);
   CircuitPlayground.setPixelColor(3, 0xFFFD00);
   CircuitPlayground.setPixelColor(4, 0xFFFD00);
   CircuitPlayground.setPixelColor(5, 0xFFFD00);
   CircuitPlayground.setPixelColor(6, 0xFFFD00);
   CircuitPlayground.setPixelColor(7, 0xFFFD00);
   CircuitPlayground.setPixelColor(8, 0xFFFD00);
   CircuitPlayground.setPixelColor(9, 0xFFFD00);
  waitSound();
  delay(levelTime[4]);
}

void waitPress(volatile bool &buttonFlag) {
  while (!buttonFlag) {

  }
}

void waitTemp() {
  while (!buttonFlag) { //this is not the correct var

  }
}

void waitSound() {
  while (!buttonFlag) { //this is not the correct var

  }
}

















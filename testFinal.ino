#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

//global variables
volatile int count = 0;
volatile int levelCount = 0; //creates the level count
const int numLevels = 5; //total number of levels
volatile bool switchFlag = false;  //switch on for gameplay
volatile bool AButtonFlag = false;
volatile bool BButtonFlag = false;
volatile bool gameOver = false;

//David A. Mellis, Arduino
unsigned long lastDebounceDelay = 0; //the last time the pin was toggled
unsigned long debounceDelay = 50; //the debounce time
int lastDebounceTime;
int8_t guess;

//time per level
int levelTime[numLevels] = {10000,8000,5000,4000,3000};

//prints the rules
void rules() {
  Serial.println();
  Serial.println("There are 5 interactions per level, and 10 levels total.");
  Serial.println("The speed increases each level");
  Serial.println("Flipping the switch pauses the game, and is shown by the LEDs turning purple");
  Serial.println("blue = left button");
  Serial.println("green = right button");
  Serial.println("red = press both buttons");
  Serial.println("yellow = double press the left button");
  Serial.println("Good Luck!");
}

//checks if the left button was pressed
bool waitForLeftButton() {
  unsigned long startTime = millis();
  while (millis() - startTime < 5000) {
    if (CircuitPlayground.leftButton()) {
      return true;
    }
    if (!switchFlag) return false; // Check for pause
  }
  return false;
}

//checks to see if the right button was pressed when needed
bool waitForRightButton() {
  unsigned long startTime = millis();
  while (millis() - startTime < 5000) {
    if (CircuitPlayground.rightButton()) {
      return true;
    }
    if (!switchFlag) return false; // Check for pause
  }
  return false;
}

//checks if both buttons were pressed
bool waitForBothButtons() {
  unsigned long startTime = millis();
  while (millis() - startTime < 5000) {
    if (CircuitPlayground.leftButton() && CircuitPlayground.rightButton()) {
      return true;
    }
    if (!switchFlag) return false; // Check for pause
  }
  return false;
}

//checks if left button is pressed twice
bool waitForLeftButtonTwice() {
  unsigned long startTime = millis();
  int count = 0;
  while (millis() - startTime < 5000) {
    if (CircuitPlayground.leftButton()) {
      count++;
      delay(300); // Debounce delay
      while (CircuitPlayground.leftButton()); // Wait for button release
    }
    if (count == 2) {
      return true;
    }
    if (!switchFlag) return false; // Check for pause
  }
  return false;
}

void S_ISR() { //attach interrupt fuction
  unsigned long currentTime = millis();
  if ((currentTime - lastDebounceTime) > debounceDelay) { //checking if the difference between the current state and the last time it was switched is greater than the delay
    switchFlag = !switchFlag; //sets the switchFlag to true/false
    lastDebounceTime = currentTime; //saves the latest time of the switch to the current time
  }
}

//LEDs
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
  
}

//LEDs
void rightButton() {
  CircuitPlayground.setPixelColor(0, 0x00FF00);
   CircuitPlayground.setPixelColor(1, 0x00FF00);
   CircuitPlayground.setPixelColor(2, 0x00FF00);
   CircuitPlayground.setPixelColor(3, 0x00FF00);
   CircuitPlayground.setPixelColor(4, 0x00FF00);
   CircuitPlayground.setPixelColor(5, 0x00FF00);
   CircuitPlayground.setPixelColor(6, 0x00FF00);
   CircuitPlayground.setPixelColor(7, 0x00FF00);
   CircuitPlayground.setPixelColor(8, 0x00FF00);
   CircuitPlayground.setPixelColor(9, 0x00FF00);
}

//LEDs
void bothButton() {
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
}

//LEDs
void doubleLeftButton() {
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
}

void gameLost() {
  Serial.println("Game Over");
  CircuitPlayground.playTone(262, 1000); // Play sad tone
  gameOver = true;
}

void resetGame() {
  count = 0;
  levelCount = 0;
}

void playGame() {
  level();
  levelCount++;
}

void level() {
  int randNumber;
  for (int i = 0; i < 4; i++) {
    randNumber = random(4);
    switch(randNumber) {
      case 0:
        leftButton();
        if (!waitForLeftButton()) {
          gameLost();
          return;
        }
        break;
      case 1:
        rightButton();
        if (!waitForRightButton()) {
          gameLost();
          return;
        }
        break;
      case 2:
        bothButton();
        if (!waitForBothButtons()) {
          gameLost();
          return;
        }
        break;
      case 3:
        doubleLeftButton();
        if (!waitForLeftButtonTwice()) {
          gameLost();
          return;
        }
        break;
    }
  }
  levelCount++;
}

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin(); 
  randomSeed(analogRead(0));
  pinMode(7, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(7), S_ISR, CHANGE); //used to pause the game
}

void loop() {
  rules();
  if (switchFlag) {
    if (!gameOver) {
      playGame();
    } else {
      resetGame();
      Serial.println("Restarting game...");
      gameOver = false;
    }
  } else {
    Serial.println("Game Paused"); //tuns LEDs to purple
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
    delay(500); //debounce delay
  }
}
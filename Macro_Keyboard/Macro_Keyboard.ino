//Include Libraries
#include <Keyboard.h>

//Switches
#define SW_1 A0
#define SW_2 A1
#define SW_3 A2
#define SW_4 15
#define SW_5 14
#define SW_6 16
#define SW_MODE 5
#define SW_SCROLL 4

//Encoder
#define ENCODER_A 3
#define ENCODER_B 2

//Bi-colour led
#define BICOLOR_R 7
#define BICOLOR_G 8

//RGB Led
#define RGB_R 6
#define RGB_G 9
#define RGB_B 10

//Threads
#define THREAD1 150
#define THREAD2 50
uint32_t thread1 = 0, thread2 = 0;

//User variables
bool state = 0;
bool press_flag = 0;
int a = 0, b = 0, c = 0;

//User functions
void rgb_update(int rled, int gled, int bled) {
  analogWrite(RGB_R, rled);
  analogWrite(RGB_G, gled);
  analogWrite(RGB_B, bled);
}

void setup() {
  Keyboard.begin();
  //Inputs
  pinMode(SW_1, INPUT_PULLUP);
  pinMode(SW_2, INPUT_PULLUP);
  pinMode(SW_3, INPUT_PULLUP);
  pinMode(SW_4, INPUT_PULLUP);
  pinMode(SW_5, INPUT_PULLUP);
  pinMode(SW_6, INPUT_PULLUP);
  pinMode(SW_MODE, INPUT_PULLUP);
  pinMode(SW_SCROLL, INPUT_PULLUP);
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  //Outputs
  pinMode(BICOLOR_G, OUTPUT);
  pinMode(BICOLOR_R, OUTPUT);
  pinMode(RGB_B, OUTPUT);
  pinMode(RGB_G, OUTPUT);
  pinMode(RGB_R, OUTPUT);

  //CC RGB LED
  rgb_update(255, 255, 255);

  a = random(255);
  b = random(255);
  c = random(255);
}

void loop() {
  if (millis() - thread1 >= THREAD1) {
    thread1 = millis();
    if (digitalRead(SW_3) == 0) {
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('c');
      press_flag = 1;
    } else if (digitalRead(SW_6) == 0) {
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('v');
      press_flag = 1;
    } else if (digitalRead(SW_2) == 0) {
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('z');
      press_flag = 1;
    } else if (digitalRead(SW_5) == 0) {
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_TAB);
      press_flag = 1;
    } else if (digitalRead(SW_1) == 0) {
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ARROW);
      press_flag = 1;
    } else if (digitalRead(SW_4) == 0) {
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ARROW);
      press_flag = 1;
    }
  }

  if (millis() - thread2 >= THREAD2) {
    thread2 = millis();
    if (press_flag) {
      press_flag = 0;
      Keyboard.releaseAll();
    }
    rgb_update(a--, b--, c--);
    if (a == 0)
      a = 255;
    if (b == 0)
      b = 255;
    if (c == 0)
      c = 255;
  }
}
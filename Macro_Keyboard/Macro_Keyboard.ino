//Include Libraries
#include <Keyboard.h>
#include <Mouse.h>
#include <Encoder.h>

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
#define THREAD1 200
#define THREAD2 50
uint32_t thread1 = 0, thread2 = 0;

//User defined class
Encoder scroll(ENCODER_A, ENCODER_B);

//User variables
int press_flag = 0, count = 0;
int scroll_val = 1;
int rled_val = 0, gled_val = 0, bled_val = 0;
int32_t value = 0, new_value = 0;

//User functions
void rgb_update(int rled, int gled, int bled) {
  analogWrite(RGB_R, rled);
  analogWrite(RGB_G, gled);
  analogWrite(RGB_B, bled);
}

void setup() {
  Keyboard.begin();
  Mouse.begin();
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

  digitalWrite(BICOLOR_R, 0);
  digitalWrite(BICOLOR_G, 1);

  rled_val = random(255);
  gled_val = random(255);
  bled_val = random(255);
}

void loop() {
  if (millis() - thread1 >= THREAD1 && press_flag == 0) {
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
      Keyboard.press(KEY_RIGHT_ARROW);
      press_flag = 1;
    } else if (digitalRead(SW_SCROLL) == 0) {
      if (scroll_val == 1) {
        scroll_val = 8;
        digitalWrite(BICOLOR_R, 1);
        digitalWrite(BICOLOR_G, 0);
      } else {
        scroll_val = 1;
        digitalWrite(BICOLOR_R, 0);
        digitalWrite(BICOLOR_G, 1);
      }
      press_flag = 10;
    }
  }

  if (millis() - thread2 >= THREAD2) {
    thread2 = millis();
    value = scroll.read();
    if (value != new_value) {
      if (value > new_value) {
        Mouse.move(0, 0, scroll_val);
      } else {
        Mouse.move(0, 0, -scroll_val);
      }
      new_value = value;
    }
    if (press_flag == 1) {
      press_flag = 10;
      Keyboard.releaseAll();
    }

    if (press_flag > 0 && count++ >= 15) {
      press_flag = 0;
      count = 0;
    }
    rgb_update(rled_val--, gled_val--, bled_val--);
    if (rled_val == 0)
      rled_val = 255;
    if (gled_val == 0)
      gled_val = 255;
    if (bled_val == 0)
      bled_val = 255;
  }
}
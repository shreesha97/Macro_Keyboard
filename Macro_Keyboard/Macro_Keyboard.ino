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

//Bi colour led
#define BICOLOR_R 7
#define BICOLOR_G 6

//RGB Led
#define RGB_R 8
#define RGB_G 9
#define RGB_B 10

//Threads
#define THREAD1 1000
#define THREAD2 200
uint64_t thread1 = 0, thread2 = 0;

//User variables
bool state = 0, value = 0;

void setup() {
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
  digitalWrite(RGB_R, 1);
  digitalWrite(RGB_G, 1);
  digitalWrite(RGB_B, 1);
}

void loop() {
  if(millis() - thread1 >= THREAD1) {
    thread1 = millis();
    state =!state;
    digitalWrite(BICOLOR_G, state);
  }

  if(millis() - thread2 >= THREAD2) {
    thread2 = millis();
    value =!value;
    digitalWrite(RGB_G, value);
  }
}

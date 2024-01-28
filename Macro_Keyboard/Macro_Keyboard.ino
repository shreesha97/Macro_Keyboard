// Include Libraries
#include <Keyboard.h>
#include <Mouse.h>
#include <Encoder.h>

// Switches
#define SW_1 A0
#define SW_2 A1
#define SW_3 A2
#define SW_4 15
#define SW_5 14
#define SW_6 16
#define SW_MODE 5
#define SW_SCROLL 4

// Encoder
#define ENCODER_A 3
#define ENCODER_B 2

// Bi-color LED
#define BICOLOR_R 7
#define BICOLOR_G 8

// RGB LED
#define RGB_R 6
#define RGB_G 9
#define RGB_B 10

// Threads
#define THREAD1 200
#define THREAD2 50
uint32_t thread1 = 0, thread2 = 0;

// User-defined class
Encoder scroll(ENCODER_A, ENCODER_B);

// User variables
int press_flag = 0;  // Flag to debounce button presses
int count = 0;       // Counter for debouncing
int scroll_val = 1;  // Initial scroll value
int rled_val = 0, gled_val = 0, bled_val = 0; // Initial RGB LED intensities
int32_t value = 0, new_value = 0;  // Encoder values

// User functions
/**
 * @brief Updates RGB LED colors.
 *
 * This function sets the RGB LED colors based on the provided values.
 *
 * @param rled Red LED intensity.
 * @param gled Green LED intensity.
 * @param bled Blue LED intensity.
 */
void rgb_update(int rled, int gled, int bled) {
  analogWrite(RGB_R, rled);
  analogWrite(RGB_G, gled);
  analogWrite(RGB_B, bled);
}

/**
 * @brief Setup function called once at the beginning.
 *
 * This function initializes the necessary configurations, pins, and variables.
 */
void setup() {
  // Initialize Keyboard and Mouse
  Keyboard.begin();
  Mouse.begin();

  // Setup Inputs
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

  // Setup Outputs
  pinMode(BICOLOR_G, OUTPUT);
  pinMode(BICOLOR_R, OUTPUT);
  pinMode(RGB_B, OUTPUT);
  pinMode(RGB_G, OUTPUT);
  pinMode(RGB_R, OUTPUT);

  // Set initial RGB LED color to white
  rgb_update(255, 255, 255);

  // Set Bicolor LED to green
  digitalWrite(BICOLOR_R, 0);
  digitalWrite(BICOLOR_G, 1);

  // Initialize random RGB LED intensities
  rled_val = random(255);
  gled_val = random(255);
  bled_val = random(255);
}

/**
 * @brief Main loop function.
 *
 * This function is executed continuously after setup.
 * It handles button presses, mouse scrolling, and RGB LED updates.
 */
void loop() {
  // Check for button presses
  if (millis() - thread1 >= THREAD1 && press_flag == 0) {
    thread1 = millis();

    // Handle different button presses
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
      // Toggle scroll value and LED colors
      if (scroll_val == 1) {
        scroll_val = 8;
        digitalWrite(BICOLOR_R, 1);
        digitalWrite(BICOLOR_G, 0);
      } else {
        scroll_val = 1;
        digitalWrite(BICOLOR_R, 0);
        digitalWrite(BICOLOR_G, 1);
      }
      press_flag = 10; // Debounce
    }
  }

  // Continuous actions
  if (millis() - thread2 >= THREAD2) {
    thread2 = millis();

    // Read encoder value for mouse scrolling
    value = scroll.read();

    // Check for changes in encoder value and move the mouse accordingly
    if (value != new_value) {
      if (value > new_value) {
        Mouse.move(0, 0, scroll_val);
      } else {
        Mouse.move(0, 0, -scroll_val);
      }
      new_value = value;
    }

    // Release keys if they were pressed
    if (press_flag == 1) {
      press_flag = 10; // Debounce
      Keyboard.releaseAll();
    }

    // Debounce button press
    if (press_flag > 0 && count++ >= 15) {
      press_flag = 0;
      count = 0;
    }

    // Update RGB LED colors with a fading effect
    rgb_update(rled_val--, gled_val--, bled_val--);
    if (rled_val == 0)
      rled_val = 255;
    if (gled_val == 0)
      gled_val = 255;
    if (bled_val == 0)
      bled_val = 255;
  }
}

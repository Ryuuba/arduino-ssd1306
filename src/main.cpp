#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SSD1306_Defs.h"

#define BASE_DELAY 1000

void changeMode();
void changeSpeed();

namespace global {
  unsigned int counter = 0;
  bool mode = false;
  uint8_t speed = 0;
  unsigned int delay = 1000;
  unsigned int pines[5] = {PB5, PB6, PB7, PB8, PB9};
  bool led_status = false;
}

void blink(unsigned);

namespace global {
    Adafruit_SSD1306* oled;
    bool ledStatus = false;
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PA5, INPUT);
  pinMode(PA6, INPUT);
  attachInterrupt(PA5, changeMode, RISING);
  attachInterrupt(PA6, changeSpeed, RISING);
  Wire.begin(SDA, SCL);
  global::oled = new Adafruit_SSD1306(OLED_WIDTH, OLED_HEIGHT);
  if(!global::oled->begin(SSD1306_SWITCHCAPVCC, 60)) {
    blink(100);
  }
  global::oled->setTextColor(SSD1306_WHITE);
}

void loop() {
  global::oled->clearDisplay();
  global::oled->setCursor(0, 0);
  global::oled->setTextSize(3);
  global::oled->print("uC 23i\n");
  global::oled->setTextSize(2);
  global::oled->print("counter\n");
  // global::oled->setCursor(0, 40);
  global::oled->printf("%d", global::counter);
  global::oled->display();
  delay(global::delay);
  global::counter = (!global::mode) 
                  ? global::counter + 1 
                  : global::counter - 1;
  global::delay = (global::speed <= 4) ? BASE_DELAY >> global::speed : 1000;
}

void blink(unsigned ms) {
  while (true) {
    digitalWrite(LED_BUILTIN, global::ledStatus);
    global::ledStatus = !global::ledStatus;
    delay(ms);
  }
}

void changeMode() {
  global::mode = !global::mode;
}

void changeSpeed() {
  global::speed = (global::speed <= 4) ? global::speed+1 : 1;
}
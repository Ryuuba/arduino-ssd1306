#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SSD1306_Defs.h"

void blink(unsigned);
void SystemClock_Config();

namespace global {
    Adafruit_SSD1306* oled;
    bool ledStatus = false;
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  SystemClock_Config();
  global::oled = new Adafruit_SSD1306(
    OLED_WIDTH, 
    OLED_HEIGHT, 
    &Wire, 
    -1
  );
  if(!global::oled->begin(SSD1306_SWITCHCAPVCC, false)) {
    blink(1000);
  }
}

void loop() {
  global::oled->clearDisplay();
  global::oled->setTextSize(2);
  global::oled->setTextColor(SSD1306_WHITE);
  global::oled->setCursor(0, 0);
  global::oled->printf("Hello world\n");
  global::oled->display();
  blink(100);
}


void blink(unsigned ms) {
  while (true) {
    digitalWrite(LED_BUILTIN, global::ledStatus);
    global::ledStatus = !global::ledStatus;
    delay(ms);
  }
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}
#include "led.h"

void Led3On(void) {
    GPIOB->PBSC ^= GPIO_PIN_5;		
}

void Led3Off(void) {
    GPIOB->PBC ^= GPIO_PIN_5;		
}

void Led3Toogle(void) {
    GPIOB->POD ^= GPIO_PIN_5;		
}

void LedInit(void) {
  GPIO_InitType GPIO_InitStructure;

  RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
  GPIO_InitStructure.Pin = GPIO_PIN_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
  Led3Off();
}

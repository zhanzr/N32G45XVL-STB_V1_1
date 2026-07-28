#include "led.h"

void Led1On(void) {
    GPIOA->PBSC ^= GPIO_PIN_8;		
}

void Led1Off(void) {
    GPIOA->PBC ^= GPIO_PIN_8;		
}

void Led1Toogle(void) {
    GPIOA->POD ^= GPIO_PIN_8;		
}

void Led2On(void) {
    GPIOB->PBSC ^= GPIO_PIN_4;		
}

void Led2Off(void) {
    GPIOB->PBC ^= GPIO_PIN_4;		
}

void Led2Toogle(void) {
    GPIOB->POD ^= GPIO_PIN_4;		
}

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

  RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
  GPIO_InitStructure.Pin = GPIO_PIN_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
	
  RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
  GPIO_InitStructure.Pin = GPIO_PIN_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
	
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
  GPIO_InitStructure.Pin = GPIO_PIN_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
	
  Led1Off();
  Led2Off();
  Led3Off();
}

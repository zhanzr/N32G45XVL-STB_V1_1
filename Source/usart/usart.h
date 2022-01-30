#ifndef __USART_H__
#define __USART_H__

#include "n32g45x.h"

#define TEST_BAUDRATE 115200

#define USARTx_RxPin GPIO_PIN_10
#define USARTx_TxPin GPIO_PIN_9

#define GPIO_APBxClkCmd RCC_EnableAPB2PeriphClk
#define USART_APBxClkCmd RCC_EnableAPB2PeriphClk

void User_Usart_Init(void);

#endif // __USART_H__

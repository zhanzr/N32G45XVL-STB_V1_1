#include "usart.h"

void User_Usart_Init(void) {
  /* Enable GPIO clock */
  GPIO_APBxClkCmd(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO, ENABLE);
  /* Enable USARTy and USARTz Clock */
  USART_APBxClkCmd(RCC_APB2_PERIPH_USART1, ENABLE);

  GPIO_InitType GPIO_InitStructure;

  /* Configure USART1 Tx as alternate function push-pull */
  GPIO_InitStructure.Pin = USARTx_TxPin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

  /* Configure USART1 Rx as input floating */
  GPIO_InitStructure.Pin = USARTx_RxPin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

  /* USARTy and USARTz configuration
   * ------------------------------------------------------*/
  USART_InitType USART_InitStructure;

  USART_InitStructure.BaudRate = TEST_BAUDRATE;
  USART_InitStructure.WordLength = USART_WL_8B;
  USART_InitStructure.StopBits = USART_STPB_1;
  USART_InitStructure.Parity = USART_PE_NO;
  USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
  USART_InitStructure.Mode = USART_MODE_RX | USART_MODE_TX;

  /* Configure USART1 */
  USART_Init(USART1, &USART_InitStructure);
  /* Enable the USART1 */
  USART_Enable(USART1, ENABLE);
}

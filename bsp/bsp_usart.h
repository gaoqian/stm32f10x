/**
  * @file bsp_usart.h
  *
  * @brief header file of bsp_usart.c 
  *  
  * @author Hins Shum
  *
  * @data 2016/09/23 23:23:52
  *
  * @version v1.0
  */
#ifndef __BSP_USART_H
#define __BSP_USART_H
/* header file include */
#include "stm32f10x.h"

/* define macro */
/**
  * @brief  usart1 macro
  * @author Hins Shum
  * @data   2016/09/23
  */
#define USART1_RCC_CLK                RCC_APB2Periph_USART1
#define USART1_GPIO_PORT_CLK          RCC_APB2Periph_GPIOA
#define USART1_GPIO_PORT              GPIOA
#define USART1_TX_PIN                 GPIO_Pin_9
#define USART1_RX_PIN                 GPIO_Pin_10
#define USART1_BAUDRATE               115200

/* extern variable */
extern int32_t bsp_usart1_init(void);

#endif /* end for bsp_usart.h */

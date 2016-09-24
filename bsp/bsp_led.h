/**
  * @file bsp_led.h
  *
  * @brief header file of bsp_led.c
  *
  * @author Hins Shum
  *
  * @data 2016/09/24 09:26:46
  *
  * @version v1.0
  */
#ifndef __BSP_LED_H
#define __BSP_LED_H
/* include */
#include "stm32f10x.h"

/* define */
/**
  * @brief  led macro
  * @author Hins Shum
  * @data   2016/09/24
  */
#define LED0                (0)
#define LED0_GPIO_PORT      GPIOB
#define LED0_GPIO_PIN       GPIO_Pin_5
#define LED0_GPIO_RCC_CLK   RCC_APB2Periph_GPIOB

#define LED1                (1)
#define LED1_GPIO_PORT      GPIOE
#define LED1_GPIO_PIN       GPIO_Pin_5
#define LED1_GPIO_RCC_CLK   RCC_APB2Periph_GPIOE

#define LED_ON              (0)
#define LED_OFF             (1)

/* extern variable */
extern int32_t bsp_led_gpio_init(void);
extern void bsp_led_control(uint32_t led_id, uint32_t led_state);
extern void bsp_led_overturn(uint32_t led_id);

#endif /* end bsp_led.h */

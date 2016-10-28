/**
  * @file bsp_led.c
  *
  * @brief led gpio initialization
  *
  * @author Hins Shum
  *
  * @date 2016/09/24 09:26:50
  *
  * @version v1.0
  */
/* header file include */
#include "bsp_led.h"

/******************************************************************************/
/*                            LED GPIO                                        */
/*                         Configuration                                      */
/******************************************************************************/

/**
  * @brief  initialize led gpio
  * @author Hins Shum
  * @date   2016/09/24
  * @param  None
  * @retval successful value of led gpio initialization
  * @explain    LED      GPIO
  *             LED0 --> GPIOB.5
  *             LED1 --> GPIOE.5
  */
int32_t bsp_led_gpio_init(void)
{
    /* led gpio register */
    GPIO_InitTypeDef GPIO_InitStructure;
    /* enable led gpio rcc clock */
    RCC_APB2PeriphClockCmd(LED0_GPIO_RCC_CLK | LED1_GPIO_RCC_CLK, ENABLE);
    /* configure led0 gpio as output push-pull */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LED0_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStructure);
    /* configure led1 gpio as output push-pull */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;
    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);
    /* LED OFF */
    GPIO_SetBits(LED0_GPIO_PORT, LED0_GPIO_PIN);
    GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);

    return 0;
} /* end bsp_led_gpio_init */

/**
  * @brief  set led bright
  * @author Hins Shum
  * @date   2016/09/24
  * @param  led_id : which led will become bright, LED0 or LED1
  * @retval None
  */
static void bsp_led_on(uint32_t led_id)
{
    switch(led_id) {
        case LED0 : GPIO_ResetBits(LED0_GPIO_PORT, LED0_GPIO_PIN); break;
        case LED1 : GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN); break;
        default : break;
    }
} /* end bsp_led_on */

/**
  * @brief  turn off the led
  * @author Hins Shum
  * @date   2016/09/24
  * @param  led_id : which led will be turn off, LED0 or LED1
  * @retval None
  */
static void bsp_led_off(uint32_t led_id)
{
    switch(led_id) {
        case LED0 : GPIO_SetBits(LED0_GPIO_PORT, LED0_GPIO_PIN); break;
        case LED1 : GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN); break;
        default : break;
    }
} /* end bsp_led_off */

/**
  * @brief  control led turn on or turn off
  * @author Hins Shum
  * @date   2016/09/24
  * @param  led_id : which led will be tcontrol, LED0 or LED1
  * @param  led_state : LED_ON  --> turn on the led
                        LED_OFF --> turn off the led
  * @retval None
  */
void bsp_led_control(uint32_t led_id, uint32_t led_state)
{
    if(!led_state) {
        bsp_led_on(led_id);
    } else {
        bsp_led_off(led_id);
    }
} /* end bsp_led_control */

/**
  * @brief  control led turn over
  * @author Hins Shum
  * @date   2016/09/24
  * @param  led_id : which led will be turn over, LED0 or LED1
  * @retval None
  */
void bsp_led_overturn(uint32_t led_id)
{
    BitAction led_state = Bit_RESET; /* led turn on */
    switch(led_id) {
        case LED0 :
            if(Bit_RESET == GPIO_ReadOutputdateBit(LED0_GPIO_PORT, LED0_GPIO_PIN)) {
                led_state = Bit_SET; /* led0 turn off */
            }
            /* led0 state turn over */
            GPIO_WriteBit(LED0_GPIO_PORT, LED0_GPIO_PIN, led_state);
            break;
        case LED1 :
            if(Bit_RESET == GPIO_ReadOutputdateBit(LED1_GPIO_PORT, LED1_GPIO_PIN)) {
                led_state = Bit_SET; /* led1 turn off */
            }
            /* led1 state turn over */
            GPIO_WriteBit(LED1_GPIO_PORT, LED1_GPIO_PIN, led_state);
            break;
        default : break;
    }
} /* end bsp_led_overturn */

/******************************************************************************/
/*                           LED GPIO                                         */
/*                             End                                            */
/******************************************************************************/

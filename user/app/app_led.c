/**
  * @file app_led.c
  *
  * @brief used to indicate that the program is running properly
  *
  * @author Hins Shum
  *
  * @data 2016/10/05 16:57:19
  *
  * @version v1.0
  */
/* header file include */
#include "includes.h"
#include "bsp_led.h"

/* marco */
#define delay_ms_led(t)     vTaskDelay(t/portTICK_RATE_MS)

/* typedef variable */

/******************************************************************************/
/*                              Led                                           */
/*                              Run                                           */
/******************************************************************************/
/**
  * @brief  app led task function
  * @author Hins Shum
  * @data   2016/10/05
  * @param  NULL
  * @retval NULL
  */
static void led_task(void *pvParameters)
{
    while(true)
    {
        /* green light */
        bsp_led_control(LED1, LED_ON);
        delay_ms_led(500);
        bsp_led_control(LED1, LED_OFF);
        delay_ms_led(500);
	}
} /* end led_task */


/**
  * @brief  app led task creat
  * @author Hins Shum
  * @data   2016/10/05
  * @param  NULL
  * @retval NULL
  */
void app_led_creat(void)
{
    xTaskCreate(led_task,
                "led",
                configMINIMAL_STACK_SIZE,
                NULL,
                LED_TASK_PRIORITY,
                NULL);
} /* end app_led_creat */
/******************************************************************************/
/*                              Led                                           */
/*                              End                                           */
/******************************************************************************/

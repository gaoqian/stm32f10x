/**
  * @file app_cmd.c
  *
  * @brief command system
  *
  * @author Hins Shum
  *
  * @data 2016/10/01 15:51:29
  *
  * @version v1.0
  */
/* header file include */
#include "includes.h"

/******************************************************************************/
/*                            Command                                         */
/*                              Run                                           */
/******************************************************************************/
/**
  * @brief  task initialization
  * @author Hins Shum
  * @data   2016/10/01
  * @parm   NULL
  * @retval NULL
  */
static void task_init(void)
{

} /* end task_init */

/**
  * @brief  app command task function
  * @author Hins Shum
  * @data   2016/10/01
  * @param  NULL
  * @retval NULL
  */
void cmd_task(void *pvParameters)
{
    task_init();
    while(true) {

    }
} /* end cmd_task */

/**
  * @brief  app command task creat
  * @author Hins Shum
  * @data   2016/10/01
  * @param  NULL
  * @retval NULL
  */
void app_cmd_creat(void)
{
    xTaskCreate(cmd_task,
                "shell",
                configMINIMAL_STACK_SIZE << 2,
                NULL,
                CMD_TASK_PRIORITY,
                NULL);
} /* end app_cmd_creat */

/******************************************************************************/
/*                            Command                                         */
/*                              End                                           */
/******************************************************************************/

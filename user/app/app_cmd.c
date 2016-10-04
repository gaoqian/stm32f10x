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
#include <string.h>
#include "includes.h"
#include "command.h"
#include "console.h"

/* typedef variable */
typedef struct cmd_info_s
{
    uint32_t len;
    uint8_t buffer[CFG_CBSIZE];
    bool is_recieveing;
} cmd_info_t;

cmd_info_t cmd_info;

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
    uint8_t ch = 0;
    task_init();
    while(true) {
        console_printf(CFG_PROMPT); /* print prompt */
        cmd_info.is_recieveing = true;
        while(cmd_info.is_recieveing) {
            if(1) {
                switch (cmd_recieve(ch, cmd_info.len)) {
                    case -1 : cmd_info.len--; break;    /* bacaspace button press */
                    case 0 : cmd_info.len++; break;     /* enter button not press */
                    default :                           /* enter button press */
                        strcpy((char *)cmd_info.buffer, (const char *)g_cmd_buffer);
                        if(cmd_run(cmd_info.buffer) <= 0) {
                            g_cmd_buffer[0] = '\0';
                        }
                        cmd_info.len = 0;
                        cmd_info.is_recieveing = false;
                        break;
                } /* end switch case */
            }
        } /* end while(is_recieveing) */
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

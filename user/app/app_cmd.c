/**
  * @file app_cmd.c
  *
  * @brief command system
  *
  * @author Hins Shum
  *
  * @date 2016/10/01 15:51:29
  *
  * @version v1.0
  */
/* header file include */
#include <string.h>
#include "includes.h"
#include "command.h"
#include "console.h"

/* marco */
#define delay_ms_cmd(t)     vTaskDelay(t/portTICK_RATE_MS)

#if defined CMD_DEBUG
    #define cmd_debug(fmt, args...)     console_printf(fmt, ##args)
#else
    #define cmd_debug(fmt, args...)
#endif

#define cmd_printf(fmt, args...)        console_printf(fmt, ##args)

#define CMD_QUEUE_RECIEVE_MAXDELAY      (0xFFU)

/* typedef variable */
cmd_info_t cmd_info;

/******************************************************************************/
/*                            Command                                         */
/*                              Run                                           */
/******************************************************************************/
/**
  * @brief  task initialization
  * @author Hins Shum
  * @date   2016/10/01
  * @parm   NULL
  * @retval NULL
  */
static void task_init(void)
{
    cmd_info.cmd_queue = xQueueCreate(5, sizeof(uint8_t));
    if(NULL == cmd_info.cmd_queue) {
        cmd_debug("### Command Queue Creat ERROR ### Please RESET the board ###\n");
        while(true);
    }
} /* end task_init */

/**
  * @brief  app command task function
  * @author Hins Shum
  * @date   2016/10/01
  * @param  NULL
  * @retval NULL
  */
void cmd_task(void *pvParameters)
{
    uint8_t ch = 0;
    task_init();
    while(true) {
        cmd_printf(CFG_PROMPT); /* print prompt */
        cmd_info.is_recieveing = true;
        while(cmd_info.is_recieveing) {
            if(xQueueReceive(cmd_info.cmd_queue, &ch, CMD_QUEUE_RECIEVE_MAXDELAY)) { /* wait for the message queue to arrive */
                switch (cmd_recieve(ch, cmd_info.len)) {
                    case -2 : break;                    /* backspace button is pressed when len is zero */
                    case -1 : cmd_info.len--; break;    /* backspace button is pressed */
                    case 0 :                            /* enter button is not pressed */
                        if(cmd_info.len < (CFG_CBSIZE - 1)) {
                            cmd_info.len++;
                        }
                        break;
                    case -3 :                           /* nothing input but enter key is pressed */
                    default :                           /* enter button is pressed */
                        if(cmd_info.len > 0) {
                            strcpy((char *)cmd_info.buffer, (const char *)g_cmd_buffer);
                            if(cmd_run(cmd_info.buffer) <= 0) {
                                g_cmd_buffer[0] = '\0';
                            }
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
  * @date   2016/10/01
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

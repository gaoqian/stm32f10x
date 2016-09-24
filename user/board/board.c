/**
  * @file board.c
  *
  * @brief initialize all devices on the board
  *
  * @author Hins Shum
  *
  * @data 2016/09/24 14:47:29
  *
  * @version v1.0
  */
/* header file include */
#include <stddef.h>
#include <stdbool.h>
#include "bsp_led.h"
#include "bsp_usart.h"
#include "console.h"

/* define */
#define BOARD_DEBUG
#ifdef BOARD_DEBUG
#define board_printf(fmt, args...)      console_printf(fmt, ##args)
#else
#define board_printf(fmt, args...)
#endif

/* typedef */
typedef int32_t (init_fnc_t)(void);

/* variables */
init_fnc_t *init_sequence[] = {
    bsp_usart1_init,        /* initialize usart1 and gpio pin */
    bsp_led_gpio_init,      /* initialize led gpio pin */
    NULL
};

/* function prototypes */
static void hang(void);

/******************************************************************************/
/*                             Board                                          */
/*                         Configuration                                      */
/******************************************************************************/

/**
  * @brief  initialize all devices on the board
  * @author Hins Shum
  * @data   2016/09/24
  * @param  None
  * @retval None
  */
void start_arm(void)
{
    init_fnc_t **init_fnc_ptr = NULL;

    for(init_fnc_ptr = init_sequence; *init_fnc_ptr; ++init_fnc_ptr) {
        if(0 != (*init_fnc_ptr)()) {
            /* init error, hang the system */
            hang();
        }
    }
    board_printf("Initialize bsp success!\n");
} /* end start_arm */

/**
  * @brief  when initialize failed, hang the system
  * @author Hins Shum
  * @data   2016/09/24
  * @param  None
  * @retval None
  */
static void hang(void)
{
    board_printf("### ERROR ### Please RESET the board ###\n");
    while(true);
} /* end hang */

/******************************************************************************/
/*                             Board                                          */
/*                              End                                           */
/******************************************************************************/

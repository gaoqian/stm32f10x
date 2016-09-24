/**
  * @file console.c
  *
  * @brief console initialization
  *
  * @author Hins Shum
  *
  * @data 2016/09/24 14:11:07
  *
  * @version v1.0
  */
/* header file include */
#include <stdarg.h>
#include <stdio.h>
#include "bsp_usart.h"
#include "console.h"

/******************************************************************************/
/*                            Console                                         */
/*                         Configuration                                      */
/******************************************************************************/

/**
  * @brief  send a string on serial port
  * @author Hins Shum
  * @data   2016/09/24
  * @param  s : a sting will be send on serial port
  * @retval None
  */
static void console_puts(const char *s)
{
    /* if *s is \0, stop send */
    while(*s) {
        bsp_serial_putc(*s++);
    }
} /* end console_puts */

/**
  * @brief  output somethins on the console
  * @author Hins Shum
  * @data   2016/09/24
  * @param  varargs 
  * @retval None
  */
void console_printf(const char *fmt, ...)
{
    va_list args;
    char printbuffer[CFG_PBSIZE] = {0};

    va_start(args, fmt);
    /* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
    vsprintf(printbuffer, fmt, args);
    va_end(args);

    /* print the string */
    console_puts(printbuffer);
} /* end console_printf */

/******************************************************************************/
/*                            Console                                         */
/*                              End                                           */
/******************************************************************************/

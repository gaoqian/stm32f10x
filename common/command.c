/**
  * @file command.c
  *
  * @brief all shell commands are define here
  *
  * @author Hins Shum
  *
  * @data 2016/10/01 13:56:19
  *
  * @version v1.0
  */
/* header file include */
#include "command.h"
#include "board.h"

/******************************************************************************/
/*                            Command                                         */
/*                         Configuration                                      */
/******************************************************************************/

/**
  * @brief  print version command
  * @author Hins Shum
  * @data   2016/10/01
  * @param  cmdtp : command data
  *         flag : no use
  *         argc : number of parameters
  *         argv : parameters string
  * @retval return 0 if the function succeeds
  */
int32_t do_version(cmd_stl_t *cmdtp, int32_t flag, int32_t argc, uint8_t *argv[])
{
    console_printf("\n%s\n", version_string);   /* print version message */
    return 0;
} /* end do_version */

ARM_CMD(
    version,
    1,
    do_version,
    "version - print monitor version",
    NULL
);

/******************************************************************************/
/*                            Command                                         */
/*                              End                                           */
/******************************************************************************/








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
#include <string.h>
#include "command.h"
#include "board.h"
#include "console.h"

/* variable */
uint8_t g_cmd_buffer[CFG_CBSIZE];
extern cmd_tbl_t arm_cmd$$Base;
extern cmd_tbl_t arm_cmd$$Limit;

/* static function prototypes */
static int32_t cmd_parse_line(uint8_t *line, uint8_t *argv[]);
static cmd_tbl_t *cmd_find(const uint8_t *cmd);

/******************************************************************************/
/*                            Command                                         */
/*                              Set                                           */
/******************************************************************************/

/**
  * @brief  print version command
  * @author Hins Shum
  * @data   2016/10/01
  * @param  cmdtp : command data
  *         argc : number of parameters
  *         argv : parameters string
  * @retval return 0 if the function succeeds
  */
int32_t do_version(cmd_tbl_t *cmdtp, int32_t argc, uint8_t *argv[])
{
    console_printf("%s\n", version_string);   /* print version message */
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
/*                             Func                                           */
/******************************************************************************/
/**
  * @brief  recieves commands into the buffer
  * @author Hins Shum
  * @data   2016/10/01
  * @param  ch : recieve a character form monitor
  *         len : the length that has been recieved
  * @retval the length of recieve buffer
  *         0 : recieve not completed
  *         -1 : the length of recieve buffer needs to be reduced by one
  */
int32_t cmd_recieve(uint8_t ch, uint32_t len)
{
    uint8_t *pbuffer = g_cmd_buffer + len;
    switch (ch) {
        case '\r' :
        case '\n' :
            console_printf("\n");
            *pbuffer = '\0';
            if(0 == len) {
                return -3; /* nothing input but enter key press */
            }
            return (pbuffer - g_cmd_buffer);
        case '\b' :
            if(len) {
                console_printf("\b \b");
                return -1; /* the backspace key is pressed and the length is not zero */
            }
            return -2; /* the backspace key is pressed and the length is zero */
        default : break;
    }
    *pbuffer = ch;
    console_printf("%c", *pbuffer);
    return 0;
} /* end cmd_recieve */

/**
  * @brief  parse and execute commands
  * @author Hins Shum
  * @data   2016/10/01
  * @param  cmd_buffer : command buffer
  * @retval -1 : command run failed
  *         0 : command run succeed
  */
int32_t cmd_run(uint8_t *cmd_buffer)
{
    cmd_tbl_t *cmdtp = NULL;
    int32_t argc = 0;
    uint8_t *argv[CFG_MAXARGS + 1];

    if(!cmd_buffer || !*cmd_buffer) {
        return -1;      /* empty command */
    }

    if(strlen((const char *)cmd_buffer) >= (CFG_CBSIZE - 1)) {
        console_printf("## Command too long! ##\n");
        return -1;  /* the length of command buffer over CFG_CBSIZE */
    }

    if(0 == (argc = cmd_parse_line(cmd_buffer, argv))) {
        return -1;  /* argc is zero, command is empty */
    }
    if(NULL == (cmdtp = cmd_find(argv[0]))) {
        console_printf("Unkonw command '%s' - try 'help'\n", argv[0]);
        return -1;
    }
    if(argc > cmdtp->maxargs) {
        console_printf("Usage:\n%s\n", cmdtp->usage);
        return -1;
    }
    if(0 != cmdtp->cmd(cmdtp, argc, argv)) {
        return -1;
    }
    return 0;
} /* end cmd_run */

/**
  * @brief  parse and split command line
  * @author Hins Shum
  * @data   2016/10/02
  * @param  line : command line
  *         argv[] : command parameters
  * @retval parameters number
  */
static int32_t cmd_parse_line(uint8_t *line, uint8_t *argv[])
{
    uint32_t nargs = 0;
    while(nargs < CFG_MAXARGS) {
        while((*line == ' ') || (*line == '\t')) {  /* skip any white space */
            line++;
        }
        if(!*line) {
            argv[nargs] = NULL;
            return nargs;
        }
        argv[nargs++] = line;
        while(*line && (*line != ' ') && (*line != '\t')) {
            line++;
        }
        if(!*line) {
            argv[nargs] = NULL;
            return nargs;
        }
        *line++ = '\0';
    }
    console_printf("** Too many args (max %d) **\n", CFG_MAXARGS);
    return nargs;
} /* end cmd_parse_line */

/**
  * @brief  find whether the command exists
  * @author Hins Shum
  * @data   2016/10/02
  * @param  cmd : command parameter argv[0]
  * @retval command addr
  *         NULL : if command not find
  */
static cmd_tbl_t *cmd_find(const uint8_t *cmd)
{
    cmd_tbl_t *cmdtp = NULL;
    uint32_t len = strlen((const char *)cmd);
    for(cmdtp = &arm_cmd$$Base; cmdtp != &arm_cmd$$Limit; cmdtp++) {
//    if(1) {
        if(0 == strncmp((const char *)cmd, (const char *)cmdtp->name, len)) {
			if(len == strlen((const char *)cmdtp->name)) {
				return cmdtp;
			}
		}
    }
	return NULL;
} /* end cmd_find */



/******************************************************************************/
/*                            Command                                         */
/*                              End                                           */
/******************************************************************************/





/**
  * @file command.h
  *
  * @brief header file of command.c
  *
  * @author Hins Shum
  *
  * @date 2016/10/01 13:59:36
  *
  * @version v1.0
  */
#ifndef __COMMAND_H
#define __COMMAND_H

/* header file include */
#include "includes.h"

/* typedef variable */
struct cmd_tbl_s
{
    uint8_t *name;      /* command name */
    uint32_t maxargs;   /* the maximum number of parameters the command can receive */
    int32_t (*cmd)(struct cmd_tbl_s *cmdtp, int32_t argc, uint8_t *argv[]);    /* do command function */
    uint8_t *usage;     /* usage message(short) */
#if defined CFG_LONGHELP
    uint8_t *help;      /* help message(long) */
#endif
};
typedef struct cmd_tbl_s cmd_tbl_t;

typedef struct cmd_info_s
{
    uint32_t len;
    uint8_t buffer[CFG_CBSIZE];
    bool is_recieveing;
    QueueHandle_t cmd_queue;
} cmd_info_t;

/* define macro */
#define STRUCT_SECTION  __attribute__((unused, section("armboot_cmd")))

#if defined CFG_LONGHELP
    #define ARMBOOT_CMD(name, maxargs, cmd, usage, help) \
    cmd_tbl_t __armboot_cmd_##name STRUCT_SECTION = {#name, maxargs, cmd, usage, help}
#else
    #define ARMBOOT_CMD(name, maxargs, cmd, usage) \
    cmd_tbl_t __armboot_cmd_##name STRUCT_SECTION = {#name, maxargs, cmd, usage}
#endif

/* extern variable */
extern uint8_t g_cmd_buffer[CFG_CBSIZE];

/* extern function */
extern int32_t cmd_recieve(uint8_t ch, uint32_t len);
extern int32_t cmd_run(uint8_t *cmd_buffer);

#endif /* end command.h */

/**
 * @file includes.h
 *
 * @brief include C header file, freertos header file and stm32f10x lib header file
 *
 * @author Hins Shum
 *
 * @date 2016/09/23
 *
 * @version v1.0
 */
#ifndef __INCLUDES_H
#define __INCLUDES_H

/* C header file */
#include <stdbool.h>

/* stm32f10x header file */
#include "stm32f10x_it.h"

/* FreeRTOS header file */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"
#include "event_groups.h"

/* user header file */

/* define version */
#define VERSION                 ("ARM BOOT V1.0")
#define CONFIG_IDENT_STRING     ("for stm32f103zet6")

/* define config marco */
#define CFG_LONGHELP

/* define debug marco */
#define BOARD_DEBUG

/* define task priority */
#define CMD_TASK_PRIORITY       (tskIDLE_PRIORITY + 3)

#endif /* end for includes.h */

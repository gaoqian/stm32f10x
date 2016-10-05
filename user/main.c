/**
  * @file main.c
  *
  * @brief enter to the world of C language
  *  
  * @author Hins Shum
  *
  * @data    2016/09/23 21:02:12
  *
  * @version v1.0
  */
/* include header file */
#include "includes.h"
#include "board.h"

/******************************************************************************/
/*                              Main                                          */
/*                              Start                                         */
/******************************************************************************/

/**
  * @brief  main function
  * @author Hins Shum
  * @data   2016/09/23
  * @param  None
  * @retval None
  */
int main(void)
{
    /* board level initialization */
    start_arm();    
    /* start the scheduler */
    vTaskStartScheduler();
    /* dead loop */
    while(true);
} /* end main */

/******************************************************************************/
/*                              Main                                          */
/*                              End                                           */
/******************************************************************************/

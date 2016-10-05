/**
  * @file bsp_nvic.c
  *
  * @brief interrupt nvic config
  *
  * @author Hins Shum
  *
  * @data 2016/10/05 19:25:42
  *
  * @version v1.0
  */
/* header file include */
#include "bsp_nvic.h"

/* typedef variable */

/******************************************************************************/
/*                              NVIC                                          */
/*                              Run                                           */
/******************************************************************************/
/**
  * @brief  nvic configuration
  * @author Hins Shum
  * @data   2016/10/05
  * @param  NULL
  * @retval 0
  */
int32_t bsp_nvic_init(void)
{
    /* turns off the global interrupt */
    __set_PRIMASK(1);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    return 0;
}

/******************************************************************************/
/*                              NVIC                                          */
/*                              End                                           */
/******************************************************************************/

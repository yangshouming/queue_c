/*
 * @Author: Stream
 * @Date: 2020-04-07 19:47:40
 * @LastEditTime: 2020-04-07 19:52:29
 * @LastEditors: Stream
 * @Description: 顺序环形队列
 * @FilePath: \Queue\Queue\queue_ring_struct\queue_ring_struct.h
 * @version: v0.0.1
 */

#ifndef _QUEUE_RING_STRUCT_H_
#define _QUEUE_RING_STRUCT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __DEBUG__ //调试信息宏开关

#ifdef __DEBUG__
#include <stdio.h>

//带标识头打印
#define queue_log_printf(format, ...)  \
    do                                 \
    {                                  \
        printf("[QueenRingLog]:");     \
        printf(format, ##__VA_ARGS__); \
    } while (0)

//不带标识头打印
#define queue_printf(format, ...)      \
    do                                 \
    {                                  \
        printf(format, ##__VA_ARGS__); \
    } while (0)

#else

//不打印
#define queue_log_printf(format, ...)
#define queue_printf(format, ...)

#endif

#define QUEUE_LEN 5      //队列长度，可缓存的数据成员个数
#define USER_ARRAY_LEN 3 //数据成员里的某数组长度

/*数据成员类型*/
typedef struct ElemType
{
    int CtrlData;
    int RunData;
    int UserArray[USER_ARRAY_LEN];
    //int 其他数据

} TS_ElemType;

/*环形队列结构体*/
typedef struct QueenRing
{
    TS_ElemType ElemRrray[QUEUE_LEN]; //数据成员数组
    int Rear;                         //尾部入队 (写)
    int Front;                        //头部出队 (读)

} TS_QueenRing;

/*
* 函数名称 : ring_buff_init
* 功能描述 : 队列初始化
* 参    数 : 无
* 返回值   :  队列指针:初始化成功
             NULL:初始化不成功
* 示    例  p_queue = ring_buff_init();
*/
/******************************************************************************/
extern TS_QueenRing *ring_buff_init( void );
/*
* 函数名称 : ring_buff_init
* 功能描述 : 队列初始化
* 参    数 : 无
* 返回值   :  队列指针:初始化成功
             NULL:初始化不成功
* 示    例  p_queue = ring_buff_init();
*/
/******************************************************************************/
extern int ring_buff_get_fullstate( TS_QueenRing *p_queue );
/*
* 函数名称 : ring_buff_get_emptystate
* 功能描述 : 判断环形队列是否为空
* 参    数 : *p_queue 队列指针
* 返回值   : 0:已空
             1:未空
* 示    例  ret_code=ring_buff_get_emptystate(p_queue);
*/
/******************************************************************************/
extern int ring_buff_get_emptystate( TS_QueenRing *p_queue );
/*
* 函数名称 : ring_buff_insert
* 功能描述 : 环形队列插入数据
* 参    数 : *p_queue 队列指针
             *p_elem 数据指针
* 返回值   : -1:队列指针为空
             -2:数据指针为空
             -3:队列已满
             0: 正常
* 示    例  ret_code=ring_buff_insert(p_queue,p_elem);
*/
/******************************************************************************/
extern int ring_buff_insert( TS_QueenRing *p_queue, TS_ElemType *p_elem );
/*
* 函数名称 : ring_buff_get
* 功能描述 : 环形队列读取数据
* 参    数 : *p_queue 队列指针
             *p_elem 数据指针
* 返回值   : -1:队列指针为空
             -2:数据指针为空
             -3:队列已空
             0: 正常
* 示    例  ret_code=ring_buff_get(p_queue,p_elem);
*/
/******************************************************************************/
extern int ring_buff_get( TS_QueenRing *p_queue, TS_ElemType *p_elem );
/*
* 函数名称 : ring_buff_destory
* 功能描述 : 环形队列销毁释放
* 参    数 : *p_queue 队列指针
* 返回值   : -1:队列指针为空
             0: 正常
* 示    例  ret_code=ring_buff_destory(p_queue);
*/
/******************************************************************************/
extern int ring_buff_destory( TS_QueenRing *p_queue );
/*
* 函数名称 : printf_elem_data
* 功能描述 : 环形队列数据打印
* 参    数 : *p_elem 数据指针
* 返回值   : 无
* 示    例  printf_elem_data(p_elem);
*/
/******************************************************************************/
extern void printf_elem_data( TS_ElemType *p_elem );

#endif

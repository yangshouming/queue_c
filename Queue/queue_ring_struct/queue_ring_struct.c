/*
 * @Author: Stream
 * @Date: 2020-04-07 19:47:40
 * @LastEditTime: 2020-04-07 19:52:52
 * @LastEditors: Stream
 * @Description:
 * @FilePath: \Queue\Queue\queue_ring_struct\queue_ring_struct.c
 * @version: v0.0.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_ring_struct.h"

/*
* 函数名称 : ring_buff_init
* 功能描述 : 队列初始化
* 参    数 : 无
* 返回值   :  队列指针:初始化成功
             NULL:初始化不成功
* 示    例  p_queue = ring_buff_init();
*/
/******************************************************************************/
TS_QueenRing *ring_buff_init( void )
{
    TS_QueenRing *pQueen = NULL;

    pQueen = ( TS_QueenRing * )malloc( sizeof( TS_QueenRing ) ); //分配队列内存空间
    if ( pQueen == NULL )
    {
        queue_log_printf( "ring_buff_init malloc error\n" );
        return NULL;
    }

    //初始化数据
    pQueen->Rear = 0;
    pQueen->Front = 0;
    memset( &pQueen->ElemRrray, 0, QUEUE_LEN * ( sizeof( TS_ElemType ) ) );
    queue_log_printf( "init p_queue%p\n", pQueen );
    return pQueen;
}

/*
* 函数名称 : ring_buff_get_fullstate
* 功能描述 : 判断环形队列是否已经满了
* 参    数 : *p_queue 队列指针
* 返回值   : 0:已满
             1:未满
* 示    例  ret_code=ring_buff_get_fullstate(p_queue);
*/
/******************************************************************************/
int ring_buff_get_fullstate( TS_QueenRing *p_queue )
{
    /*如果写位置减去读位置等于队列长度，就说明这个环形队列已经满*/
    if ( ( p_queue->Rear - p_queue->Front ) == QUEUE_LEN )
    {
        return ( 1 );
    }
    else
    {
        return ( 0 );
    }
}

/*
* 函数名称 : ring_buff_get_emptystate
* 功能描述 : 判断环形队列是否为空
* 参    数 : *p_queue 队列指针
* 返回值   : 0:已空
             1:未空
* 示    例  ret_code=ring_buff_get_emptystate(p_queue);
*/
/******************************************************************************/
int ring_buff_get_emptystate( TS_QueenRing *p_queue )
{
    /*如果写位置和读的位置相等，就说明这个环形队列为空*/
    if ( p_queue->Rear == p_queue->Front )
    {
        return ( 1 );
    }
    else
    {
        return ( 0 );
    }
}

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
int ring_buff_insert( TS_QueenRing *p_queue, TS_ElemType *p_elem )
{
    if ( p_queue == NULL )
    {
        queue_log_printf( "p_queue null\n" );
        return ( -1 );
    }

    if ( p_elem == NULL )
    {
        queue_log_printf( "p_elem null\n" );
        return ( -2 );
    }

    if ( ring_buff_get_fullstate( p_queue ) == 1 )
    {
        queue_log_printf( "buff is full\n" );
        return ( -3 );
    }

    memcpy( &p_queue->ElemRrray[p_queue->Rear % QUEUE_LEN], p_elem, sizeof( TS_ElemType ) ); //复制数据

    p_queue->Rear++;

    queue_log_printf( "ring_buff_insert   p_queue->Front %d,p_queue->Rear %d\n", p_queue->Front, p_queue->Rear );

    return ( 0 );
}

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
int ring_buff_get( TS_QueenRing *p_queue, TS_ElemType *p_elem )
{

    if ( p_queue == NULL )
    {
        queue_log_printf( "p_queue null\n" );
        return ( -1 );
    }

    if ( p_elem == NULL )
    {
        queue_log_printf( "p_elem null\n" );
        return ( -2 );
    }

    if ( ring_buff_get_emptystate( p_queue ) == 1 )
    {
        queue_log_printf( "buff is empty\n" );
        return ( -3 );
    }

    memcpy( p_elem, &p_queue->ElemRrray[p_queue->Front % QUEUE_LEN], sizeof( TS_ElemType ) ); //复制数据

    p_queue->Front++;

    queue_log_printf( "ring_buff_get   p_queue->Front %d,p_queue->Rear %d\n", p_queue->Front, p_queue->Rear );
    if ( p_queue->Front > QUEUE_LEN ) //当队头到达队列长度时，队头和队尾都做减去队列长度操作，防止溢出
    {
//        p_queue->Front = p_queue->Front - QUEUE_LEN;
//        p_queue->Rear = p_queue->Rear - QUEUE_LEN;

        p_queue->Front = 0;
        p_queue->Rear = p_queue->Rear % QUEUE_LEN;
    }

    return 0;
}

/*
* 函数名称 : ring_buff_destory
* 功能描述 : 环形队列销毁释放
* 参    数 : *p_queue 队列指针
* 返回值   : -1:队列指针为空
             0: 正常
* 示    例  ret_code=ring_buff_destory(p_queue);
*/
/******************************************************************************/
int ring_buff_destory( TS_QueenRing *p_queue )
{
    if ( p_queue == NULL )
    {
        queue_log_printf( "p null\n" );
        return ( -1 );
    }
    queue_log_printf( "free p_queue%p\n", p_queue );
    free( p_queue );

    return ( 0 );
}

/*
* 函数名称 : printf_elem_data
* 功能描述 : 环形队列数据打印
* 参    数 : *p_elem 数据指针
* 返回值   : 无
* 示    例  printf_elem_data(p_elem);
*/
/******************************************************************************/
void printf_elem_data( TS_ElemType *p_elem )
{
    int i = 0;
    queue_printf( "\n" );
    queue_log_printf( "p_elem->CtrlData:%d\n", p_elem->CtrlData );
    queue_log_printf( "p_elem->RunData:%d\n", p_elem->RunData );

    for ( i = 0; i < USER_ARRAY_LEN; i++ )
    {
        queue_printf( "%02d ", i );
    }
    queue_printf( "\n" );
    for ( i = 0; i < USER_ARRAY_LEN; i++ )
    {
        queue_printf( "%02d ", p_elem->UserArray[i] );
    }
    queue_printf( "\n" );
}

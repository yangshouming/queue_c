/*
 * @Author: your name
 * @Date: 2020-03-25 16:48:58
 * @LastEditTime: 2020-03-26 09:46:00
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \keil_simulator_printf\main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue_ring_struct.h"

#define NUMBER_SEPARATE(num,place)  ((num)/(place)%10)


int num = 123456;

int main()
{
    int i = 0;
    char cmd;
    int wcnt = 0;
    TS_ElemType ElemRead;
    TS_ElemType ElemWrite;

    TS_QueenRing *pt_ring_buff = NULL;
    pt_ring_buff = ring_buff_init(); /*初始化一个环形缓冲区*/

    printf( "enter cmd:r-read,w-write,q-quit\n" );
    printf( "sizeof(TS_ElemType):%d sizeof(TS_QueenRing):%d\n", sizeof( TS_ElemType ), sizeof( TS_QueenRing ) );

    memset( &ElemRead, 0, ( sizeof( TS_ElemType ) ) );
    memset( &ElemWrite, 0, ( sizeof( TS_ElemType ) ) );

    printf_elem_data( &ElemRead ); //打印数据成员信息


    while ( 1 )
    {

        scanf( "%s", &cmd );

        switch ( cmd )
        {

            case 'r':
            {
                printf( "ring_buff_get " );
                /*从环形缓冲区中读出数据*/
                if ( ring_buff_get( pt_ring_buff, &ElemRead ) == 0 )
                {
                    printf( "ok\n" );
                }
                else
                {
                    printf( "error\n" );
                }
                printf_elem_data( &ElemRead ); //打印数据成员信息
                break;
            }

            case 'w':
            {
                /*向环形缓冲区中写入数据*/
                ElemWrite.CtrlData = wcnt;
                ElemWrite.RunData = wcnt;
                for ( i = 0; i < USER_ARRAY_LEN; i++ )
                {
                    /* code */
                    ElemWrite.UserArray[i] = wcnt;
                }
                printf( "ring_buff_insert " );
                if ( ring_buff_insert( pt_ring_buff, &ElemWrite ) == 0 )
                {
                    wcnt++;
                    printf( "ok\n" );
                }
                else
                {
                    printf( "error\n" );
                }

                printf_elem_data( &ElemWrite ); //打印数据成员信息

                break;
            }

            case 'q':
            {
                /*销毁一个环形缓冲区*/
                ring_buff_destory( pt_ring_buff );
                return ( 1 );
                //break;
            }

            default:
            {
                printf( "error cmd\n" );
                break;
            }
        }

        printf( "*****all data******\n" );
        for ( i = 0; i < QUEUE_LEN; i++ )
        {
            printf_elem_data(&pt_ring_buff->ElemRrray[i]); //打印全部数据成员信息
        }
        
         printf( "============================================================\n" );
    }
}

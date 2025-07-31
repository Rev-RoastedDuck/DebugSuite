/*
 * test.c
 *	
 *  Created on: 2025_07_31
 *      Author: Rev_RoastDuck
 *      Github: https://github.com/Rev-RoastedDuck
 * 
 * :copyright: (c) 2025 by Rev-RoastedDuck.
 */

#include "debug.h"
#include <sys/time.h>
#include <unistd.h>

int main(void){

    TIME_TAKEN_SATRT(1);
    usleep(10000);
    TIME_TAKEN_END;

    DEBUG_PRINT(1,"hello\r\n");
    
    DEBUG_PRINT_DEBUG(1,"hello");
    DEBUG_PRINT_WARNING(1,"hello");
    DEBUG_PRINT_FATAL(1,"hello");
    DEBUG_PRINT_SUCCESS(1,"hello");
    DEBUG_PRINT_NOTICE(1,"hello");
    DEBUG_PRINT_INFO(1,"hello");
    
    int a = 0;
    float b = 12.22;
    DEBUG_PRINT_VALUES(a, b);

    DEBUG_ASSERT(1 < 0);

    return 0;
}
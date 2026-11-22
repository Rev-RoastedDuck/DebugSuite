/*
 * test.c
 *	
 *  Created on: 2025_07_31
 *      Author: Rev_RoastDuck
 *      Github: https://github.com/Rev-RoastedDuck
 * 
 * :copyright: (c) 2025 by Rev-RoastedDuck.
 */
#include "time.h"
#include "stdint.h"
#include "debug_suite.h"

/*
 * Integration note:
 *   The #undef / #define overrides below are for demonstration only,
 *   to temporarily replace the default hook implementations in this test.
 *
 *   For production integration, do NOT override hooks this way. Instead,
 *   define them directly in the "hook and callback" section of
 *   debug_suite.h, for example:
 *
 *       #define __DEBUG_GET_LOCAL_TIME_MS_HOOK   dbg_local_time_ms
 *       #define __DEBUG_GET_SYSTEM_TIME_MS_HOOK  dbg_system_time_ms
 *
 *   This way the compile-time static checks in the header can correctly
 *   recognize the hooks as "configured".
 */

#if defined(_WIN32)
	unsigned long GetTickCount(void);
	static unsigned long long dbg_system_time_ms(void) { return (unsigned long long)GetTickCount(); }
	static unsigned long long dbg_local_time_ms(void) { return (unsigned long long)time(NULL) * 1000ULL; }
	void Sleep(unsigned long dwMilliseconds);
	static void dbg_sleep_ms(int ms) { Sleep((unsigned long)ms); }
#else
	#include <sys/time.h>
	#include <unistd.h>
	static unsigned long long dbg_system_time_ms(void) {
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return (unsigned long long)tv.tv_sec * 1000ULL + (unsigned long long)tv.tv_usec / 1000ULL;
	}
	static unsigned long long dbg_local_time_ms(void) {
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return (unsigned long long)tv.tv_sec * 1000ULL + (unsigned long long)tv.tv_usec / 1000ULL;
	}
	static void dbg_sleep_ms(int ms) { usleep(ms * 1000); }
#endif
#undef  __DEBUG_GET_SYSTEM_TIME_MS_HOOK
#define __DEBUG_GET_SYSTEM_TIME_MS_HOOK dbg_system_time_ms
#undef  __DEBUG_GET_LOCAL_TIME_MS_HOOK
#define __DEBUG_GET_LOCAL_TIME_MS_HOOK dbg_local_time_ms

int main(void){
    debug_set_level(DEBUG_LEVEL_DEBUG);
    
    DEBUG_PRINT_DEBUG(1,"hello");
    // DEBUG_PRINT_INFO(1,"hello");
    // DEBUG_PRINT_SUCCESS(1,"hello");
    // DEBUG_PRINT_WARNING(1,"hello");
    // DEBUG_PRINT_ERROR(1,"hello");
    // DEBUG_PRINT_FATAL(1,"hello");
    
    int a = 0;
    float b = 12.22;
    double c = 3.1415926;
    // DEBUG_PRINT_VALUES_DEBUG(1, a, b, c);
    // DEBUG_PRINT_VALUES_INFO(1, a, b, c);
    DEBUG_PRINT_VALUES_SUCCESS(1, a, b, c);
    // DEBUG_PRINT_VALUES_WARNING(1, a, b, c);
    // DEBUG_PRINT_VALUES_FATAL(1, a, b, c);

    uint8_t buf[] = {0xf9,0x24,0x76,0xd2,0xc7,0x39,0x8b,0x8e,0x0e,0xb1,0xc4,0xe4,0x26,0xe0,0x68,0x41,0xe0,0x68,0x41};
    // DEBUG_PRINT_HEX_DEBUG(1, buf, sizeof(buf));
    // DEBUG_PRINT_HEX_INFO(1, buf, sizeof(buf));
    // DEBUG_PRINT_HEX_SUCCESS(1, buf, sizeof(buf));
    DEBUG_PRINT_HEX_WARNING(1, buf, sizeof(buf));
    // DEBUG_PRINT_HEX_FATAL(1, buf, sizeof(buf));

    for (int i = 0; i < 7; i++) {
        DEBUG_TIME_TAKEN_START(DEBUG_ENABLE, 3);
        dbg_sleep_ms(20);
        DEBUG_TIME_TAKEN_END;
    }

    DEBUG_ASSERT(DEBUG_ENABLE, 1 < 0);

    return 0;
}
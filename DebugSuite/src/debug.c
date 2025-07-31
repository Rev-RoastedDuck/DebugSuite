/*
 * debug.h
 *	
 *  Created on: 2025_07_31
 *      Author: Rev_RoastDuck
 *      Github: https://github.com/Rev-RoastedDuck
 * 
 * :copyright: (c) 2025 by Rev-RoastedDuck.
 */

#include "debug.h"

/** \addtogroup common
 ** \{ */
#if DEBUG_COMMOM_USE_STRING_LIB
	#include "string.h"
	#define __debug_common_strtok	strtok
#else
char* __debug_common_strtok(char* str, const char* delim) {
	static char* last = 0;

    if (str != 0) {
        last = str;
    }
    if (last == 0) {
        return 0;
    }

    char* token_start = last;
    int is_delim = 1;
    while (*token_start != '\0' && is_delim) {
        is_delim = 0;
        const char* d = delim;
        while (*d != '\0') {
            if (*token_start == *d) {
                is_delim = 1;
                break;
            }
            ++d;
        }
        if (is_delim) ++token_start;
    }

    if (*token_start == '\0') {
        last = 0;
        return 0;
    }

    char* token_end = token_start;
    while (*token_end != '\0') {
        const char* d = delim;
        int is_end = 0;
        while (*d != '\0') {
            if (*token_end == *d) {
                is_end = 1;
                break;
            }
            ++d;
        }
        if (is_end) break;
        ++token_end;
    }

    if (*token_end != '\0') {
        *token_end = '\0';
        last = token_end + 1;
    } else {
        last = 0;
    }

    return token_start;
}
#endif
/** \} */

/** \addtogroup measure execution time
 ** \{ */
#ifdef __linux__
#include <sys/time.h>
size_t __debug_measure_executeion_time_get_time_ms(void){
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000L + t.tv_usec / 1000L;
}
#endif
/** \} */

/** \addtogroup message out
 ** \{ */
void __debug_print_values(char *name_line, double values[], int count) {
	char *token = __debug_common_strtok(name_line, ",");
	for (int i = 0; i < count && token; ++i) {
		while (*token == ' ') token++;
		printf("%s = %.3f", token, values[i]);
		token = __debug_common_strtok(NULL, ",");
		(token != NULL ? (void)printf(", ") : (void)0);
	}
	printf("\r\n");
}
/** \} */
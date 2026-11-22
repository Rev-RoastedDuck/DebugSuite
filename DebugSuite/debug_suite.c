/*
 * debug_suite.c
 *	
 *  Created on: 2025_07_31
 *      Author: Rev_RoastDuck
 *      Github: https://github.com/Rev-RoastedDuck
 * 
 * :copyright: (c) 2025 by Rev-RoastedDuck.
 */

#include "debug_suite.h"

#if DEBUG_PRINT_ENABLE
/******************************************************************************/
/*----------------------------------Private-----------------------------------*/
/******************************************************************************/
#if DEBUG_PRINT_SHOW_UTC_TIME
#include "time.h"
void __debug_format_utc_time(unsigned long long ms, char *buf) {
	time_t sec = (time_t)(ms / 1000);
	struct tm *t = gmtime(&sec);
	if (t != 0) {
		sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d",
				t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
				t->tm_hour, t->tm_min, t->tm_sec);
	} else {
		buf[0] = '\0';
	}
}
#endif /* DEBUG_PRINT_SHOW_UTC_TIME */

/** \addtogroup message out
 ** \{ */
#if DEBUG_PRINT_VALUES_ENABLE
#if DEBUG_COMMON_USE_STRING_LIB
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
#endif /* DEBUG_COMMON_USE_STRING_LIB */

void __debug_print_values(char *name_line, double values[], unsigned int count) {
	char *token = __debug_common_strtok(name_line, ",");
	for (unsigned int i = 0; i < count && token; ++i) {
		while (*token == ' ') token++;
		__DEBUG_PRINT_HOOK("%s = %.3f", token, values[i]);
		token = __debug_common_strtok(NULL, ",");
		(token != NULL ? (void)__DEBUG_PRINT_HOOK(", ") : (void)0);
	}
}
#endif /* DEBUG_PRINT_VALUES_ENABLE */

#if DEBUG_PRINT_HEX_ENABLE
void __debug_print_hex(const unsigned char *data, unsigned int len) {
	for (unsigned int i = 0; i < len; i += 16) {
        if (i > 0) {
            __DEBUG_PRINT_HOOK("\n");
        }
        
		unsigned int line_len = (len - i < 16) ? (len - i) : 16;
        __DEBUG_PRINT_HOOK("  ");
		for (unsigned int j = 0; j < line_len; j++) {
			__DEBUG_PRINT_HOOK("%02x ", data[i + j]);
		}
		for (unsigned int j = line_len; j < 16; j++) {
			__DEBUG_PRINT_HOOK("XX ");
		}
		__DEBUG_PRINT_HOOK("|");
		for (unsigned int j = 0; j < line_len; j++) {
			char c = (char)data[i + j];
			__DEBUG_PRINT_HOOK("%c", (c >= 32 && c <= 126) ? c : '.');
		}
		for (unsigned int j = line_len; j < 16; j++) {
			__DEBUG_PRINT_HOOK(".");
		}
	}
}
#endif /* DEBUG_PRINT_HEX_ENABLE */
/** \} */

/******************************************************************************/
/*-----------------------------------Public-----------------------------------*/
/******************************************************************************/
/** \addtogroup message level
 ** \{ */
static unsigned char __debug_level = DEBUG_LEVEL_DEBUG;
unsigned char debug_get_level(void)       { return __debug_level; }
void debug_set_level(unsigned char level) { __debug_level = level; }
/** \} */

#endif /* DEBUG_PRINT_ENABLE */
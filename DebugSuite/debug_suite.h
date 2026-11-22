/*
 * debug_suite.h
 *
 *  Doc:
 *    \{
 *      Overview
 *        DebugSuite - a lightweight and flexible C debug / logging library.
 *        Features: colored console output, execution-time measurement,
 *        value / hex dumping and assertion, all with file / line / function info.
 *
 *      API
 *        - Log level control
 *            debug_get_level(void)
 *            debug_set_level(uint8_t level)
 *            level: DEBUG_LEVEL_DEBUG(0) 	DEBUG_LEVEL_INFO(1) 
 * 					 DEBUG_LEVEL_SUCCESS(2) DEBUG_LEVEL_WARNING(4) 
 *					 DEBUG_LEVEL_ERROR(5)  DEBUG_LEVEL_FATAL(6)
 *
 *        - Message output
 *            DEBUG_PRINT(__enable, __fmt, ...)
 *            DEBUG_PRINT_COLOR(__enable, __font_attr, __fg_color, __bg_color, __fmt, ...)
 *            DEBUG_PRINT_DEBUG(__enable, __fmt, ...)
 *            DEBUG_PRINT_INFO(__enable, __fmt, ...)
 *            DEBUG_PRINT_SUCCESS(__enable, __fmt, ...)
 *            DEBUG_PRINT_WARNING(__enable, __fmt, ...)
 *            DEBUG_PRINT_ERROR(__enable, __fmt, ...)
 *            DEBUG_PRINT_FATAL(__enable, __fmt, ...)
 *
 *        - Values output
 *            DEBUG_PRINT_VALUES(__enable, ...)
 *            DEBUG_PRINT_VALUES_DEBUG(__enable, ...)
 *            DEBUG_PRINT_VALUES_INFO(__enable, ...)
 *            DEBUG_PRINT_VALUES_SUCCESS(__enable, ...)
 *            DEBUG_PRINT_VALUES_WARNING(__enable, ...)
 *            DEBUG_PRINT_VALUES_ERROR(__enable, ...)
 *            DEBUG_PRINT_VALUES_FATAL(__enable, ...)
 *
 *        - Hex dump output
 *            DEBUG_PRINT_HEX(__enable, __data, __len)
 *            DEBUG_PRINT_HEX_DEBUG(__enable, __data, __len)
 *            DEBUG_PRINT_HEX_INFO(__enable, __data, __len)
 *            DEBUG_PRINT_HEX_SUCCESS(__enable, __data, __len)
 *            DEBUG_PRINT_HEX_WARNING(__enable, __data, __len)
 *            DEBUG_PRINT_HEX_ERROR(__enable, __data, __len)
 *            DEBUG_PRINT_HEX_FATAL(__enable, __data, __len)
 *
 *        - Execution time
 *            DEBUG_TIME_TAKEN_START(__enable, __max_execute_count)
 *            DEBUG_TIME_TAKEN_END
 *
 *        - Assert
 *            DEBUG_ASSERT(__enable, __expr)
 *
 *      PARAMS
 *        DEBUG_ENABLE    (1)  enable the output
 *        DEBUG_DISABLE   (0)  disable the output
 *
 *      EXAMPLE
 *        - Message output
 *            ``` c
 *            DEBUG_PRINT_DEBUG(1, "Hello debug");
 *            DEBUG_PRINT_SUCCESS(1, "Task succeeded!");
 *            DEBUG_PRINT_WARNING(1, "Warning: %d", 123);
 *            DEBUG_PRINT_FATAL(1, "Fatal error happened");
 *            DEBUG_PRINT_INFO(DEBUG_ENABLE, "Info message");
 *            DEBUG_PRINT_COLOR(DEBUG_ENABLE, DEBUG_PRINT_ATTR_BOLD,
 *                              DEBUG_PRINT_COLOR_FG_RED, DEBUG_PRINT_COLOR_BG_BLACK,
 *                              "Hello debug");
 *            ```
 *
 *        - Values output
 *            ``` c
 *            int a = 0;
 *            float b = 12.22;
 *            DEBUG_PRINT_VALUES(1, a, b);
 *            DEBUG_PRINT_VALUES_INFO(1, a, b);
 *            ```
 *
 *        - Hex dump output
 *            ``` c
 *            uint8_t buf[] = {0xf9,0x24,0x76,0xd2,0xc7,0x39,0x8b,0x8e,
 *                             0x0e,0xb1,0xc4,0xe4,0x26,0xe0,0x68,0x41};
 *            DEBUG_PRINT_HEX(1, buf, sizeof(buf));
 *            DEBUG_PRINT_HEX_INFO(1, buf, sizeof(buf));
 *            ```
 *
 *        - Execution time
 *            ``` c
 *            DEBUG_TIME_TAKEN_START(1, 3);
 *            usleep(10000);
 *            DEBUG_TIME_TAKEN_END;
 *            ```
 *
 *        - Assert
 *            ``` c
 *            DEBUG_ASSERT(DEBUG_ENABLE, 1 < 0);
 *            ```
 *    \}
 *
 *  Created on: 2025_07_31
 *      Author: Rev_RoastDuck
 *      Github: https://github.com/Rev-RoastedDuck
 *
 * :copyright: (c) 2025 by Rev-RoastedDuck.
 */

#ifndef DEBUG_SUITE_H_
#define DEBUG_SUITE_H_

/******************************************************************************/
/*----------------------------------Include-----------------------------------*/
/******************************************************************************/
#include "stdio.h"

/******************************************************************************/
/*-----------------------------------Config-----------------------------------*/
/******************************************************************************/
/** \addtogroup hook and callback
 ** \{ */
#define __DEBUG_PRINT_HOOK( __fmt, ...)	printf(__fmt, ##__VA_ARGS__)	/* \def void fnt (const char *fmt, ...) */
#define __DEBUG_GET_LOCAL_TIME_MS_HOOK	(0)								/* \def size_t fnt (void) */
#define __DEBUG_GET_SYSTEM_TIME_MS_HOOK	(0)								/* \def size_t fnt (void) */
#define __DEBUG_ASSERT_FAILED_CALLBACK	(0)								/* \def void fnt (void) */
/** \} */

/** \addtogroup switch parameter
 ** \{ */
// \def 0: disable, 1: enable
#define DEBUG_PRINT_ENABLE   			(1)
#define DEBUG_PRINT_HEX_ENABLE     		(1)
#define DEBUG_PRINT_VALUES_ENABLE     	(1)
#define DEBUG_PRINT_ASSERT_ENABLE     	(1)
#define DEBUG_PRINT_MEASURE_TIME_ENABLE	(1)

#define DEBUG_PRINT_SHOW_LEVEL   		(1)
#define DEBUG_PRINT_SHOW_COLOR   		(1)
#define DEBUG_PRINT_SHOW_FILE_NAME   	(1)
#define DEBUG_PRINT_SHOW_LINE_NUMBER   	(1)
#define DEBUG_PRINT_SHOW_FUNC_NAME   	(1)
#define DEBUG_PRINT_SHOW_UTC_TIME   	(1)
#define DEBUG_PRINT_SHOW_SYSTEM_TIME   	(1)
#define DEBUG_COMMON_USE_STRING_LIB   	(1)
/** \} */

/** \addtogroup option
 ** \{ */
// \option DEBUG_LEVEL_DEBUG | DEBUG_LEVEL_INFO 
//			| DEBUG_LEVEL_SUCCESS | DEBUG_LEVEL_WARNING 
//			| DEBUG_LEVEL_ERROR | DEBUG_LEVEL_FATAL
#define DEBUG_PRINT_LEVEL_COMPILE    DEBUG_LEVEL_DEBUG
/** \} */

/******************************************************************************/
/*---------------------------------Constants----------------------------------*/
/******************************************************************************/
/** \addtogroup common
 ** \{ */
#define DEBUG_ENABLE		(1)
#define DEBUG_DISABLE		(0)
#define DEBUG_UNUSE_BLOCK	(0)
/** \} */

/** \addtogroup message level
 ** \{ */
#define DEBUG_LEVEL_DEBUG      0
#define DEBUG_LEVEL_INFO       1
#define DEBUG_LEVEL_SUCCESS    2
#define DEBUG_LEVEL_WARNING    4
#define DEBUG_LEVEL_ERROR      5
#define DEBUG_LEVEL_FATAL      6
/** \} */

/** \addtogroup font type and color
 ** \{ */
// Attrition
#define DEBUG_PRINT_ATTR_RESET      		0
#define DEBUG_PRINT_ATTR_BOLD       		1
#define DEBUG_PRINT_ATTR_UNDERLINE  		4
#define DEBUG_PRINT_ATTR_BLINK      		5 
#define DEBUG_PRINT_ATTR_REVERSE    		7

// Foreground color
#define DEBUG_PRINT_COLOR_FG_BLACK   		30
#define DEBUG_PRINT_COLOR_FG_RED     		31
#define DEBUG_PRINT_COLOR_FG_GREEN   		32
#define DEBUG_PRINT_COLOR_FG_YELLOW  		33
#define DEBUG_PRINT_COLOR_FG_BLUE    		34
#define DEBUG_PRINT_COLOR_FG_PURPLE  		35
#define DEBUG_PRINT_COLOR_FG_CYAN    		36
#define DEBUG_PRINT_COLOR_FG_WHITE   		37

#define DEBUG_PRINT_COLOR_FG_BRIGHT_BLACK   90
#define DEBUG_PRINT_COLOR_FG_BRIGHT_RED     91
#define DEBUG_PRINT_COLOR_FG_BRIGHT_GREEN   92
#define DEBUG_PRINT_COLOR_FG_BRIGHT_YELLOW  93
#define DEBUG_PRINT_COLOR_FG_BRIGHT_BLUE    94
#define DEBUG_PRINT_COLOR_FG_BRIGHT_PURPLE  95
#define DEBUG_PRINT_COLOR_FG_BRIGHT_CYAN    96
#define DEBUG_PRINT_COLOR_FG_BRIGHT_WHITE   97

// Background color
#define DEBUG_PRINT_COLOR_BG_BLACK   		40
#define DEBUG_PRINT_COLOR_BG_RED     		41
#define DEBUG_PRINT_COLOR_BG_GREEN   		42
#define DEBUG_PRINT_COLOR_BG_YELLOW  		43
#define DEBUG_PRINT_COLOR_BG_BLUE    		44
#define DEBUG_PRINT_COLOR_BG_PURPLE  		45
#define DEBUG_PRINT_COLOR_BG_CYAN    		46
#define DEBUG_PRINT_COLOR_BG_WHITE   		47

#define DEBUG_PRINT_COLOR_BG_BRIGHT_BLACK   100
#define DEBUG_PRINT_COLOR_BG_BRIGHT_RED     101
#define DEBUG_PRINT_COLOR_BG_BRIGHT_GREEN   102
#define DEBUG_PRINT_COLOR_BG_BRIGHT_YELLOW  103
#define DEBUG_PRINT_COLOR_BG_BRIGHT_BLUE    104
#define DEBUG_PRINT_COLOR_BG_BRIGHT_PURPLE  105
#define DEBUG_PRINT_COLOR_BG_BRIGHT_CYAN    106
#define DEBUG_PRINT_COLOR_BG_BRIGHT_WHITE   107
/** \} */

/** \addtogroup message params
 ** \{ */
#define __LEVEL_DEBUG__   	"D"
#define __LEVEL_INFO__   	"I"
#define __LEVEL_SUCCESS__	"S"
#define __LEVEL_WARNING__ 	"W"
#define __LEVEL_ERROR__   	"E"
#define __LEVEL_FATAL__   	"F"

#define __FUNCNAME__ (__func__)
#define __FILELINE__ (__LINE__)
#if defined(__GNUC__) || defined(__clang__)
	#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)
#elif defined(_WIN32)
	#include <string.h>
	#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
	#define __FILENAME__ (__FILE__)
#endif
/** \} */

/******************************************************************************/
/*------------------------------------Marco-----------------------------------*/
/******************************************************************************/
/** \addtogroup message out
 ** \{ */
#if DEBUG_PRINT_ENABLE
	void __debug_format_utc_time(unsigned long long ms, char *buf);
	#define __DEBUG_PRINT_TIMESTAMP() 																			\
		do { 																									\
			if (DEBUG_PRINT_SHOW_UTC_TIME) { 																	\
				char __time_buf[20]; 																			\
				__debug_format_utc_time((unsigned long long)__DEBUG_GET_LOCAL_TIME_MS_HOOK(), __time_buf); 		\
				__DEBUG_PRINT_HOOK("%s", __time_buf); 															\
			} 																									\
			if (DEBUG_PRINT_SHOW_UTC_TIME && DEBUG_PRINT_SHOW_SYSTEM_TIME) { 									\
				__DEBUG_PRINT_HOOK("(%llu)", (unsigned long long)__DEBUG_GET_SYSTEM_TIME_MS_HOOK()); 			\
			} else if (!DEBUG_PRINT_SHOW_UTC_TIME && DEBUG_PRINT_SHOW_SYSTEM_TIME) {							\
				__DEBUG_PRINT_HOOK("%llu", (unsigned long long)__DEBUG_GET_SYSTEM_TIME_MS_HOOK()); 				\
			} 																									\
			if (DEBUG_PRINT_SHOW_UTC_TIME || DEBUG_PRINT_SHOW_SYSTEM_TIME) { 									\
				__DEBUG_PRINT_HOOK(" "); 																		\
			} 																									\
		} while (0)

	#define __DEBUG_PRINT_PREFIX() 																												\
		do { 																																	\
			__DEBUG_PRINT_TIMESTAMP();																											\
			if (DEBUG_PRINT_SHOW_FILE_NAME || DEBUG_PRINT_SHOW_FUNC_NAME) 		{ __DEBUG_PRINT_HOOK("["); }									\
			if (DEBUG_PRINT_SHOW_FILE_NAME && !DEBUG_PRINT_SHOW_LINE_NUMBER) 	{ __DEBUG_PRINT_HOOK("%s", __FILENAME__); }						\
			if (DEBUG_PRINT_SHOW_FILE_NAME && DEBUG_PRINT_SHOW_LINE_NUMBER) 	{ __DEBUG_PRINT_HOOK("%s:%d", __FILENAME__, __FILELINE__); }	\
			if (DEBUG_PRINT_SHOW_FILE_NAME && DEBUG_PRINT_SHOW_FUNC_NAME) 		{ __DEBUG_PRINT_HOOK(" %s", __FUNCNAME__); }					\
			if (!DEBUG_PRINT_SHOW_FILE_NAME && DEBUG_PRINT_SHOW_FUNC_NAME) 		{ __DEBUG_PRINT_HOOK("%s", __FUNCNAME__); }						\
			if (DEBUG_PRINT_SHOW_FILE_NAME || DEBUG_PRINT_SHOW_FUNC_NAME) 		{ __DEBUG_PRINT_HOOK("] "); }									\
		} while (0)

	#define __DEBUG_PRINT_ONE_LINE(__enable, __fmt, ...) 	\
		do {  												\
			if (__enable) {  								\
				__DEBUG_PRINT_PREFIX();						\
				__DEBUG_PRINT_HOOK(__fmt, ##__VA_ARGS__);	\
			}												\
		} while (0)

	#define DEBUG_PRINT(__enable, __fmt, ...)  						\
		do {  														\
			if (__enable) {  										\
				__DEBUG_PRINT_PREFIX();								\
				__DEBUG_PRINT_HOOK(__fmt"\n", ##__VA_ARGS__);		\
			}														\
		} while (0)
		
	#define __DEBUG_PRINT_CLEAR_COLOR()	__DEBUG_PRINT_HOOK("\033[0m\n")
	#define __DEBUG_PRINT_SET_COLOR(__font_attr, __fg_color, __bg_color)			\
		do {																		\
			__DEBUG_PRINT_HOOK("\033[");											\
			if (__font_attr >= 0) { __DEBUG_PRINT_HOOK("%d", __font_attr); }		\
			if (__fg_color  >= 0) { __DEBUG_PRINT_HOOK(";%d", __fg_color); }		\
			if (__bg_color  >= 0) { __DEBUG_PRINT_HOOK(";%d", __bg_color); }		\
			__DEBUG_PRINT_HOOK("m");												\
		} while (0)

	#define DEBUG_PRINT_COLOR(__enable, __font_attr, __fg_color, __bg_color, __fmt, ...) 		\
		do { 																					\
			if (__enable) { 																	\
				if (DEBUG_PRINT_SHOW_COLOR) {													\
					__DEBUG_PRINT_SET_COLOR(__font_attr, __fg_color, __bg_color);				\
					__DEBUG_PRINT_ONE_LINE(__enable, __fmt, ##__VA_ARGS__);						\
					__DEBUG_PRINT_CLEAR_COLOR();												\
				} else {																		\
					DEBUG_PRINT(__enable, __fmt, ##__VA_ARGS__);								\
				}																				\
			} 																					\
		} while (0)

	unsigned char debug_get_level(void);
	void debug_set_level(unsigned char level);
	#define __DEBUG_PRINT_LEVEL(__level_num, __enable, __level, __font_attr, __fg_color, __bg_color, __fmt, ...) 	\
		do { 																										\
			if ((__level_num) >= DEBUG_PRINT_LEVEL_COMPILE && (__enable) && (debug_get_level() <= (__level_num))) { \
				if (DEBUG_PRINT_SHOW_COLOR) {																		\
					__DEBUG_PRINT_SET_COLOR(__font_attr, __fg_color, __bg_color);									\
					if (DEBUG_PRINT_SHOW_LEVEL) { __DEBUG_PRINT_HOOK(__level " "); }								\
					__DEBUG_PRINT_ONE_LINE(__enable, __fmt, ##__VA_ARGS__);											\
					__DEBUG_PRINT_CLEAR_COLOR();																	\
				} else {																							\
					if (DEBUG_PRINT_SHOW_LEVEL) { __DEBUG_PRINT_HOOK(__level " "); }								\
					DEBUG_PRINT(__enable, __fmt, ##__VA_ARGS__);													\
				}																									\
			} 																										\
		} while (0)

	#define DEBUG_PRINT_DEBUG(__enable, __fmt, ...)   __DEBUG_PRINT_LEVEL(DEBUG_LEVEL_DEBUG,   __enable, __LEVEL_DEBUG__,   -1, DEBUG_PRINT_COLOR_FG_BRIGHT_BLACK, -1, __fmt, ##__VA_ARGS__)
	#define DEBUG_PRINT_INFO(__enable, __fmt, ...)    __DEBUG_PRINT_LEVEL(DEBUG_LEVEL_INFO,    __enable, __LEVEL_INFO__,    -1, DEBUG_PRINT_COLOR_FG_BLUE,         -1, __fmt, ##__VA_ARGS__)
	#define DEBUG_PRINT_WARNING(__enable, __fmt, ...) __DEBUG_PRINT_LEVEL(DEBUG_LEVEL_WARNING, __enable, __LEVEL_WARNING__, -1, DEBUG_PRINT_COLOR_FG_YELLOW,       -1, __fmt, ##__VA_ARGS__)
	#define DEBUG_PRINT_ERROR(__enable, __fmt, ...)   __DEBUG_PRINT_LEVEL(DEBUG_LEVEL_ERROR,   __enable, __LEVEL_ERROR__,   -1, DEBUG_PRINT_COLOR_FG_RED,          -1, __fmt, ##__VA_ARGS__)
	#define DEBUG_PRINT_FATAL(__enable, __fmt, ...)   __DEBUG_PRINT_LEVEL(DEBUG_LEVEL_FATAL,   __enable, __LEVEL_FATAL__,    1, DEBUG_PRINT_COLOR_FG_BRIGHT_RED,   -1, __fmt, ##__VA_ARGS__)
	#define DEBUG_PRINT_SUCCESS(__enable, __fmt, ...) __DEBUG_PRINT_LEVEL(DEBUG_LEVEL_SUCCESS, __enable, __LEVEL_SUCCESS__, -1, DEBUG_PRINT_COLOR_FG_GREEN,        -1, __fmt, ##__VA_ARGS__)
#else
	#define DEBUG_PRINT(__enable, __fmt, ...)
	#define DEBUG_PRINT_COLOR(__enable, __font_attr,__fg_color, __bg_color, __fmt, ...)
	#define DEBUG_PRINT_DEBUG(__enable,fmt, ...)   
	#define DEBUG_PRINT_INFO(__enable,fmt, ...)    
	#define DEBUG_PRINT_WARNING(__enable,fmt, ...) 
	#define DEBUG_PRINT_ERROR(__enable,fmt, ...)   
	#define DEBUG_PRINT_FATAL(__enable,fmt, ...)   
	#define DEBUG_PRINT_SUCCESS(__enable,fmt, ...) 
#endif /* DEBUG_PRINT_ENABLE */

#if DEBUG_PRINT_ENABLE && DEBUG_PRINT_HEX_ENABLE
	void __debug_print_hex(const unsigned char *data, unsigned int len);
	#define DEBUG_PRINT_HEX(__enable, __data, __len) 	\
		do { 											\
			if (__enable) { 							\
				__DEBUG_PRINT_PREFIX();					\
				__DEBUG_PRINT_HOOK("hex:\n");			\
				__debug_print_hex((__data), (__len));	\
			} 											\
		} while (0)

	#define __DEBUG_PRINT_HEX_LEVEL(__level_num, __enable, __level, __font_attr, __fg_color, __bg_color, __data, __len) 	\
		do { 																												\
			if ((__level_num) >= DEBUG_PRINT_LEVEL_COMPILE && (__enable) && (debug_get_level() <= (__level_num))) { 		\
				if (DEBUG_PRINT_SHOW_COLOR) {																				\
					__DEBUG_PRINT_SET_COLOR(__font_attr, __fg_color, __bg_color);											\
					if (DEBUG_PRINT_SHOW_LEVEL) { __DEBUG_PRINT_HOOK(__level " "); }										\
					__DEBUG_PRINT_PREFIX();																					\
					__DEBUG_PRINT_HOOK("hex:\n");																			\
					__debug_print_hex((__data), (__len));																	\
					__DEBUG_PRINT_CLEAR_COLOR();																			\
				} else {																									\
					if (DEBUG_PRINT_SHOW_LEVEL) { __DEBUG_PRINT_HOOK(__level " "); }										\
					__DEBUG_PRINT_PREFIX();																					\
					__DEBUG_PRINT_HOOK("hex:\n");																			\
					__debug_print_hex((__data), (__len));																	\
				}																											\
			} 																												\
		} while (0)

	#define DEBUG_PRINT_HEX_DEBUG(__enable, __data, __len)   __DEBUG_PRINT_HEX_LEVEL(DEBUG_LEVEL_DEBUG,   __enable, __LEVEL_DEBUG__,   -1, DEBUG_PRINT_COLOR_FG_BRIGHT_BLACK, -1, __data, __len)
	#define DEBUG_PRINT_HEX_INFO(__enable, __data, __len)    __DEBUG_PRINT_HEX_LEVEL(DEBUG_LEVEL_INFO,    __enable, __LEVEL_INFO__,    -1, DEBUG_PRINT_COLOR_FG_BLUE,         -1, __data, __len)
	#define DEBUG_PRINT_HEX_WARNING(__enable, __data, __len) __DEBUG_PRINT_HEX_LEVEL(DEBUG_LEVEL_WARNING, __enable, __LEVEL_WARNING__, -1, DEBUG_PRINT_COLOR_FG_YELLOW,       -1, __data, __len)
	#define DEBUG_PRINT_HEX_ERROR(__enable, __data, __len)   __DEBUG_PRINT_HEX_LEVEL(DEBUG_LEVEL_ERROR,   __enable, __LEVEL_ERROR__,   -1, DEBUG_PRINT_COLOR_FG_RED,          -1, __data, __len)
	#define DEBUG_PRINT_HEX_FATAL(__enable, __data, __len)   __DEBUG_PRINT_HEX_LEVEL(DEBUG_LEVEL_FATAL,   __enable, __LEVEL_FATAL__,    1, DEBUG_PRINT_COLOR_FG_BRIGHT_RED,   -1, __data, __len)
	#define DEBUG_PRINT_HEX_SUCCESS(__enable, __data, __len) __DEBUG_PRINT_HEX_LEVEL(DEBUG_LEVEL_SUCCESS, __enable, __LEVEL_SUCCESS__, -1, DEBUG_PRINT_COLOR_FG_GREEN,        -1, __data, __len)
#endif /* DEBUG_PRINT_ENABLE && DEBUG_PRINT_HEX_ENABLE */

#if DEBUG_PRINT_ENABLE && DEBUG_PRINT_VALUES_ENABLE
	void __debug_print_values(char *name_line, double values[], unsigned int count);
	#define DEBUG_PRINT_VALUES(__enable, ...) 																\
		do { 																								\
			if (__enable) { 																				\
				char __name_line[] = #__VA_ARGS__; 															\
				double __values[] = { __VA_ARGS__ }; 														\
				__DEBUG_PRINT_PREFIX();																		\
				__debug_print_values(__name_line, __values, sizeof(__values) / sizeof(double)); 			\
				__DEBUG_PRINT_HOOK("\n");																	\
			} 																								\
		} while (0)

	#define __DEBUG_PRINT_VALUES_LEVEL(__level_num, __enable, __level, __font_attr, __fg_color, __bg_color, ...) 	\
		do { 																										\
			if ((__level_num) >= DEBUG_PRINT_LEVEL_COMPILE && (__enable) && (debug_get_level() <= (__level_num))) {	\
				char __name_line[] = #__VA_ARGS__; 																	\
				double __values[] = { __VA_ARGS__ }; 																\
				if (DEBUG_PRINT_SHOW_COLOR) {																		\
					__DEBUG_PRINT_SET_COLOR(__font_attr, __fg_color, __bg_color);									\
					if (DEBUG_PRINT_SHOW_LEVEL) { __DEBUG_PRINT_HOOK(__level " "); }								\
					__DEBUG_PRINT_PREFIX();																			\
					__debug_print_values(__name_line, __values, sizeof(__values) / sizeof(double)); 				\
					__DEBUG_PRINT_CLEAR_COLOR();																	\
				} else {																							\
					if (DEBUG_PRINT_SHOW_LEVEL) { __DEBUG_PRINT_HOOK(__level " "); }								\
					__DEBUG_PRINT_PREFIX();																			\
					__debug_print_values(__name_line, __values, sizeof(__values) / sizeof(double)); 				\
					__DEBUG_PRINT_HOOK("\n");																		\
				}																									\
			} 																										\
		} while (0)

	#define DEBUG_PRINT_VALUES_DEBUG(__enable, ...)   __DEBUG_PRINT_VALUES_LEVEL(DEBUG_LEVEL_DEBUG,   __enable, __LEVEL_DEBUG__,   -1, DEBUG_PRINT_COLOR_FG_BRIGHT_BLACK, -1, __VA_ARGS__)
	#define DEBUG_PRINT_VALUES_INFO(__enable, ...)    __DEBUG_PRINT_VALUES_LEVEL(DEBUG_LEVEL_INFO,    __enable, __LEVEL_INFO__,    -1, DEBUG_PRINT_COLOR_FG_BLUE,         -1, __VA_ARGS__)
	#define DEBUG_PRINT_VALUES_WARNING(__enable, ...) __DEBUG_PRINT_VALUES_LEVEL(DEBUG_LEVEL_WARNING, __enable, __LEVEL_WARNING__, -1, DEBUG_PRINT_COLOR_FG_YELLOW,       -1, __VA_ARGS__)
	#define DEBUG_PRINT_VALUES_ERROR(__enable, ...)   __DEBUG_PRINT_VALUES_LEVEL(DEBUG_LEVEL_ERROR,   __enable, __LEVEL_ERROR__,   -1, DEBUG_PRINT_COLOR_FG_RED,          -1, __VA_ARGS__)
	#define DEBUG_PRINT_VALUES_FATAL(__enable, ...)   __DEBUG_PRINT_VALUES_LEVEL(DEBUG_LEVEL_FATAL,   __enable, __LEVEL_FATAL__,    1, DEBUG_PRINT_COLOR_FG_BRIGHT_RED,   -1, __VA_ARGS__)
	#define DEBUG_PRINT_VALUES_SUCCESS(__enable, ...) __DEBUG_PRINT_VALUES_LEVEL(DEBUG_LEVEL_SUCCESS, __enable, __LEVEL_SUCCESS__, -1, DEBUG_PRINT_COLOR_FG_GREEN,        -1, __VA_ARGS__)
#else
	#define DEBUG_PRINT_VALUES(__enable, ...)
	#define DEBUG_PRINT_VALUES_DEBUG(__enable, ...)
	#define DEBUG_PRINT_VALUES_INFO(__enable, ...)
	#define DEBUG_PRINT_VALUES_SUCCESS(__enable, ...)
	#define DEBUG_PRINT_VALUES_WARNING(__enable, ...)
	#define DEBUG_PRINT_VALUES_ERROR(__enable, ...)
	#define DEBUG_PRINT_VALUES_FATAL(__enable, ...)
#endif /* DEBUG_PRINT_ENABLE && DEBUG_PRINT_VALUES_ENABLE */

/** \} */

/** \addtogroup assert
** \{ */
#if DEBUG_PRINT_ASSERT_ENABLE
	#if !__DEBUG_ASSERT_FAILED_CALLBACK
		#undef __DEBUG_ASSERT_FAILED_CALLBACK
		#define __DEBUG_ASSERT_FAILED_CALLBACK()	while (1)
	#endif
	#define DEBUG_ASSERT(__enable, __expr) 																	\
		do { 																								\
			if (__enable && (!(__expr))) { 																	\
				if (DEBUG_PRINT_SHOW_FILE_NAME) {															\
					DEBUG_PRINT_FATAL(1,"assert: \"%s\"", #__expr);											\
				} else {																					\
					DEBUG_PRINT_FATAL(1,"assert: \"%s\" in %s:%d", #__expr, __FILENAME__, __FILELINE__);	\
				}																							\
				__DEBUG_ASSERT_FAILED_CALLBACK(); 															\
			} 																								\
		} while (0)
#else
	#define DEBUG_ASSERT(__enable, __expr)
#endif /* DEBUG_PRINT_ASSERT_ENABLE */
/** \} */

/** \addtogroup measure execution time
 ** \{ */
#if DEBUG_PRINT_MEASURE_TIME_ENABLE
	#define DEBUG_TIME_TAKEN_START(__enable_, __max_execute_count_)				\
		do {																	\
			static unsigned long __start, __end;   				        		\
			static unsigned long __time = 0;									\
			static unsigned long __execute_count = 0;							\
			unsigned long __enable = __enable_;									\
			unsigned long __max_execute_count = __max_execute_count_;			\
			__start = __DEBUG_GET_SYSTEM_TIME_MS_HOOK();

	#define DEBUG_TIME_TAKEN_END																												\
			if (__enable) {																														\
				__end = __DEBUG_GET_SYSTEM_TIME_MS_HOOK();                                        												\
				unsigned long elapsed_ms = (__end - __start);                      	            												\
				__time += elapsed_ms;                                                           												\
				__execute_count++;                                                              												\
				if (__execute_count >= __max_execute_count) {                                   												\
					DEBUG_PRINT_INFO(1, "time taken: total=%lu ms,avg=%lu ms,count=%lu", __time, (__time / __execute_count), __execute_count);	\
					__execute_count = 0;                                                        												\
					__time = 0;                                                                 												\
				}																																\
			}																																	\
		} while(0)
#else
	#define DEBUG_TIME_TAKEN_START(__enable_, __max_execute_count_)
	#define DEBUG_TIME_TAKEN_END
#endif /* DEBUG_PRINT_MEASURE_TIME_ENABLE */
/** \} */

#endif

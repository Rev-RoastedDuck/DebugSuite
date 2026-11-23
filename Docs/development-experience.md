## C
#### xx.98 杂项
##### 1) 关于短路表达式
a) `a && b` 要求 `b` 是一个能求值的**表达式**。一旦 `b` 是语句或宏被改成 `do{}while(0)`，整行直接编译失败：
```c
// OK
#define HOOK(fmt, ...) printf(fmt, ##__VA_ARGS__)
(cond) && HOOK("hello");

// error: expected expression
#define HOOK(fmt, ...) do { printf(fmt, ##__VA_ARGS__); } while (0)
(cond) && HOOK("hello");
```

b) `&&` 两侧会被提升为标量参与运算。如果函数返回 `void`、结构体、或指针类型，要么编译错，要么行为怪异。`(x >= 0) && (func(), 1)` 这类逗号表达式虽然强行"求值"，但**可读性极差**，且仍然依赖 `func` 返回可丢弃的表达式。
```c
void *p = ...;
(cond) && p;   // 能编译，但语义模糊，返回值被丢弃
```
---
##### 2) static 局部变量：作用域块级，存储期静态
`static long x = 变量;` 要求编译期常量，传运行时变量报 `initializer element is not constant`。
```c
#define DEBUG_TIME_TAKEN_START(__enable_, __max_execute_count_) \
    do { \
        static unsigned long __start, __end; \
        static unsigned long __time = 0; \
        static unsigned long __execute_count = 0; \
        unsigned long __enable = __enable_; /*不可声明为 static*/ \
        unsigned long __max_execute_count = __max_execute_count_; /*不可声明为 static*/ \
        __start = __DEBUG_GET_SYSTEM_TIME_MS_HOOK();

	#define DEBUG_TIME_TAKEN_END \
			if (__enable) { \
				__end = __DEBUG_GET_SYSTEM_TIME_MS_HOOK(); \
				unsigned long elapsed_ms = (__end - __start); \
				__time += elapsed_ms; \
				__execute_count++; \
				if (__execute_count >= __max_execute_count) {  \
					DEBUG_PRINT_INFO(1, "time taken: total=%lu ms,avg=%lu ms,count=%lu", __time, (__time / __execute_count), __execute_count);	\
					__execute_count = 0; \
					__time = 0; \
				} \
			} \
		} while(0)

DEBUG_TIME_TAKEN_START(DEBUG_ENABLE, 3);
dbg_sleep_ms(20);
DEBUG_TIME_TAKEN_END;
```
---
##### 3) 枚举常量不能用于 #if
预处理阶段枚举值未定义，`#if DEBUG_LEVEL_WARNING >= X` 中若 `DEBUG_LEVEL_WARNING` 是枚举会失败。编译期裁剪必须用 `#define` 数值宏。

```
源文件(.c)
   │
   ▼
[1] 预处理   ← 只做文本/宏替换、#if/#ifdef 条件、#include 展开
   │
   ▼
[2] 编译     ← 词法/语法/语义分析，此时才认识 enum、struct、typedef、函数等
   │
   ▼
[3] 汇编
   ▼
[4] 链接
```
> **`#if` 在 [1] 预处理阶段就被求值并裁剪掉了**，而**枚举常量要到 [2] 编译阶段才被定义**。顺序上，`#if` 求值先于枚举的产生，所以预处理器根本"看不到"枚举值。

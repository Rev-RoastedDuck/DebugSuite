#[[
  CMakeLists for DebugSuite_c
   Created on: 2026_11_22
       Author: Rev_RoastDuck
       Github: https://github.com/Rev-RoastedDuck
  
  :copyright: (c) 2026 by Rev-RoastedDuck.
]]

#[[----------------- 基础配置信息 --------------------
=====================================================]]
cmake_minimum_required(VERSION 3.0)
project(DebugSuite
    VERSION 1.0.0
    DESCRIPTION "A lightweight and flexible C debug / logging library"
    LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-g")

#[[------------------ 创建静态库 -------------------
=====================================================]]
add_library(debugsuite STATIC ${CMAKE_CURRENT_SOURCE_DIR}/debug_suite.c)

#[[------------------ 配置头文件路径 --------------------
=====================================================]]
target_include_directories(debugsuite PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


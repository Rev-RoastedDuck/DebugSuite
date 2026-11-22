#[[
  CMakeLists for DebugSuite-Lib-Test
   Created on: 2026_11_22
       Author: Rev_RoastDuck
       Github: https://github.com/Rev-RoastedDuck
  
  :copyright: (c) 2026 by Rev-RoastedDuck.
]]

#[[----------------- 基础配置信息 --------------------
=====================================================]]
cmake_minimum_required(VERSION 3.0)
project(DebugSuite-Lib-Test)

set(EXECUTABLE_OUTPUT_PATH ../)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

#[[------------------ 添加子模块 ---------------------
=====================================================]]
add_subdirectory(../DebugSuite debuguite)

#[[----------------- 生成可执行文件 -------------------
=====================================================]]
add_executable(start test.c)

#[[------------------ 添加依赖库-- -------------------
=====================================================]]
target_link_libraries(start debugsuite)
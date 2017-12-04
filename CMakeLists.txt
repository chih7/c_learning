cmake_minimum_required(VERSION 2.6)
project(c_learning)

#add_executable(c_learning sleep.c)

# -----------同一目录，多个源文件---------------

# add_executable(Demo main.cc MathFunctions.cc)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
 aux_source_directory(./btree/ DIR_SRCS)
# 指定生成目标
 add_executable(c_learning ${DIR_SRCS})

# -----------多个目录，多个源文件---------------

# 子目录
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
# aux_source_directory(. DIR_LIB_SRCS)
# 生成链接库
# add_library (MathFunctions ${DIR_LIB_SRCS})


# 根目录
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
#aux_source_directory(. DIR_SRCS)
# 添加 math 子目录
#add_subdirectory(math)
# 指定生成目标 
#add_executable(Demo main.cc)
# 添加链接库
#target_link_libraries(Demo MathFunctions)

# 选项
# 加入一个配置头文件，用于处理 CMake 对源码的设置
#configure_file (
#        "${PROJECT_SOURCE_DIR}/config.h.in"
#        "${PROJECT_BINARY_DIR}/config.h"
#)
# 是否使用自己的 MathFunctions 库
#option (USE_MYMATH
#        "Use provided math implementation" ON)
# 是否加入 MathFunctions 库
#if (USE_MYMATH)
#    include_directories ("${PROJECT_SOURCE_DIR}/math")
#    add_subdirectory (math)
#    set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
#endif (USE_MYMATH)


# 指定 MathFunctions 库的安装路径
#install (TARGETS MathFunctions DESTINATION bin)
#install (FILES MathFunctions.h DESTINATION include)

# 指定安装路径
#install (TARGETS Demo DESTINATION bin)
#install (FILES "${PROJECT_BINARY_DIR}/config.h"
#        DESTINATION include)

# 启用测试
#enable_testing()
# 测试程序是否成功运行
#add_test (test_run Demo 5 2)
# 测试帮助信息是否可以正常提示
#add_test (test_usage Demo)
#set_tests_properties (test_usage
#        PROPERTIES PASS_REGULAR_EXPRESSION "Usage: .* base exponent")

# 定义一个宏，用来简化测试工作
#macro (do_test arg1 arg2 result)
#    add_test (test_${arg1}_${arg2} Demo ${arg1} ${arg2})
#    set_tests_properties (test_${arg1}_${arg2}
#            PROPERTIES PASS_REGULAR_EXPRESSION ${result})
#endmacro (do_test)

# 使用该宏进行一系列的数据测试
#do_test (5 2 "is 25")
#do_test (10 5 "is 100000")
#do_test (2 10 "is 1024")

# gdb
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
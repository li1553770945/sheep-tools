cmake_minimum_required(VERSION 3.22)
project(sheep-tools)
set( CMAKE_CXX_FLAGS "-std=c++17" )

file(GLOB SHEEP_TOOLS_SOURCES "args/*.cpp" "basic/*.cpp")
# 添加其他模块的include目录
include_directories(args/include)
include_directories(basic/include)

# 生成静态库
add_library(sheeptools STATIC ${SHEEP_TOOLS_SOURCES})

# 指定库的公共头文件路径（对其他链接此库的目标可见）
target_include_directories(sheeptools PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/args/include
    ${CMAKE_CURRENT_SOURCE_DIR}/basic/include
)

cmake_minimum_required(VERSION 3.22)
project(sheep-tools)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Werror=return-type")


file(GLOB SHEEP_TOOLS_SOURCES "args/*.cpp" "basic/*.cpp" "random/*.cpp" "string/*.cpp" "log/*.cpp")
# 添加其他模块的include目录
include_directories(args/include)
include_directories(basic/include)
include_directories(random/include)

# 生成静态库
add_library(sheeptools STATIC ${SHEEP_TOOLS_SOURCES})

# 指定库的公共头文件路径（对其他链接此库的目标可见）
target_include_directories(sheeptools PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/args/include
    ${CMAKE_CURRENT_SOURCE_DIR}/basic/include
    ${CMAKE_CURRENT_SOURCE_DIR}/random/include
    ${CMAKE_CURRENT_SOURCE_DIR}/string/include
    ${CMAKE_CURRENT_SOURCE_DIR}/log/include
)

# 查找所有测试文件
file(GLOB TEST_SOURCES "temp_test/*.cpp")
foreach(testsourcefile ${TEST_SOURCES})
    # 从文件路径获取文件名
    get_filename_component(testname ${testsourcefile} NAME_WE)

    # 添加可执行文件目标
    add_executable(${testname} ${testsourcefile})

    # 链接静态库
    target_link_libraries(${testname} sheeptools)
endforeach()
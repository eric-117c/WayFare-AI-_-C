cmake_minimum_required(VERSION 3.10)
project(WayFareBackend)

set(CMAKE_CXX_STANDARD 17)

# 包含第三方库目录
include_directories(include)

add_executable(wayfare_sidecar 
    src/main.cpp
)

# 链接多线程库
find_package(Threads REQUIRED)
target_link_libraries(wayfare_sidecar Threads::Threads)
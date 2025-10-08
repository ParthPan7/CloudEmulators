cmake_minimum_required(VERSION 3.20)
project(Clog LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)



find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(aws-cpp-sdk-core)
find_package(aws-cpp-sdk-s3)


add_executable(clog src/main.cpp)

target_link_libraries(clog
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        aws-cpp-sdk-s3
        aws-cpp-sdk-core
)

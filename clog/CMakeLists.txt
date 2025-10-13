cmake_minimum_required(VERSION 3.20)
project(Clog LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)



find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(aws-cpp-sdk-core)
find_package(aws-cpp-sdk-s3)


# Automatically gather all .cpp files in the 'src' directory
file(GLOB_RECURSE SOURCES "src/*.cpp")



add_executable(clog ${SOURCES})

target_include_directories(clog
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/clog
)

target_link_libraries(clog
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        aws-cpp-sdk-s3
        aws-cpp-sdk-core
)

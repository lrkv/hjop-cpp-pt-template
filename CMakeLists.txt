cmake_minimum_required(VERSION 3.0)
project(hjop-pt-cpp-template)

set(SOURCE_FILES
    src/main.cpp
    src/pt-api.cpp
)

add_executable(hjop-pt-cpp-template ${SOURCE_FILES})

target_include_directories(hjop-pt-cpp-template PUBLIC src)
target_include_directories(hjop-pt-cpp-template PUBLIC lib/cpp-httplib)
target_include_directories(hjop-pt-cpp-template PUBLIC lib/nlohmann)

# Configure compiler warnings
if (CMAKE_C_COMPILER_ID MATCHES Clang OR ${CMAKE_C_COMPILER_ID} STREQUAL GNU)
  # using regular Clang, AppleClang or GCC
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++20 -Wall -Wextra -pedantic")
elseif (${CMAKE_C_COMPILER_ID} STREQUAL MSVC)
  # using Visual Studio C++
  target_compile_definitions(playground06 PRIVATE _CRT_SECURE_NO_DEPRECATE)
  target_compile_definitions(tests06 PRIVATE _CRT_SECURE_NO_DEPRECATE)
  set(CMAKE_CXX_FLAGS "/permissive- /W4 /EHsc")
endif()

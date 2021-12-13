cmake_minimum_required(VERSION 3.16)

project(tests)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(glm)
include_directories(glm/detail)
include_directories(glm/ext)
include_directories(glm/gtc)
include_directories(glm/gtx)
include_directories(glm/simd)

add_executable(tests
        catch.hpp
        sexymathtests.cpp)

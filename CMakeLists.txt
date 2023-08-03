cmake_minimum_required(VERSION 3.24)
project(City_Recommender)

set(CMAKE_CXX_STANDARD 14)

add_executable(City_Recommender main.cpp
        SeparateChain.h
        SeparateChain.cpp
)

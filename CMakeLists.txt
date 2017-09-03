cmake_minimum_required(VERSION 2.6)
project(c_learning)

add_executable(c_learning main.cpp)

install(TARGETS c_learning RUNTIME DESTINATION bin)

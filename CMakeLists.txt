cmake_minimum_required(VERSION 3.0.0)
project(msr VERSION 0.1.0)

file(GLOB SOURCES src/*.hh src/*.cc)

add_executable(${PROJECT_NAME} ${SOURCES})
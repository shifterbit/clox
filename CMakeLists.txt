cmake_minimum_required(VERSION 3.1...3.20)

set(CMAKE_C_STANDARD 99)

project(
  clox
  DESCRIPTION "Implementation of clox"
  LANGUAGES C)


add_executable(clox src/main.c)


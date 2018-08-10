cmake_minimum_required(VERSION 3.9)
project(Assn5 C)

set(CMAKE_C_STANDARD 99)

add_executable(Assn5 main.c hashMap.h hashMap.c CuTest.c  spellChecker.c tests.c)
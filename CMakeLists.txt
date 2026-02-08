cmake_minimum_required(VERSION 3.31)

project(AdventOfCode LANGUAGES CXX)

set(CXX_STANDARD_REQUIRED yes)
set(CXX_STANDARD 23)

add_compile_options(-Wall -Wextra -Wconversion -Wshadow)

add_subdirectory(2015)

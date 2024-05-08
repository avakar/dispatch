cmake_minimum_required(VERSION 3.19)
project(avakar.dispatch)

include(FetchContent)
FetchContent_Declare(avakar.mutest SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/mutest")
FetchContent_MakeAvailable(avakar.mutest)

add_library(avakar.dispatch INTERFACE
	include/avakar/dispatch.h
	)
add_library(avakar::dispatch ALIAS avakar.dispatch)

target_include_directories(avakar.dispatch INTERFACE include)
target_compile_features(avakar.dispatch INTERFACE cxx_std_17)

add_mutest(test/test.cpp avakar::dispatch)

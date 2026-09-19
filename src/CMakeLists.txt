cmake_minimum_required(VERSION 3.10)

project(gmserial LANGUAGES CXX)

set(CMAKE_CONFIGURATION_TYPES Release Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
	gmod-module-base
	GIT_REPOSITORY https://github.com/Facepunch/gmod-module-base
	GIT_TAG e0156e5f96cd0bad8eed738f0d20e2c9a14b2a0d)
FetchContent_MakeAvailable(gmod-module-base)

add_library(gmserial SHARED)
target_sources(gmserial PRIVATE main.cpp SerialPort.cpp)
target_link_libraries(gmserial gmod-module-base)

set_gmod_suffix_prefix(gmserial)

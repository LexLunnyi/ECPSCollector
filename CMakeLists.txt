cmake_minimum_required(VERSION 2.8)
project(ECPSCollector)

set(build_type_default "testing")
set(version_string_default "0.0.0")



add_definitions(-D__STDC_LIMIT_MACROS)
add_definitions(-D__STDC_CONSTANT_MACROS)

cmake_policy(SET CMP0015 NEW)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_FLAGS "-ggdb -std=c++11")


if (build_type)
    add_definitions(-DRS_BUILD_TYPE="${build_type}")
else (build_type)
    add_definitions(-DRS_BUILD_TYPE="${build_type_default}")
endif (build_type)


if (version_string)
    add_definitions(-DRS_VERSION_STRING="${version_string}")
else (version_string)
    add_definitions(-DRS_VERSION_STRING="${version_string_default}")
endif (version_string)


unset(build_type CACHE)
unset(version_string CACHE)


include_directories(
    ./
    src
    include
    include/SDL2
)



file(GLOB WAV_PROCESSOR_TEST_SRC *.cpp)

add_subdirectory(src)


find_package(Threads REQUIRED)
#find_library(RT rt)
#find_library(X11 X11)
find_library(ICONV iconv)
find_library(WINMM winmm)
find_library(IMM32 imm32)
find_library(LLVERSION version)
find_library(SDL2 NAMES SDL2 HINTS lib NO_DEFAULT_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_PATH NO_CMAKE_SYSTEM_PATH)
#find_library(SDL2MAIN NAMES SDL2main HINTS lib NO_DEFAULT_PATH NO_CMAKE_ENVIRONMENT_PATH NO_CMAKE_PATH NO_CMAKE_SYSTEM_PATH)


link_directories(lib)

set(WAV_PROCESSOR_TEST_OBJ_LIBS $<TARGET_OBJECTS:src>)



set(SO_LIBS ${CMAKE_THREAD_LIBS_INIT}
    ${SRC}
#    ${RT}
#    ${X11}
    ${ICONV}
    ${WINMM}
    ${IMM32}
    ${LLVERSION}
    ${SDL2})
    #${SDL2MAIN})

add_executable(${PROJECT_NAME} ${WAV_PROCESSOR_TEST_SRC} ${WAV_PROCESSOR_TEST_OBJ_LIBS})
target_link_libraries(${PROJECT_NAME} ${SO_LIBS})

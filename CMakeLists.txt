cmake_minimum_required(VERSION 3.2)
project(mandelbroseph)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

find_package(PNGwriter REQUIRED)

if(PNGwriter_FOUND)
    # where to find the pngwriter.h header file (-I include for your compiler)
    include_directories(SYSTEM ${PNGwriter_INCLUDE_DIRS})
    # additional compiler flags (e.g. -DNO_FREETYPE)
    add_definitions(${PNGwriter_DEFINITIONS})
    # libraries to link against (including dependencies)
    set(LIBS ${LIBS} ${PNGwriter_LIBRARIES})
endif(PNGwriter_FOUND)

find_package(OPENCL REQUIRED)


if (OpenCL_FOUND)
endif(OpenCL_FOUND)

add_executable(mandelbroseph ${SOURCE_FILES})

target_link_libraries(mandelbroseph ${LIBS})

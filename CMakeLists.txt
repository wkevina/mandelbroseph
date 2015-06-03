cmake_minimum_required(VERSION 3.2)
INCLUDE(ExternalProject)
project(mandelbroseph)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

set(DEPS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

find_package(OPENCL REQUIRED)


if (OpenCL_FOUND)
endif(OpenCL_FOUND)

ExternalProject_Add(
    cxxopts
    #SOURCE_DIR "/Users/kevinward/projects/cxxopts"
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_DIR}

    GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
)


ExternalProject_Add(
    "libpng"
    #SOURCE_DIR "/Users/kevinward/projects/cxxopts"
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_DIR}

    GIT_REPOSITORY https://github.com/glennrp/libpng.git
)

ExternalProject_Add(
    pngwriter
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_DIR}
    GIT_REPOSITORY https://github.com/pngwriter/pngwriter.git
)

find_package(PNGwriter REQUIRED)

if(PNGwriter_FOUND)
    # where to find the pngwriter.h header file (-I include for your compiler)
    include_directories(SYSTEM ${PNGwriter_INCLUDE_DIRS})
    # additional compiler flags (e.g. -DNO_FREETYPE)
    add_definitions(${PNGwriter_DEFINITIONS})
    # libraries to link against (including dependencies)
    set(LIBS ${LIBS} ${PNGwriter_LIBRARIES})
endif(PNGwriter_FOUND)

include_directories("/usr/local/include/" ${DEPS_DIR}/include)

add_executable(mandelbroseph ${SOURCE_FILES} mandelbrot.cpp mandelbrot.h)

add_dependencies(mandelbroseph cxxopts)

add_dependencies(mandelbroseph pngwriter)

add_dependencies(pngwriter "libpng")

target_link_libraries(mandelbroseph ${LIBS})


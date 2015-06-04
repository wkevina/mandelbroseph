cmake_minimum_required(VERSION 3.2)
INCLUDE(ExternalProject)
project(mandelbroseph)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DNO_FREETYPE")

set(SOURCE_FILES main.cpp)

set(DEPS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

include_directories(${DEPS_DIR}/include)

link_directories(${DEPS_DIR}/lib)

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${DEPS_DIR}/lib)

#find_package(OPENCL)


#if (OpenCL_FOUND)
#endif(OpenCL_FOUND)

ExternalProject_Add(
    cxxopts
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_DIR}
    GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
)


ExternalProject_Add(
    libpng
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_DIR} -DNOFREETYPE=1
    GIT_REPOSITORY https://github.com/glennrp/libpng.git
)

ExternalProject_Add(
    pngwriter
    DEPENDS libpng
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_DIR} -DCMAKE_LIBRARY_PATH=${DEPS_DIR}/lib
    GIT_REPOSITORY https://github.com/pngwriter/pngwriter.git
    GIT_TAG release-0.5.5
)

set(LIBS ${LIBS} ${CMAKE_SHARED_LIBRARY_PREFIX}pngwriter${CMAKE_SHARED_LIBRARY_SUFFIX})

add_executable(mandelbroseph ${SOURCE_FILES} mandelbrot.cpp mandelbrot.h)

add_dependencies(mandelbroseph cxxopts)

add_dependencies(mandelbroseph pngwriter)

target_link_libraries(mandelbroseph ${LIBS})

cmake_minimum_required(VERSION 3.26)
project(Kastane-X LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist)

# Automatically detect and set the GPU architecture
set(CMAKE_CUDA_ARCHITECTURES native) 

# Enable separable compilation for CUDA
set(CMAKE_CUDA_SEPARABLE_COMPILATION ON)

# Get all the source files
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.cu
)

add_executable(kastane_x ${SRC_FILES})

target_include_directories(kastane_x PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cpp-httplib-0.23.0/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cuda-12.9.1/include
)

find_package(CUDAToolkit REQUIRED)

target_link_libraries(kastane_x PRIVATE CUDA::cudart)
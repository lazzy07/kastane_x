cmake_minimum_required(VERSION 3.26)
project(Kastane-X LANGUAGES CXX CUDA)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist)

# Automatically detect and set the GPU architecture
set(CMAKE_CUDA_ARCHITECTURES native) 

add_executable(kastane_x src/main.cu)
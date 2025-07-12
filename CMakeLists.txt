cmake_minimum_required(VERSION 3.26)
project(Kastane-X LANGUAGES CXX CUDA)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist)

# ---- pick the GPU architectures you need -----------------------------------
# 86 = Ampere laptop/desktop (RTX 30-series), 89 = Ada (RTX 40), 90 = Hopper
set(CMAKE_CUDA_ARCHITECTURES 89) 

add_executable(kastane_x src/main.cu)
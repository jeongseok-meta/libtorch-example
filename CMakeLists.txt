cmake_minimum_required(VERSION 3.16.3)

project(LibTorchExample)

set(ENV{NVTOOLSEXT_PATH} "$ENV{CONDA_PREFIX}/include")

if(WIN32)
  set(libtorch_base_path $ENV{CONDA_PREFIX}/Lib/site-packages/torch)
else()
  set(libtorch_base_path $ENV{CONDA_PREFIX}/lib/python${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}/site-packages/torch)
endif()

if(NOT EXISTS "${libtorch_base_path}")
  message(FATAL_ERROR
    "PyTorch not found in the expected location: ${libtorch_base_path}"
    "Please ensure PyTorch is installed in your Conda/Pixi environment."
  )
endif()

find_package(ATen CONFIG REQUIRED HINTS ${libtorch_base_path})
find_package(Torch CONFIG REQUIRED HINTS ${libtorch_base_path})
find_library(torch_python NAMES torch_python HINTS ${libtorch_base_path}/lib/ REQUIRED)

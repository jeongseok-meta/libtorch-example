cmake_minimum_required(VERSION 3.16.3)

project(LibTorchExample)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG REQUIRED)

if(NOT DEFINED ENV{CONDA_PREFIX})
  message(FATAL_ERROR "CONDA_PREFIX is not set")
endif()

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

set(target_name libtorch_example)
add_executable(${target_name} main.cpp)
target_include_directories(${target_name} PRIVATE
  ${ATEN_INCLUDE_DIR}
  ${TORCH_INCLUDE_DIRS}
  ${Python3_INCLUDE_DIRS}
)
target_link_libraries(${target_name} PRIVATE
  ${ATEN_LIBRARIES}
  ${TORCH_LIBRARIES}
  ${torch_python}
  pybind11::pybind11
  Python3::Python
)
target_compile_options(${target_name} PRIVATE
  ${TORCH_CXX_FLAGS}
)
target_compile_features(${target_name} PRIVATE cxx_std_17)
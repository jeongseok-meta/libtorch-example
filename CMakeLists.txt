cmake_minimum_required(VERSION 3.16.3)

project(LibTorchExample)

find_package(ATen CONFIG REQUIRED)
find_package(Torch CONFIG REQUIRED)
find_library(torch_python
  NAMES torch_python
  REQUIRED
)

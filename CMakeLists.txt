cmake_minimum_required(VERSION 3.1)
project(helper-streambufs LANGUAGES CXX)

add_library(helper-streambufs INTERFACE)
target_include_directories(helper-streambufs
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
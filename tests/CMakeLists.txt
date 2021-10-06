cmake_minimum_required(VERSION 3.1)

find_package(GTest REQUIRED)

set(TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/nulbufTests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filebufTests.cpp
)

add_executable(helper-streambufs-tests ${TEST_SOURCES})
target_link_libraries(helper-streambufs-tests PRIVATE gtest gtest_main helper-streambufs)
target_link_libraries(helper-streambufs-tests PUBLIC pthread)

target_compile_options(helper-streambufs-tests PRIVATE -g)

add_test(NAME helper-streambufs-tests COMMAND helper-streambufs-tests)


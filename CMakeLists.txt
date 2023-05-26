cmake_minimum_required(VERSION 3.0.0)
project(TEST_COM VERSION 0.1.0)

set(CMAKE_SYSTEM_NAME Windows)

add_subdirectory(serial-com)

# add compile definitions before executables.
target_compile_definitions(SERIAL_COM PUBLIC DEBUG ON)

add_executable(TEST_COM main.cpp)

set_target_properties(SERIAL_COM PROPERTIES CMAKE_POSITION_INDEPENDENT_CODE ON)
target_link_libraries(${PROJECT_NAME} SERIAL_COM)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

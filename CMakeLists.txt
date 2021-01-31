cmake_minimum_required(VERSION 3.0.0)
project(MonkeysWorldDemo VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/monkeys-world)
add_executable(MonkeysWorldDemo main.cpp)

target_link_libraries(MonkeysWorldDemo PRIVATE MonkeysWorld::Engine)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

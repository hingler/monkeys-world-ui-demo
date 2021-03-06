cmake_minimum_required(VERSION 3.0.0)
project(MonkeysWorldDemo VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/monkeys-world)
add_executable(MonkeysWorldDemo     src/scene/SplashScreen.cpp
                                    src/mat/DitheredOctMat.cpp
                                    src/game/OctTube.cpp
                                    src/game/Monkey.cpp
                                    src/ui/HorizontalMenuGroup.cpp
                                    src/ui/LerpMenu.cpp
                                    
                                    src/gamemenu/mat/BlindsTransitionMat.cpp
                                    src/gamemenu/mat/MenuBGMat.cpp
                                    src/gamemenu/ui/SlidingBlindsTransition.cpp
                                    src/gamemenu/ui/MenuBG.cpp
                                    src/gamemenu/ui/CourseSelectGroup.cpp
                                    src/gamemenu/GameMenu.cpp

                                    main.cpp)

target_include_directories(MonkeysWorldDemo PRIVATE include/)

target_link_libraries(MonkeysWorldDemo PRIVATE MonkeysWorld::Engine)

add_custom_command(TARGET MonkeysWorldDemo POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:MonkeysWorldDemo>/resources)

add_custom_command(TARGET MonkeysWorldDemo POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/monkeys-world/resources $<TARGET_FILE_DIR:MonkeysWorldDemo>/resources)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

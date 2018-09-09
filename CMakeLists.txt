cmake_minimum_required(VERSION 3.12)

project(ToxicRun)

add_compile_options(-Wall -Wextra -Wpedantic)

set(CMAKE_CXX_STANDARD 17)

set(SRC ${PROJECT_SOURCE_DIR}/src)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake-modules")
# all source files
set(SOURCES
        main.cpp
        ${SRC}/GameObject.cpp
        ${SRC}/Player.cpp
        ${SRC}/GameObjects.cpp
        ${SRC}/MyContactListener.cpp
        ${SRC}/ShadowObject.cpp
        ${SRC}/MapGenerator.cpp
        ${SRC}/Water.cpp
        ${SRC}/Stats.cpp
        ${SRC}/Game.cpp)

find_package(SFML REQUIRED COMPONENTS System Window Graphics)
find_package(Box2D REQUIRED)
find_package(LTBL REQUIRED)

#set headers stuff
set(INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}/include
        ${SFML_INCLUDE_DIR}
        ${BOX2D_INCLUDE_DIR}
        ${LTBL_INCLUDE_DIR})

#set lib stuff
set(DEPEND_LIBS
        ${SFML_LIBRARIES}
        ${BOX2D_LIBRARY}
        ${LTBL_LIBRARY})

include_directories(${INCLUDE_DIRS})
add_executable(ToxicRun ${SOURCES})
target_link_libraries(ToxicRun ${DEPEND_LIBS})


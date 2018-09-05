cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

#Enable debug symbols
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose debug or release" FORCE)
endif()

project(MCOneWeek)

#Add the files
file(GLOB_RECURSE SOURCES Source/*.cpp)
add_executable(MCOneWeek ${SOURCES})

#Include directory
include_directories(src/Dependencies/)

#Add libraries
#SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED graphics network audio window system)

# glad
# https://github.com/aaronmjacobs/InitGL
set(GLAD_DIR "Source/glad")
add_library("glad" "${GLAD_DIR}/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")
find_package(Threads)

target_link_libraries(MCOneWeek Threads::Threads ${EXECUTABLE_NAME} ${SFML_LIBRARIES}) 

#Copy resources
file(COPY ${CMAKE_SOURCE_DIR}/Res DESTINATION ${CMAKE_BINARY_DIR})

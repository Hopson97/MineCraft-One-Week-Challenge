cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

#Enable debug symbols
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose debug or release" FORCE)
endif()

project(mc-one-week)

#Add the files
file(GLOB_RECURSE SOURCES Source/*.cpp)
add_executable(mc-one-week ${SOURCES})

#Add libraries
#SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED graphics network audio window system)

#glm
find_package(glm REQUIRED)

# glad
# https://github.com/aaronmjacobs/InitGL
set(GLAD_DIR "Source/glad")
add_library("glad" "${GLAD_DIR}/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_INCLUDE_DIRS} PRIVATE "${GLAD_DIR}")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")


find_package(Threads)

target_link_libraries(mc-one-week Threads::Threads ${EXECUTABLE_NAME} ${SFML_LIBRARIES}) 

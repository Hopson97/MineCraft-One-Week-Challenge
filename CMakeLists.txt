cmake_minimum_required(VERSION 3.20)

#Set module path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake"  ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules"  ${CMAKE_MODULE_PATH})

#Includes
include(CheckIPOSupported)

include(message_macros)
include(clang_format)



#Set up project
project(mc-one-week VERSION 1.0)

begin_header(Configuration)
# TODO: move such stuff into toolchain file
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "ccache")
    set(CMAKE_C_COMPILER_LAUNCHER "ccache")
endif()


find_program(NINJA_PROGRAM ninja)
if(NINJA_PROGRAM)
    message(STATUS "Using Ninja as the build system : ${NINJA_PROGRAM}")
    set(CMAKE_GENERATOR Ninja)
endif()


check_ipo_supported(RESULT supported)
if(supported)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION True)
endif()

end_header()

begin_header(Linters)
# linters:
set(CMAKE_LINK_WHAT_YOU_USE ON)
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE iwyu)
end_header()


configure_file(config.txt ${CMAKE_BINARY_DIR}/config.txt COPYONLY)

# Copy the resource files to the new binary dir
add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/Res
    ${PROJECT_BINARY_DIR}/Res
    COMMENT "Copying game resources into Res folder")


add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/Shaders
    ${PROJECT_BINARY_DIR}/Shaders
    COMMENT "Copying shaders into Shaders folder")

#Set executable
add_executable(mc-one-week
    Source/Item/Material.cpp
    Source/Item/ItemStack.cpp
    Source/Application.cpp
    Source/World/Event/PlayerDigEvent.cpp
    Source/World/Block/BlockDatabase.cpp
    Source/World/Block/BlockData.cpp
    Source/World/Block/ChunkBlock.cpp
    Source/World/Block/BlockTypes/BlockType.cpp
    Source/World/World.cpp
    Source/World/Generation/Biome/LightForest.cpp
    Source/World/Generation/Biome/Biome.cpp
    Source/World/Generation/Biome/DesertBiome.cpp
    Source/World/Generation/Biome/GrasslandBiome.cpp
    Source/World/Generation/Biome/TemperateForestBiome.cpp
    Source/World/Generation/Biome/OceanBiome.cpp
    Source/World/Generation/Structures/TreeGenerator.cpp
    Source/World/Generation/Structures/StructureBuilder.cpp
    Source/World/Generation/Terrain/SuperFlatGenerator.cpp
    Source/World/Generation/Terrain/ClassicOverWorldGenerator.cpp
    Source/World/Chunk/ChunkMesh.cpp
    Source/World/Chunk/ChunkManager.cpp
    Source/World/Chunk/Chunk.cpp
    Source/World/Chunk/ChunkSection.cpp
    Source/World/Chunk/ChunkMeshBuilder.cpp
    Source/States/PlayState.cpp
    Source/Player/Player.cpp
    Source/Maths/Ray.cpp
    Source/Maths/Frustum.cpp
    Source/Maths/NoiseGenerator.cpp
    Source/Maths/Vector2XZ.cpp
    Source/Maths/Matrix.cpp
    Source/Maths/GeneralMaths.cpp
    Source/Camera.cpp
    Source/GL/GLFunctions.cpp
    Source/Context.cpp
    Source/Texture/CubeTexture.cpp
    Source/Texture/BasicTexture.cpp
    Source/Texture/TextureAtlas.cpp
    Source/Input/ToggleKey.cpp
    Source/Input/Keyboard.cpp
    Source/Main.cpp
    Source/Controller.cpp
    Source/Util/Random.cpp
    Source/Util/FPSCounter.cpp
    Source/Util/FileUtil.cpp
    Source/Shaders/FloraShader.cpp
    Source/Shaders/WaterShader.cpp
    Source/Shaders/SkyboxShader.cpp
    Source/Shaders/Shader.cpp
    Source/Shaders/ChunkShader.cpp
    Source/Shaders/BasicShader.cpp
    Source/Shaders/ShaderLoader.cpp
    Source/Renderer/RenderMaster.cpp
    Source/Renderer/WaterRenderer.cpp
    Source/Renderer/ChunkRenderer.cpp
    Source/Renderer/SkyboxRenderer.cpp
    Source/Renderer/FloraRenderer.cpp
    Source/Model.cpp
)



#Find libraries
find_package(Threads REQUIRED)
find_package(SFML REQUIRED graphics window system)

add_subdirectory(deps/glm)
add_subdirectory(deps/glad)

function(setup_target TARGET)
    #Set C++17
    target_compile_features(${TARGET} PUBLIC cxx_std_17)
    set_target_properties(${TARGET} PROPERTIES CXX_EXTENSIONS OFF)

    #Set flags
    if(MSVC)
        target_compile_options(${TARGET} PRIVATE 
            /W4 /WX)
    else()
        target_compile_options(${TARGET} PRIVATE 
            -Wall -Wextra -pedantic)
    endif()

    target_include_directories(
        ${TARGET}
        PRIVATE
        deps
    )
endfunction(setup_target)

setup_target(mc-one-week)
target_link_libraries(mc-one-week
    glm
    glad
    Threads::Threads
    ${SFML_LIBRARIES}
    ${SFML_DEPENDENCIES}
    ${CMAKE_DL_LIBS}
)

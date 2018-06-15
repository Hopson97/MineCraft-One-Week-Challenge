cmake_minimum_required (VERSION 3.8.2)
project (MineCraftOWC)
add_executable (minecraft 
./Source/Application.cpp
./Source/Camera.cpp
./Source/Config.cpp
./Source/Context.cpp
./Source/Controller.cpp
./Source/GL/GLFunctions.cpp
./Source/GLAD/glad.cpp
./Source/GlobalInfo.cpp
./Source/Item/ItemStack.cpp
./Source/Item/Material.cpp
./Source/Main.cpp
./Source/Maths/Frustum.cpp
./Source/Maths/GeneralMaths.cpp
./Source/Maths/Matrix.cpp
./Source/Maths/NoiseGenerator.cpp
./Source/Maths/Ray.cpp
./Source/Maths/Vector2XZ.cpp
./Source/Model.cpp
./Source/Physics/AABB.cpp
./Source/Player/Player.cpp
./Source/PostProcess/Antialiasing.cpp
./Source/PostProcess/Bloom.cpp
./Source/PostProcess/Combine.cpp
./Source/PostProcess/Framebuffer.cpp
./Source/PostProcess/GaussianBlur.cpp
./Source/PostProcess/GodRayShader.cpp
./Source/PostProcess/GodRays.cpp
./Source/PostProcess/HorizontalGaussian.cpp
./Source/PostProcess/ImageRenderer.cpp
./Source/PostProcess/MBlur.cpp
./Source/PostProcess/Mask.cpp
./Source/PostProcess/MotionBlur.cpp
./Source/PostProcess/PostProcessRenderer.cpp
./Source/PostProcess/VerticalGaussian.cpp
./Source/PostProcess/fxaa.cpp
./Source/RenderSettings.cpp
./Source/Renderer/ChunkRenderer.cpp
./Source/Renderer/FloraRenderer.cpp
./Source/Renderer/RenderMaster.cpp
./Source/Renderer/SFMLRenderer.cpp
./Source/Renderer/WaterRenderer.cpp
./Source/ShaderData.cpp
./Source/Shaders/BasicShader.cpp
./Source/Shaders/ChunkShader.cpp
./Source/Shaders/CloudShader.cpp
./Source/Shaders/FloraShader.cpp
./Source/Shaders/PostProcessShader.cpp
./Source/Shaders/ProcSkyShader.cpp
./Source/Shaders/Shader.cpp
./Source/Shaders/ShaderLoader.cpp
./Source/Shaders/SunShader.cpp
./Source/Shaders/WaterShader.cpp
./Source/Sky/Cloud.cpp
./Source/Sky/ProcSky.cpp
./Source/Sky/SkyManager.cpp
./Source/States/PlayingState.cpp
./Source/Texture/BasicTexture.cpp
./Source/Texture/TextureAtlas.cpp
./Source/Tick/TickManager.cpp
./Source/ToggleKey.cpp
./Source/Util/FPSCounter.cpp
./Source/Util/FileUtil.cpp
./Source/Util/Random.cpp
./Source/World/Block/BlockData.cpp
./Source/World/Block/BlockDatabase.cpp
./Source/World/Block/BlockTypes/BlockType.cpp
./Source/World/Block/ChunkBlock.cpp
./Source/World/Chunk/Chunk.cpp
./Source/World/Chunk/ChunkManager.cpp
./Source/World/Chunk/ChunkMesh.cpp
./Source/World/Chunk/ChunkMeshBuilder.cpp
./Source/World/Chunk/ChunkSection.cpp
./Source/World/Event/PlayerDigEvent.cpp
./Source/World/Generation/Biome/Biome.cpp
./Source/World/Generation/Biome/DesertBiome.cpp
./Source/World/Generation/Biome/GrasslandBiome.cpp
./Source/World/Generation/Biome/LightForest.cpp
./Source/World/Generation/Biome/OceanBiome.cpp
./Source/World/Generation/Biome/TemperateForestBiome.cpp
./Source/World/Generation/Structures/StructureBuilder.cpp
./Source/World/Generation/Structures/TreeGenerator.cpp
./Source/World/Generation/Terrain/ClassicOverWorldGenerator.cpp
./Source/World/Generation/Terrain/SuperFlatGenerator.cpp
./Source/World/World.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set_property(TARGET minecraft PROPERTY CXX_STANDARD 17)
set_property(TARGET minecraft PROPERTY CXX_STANDARD_REQUIRED ON)
find_package(SFML 2.4 REQUIRED graphics window system)
find_package(Threads)
find_package(OpenGL)
file(COPY Res Shaders DESTINATION ${CMAKE_BINARY_DIR})
option(SFML_STATIC_LIBRARIES "Set to TRUE to link libraries statically. Requires statically built SFML." FALSE)
target_link_libraries(minecraft Threads::Threads ${OPENGL_gl_LIBRARY} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} )


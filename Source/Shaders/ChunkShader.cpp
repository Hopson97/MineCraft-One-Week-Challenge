#include "ChunkShader.h"

ChunkShader::ChunkShader()
:   BasicShader ("ChunkVertex", "ChunkFragment")
{
    getUniforms();
}

void ChunkShader::loadLighting(float light){
    loadFloat(lighting, light);
}

void ChunkShader::getUniforms()
{
    BasicShader::getUniforms();
    lighting = glGetUniformLocation(m_id, "lighting");
}

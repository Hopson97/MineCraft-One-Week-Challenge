#include "ChunkShader.h"
#include "../GlobalInfo.h"

ChunkShader::ChunkShader()
:   BasicShader ("Chunk", "Chunk")
{
    getUniforms();
}

void ChunkShader::loadLighting(float light){
    loadFloat(lighting, light);
    loadInt(dtime, g_info.dayTime);
}

void ChunkShader::getUniforms()
{
    BasicShader::getUniforms();
    lighting = glGetUniformLocation(m_id, "lighting");
    dtime = glGetUniformLocation(m_id, "dayTime");
}

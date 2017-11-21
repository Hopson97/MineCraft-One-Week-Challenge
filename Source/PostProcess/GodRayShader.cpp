#include "GodRayShader.h"

GodRayShader::GodRayShader(): BasicShader("GodRays","GodRays"){
    getUniforms();
}

void GodRayShader::getUniforms(){
    BasicShader::getUniforms();
    m_time = glGetUniformLocation(m_id, "time");
    m_camPV = glGetUniformLocation(m_id, "CPVM");
    m_res = glGetUniformLocation(m_id, "resolution");
    m_mm = glGetUniformLocation(m_id, "sunMat");
}

void GodRayShader::loadRes(glm::vec2 v){
    loadVector2(m_res, v);
} 

void GodRayShader::loadTime(float time){
    loadFloat(m_time, time);
}

void GodRayShader::loadCPV(glm::mat4 m){
    loadMatrix4(m_camPV, m);
}

void GodRayShader::loadMM(glm::mat4 m){
    loadMatrix4(m_mm, m);
}
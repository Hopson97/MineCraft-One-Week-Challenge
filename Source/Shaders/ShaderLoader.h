#ifndef SHADERLOADER_H_INCLUDED
#define SHADERLOADER_H_INCLUDED 1

#include <glad/glad.h>
#include <string>

GLuint loadShaders(const std::string &vertexShader,
                   const std::string &fragmentShader);

#endif // SHADERLOADER_H_INCLUDED

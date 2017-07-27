#ifndef BASICSHADER_H_INCLUDED
#define BASICSHADER_H_INCLUDED

#include "Shader.h"

class BasicShader : public Shader
{
    public:
        BasicShader(const std::string& vertexFile   = "BasicVertex",
                    const std::string& fragmentFile = "BasicFragment");

        void loadProjectionViewMatrix   (const glm::mat4& pvMatrix);
        void loadModelMatrix            (const glm::mat4& matrix);

    private:
        virtual void getUniforms() override;

        GLuint m_locationProjectionViewMatrix;
        GLuint m_locationModelMatrix;
};

#endif // BASICSHADER_H_INCLUDED

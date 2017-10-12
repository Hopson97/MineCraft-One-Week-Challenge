#include "GLFunctions.h"

void GL::drawElements(GLuint indicesCount) noexcept
{
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
}

void GL::bindVAO(GLuint vao) noexcept
{
    glBindVertexArray(vao);
}

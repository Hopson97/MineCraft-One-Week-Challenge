#include "GLFunctions.h"

void GL::drawElements(GLuint indicesCount) noexcept
{
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
}

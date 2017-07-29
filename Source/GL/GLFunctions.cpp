#include "GLFunctions.h"

void GL::drawElements(GLuint indicesCount)
{
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
}

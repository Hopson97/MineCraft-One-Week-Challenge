#ifndef GLFUNCTIONS_H_INCLUDED
#define GLFUNCTIONS_H_INCLUDED

#include <glad/glad.h>

namespace GL {
void drawElements(GLuint indicesCount) noexcept;
void bindVAO(GLuint vao) noexcept;

namespace Enum {
enum Texture { Tex2D = GL_TEXTURE_2D, TexCubeMap = GL_TEXTURE_CUBE_MAP };
}
} // namespace GL

#endif // GLFUNCTIONS_H_INCLUDED

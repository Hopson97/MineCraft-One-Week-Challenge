#ifndef CUBETEXTURE_H_INCLUDED
#define CUBETEXTURE_H_INCLUDED

#include <glad/glad.h>

#include <SFML/Graphics.hpp>
#include <array>
#include <string>

#include "../Util/NonCopyable.h"

/// @brief Complex texture class that applies textures to all sides of a cube.
class CubeTexture : public NonCopyable {
  public:
    CubeTexture() = default;
    CubeTexture(const std::array<std::string, 6> &files);

    ~CubeTexture();

    /**
        MUST BE IN THIS ORDER:
            -right
            -left
            -top
            -bottom
            -back
            -front
    */
    void loadFromFiles(const std::array<std::string, 6> &files);

    void bindTexture() const;

  private:
    GLuint m_texId;
};

#endif // CUBETEXTURE_H_INCLUDED

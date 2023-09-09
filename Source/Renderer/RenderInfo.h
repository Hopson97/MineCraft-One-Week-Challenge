#ifndef RENDERINFO_H_INCLUDED
#define RENDERINFO_H_INCLUDED 1

struct RenderInfo {
    GLuint vao = 0; // Vertex Array Object
    GLuint indicesCount = 0;

    inline void reset()
    {
        vao = 0;
        indicesCount = 0;
    }
};

#endif // RENDERINFO_H_INCLUDED

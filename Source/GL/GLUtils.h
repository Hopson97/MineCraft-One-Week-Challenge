#pragma once

#include <glad/glad.h>

namespace gl
{
    enum class Face
    {
        Back = GL_BACK,
        Front = GL_FRONT,
        FrontAndBack = GL_FRONT_AND_BACK,
    };

    enum class Capability
    {
        Blend = GL_BLEND,
        DepthTest = GL_DEPTH_TEST,
        CullFace = GL_CULL_FACE,
        ScissorTest = GL_SCISSOR_TEST,
        StencilTest = GL_STENCIL_TEST
    };

    enum class PolygonMode
    {
        Point = GL_POINT,
        Line = GL_LINE,
        Fill = GL_FILL
    };

    enum class PrimitiveType
    {
        Points = GL_POINTS,
        Lines = GL_LINES,
        LineStrip = GL_LINE_STRIP,
        Triangles = GL_TRIANGLES,
        TriangleStrip = GL_TRIANGLE_STRIP,
        TriangleFan = GL_TRIANGLE_FAN
    };

    void enable_debugging();

    /**
     * @brief Wrapper for glCullFace.
     *
     * @param face The face to cull.
     */
    void cull_face(Face face);

    /**
     * @brief Wrapper for glEnable.
     *
     * @param capability The capability to enable.
     */
    void enable(Capability capability);

    /**
     * @brief Wrapper for glDisable.
     *
     * @param capability The capability to disable.
     */
    void disable(Capability capability);

    /**
     * @brief Wrapper for glPolygonMode.
     *
     * @param face The face to set the polygon mode for.
     * @param mode The polygon mode to set.
     */
    void polygon_mode(Face face, PolygonMode mode);
} // namespace gl

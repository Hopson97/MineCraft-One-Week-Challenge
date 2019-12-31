#include "Model.h"

Model::Model(const Mesh &mesh)
{
    addData(mesh);
}

Model::~Model()
{
    deleteData();
}

Model::Model(Model &&other)
    : m_renderInfo(other.m_renderInfo)
    , m_vboCount(other.m_vboCount)
    , m_buffers(std::move(other.m_buffers))
{
    other.m_renderInfo.reset();
    other.m_vboCount = 0;
}

Model &Model::operator=(Model &&other)
{
    m_renderInfo = other.m_renderInfo;
    m_vboCount = other.m_vboCount;
    m_buffers = std::move(other.m_buffers);

    other.m_renderInfo.reset();
    other.m_vboCount = 0;

    return *this;
}

void Model::genVAO()
{
    if (m_renderInfo.vao != 0)
        deleteData();

    glGenVertexArrays(1, &m_renderInfo.vao);
    glBindVertexArray(m_renderInfo.vao);
}

void Model::bindVAO() const
{
    glBindVertexArray(m_renderInfo.vao);
}

void Model::addData(const Mesh &mesh)
{
    genVAO();

    addVBO(3, mesh.vertexPositions);
    addVBO(2, mesh.textureCoords);
    addEBO(mesh.indices);
}

void Model::addVBO(int dimensions, const std::vector<GLfloat> &data)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(static_cast<GLuint>(m_vboCount), dimensions, GL_FLOAT,
                          GL_FALSE, 0, (GLvoid *)0);

    glEnableVertexAttribArray(static_cast<GLuint>(m_vboCount++));

    m_buffers.push_back(vbo);
}

void Model::addEBO(const std::vector<GLuint> &indices)
{
    m_renderInfo.indicesCount = static_cast<GLuint>(indices.size());
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
                 indices.data(), GL_STATIC_DRAW);
}

void Model::deleteData()
{
    if (m_renderInfo.vao)
        glDeleteVertexArrays(1, &m_renderInfo.vao);
    if (m_buffers.size() > 0)
        glDeleteBuffers(static_cast<GLsizei>(m_buffers.size()),
                        m_buffers.data());

    m_buffers.clear();

    m_vboCount = 0;
    m_renderInfo.reset();
}

int Model::getIndicesCount() const
{
    return m_renderInfo.indicesCount;
}

const RenderInfo &Model::getRenderInfo() const
{
    return m_renderInfo;
}

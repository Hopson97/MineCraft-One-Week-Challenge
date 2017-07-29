#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include "Mesh.h"

#include "Util/NonCopyable.h"

class Model : public NonCopyable
{
    public:
        Model() = default;
        Model(const Mesh& mesh);
        ~Model();

        Model(Model&& other);
        Model& operator= (Model&& other);

        void addData(const Mesh& mesh);

        void deleteData();

        void addVBO(int dimensions, const std::vector<GLfloat>& data);
        void bindVAO() const;

        int getIndicesCount() const;

    private:
        void addEBO(const std::vector<GLuint>& indices);

        GLuint m_vao = 0;
        int m_vboCount = 0;
        int m_indicesCount = 0;
        std::vector<GLuint> m_buffers;
};

#endif // MODEL_H_INCLUDED

#include "Mesh.h"
#include "VertexBufferLayout.h"
#include "src/Shader.h"

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices)
    : m_VBO(vertices),
      m_IBO(indices)
{
    m_Vertices = vertices;
    m_Indices = indices;
    VertexBufferLayout layout;
    layout.Push<GL_FLOAT>(3); // position coords
    // layout.Push<GL_FLOAT>(3); // normals
    layout.Push<GL_FLOAT>(2); // texture coords

    m_VAO.AddBuffer(m_VBO, layout);

    m_VertexCount = indices.size();
}

Mesh::~Mesh()
{
}

void Mesh::bind() const
{
    m_VAO.Bind();
    m_IBO.Bind();
}

void Mesh::unbind() const
{
    m_VAO.Unbind();
    m_IBO.Unbind();
}

void Mesh::render(Shader& shader) const
{
    shader.use();
    bind();
    GlCall(glDrawElements(GL_TRIANGLES, m_VertexCount, GL_UNSIGNED_INT, nullptr));
}

void Mesh::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

std::vector<Vertex> Mesh::getVertices() const {
    return m_Vertices;
}

std::vector<unsigned int> Mesh::getIndices() const {
    return  m_Indices;
}

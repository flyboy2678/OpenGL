#pragma once

#include <vector>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Mesh
{
private:
    VertexArray m_VAO;
    VertexBuffer m_VBO;
    IndexBuffer m_IBO;
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    unsigned int m_VertexCount;

public:
    //change this to an array of vertices
    Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);
    ~Mesh();

    void bind() const;
    void unbind() const;
    void render(Shader &shader) const;
    void clear() const;
    std::vector<Vertex> getVertices() const;
    std::vector<unsigned int> getIndices() const;
};

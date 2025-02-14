#pragma once

#include <vector>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

class Mesh
{
private:
    VertexArray m_VAO;
    VertexBuffer m_VBO;
    IndexBuffer m_IBO;
    unsigned int m_VertexCount;

public:
    Mesh(const std::vector<float> &vertices, const std::vector<unsigned int> &indices);
    ~Mesh();

    void bind() const;
    void unbind() const;
    void render() const;
    void clear() const;
};
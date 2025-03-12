#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertices)
{
    GlCall(glGenBuffers(1, &m_RenderID));
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
    GlCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GlCall(glDeleteBuffers(1, &m_RenderID));
}

void VertexBuffer::Bind() const
{

    GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
}

void VertexBuffer::Unbind() const
{

    GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

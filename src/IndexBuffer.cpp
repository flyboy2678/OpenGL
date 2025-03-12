#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& indices) : m_Count(indices.size())
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GlCall(glGenBuffers(1, &m_RenderID));
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));
    GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GlCall(glDeleteBuffers(1, &m_RenderID));
}

void IndexBuffer::Bind() const
{

    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));
}

void IndexBuffer::Unbind() const
{

    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

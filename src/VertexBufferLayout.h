#pragma once
#include <vector>
#include "Renderer.h"

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
        default:
            break;
        }
        ASSERT(false);
        return 0;
    }
    VertexBufferElement(unsigned int t, unsigned int c, bool n) : type(t), count(c), normalized(n)
    {
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

public:
    VertexBufferLayout() : m_Stride(0) {}

    template <GLenum T>
    void Push(unsigned int count)
    {
        m_Elements.push_back({T, count, false});
        m_Stride += count * VertexBufferElement::GetSizeOfType(T);
    }

    inline const std::vector<VertexBufferElement> &GetElements() const { return m_Elements; };
    inline unsigned int GetStride() const { return m_Stride; }
};

#pragma once

#include <vector>

class IndexBuffer
{
private:
    unsigned int m_RenderID;
    unsigned int m_Count;

public:
    IndexBuffer(const std::vector<unsigned int>& indices);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int getCount() const { return m_Count; }
};

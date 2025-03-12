#pragma once

#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 positon;
    //glm::vec3 normal;
    //glm::vec3 color;
    glm::vec2 texture;
};

class VertexBuffer
{
private:
    unsigned int m_RenderID;

public:
    VertexBuffer(const std::vector<Vertex>& vertices);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};

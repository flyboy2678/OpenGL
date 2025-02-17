#pragma once
#include "Mesh.h"

#include <glm/glm.hpp>

enum class BlockType
{
    AIR,
    GRASS,
    DIRT,
    STONE,
    WATER,
    SAND,
    WOOD,
    LEAVES
};

class Block
{
private:
    BlockType m_Type;
    glm::vec3 m_Position;
    bool m_IsActive;

public:
    Block();
    Block(BlockType type, glm::vec3 postion);
    BlockType getType() const;
    glm::vec3 getPosition() const;
    bool isActive() const;
    void setIsActive(bool active);
};
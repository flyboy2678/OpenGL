#include "Block.h"

Block::Block() {}

Block::Block(BlockType type, glm::vec3 postion)
    : m_Type(type), m_Position(postion), m_IsActive(type != BlockType::AIR)
{
}

void Block::setIsActive(bool isActive)
{
    m_IsActive = isActive;
}

BlockType Block::getType() const
{
    return m_Type;
}

glm::vec3 Block::getPosition() const
{
    return m_Position;
}

bool Block::isActive() const
{
    return m_IsActive;
}
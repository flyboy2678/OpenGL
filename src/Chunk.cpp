#include "Chunk.h"

Chunk::Chunk(glm::ivec3 position)
    : m_Position(position), m_Mesh(nullptr), m_isDirty(true)
{
    m_Blocks = new Block **[CHUNK_SIZE_X];

    // allocation memory
    for (int i = 0; i < CHUNK_SIZE_X; i++)
    {
        m_Blocks[i] = new Block *[CHUNK_SIZE_Z];
        for (int j = 0; j < CHUNK_SIZE_Z; j++)
        {
            m_Blocks[i][j] = new Block[CHUNK_SIZE_Y];
        }
    }

    for (int i = 0; i < CHUNK_SIZE_X; i++)
    {
        for (int j = 0; j < CHUNK_SIZE_Z; j++)
        {
            for (int k = 0; k < CHUNK_SIZE_Y; k++)
            {
                BlockType type = (k == 0)  ? BlockType::STONE
                                 : (k < 4) ? BlockType::DIRT
                                           : BlockType::GRASS;
                m_Blocks[i][j][k] = Block(type, glm::vec3(i, j, k));
            }
        }
    }
}

Chunk::~Chunk()
{
    for (int i = 0; i < CHUNK_SIZE_X; i++)
    {
        for (int j = 0; j < CHUNK_SIZE_Z; j++)
        {
            delete[] m_Blocks[i][j];
        }
        delete[] m_Blocks[i];
    }

    delete[] m_Blocks;
}
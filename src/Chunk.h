#pragma once

#include <vector>
#include "Block.h"
#include "Mesh.h"

const int CHUNK_SIZE_X = 16;
const int CHUNK_SIZE_Y = 256;
const int CHUNK_SIZE_Z = 16;

class Chunk
{
private:
    glm::ivec3 m_Position; // Chunk position in world space
    Block ***m_Blocks;     // 3D dynamic array of block
    Mesh *m_Mesh;          // Pointer to a chunk's mesh
    bool m_isDirty;

    void generateMesh(); // Generates a new mesh for the chunk

public:
    Chunk(glm::ivec3 position);
    ~Chunk();
    Block *GetBlock(int x, int y, int z);
    void SetBlock(int x, int y, int z);
    void Render();
};
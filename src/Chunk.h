#pragma once

#include "Block.h"
#include "Mesh.h"
#include "Texture.h"

const int CHUNK_SIZE_X = 16;
const int CHUNK_SIZE_Y = 24;
const int CHUNK_SIZE_Z = 16;

class Chunk
{
private:
    glm::ivec3 m_Position; // Chunk position in world space
    Block ***m_Blocks;     // 3D dynamic array of block
    bool m_isDirty;
    Mesh* m_BlockMesh;
    void generateMesh(); // Generates a new mesh for the chunk

public:
    Chunk(glm::vec3 position);
    ~Chunk();
    Block &GetBlock(int x, int y, int z);
    void SetBlock(int x, int y, int z);
    void Render(Shader& shader, Texture &Texture);
    Mesh& generateChunkData();
};

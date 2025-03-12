#include "Chunk.h"
#include "glm/gtc/matrix_transform.hpp"

Chunk::Chunk(glm::vec3 position)
    : m_Position(position), m_isDirty(true)
{
    generateChunkData();

    m_Blocks = new Block **[CHUNK_SIZE_X];

    // allocation memory
    for (int i = 0; i < CHUNK_SIZE_X; i++)
    {
        m_Blocks[i] = new Block *[CHUNK_SIZE_Y];
        for (int j = 0; j < CHUNK_SIZE_Y; j++)
        {
            m_Blocks[i][j] = new Block[CHUNK_SIZE_Y];
        }
    }

    for (int i = 0; i < CHUNK_SIZE_X; i++)
    {
        for (int j = 0; j < CHUNK_SIZE_Y; j++)
        {
            for (int k = 0; k < CHUNK_SIZE_Z; k++)
            {
                BlockType type = (j == 0)   ? BlockType::STONE
                                 : (j < 12) ? BlockType::DIRT
                                            : BlockType::GRASS;

                glm::vec3 pos = glm::vec3(
                    i + m_Position.x * CHUNK_SIZE_X,
                    j + m_Position.y * CHUNK_SIZE_Y,
                    k + m_Position.z * CHUNK_SIZE_Z);

                m_Blocks[i][j][k] = Block(type, pos);
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
    delete m_BlockMesh;
}

Block &Chunk::GetBlock(int x, int y, int z)
{
    return m_Blocks[x][y][z];
}

Mesh &Chunk::generateChunkData()
{
    std::vector<Vertex> vertices = {
        // Back face
        Vertex{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
        Vertex{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},

        // Front Face
        Vertex{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
        Vertex{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},

        // Left Face
        Vertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
        Vertex{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},

        // Right Face
        Vertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
        Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},

        // Bottom Face
        Vertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
        Vertex{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},

        // Top Face
        Vertex{glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
        Vertex{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
    };

    std::vector<unsigned int> indices = {
        // Back face
        0, 1, 2, 1, 3, 2,

        // Front face
        4, 5, 6, 5, 7, 6,

        // Left face
        8, 9, 10, 9, 11, 10,

        // Right face
        12, 13, 14, 13, 15, 14,

        // Bottom face
        16, 17, 18, 17, 19, 18,

        // Top face
        20, 21, 22, 21, 23, 22};

    m_BlockMesh = new Mesh(vertices, indices);
    m_BlockMesh->bind();
    return *m_BlockMesh;
}

void Chunk::Render(Shader &shader, Texture &texture)
{
    for (int i = 0; i < CHUNK_SIZE_X; i++)
    {
        for (int j = 0; j < CHUNK_SIZE_Y; j++)
        {
            for (int k = 0; k < CHUNK_SIZE_Z; k++)
            {
                if (m_Blocks[i][j][k].isActive())
                {
                    bool isExposed = (i == 0 || i == CHUNK_SIZE_X - 1 ||
                                      j == 0 || j == CHUNK_SIZE_Y - 1 ||
                                      k == 0 || k == CHUNK_SIZE_Z - 1
                                     );

                    if(!isExposed)
                        continue;
                    // draw here
                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, m_Blocks[i][j][k].getPosition());
                    shader.use();
                    shader.setUniformMat4f("u_Model", model);
                    shader.unbind();
                    m_BlockMesh->render(shader);
                }
            }
        }
    }
}

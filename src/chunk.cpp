#include <iostream>
#include <vector>

#include "chunk.h"

Chunk::Chunk(World &w, int x, int z)
{
    m_world = &w;
    m_chunkX = x;
    m_chunkZ = z;
    init();
    m_hasVBO = false;
}
Chunk::~Chunk()
{
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 192; y++)
            delete [] m_blocks[x][y];

        delete [] m_blocks[x];
    }
    delete [] m_blocks;

    delete [] m_vbos;
}
void Chunk::init()
{
    m_blocks = new uint8_t**[16];
    for(int x = 0; x < 16; x++)
    {
        m_blocks[x] = new uint8_t*[192];
        for(int y = 0; y < 192; y++)
            m_blocks[x][y] = new uint8_t[16];
    }

    for(int i = 0; i < 12; i++)
        m_dirtyVBOs[i] = false;
}
int Chunk::getBlockId(int x, int y, int z)
{
    if(y < 0 || y >= 192)
        return 0;

    x -= m_chunkX * 16;
    z -= m_chunkZ * 16;
    if(x >= 0 && x < 16 && z >= 0 && z < 16)
        return m_blocks[x][y][z];
    return -1;
}
void Chunk::setBlock(int x, int y, int z, int id)
{
    if(!m_blocks)
        return;
    if(y < 0 || y >= 192)
        return;
    x -= m_chunkX * 16;
    z -= m_chunkZ * 16;
    if(x > 15 || x < 0 || z > 15 || z < 0)
        return;

    m_blocks[x][y][z] = (uint8_t)id;
}
void Chunk::render(Camera &cam)
{
    if(!m_hasVBO)
        buildVBOs();
    if(!m_blocks)
        return;
    if(isDirty())
        cleanVBOs();
    for(int i = 0; i < 12; i++)
    {
        if(m_vbos[i])// && !m_vbos[i]->hasTransparentBlocks())
        {
            sf::Vector3<float> pos(m_vbos[i]->posx*200, m_vbos[i]->posy*200, m_vbos[i]->posz*200);
            pos -= cam.getPosition();
            pos.x += 1600.0;
            pos.y += 1600.0;
            pos.z += 1600.0;
            //AABB box(pos, 3200, 3200, 3200);
            if(cam.isSpereInFrustum(pos, 5500))
                m_vbos[i]->render(cam);
        }
    }
}

void Chunk::renderTransparent(Camera &cam)
{
    if(!m_hasVBO)
        buildVBOs();
    if(!m_blocks)
        return;
    if(isDirty())
        cleanVBOs();
    for(int i = 0; i < 12; i++)
    {
        if(m_vbos[i] && m_vbos[i]->hasTransparentBlocks())
        {
            sf::Vector3<float> pos(m_vbos[i]->posx*200, m_vbos[i]->posy*200, m_vbos[i]->posz*200);
            pos -= cam.getPosition();
            pos.x += 1700.0; // 8.5 m_blocks
            pos.y += 1700.0;
            pos.z += 1700.0;
            //AABB box(pos, 3200, 3200, 3200);
            if(cam.isSpereInFrustum(pos, 5500))
                m_vbos[i]->renderTransparent(cam);
        }
    }
}

bool Chunk::isDirty()
{
    for(int i = 0; i < 12; i++)
        if(m_dirtyVBOs[i])
            return true;
    return false;
}

void Chunk::cleanVBOs()
{
    std::vector<Vertex> vb; // vertex buffer
    std::vector<TexVert> tb; // texture buffer
    std::vector<ColVert> cb; // color buffer
    std::vector<Vertex> tvb; // transparent vertex buffer
    std::vector<TexVert> ttb; // transparent texture buffer
    std::vector<ColVert> tcb; // transparent color buffer

    for(int i = 0; i < 12; i++)
    {
        if(m_dirtyVBOs[i])
        {
            if(m_vbos[i])
                m_vbos[i]->reBuildVBO(*m_world, &vb, &tb, &cb, &tvb, &ttb, &tcb);
            else
            {
                m_vbos[i] = new VBOChunk(m_chunkX * 16, i * 16, m_chunkZ * 16);
                if(!m_vbos[i]->buildVBO(*m_world, &vb, &tb, &cb, &tvb, &ttb, &tcb))
                {
                    delete m_vbos[i];
                    m_vbos[i] = NULL; // no VBO there, make null so it won't be rendered
                }
            }
            m_dirtyVBOs[i] = false;
        }
    }
}
void Chunk::setBlocks(uint8_t ***b)
{
    if(!m_blocks)
        m_blocks = b;
}
void Chunk::markBlockDirty(int x, int y, int z)
{
    if(y < 0 || y >= 192)
        return;
    
    x = x >> 4;
    z = z >> 4;
    if(x != m_chunkX || z != m_chunkZ)
        return;
    
    m_dirtyVBOs[y/16] = true;
    if(y % 16 == 0 && y > 15)
        m_dirtyVBOs[y/16 - 1] = true;
    else if(y % 16 == 15 && y < 176) // 192-16 = 176 
        m_dirtyVBOs[y/16 + 1] = true;
}
void Chunk::buildVBOs()
{
    std::vector<Vertex> vertBuff;
    std::vector<TexVert> texBuff;
    std::vector<ColVert> colBuff;
    std::vector<Vertex> transVertBuff;
    std::vector<TexVert> transTexBuff;
    std::vector<ColVert> transColBuff;
    for(int i = 0; i < 12; i++)
    {
        m_vbos[i] = new VBOChunk(m_chunkX * 16, i * 16, m_chunkZ * 16);
        if(!m_vbos[i]->buildVBO(*m_world, &vertBuff, &texBuff, &colBuff, &transVertBuff, &transTexBuff, &transColBuff))
        {
            delete m_vbos[i];
            m_vbos[i] = NULL; // no VBO there, make null so it won't be rendered
        }
    }
    m_hasVBO = true;
}

void Chunk::saveToFile(std::ofstream &outfile)
{
    // files should be opened in binary mode
    for(int x = 0; x < 16; x++)
        for(int y = 0; y < 192; y++)
            outfile.write((char *)m_blocks[x][y], 16);
    outfile.close();
}
void Chunk::loadFromFile(std::ifstream &infile)
{
    if(!m_blocks)
        init();

    for(int x = 0; x < 16; x++)
        for(int y = 0; y < 192; y++)
            infile.read((char *)m_blocks[x][y], 16);
    //BuildVBOs();
    infile.close();
}
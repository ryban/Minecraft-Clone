#ifndef CHUNK_H
#define CHUNK_H

#include <list>
#include <fstream>
class Chunk;
#include "AABB.h"
#include "vertex.h"
#include "camera.h"
#include "world.h"

#define uint8_t unsigned char

class Chunk
{
    public:
        Chunk(World &world, int x, int z);
        ~Chunk();
        int getBlockId(int x, int y, int z);
        void setBlock(int x, int y, int z, int id);
        void render(Camera &cam);
        void renderTransparent(Camera &cam);
        void markBlockDirty(int x, int y, int z);
        int getChunkX() { return m_chunkX; }
        int getChunkZ() { return m_chunkZ; }

        void setBlocks(uint8_t ***b);
        uint8_t ***getBlocks() { return m_blocks; }

        void saveToFile(std::ofstream &outfile);
        void loadFromFile(std::ifstream &infile);

        bool isDirty();
    private:
        void cleanVBOs();
        void buildVBOs();
        void init();
        World *m_world;
        int m_chunkX;
        int m_chunkZ;
        bool m_hasVBO;
        uint8_t ***m_blocks;
        VBOChunk *m_vbos[12];
        bool m_dirtyVBOs[12];
};

#endif
#ifndef WORLD_H
#define WORLD_H

#include <ctime>
#include <string>

class World;
#include "block.h"
#include "camera.h"
#include "chunk.h"
#include "chunkgenerator.h"

const int chunkSide = 25;
const int chunkHalfSide = (chunkSide-1)/2;
const int totalChunks = chunkSide * chunkSide;

class World
{
    public:
        World();
        World(long s);
        World(long s, std::string &directory);
        ChunkGenerator *GetChunkGenerator();
        int getBlockId(int x, int y, int z);
        void setBlockId(int x, int y, int z, int id);
        void markBlockDirty(int x, int y, int z);
        Block *getBlock(int x, int y, int z);
        Block *getBlockFromId(int id);
        bool isBlockOpaque(int x, int y, int z);
        bool isBlockOpaque(int id);

        void render(Camera &cam);
        void saveWorld(std::string &directory);
    private:
        void init();
        void init_LoadSavedWorld(std::string &directory);
        void initBlocks();
        Chunk *chunkWithXZ(int x, int z);
        long m_seed;
        Chunk *m_chunks[totalChunks]; // 13x13 chunks
        Block *m_blockList[256];
        ChunkGenerator *m_chunkGen;
};

#endif
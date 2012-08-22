#include <iostream>
#include <sys/time.h>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "world.h"
#include "blockids.h"


World::World()
{
    m_seed = time(0); // get new seed from current time
    init();
}
World::World(long s)
{
    m_seed = s;
    init();
}
World::World(long s, std::string &directory)
{
    m_seed = s;
    init_LoadSavedWorld(directory);
}

void World::init()
{
    std::cout << totalChunks << std::endl;
    m_chunkGen = new ChunkGenerator(m_seed);
    clock_t time_start;
    clock_t total;

    initBlocks();
    for(int i = 0; i < totalChunks; i++)
        m_chunks[i] = NULL;
    for(int x = -chunkHalfSide; x <= chunkHalfSide; x++)
    {
        for(int z = -chunkHalfSide; z <= chunkHalfSide; z++)
        {
            int cindex = ((x + chunkHalfSide) * chunkSide) + z + chunkHalfSide;
            m_chunks[cindex] = new Chunk(*this, x, z);
            if(cindex % (totalChunks/20) == 0)
                std::cout << "Generating chunks..." << ((float)cindex/totalChunks)*100 << "%\n";
            time_start = clock();
            m_chunkGen->generateChunk(m_chunks[cindex]);
            total += clock() - time_start;
        }
    }
    std::cout << "avg time/chunk: " << (((double)total/totalChunks) / CLOCKS_PER_SEC)*1000 << "ms\n";
}

void World::init_LoadSavedWorld(std::string &directory)
{
    // im lazy, assumes file exists
    m_chunkGen = new ChunkGenerator(m_seed);
    initBlocks();

    for(int i = 0; i < totalChunks; i++)
        m_chunks[i] = NULL;
    std::ostringstream oss;
    for(int x = -chunkHalfSide; x <= chunkHalfSide; x++)
    {
        for(int z = -chunkHalfSide; z <= chunkHalfSide; z++)
        {
            int cindex = ((x + chunkHalfSide) * chunkSide) + z + chunkHalfSide;
            m_chunks[cindex] = new Chunk(*this, x, z);

            std::string filename = directory;
            oss << x << z;
            filename += '/' + oss.str() + ".dat";
            oss.str("");

            std::ifstream infile;
            infile.open(filename.c_str(),  std::ios::in | std::ios::binary);
            m_chunks[cindex]->loadFromFile(infile);
        }
    }
}

void World::initBlocks()
{
    for(int i = 0; i < 255; i++)
        m_blockList[i] = NULL;

    m_blockList[STONE_ID] = new BlockStone(STONE_ID);
    m_blockList[DIRT_ID] = new BlockDirt(DIRT_ID);
    m_blockList[GRASS_ID] = new BlockGrass(GRASS_ID);
    m_blockList[WATER_ID] = new BlockWater(WATER_ID);
    m_blockList[GRANITE_ID] = new BlockGranite(GRANITE_ID);
    m_blockList[LIMESTONE_ID] = new BlockLimeStone(LIMESTONE_ID);
    m_blockList[SLATE_ID] = new BlockSlate(SLATE_ID);
    m_blockList[GABBRO_ID] = new BlockGabbro(GABBRO_ID);
    m_blockList[SAND_ID] = new BlockSand(SAND_ID);
}

void World::saveWorld(std::string &directory)
{
    std::ostringstream oss;
    for(int i = 0; i < totalChunks; i++)
    {   
        std::string filename = directory;
        oss << m_chunks[i]->getChunkX() << m_chunks[i]->getChunkZ();
        filename += '/' + oss.str() + ".dat";
        oss.str("");

        std::ofstream outfile;
        outfile.open(filename.c_str(),  std::ios::out | std::ios::binary);
        m_chunks[i]->saveToFile(outfile);
    }
}

int World::getBlockId(int x, int y, int z)
{
    int chunkX = x >> 4;
    int chunkZ = z >> 4;
    Chunk *chunk = chunkWithXZ(chunkX, chunkZ);
    if(chunk)
        return chunk->getBlockId(x, y, z);
    return 0;
}
void World::setBlockId(int x, int y, int z, int id)
{
    int chunkX = x >> 4;
    int chunkZ = z >> 4;
    Chunk *chunk = chunkWithXZ(chunkX, chunkZ);
    if(chunk)
    {
        chunk->setBlock(x, y, z, id);
        markBlockDirty(x, y, z);
    }
}
void World::markBlockDirty(int x, int y, int z)
{
    int chunkX = x >> 4;
    int chunkZ = z >> 4;
    Chunk *chunk = chunkWithXZ(chunkX, chunkZ);
    if(chunk)
        chunk->markBlockDirty(x, y, z);

    chunk = chunkWithXZ(chunkX-1, chunkZ);
    if(chunk)
        chunk->markBlockDirty(x-1, y, z);
    chunk = chunkWithXZ(chunkX+1, chunkZ);
    if(chunk)
        chunk->markBlockDirty(x+1, y, z);

    chunk = chunkWithXZ(chunkX, chunkZ-1);
    if(chunk)
        chunk->markBlockDirty(x, y, z-1);
    chunk = chunkWithXZ(chunkX, chunkZ+1);
    if(chunk)
        chunk->markBlockDirty(x, y, z+1);
    
}
Block *World::getBlock(int x, int y, int z)
{
    return getBlockFromId(getBlockId(x, y, z));
}
Block *World::getBlockFromId(int id)
{
    if(id > 0 && id < 256)
        return m_blockList[id];
    return NULL;
}
Chunk *World::chunkWithXZ(int x, int z)
{
    if(x <= chunkHalfSide && x >= -chunkHalfSide && z <= chunkHalfSide && z >= -chunkHalfSide)
        return m_chunks[((x + chunkHalfSide) * chunkSide) + z + chunkHalfSide]; // with static m_chunks, this works for now
    //for(int i = 0; i < 81; i++)
        //if(m_chunks[i] != NULL && m_chunks[i]->getChunkX() == x && m_chunks[i]->getChunkZ() == z)
            //return m_chunks[i];
    return NULL;
}
void World::render(Camera &cam)
{
    static bool first = true;
    clock_t time_start;
    clock_t total;
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );

    for(int i = 0; i < totalChunks; i++)
    {
        if(first)
        {
            time_start = clock();
            if(i % (totalChunks/20) == 0)
                std::cout << "Generating VBOs..." << ((float)i/totalChunks)*100 << "%\n";
        }
        m_chunks[i]->render(cam);
        if(first)
            total += clock() - time_start;
    }
    for(int i = 0; i < totalChunks; i++)
        m_chunks[i]->renderTransparent(cam);

    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );
    if(first)
    {
        first = false;
        std::cout << "avg time to generate 12 VBOs: " << (((double)total/totalChunks) / CLOCKS_PER_SEC)*1000 << "ms\n";
    }
}

bool World::isBlockOpaque(int x, int y, int z)
{
    Block *b = getBlock(x, y, z);
    if(b)
        return b->isOpaque();
    else
        return false;
}

bool World::isBlockOpaque(int id)
{
    Block *b = getBlockFromId(id);
    if(b)
        return b->isOpaque();
    else
        return false;
}
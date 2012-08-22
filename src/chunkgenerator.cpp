#include <SFML/System.hpp>
#include <iostream>
#include <cmath>
#include "chunkgenerator.h"
#include "blockids.h"

ChunkGenerator::ChunkGenerator(long seed)
{
    m_seed = seed;
    // perlin noise that controls what type of terrain to generate
    terrainControl = new Noise::PerlinModule(m_seed, 4, 0.0025, 0.3, -1.0, 0.8);
    // the cache makes it so that we don't waste time calling the same funciton on the same
    // position over and over again, and saves time
    terrainControlCache = new Noise::CacheModule(terrainControl);

    // terrain shapr for various terrain types
    mountains = new Noise::PerlinModule(m_seed+1, 5, 0.006, 0.65, 0.2, 1.0);
    hills = new Noise::PerlinModule(m_seed+2, 6, 0.004, 0.52, 0.1, 0.4);
    plains = new Noise::PerlinModule(m_seed+3, 4, 0.007, 0.4, 0.0, 0.2);
    ocean = new Noise::PerlinModule(m_seed+4, 4, 0.007, 0.4, -0.32, 0.2);

    // ocean  plains  hills  mountains
    // -1 === -0.5 === 0.0 === 0.5 === 1
    // each of these selects between the other type
    // mountainHillSelect is the one used to select between all noises
    plainOceanSelect = new Noise::SelectModule(terrainControlCache, ocean, plains, -0.5, 0.2);
    hillPlainSelect = new Noise::SelectModule(terrainControlCache, plainOceanSelect, hills, 0.0, 0.2);
    mountainHillSelect = new Noise::SelectModule(terrainControlCache, hillPlainSelect, mountains, 0.5, 0.2);

    // perlin noise for cave genreation
    cave_generator = new Noise::PerlinModule(m_seed + 13, 4, 0.05, 0.4, -1.0, 1.0);
}
ChunkGenerator::~ChunkGenerator()
{
    // deleteing mountainHillSelect deletes all
    // of the classes contained within it. Cascades down
    // and deletes all of the generators
    delete mountainHillSelect;
    delete cave_generator;
}

// generates the terrain for a chunk
void ChunkGenerator::generateChunk(Chunk *chunk)
{
    uint8_t ***blocks = chunk->getBlocks();
    int x_offset = chunk->getChunkX() * 16;
    int z_offset = chunk->getChunkZ() * 16;

    init_TerrainNoise(chunk);
    for(int x = 0; x < 16; x++)
    {
        int xx = x + x_offset;
        for(int z = 0; z < 16; z++)
        {
            int zz = z + z_offset;
            for(int y = 0; y < 192; y++)
            {
                double n = getTerrainNoise(chunk, xx, y, zz);
                if(n > ((y-96)/192.0) * 2.0)
                    blocks[x][y][z] = STONE_ID;
                else if(y < 104)
                    blocks[x][y][z] = WATER_ID;
                else
                    blocks[x][y][z] = AIR_ID;
            }
        }
    }
    decorateChunk(chunk);
}
// adds caves, grass, sand, and various colored stones
// to the world
void ChunkGenerator::decorateChunk(Chunk *chunk)
{
    int x_offset = chunk->getChunkX() * 16;
    int z_offset = chunk->getChunkZ() * 16;

    int heightMap[16][16];

    for(int x = x_offset; x < x_offset+16; x++)
    {
        for(int z = z_offset; z < z_offset+16; z++)
        {
            int topY = getTopSolidBlockY(chunk, x, z, 191, 0);

            heightMap[x - x_offset][z - z_offset] = topY;
            if(topY <= 106)
            {
                chunk->setBlock(x, topY, z, SAND_ID);
                chunk->setBlock(x, topY-1, z, SAND_ID);
                for(int y = topY-2; y > topY-5; y--)
                    if(chunk->getBlockId(x, y, z) != AIR_ID)
                        chunk->setBlock(x, y, z, DIRT_ID);
            }
            else
            {
                chunk->setBlock(x, topY, z, GRASS_ID);
                for(int y = topY-1; y > topY-4; y--)
                    if(chunk->getBlockId(x, y, z) != AIR_ID)
                        chunk->setBlock(x, y, z, DIRT_ID);
            }
        }
    }

    // caves and different stones
    init_CaveNoise(chunk);

    for(int x = 0; x < 16; x++)
    {
        int xx = x + x_offset;
        for(int z = 0; z < 16; z++)
        {
            int zz = z + z_offset;
            for(int y = 0; y < 192; y++)
            {
                // make caves
                if(y > 3 && chunk->GetBlockId(xx, y+1, zz) != 4 && chunk->GetBlockId(xx, y+2, zz) != 4)
                {
                    double cave_n = GetCaveNoise(chunk, xx, y, zz);
                    if(cave_n > ((y-52)/192.0) * 2.0 && cave_n < ((y-16)/192.0) * 2.0 && chunk->GetBlockId(xx, y, zz) != 4)
                        chunk->SetBlock(xx, y, zz, 0);
                }
                // place stone layers
                if(chunk->getBlockId(xx, y, zz) == STONE_ID)
                {
                    if(y < heightMap[x][z]-104 + 16)
                        chunk->setBlock(xx, y, zz, GABBRO_ID);
                    else if(y < heightMap[x][z]-104 + 36)
                        chunk->setBlock(xx, y, zz, GRANITE_ID);
                    else if(y < heightMap[x][z]-104 + 64)
                        chunk->setBlock(xx, y, zz, SLATE_ID);
                    else if(y < heightMap[x][z]-104 + 86)
                        chunk->setBlock(xx, y, zz, LIMESTONE_ID);
                }
            }
        }
    }
}
// gets the top solid (non transparent) block id
int ChunkGenerator::getTopSolidBlockY(Chunk *chunk, int x, int z, int startY, int stopY)
{
    for(int y = startY; y >= stopY; y--)
        if(chunk->getBlockId(x, y ,z) != AIR_ID && chunk->getBlockId(x, y ,z) != WATER_ID)
            return y;
    return 0;
}
// initializes the cave noise at the corners of the 
// 16x16x16 mini-chunk so we can interpolate the blocks
// between and save a lot of time 
void ChunkGenerator::init_CaveNoise(Chunk *chunk)
{
    int chunkX = chunk->getChunkX()*16;
    int chunkZ = chunk->getChunkZ()*16;
    for(int x = 0; x < 2; x++)
        for(int y = 0; y < 13; y++)
            for(int z = 0; z < 2; z++)
                cave_noise[x][y][z] = cave_generator->getValue(x*16+chunkX
                                                                , y * 16
                                                                , z*16+chunkZ);
}
// initialize the terrain noise to speed up terrain generation
// the number of points to generate is modifiable.
// 16 gives fast terrain, but looks odd
// 8 is ok
// 4 is good, what I use and no loss in speed compared to 8
// 2 is horribly slow
// 1 takes about 10 seconds to generate a single chunk
void ChunkGenerator::init_TerrainNoise(Chunk *chunk)
{
    int chunkX = chunk->getChunkX()*16;
    int chunkZ = chunk->getChunkZ()*16;
    for(int x = 0; x < XZsubdivisions; x++)
        for(int y = 0; y < Ysubdivisions; y++)
            for(int z = 0; z < XZsubdivisions; z++)
                terrain_noise[x][y][z] = mountainHillSelect->getValue(x*subDivisionSize+chunkX
                                                                , y * subDivisionSize
                                                                , z*subDivisionSize+chunkZ);
}

// gets whether a block should be solid or air at a given position
// by interpolating between the points generated in init_CaveNoise(...)
double ChunkGenerator::getCaveNoise(Chunk *chunk, int x, int y, int z)
{
    int y0 = y / 16;

    double v000 = cave_noise[0][y0][0];
    double v100 = cave_noise[1][y0][0];
    double v010 = cave_noise[0][y0+1][0];
    double v110 = cave_noise[1][y0+1][0];
    double v001 = cave_noise[0][y0][1];
    double v101 = cave_noise[1][y0][1];
    double v011 = cave_noise[0][y0+1][1];
    double v111 = cave_noise[1][y0+1][1];

    double x1 = fabs((double)((x-chunk->getChunkX()*16) / 16.0));
    double z1 = fabs((double)((z-chunk->getChunkZ()*16) / 16.0));
    double y1 = (double)((y % 16) / 16.0);

    return Noise::Utils::trilerp(v000, v100, v010, v110, v001, v101, v011, v111, x1, y1, z1);
}
// gets whether a block should be solid or air at a given position
// by interpolating between the points generated in init_TerrainNoise(...)
double ChunkGenerator::getTerrainNoise(Chunk *chunk, int x, int y, int z)
{
    int y0 = y / subDivisionSize;
    int x0 = (x - (chunk->getChunkX() * 16)) / subDivisionSize;
    int z0 = (z - (chunk->getChunkZ() * 16)) / subDivisionSize;

    double v000 = terrain_noise[x0][y0][z0];
    double v100 = terrain_noise[x0+1][y0][z0];
    double v010 = terrain_noise[x0][y0+1][z0];
    double v110 = terrain_noise[x0+1][y0+1][z0];
    double v001 = terrain_noise[x0][y0][z0+1];
    double v101 = terrain_noise[x0+1][y0][z0+1];
    double v011 = terrain_noise[x0][y0+1][z0+1];
    double v111 = terrain_noise[x0+1][y0+1][z0+1];

    // x1, z1, y1 are values from 0.0-1.0
    
    double x1 = fabs((double)(((x-chunk->getChunkX()*16)%subDivisionSize) / (float)subDivisionSize));
    double z1 = fabs((double)(((z-chunk->getChunkZ()*16)%subDivisionSize) / (float)subDivisionSize));
    double y1 = (double)((y % subDivisionSize) / (float)subDivisionSize);

    return Noise::Utils::trilerp(v000, v100, v010, v110, v001, v101, v011, v111, x1, y1, z1);
}
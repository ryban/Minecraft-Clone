#ifndef CHUNKGENERATOR_H
#define CHUNKGENERATOR_H

class ChunkGenerator;
#include "chunk.h"
#include "noise/Noise.h"

const int subDivisionSize = 4;
const int XZsubdivisions = 16 / subDivisionSize + 1;
const int Ysubdivisions = 192 / subDivisionSize + 1;

class ChunkGenerator
{
    public:
        ChunkGenerator(long seed);
        ~ChunkGenerator();

        void generateChunk(Chunk *chunk);
        void decorateChunk(Chunk *chunk);
    private:
        int getTopSolidBlockY(Chunk *chunk, int x, int z, int startY, int stopY);
        void init_CaveNoise(Chunk *chunk);
        void init_TerrainNoise(Chunk *chunk);
        double getCaveNoise(Chunk *chunk, int x, int y, int z);
        double getTerrainNoise(Chunk *chunk, int x, int y, int z);
        long m_seed;

        Noise::PerlinModule *terrainControl;   // control srouce for all selectors
        Noise::CacheModule *terrainControlCache;

        Noise::SelectModule *mountainHillSelect; // selects between hillPlainSelect, and mountains
        Noise::SelectModule *hillPlainSelect; // selects betweens hills and plainsOceanSelect
        Noise::SelectModule *plainOceanSelect; // selects between plains and ocean

        Noise::PerlinModule *mountains;
        Noise::PerlinModule *hills;
        Noise::PerlinModule *plains;
        Noise::PerlinModule *ocean;

        Noise::PerlinModule *cave_generator;

        double cave_noise[2][13][2];
        double terrain_noise[XZsubdivisions][Ysubdivisions][XZsubdivisions];
};

/*
inline double trilerp(double v000, double v100, double v010, double v110,
               double v001, double v101, double v011, double v111,
               double x, double y, double z);
*/
#endif
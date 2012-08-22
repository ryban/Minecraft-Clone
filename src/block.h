#ifndef BLOCK_H
#define BLOCK_H

// all of the block classes in the game in one easy spot.
// all blocks inherit the virtual class Block

class Block;
class BlockGrass;
class BlockWater;
#include "vertex.h"
#include "camera.h"
#include "texcoords.h"
#include "world.h"

class Block
{
    public:
        Block(int id);
        ~Block();
        virtual void renderToVBO(World &world, VBOChunk &vbo, int x, int y, int z) = 0;
        virtual bool isOpaque() { return true; }
    protected:
        int blockId;
};

/////////////////////////
//////    Grass    //////
/////////////////////////

class BlockGrass : public Block
{
    public:
        BlockGrass(int id);
        ~BlockGrass();
        virtual void renderToVBO(World &world, VBOChunk &vbo, int x, int y, int z);
    protected:
        TexCoords texside;
        TexCoords textop;
        TexCoords texbot;
};

/////////////////////////
//////    Water    //////
/////////////////////////

class BlockWater : public Block
{
    public:
        BlockWater(int id);
        ~BlockWater();
        virtual void renderToVBO(World &world, VBOChunk &vbo, int x, int y, int z);
        virtual bool isOpaque() { return false; }
    protected:
        TexCoords texside;
};

//////////////////////////
//////    Stones    //////
//////////////////////////

class BlockStone : public Block
{
    public:
        BlockStone(int id);
        ~BlockStone();
        virtual void renderToVBO(World &world, VBOChunk &vbo, int x, int y, int z);
        virtual bool isOpaque() { return true; }
    protected:
        TexCoords texside;

};

class BlockGranite : public BlockStone
{
    public:
        BlockGranite(int id);
};

class BlockLimeStone : public BlockStone
{
    public:
        BlockLimeStone(int id);
};

class BlockSlate : public BlockStone
{
    public:
        BlockSlate(int id);
};

class BlockGabbro : public BlockStone
{
    public:
        BlockGabbro(int id);
};

/////////////////////////
/////     Sand     //////
/////////////////////////

class BlockSand : public BlockStone
{
    public:
        BlockSand(int id);
};

////////////////////////
//////    Dirt    //////
////////////////////////

class BlockDirt : public BlockStone
{
    public:
        BlockDirt(int id);
        ~BlockDirt();
};

#endif
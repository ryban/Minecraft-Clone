#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "block.h"
#include "renderhelper.h"

Block::Block(int id)
{
    blockId = id;
}
Block::~Block()
{
}

/////////////////////////////
//////     Grass     ////////
/////////////////////////////

BlockGrass::BlockGrass(int id) : Block(id)
{
    texside.setCoords(2, 0);
    textop.setCoords(3, 0);
    texbot.setCoords(1, 0);
}

BlockGrass::~BlockGrass()
{
}
void BlockGrass::renderToVBO(World &world, VBOChunk &vbo, int x, int y, int z)
{
    // dont try and render a NULL block, like air
    if(!this)
        return;
    // xyz are the corridinates relative to the subchunk
    // Get the position in the world
    int wx = x + vbo.posx;
    int wz = z + vbo.posz;
    int wy = y + vbo.posy;
    if(world.getBlockId(wx, wy, wz) <= 0)
        return;
    // west
    if(!world.isBlockOpaque(wx, wy ,wz-1))
        rh::drawWestFace(vbo, texside, x, y, z);
    // east
    if(!world.isBlockOpaque(wx, wy, wz+1))
       rh::drawEastFace(vbo, texside, x, y, z);
    // south
    if(!world.isBlockOpaque(wx-1, wy, wz))
        rh::drawSouthFace(vbo, texside, x, y, z);
    // north
    if(!world.isBlockOpaque(wx+1, wy, wz))
        rh::drawNorthFace(vbo, texside, x, y, z);
    // bottom
    if(!world.isBlockOpaque(wx, wy-1, wz))
        rh::drawBottomFace(vbo, texbot, x, y, z);
    // top
    if(!world.isBlockOpaque(wx, wy+1, wz))
        rh::drawTopFace(vbo, textop, x, y, z);
}

/////////////////////////////
//////     Water     ////////
/////////////////////////////


BlockWater::BlockWater(int id) : Block(id)
{
    texside.setCoords(1, 1);
}

BlockWater::~BlockWater()
{
}

void BlockWater::renderToVBO(World &world, VBOChunk &vbo, int x, int y, int z)
{
    if(!this)
        return;
    // xyz are the corridinates relative to the subchunk
    // Get the position in the world
    int wx = x + vbo.posx;
    int wz = z + vbo.posz;
    int wy = y + vbo.posy;
    if(world.getBlockId(wx, wy, wz) <= 0)
        return;

    // west
    int id = world.getBlockId(wx, wy ,wz-1);
    if(id != blockId && !world.isBlockOpaque(id))
        rh::drawWestFaceTransparent(vbo, texside, x, y, z);
    // east
    id = world.getBlockId(wx, wy, wz+1);
    if(id != blockId && !world.isBlockOpaque(id))
        rh::drawEastFaceTransparent(vbo, texside, x, y, z);
    // south
    id = world.getBlockId(wx-1, wy, wz);
    if(id != blockId && !world.isBlockOpaque(id))
        rh::drawSouthFaceTransparent(vbo, texside, x, y, z);
    // north
    id = world.getBlockId(wx+1, wy ,wz);
    if(id != blockId && !world.isBlockOpaque(id))
        rh::drawNorthFaceTransparent(vbo, texside, x, y, z);
    // bottom
    id = world.getBlockId(wx, wy-1 ,wz);
    if(id != blockId && !world.isBlockOpaque(id))
        rh::drawBottomFaceTransparent(vbo, texside, x, y, z);
    // top
    id = world.getBlockId(wx, wy+1 ,wz);
    if(id != blockId && !world.isBlockOpaque(id))
        rh::drawTopFaceTransparent(vbo, texside, x, y, z);
}

//////////////////////////
//////    Stones    //////
//////////////////////////

BlockStone::BlockStone(int id) : Block(id)
{
    texside.setCoords(0, 0);
}

BlockStone::~BlockStone()
{
}

BlockGranite::BlockGranite(int id) : BlockStone(id)
{
    texside.setCoords(0, 1);
}

BlockLimeStone::BlockLimeStone(int id) : BlockStone(id)
{
    texside.setCoords(0, 2);
}

BlockSlate::BlockSlate(int id) : BlockStone(id)
{
    texside.setCoords(0, 3);
}

BlockGabbro::BlockGabbro(int id) : BlockStone(id)
{
    texside.setCoords(0, 4);
}

void BlockStone::renderToVBO(World &world, VBOChunk &vbo, int x, int y, int z)
{
    if(!this)
        return;
    // xyz are the corridinates relative to the subchunk
    // Get the position in the world
    int wx = x + vbo.posx;
    int wz = z + vbo.posz;
    int wy = y + vbo.posy;
    if(world.getBlockId(wx, wy, wz) <= 0)
        return;

    // west
    if(!world.isBlockOpaque(wx, wy ,wz-1))
        rh::drawWestFace(vbo, texside, x, y, z);
    // east
    if(!world.isBlockOpaque(wx, wy, wz+1))
       rh::drawEastFace(vbo, texside, x, y, z);
    // south
    if(!world.isBlockOpaque(wx-1, wy, wz))
        rh::drawSouthFace(vbo, texside, x, y, z);
    // north
    if(!world.isBlockOpaque(wx+1, wy, wz))
        rh::drawNorthFace(vbo, texside, x, y, z);
    // bottom
    if(!world.isBlockOpaque(wx, wy-1, wz))
        rh::drawBottomFace(vbo, texside, x, y, z);
    // top
    if(!world.isBlockOpaque(wx, wy+1, wz))
        rh::drawTopFace(vbo, texside, x, y, z);
    
}

/////////////////////////
/////     Sand     //////
/////////////////////////

BlockSand::BlockSand(int id) : BlockStone(id)
{
    texside.setCoords(2, 1);
}

////////////////////////
//////    Dirt    //////
////////////////////////

BlockDirt::BlockDirt(int id) : BlockStone(id)
{
    texside.setCoords(1, 0);
}
BlockDirt::~BlockDirt()
{
}
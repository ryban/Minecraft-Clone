#ifndef RENDERHELPER_H
#define RENDERHELPER_H

#include "block.h"
#include "texcoords.h"
#include "vertex.h"

// namespace for render functions
namespace rh
{
    const float topCol = 1.0;
    const float sideCol = 232.0 / 255.0;
    const float bottomCol = 200.0 / 255.0;

    const float BLOCK_SIZE = 200;
    const float HALF_BLOCK_SIZE = BLOCK_SIZE / 2;

    const float WATER_VISIBILITY = 1.0;

    // for perfect cube
    void drawTopFace(VBOChunk &vbo, TexCoords &tex, int x, int y, int z);
    void drawBottomFace(VBOChunk &vbo, TexCoords &tex, int x, int y, int z);
    void drawNorthFace(VBOChunk &vbo, TexCoords &tex, int x, int y, int z); // +x
    void drawSouthFace(VBOChunk &vbo, TexCoords &tex, int x, int y, int z); // -x
    void drawEastFace(VBOChunk &vbo, TexCoords &tex, int x, int y, int z); // +z
    void drawWestFace(VBOChunk &vbo, TexCoords &tex, int x, int y, int z); // -z

    void drawTopFaceTransparent(VBOChunk &vbo, TexCoords &tex, int x, int y, int z);
    void drawBottomFaceTransparent(VBOChunk &vbo, TexCoords &tex, int x, int y, int z);
    void drawNorthFaceTransparent(VBOChunk &vbo, TexCoords &tex, int x, int y, int z); // +x
    void drawSouthFaceTransparent(VBOChunk &vbo, TexCoords &tex, int x, int y, int z); // -x
    void drawEastFaceTransparent(VBOChunk &vbo, TexCoords &tex, int x, int y, int z); // +z
    void drawWestFaceTransparent(VBOChunk &vbo, TexCoords &tex, int x, int y, int z); // -z

    /*
    // for not perfect cube
    void drawTopFaceWithBounds(VBOChunk &vbo, TexCoords &tex, int x, int y, int z, AABB &bounds);
    void drawBottomFaceWithBounds(VBOChunk &vbo, TexCoords &tex, int x, int y, int z, AABB &bounds);
    void drawNorthFaceWithBounds(VBOChunk &vbo, TexCoords &tex, int x, int y, int z, AABB &bounds); // +x
    void drawSouthFaceWithBounds(VBOChunk &vbo, TexCoords &tex, int x, int y, int z, AABB &bounds); // -x
    void drawEastFaceWithBounds(VBOChunk &vbo, TexCoords &tex, int x, int y, int z, AABB &bounds); // +z
    void drawWestFaceWithBounds(VBOChunk &vbo, TexCoords &tex, int x, int y, int z, AABB &bounds); // -z
    */
}

#endif
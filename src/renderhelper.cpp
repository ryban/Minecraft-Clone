#include "renderhelper.h"

namespace rh
{ 
    // for perfect cube
    void drawTopFace(VBOChunk &vbo, TexCoords &tex, int x, int y, int z)
    {
        float fx = x * BLOCK_SIZE;
        float fy = y * BLOCK_SIZE;
        float fz = z * BLOCK_SIZE;

        float fxx = fx + BLOCK_SIZE;
        float fyy = fy + BLOCK_SIZE;
        float fzz = fz + BLOCK_SIZE;

        Vertex vert;
        vert.x = fx; vert.y = fyy; vert.z = fzz;
        vbo.vertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fyy; vert.z = fzz;
        vbo.vertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fyy; vert.z = fz;
        vbo.vertBuffer->push_back(vert);
        vert.x = fx; vert.y = fyy; vert.z = fz;
        vbo.vertBuffer->push_back(vert);

        TexVert tvert;
        tvert.u = tex.left; tvert.v = tex.bottom;
        vbo.texBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.bottom;
        vbo.texBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.top;
        vbo.texBuffer->push_back(tvert);
        tvert.u = tex.left; tvert.v = tex.top;
        vbo.texBuffer->push_back(tvert);

        ColVert cvert;
        cvert.r = cvert.g = cvert.b = topCol;
        cvert.a = 1.0;
        vbo.colBuffer->push_back(cvert);
        vbo.colBuffer->push_back(cvert);
        vbo.colBuffer->push_back(cvert);
        vbo.colBuffer->push_back(cvert);
    }
    void drawBottomFace(VBOChunk &vbo, TexCoords &tex, int x, int y, int z)
    {
        float fx = x * BLOCK_SIZE;
        float fy = y * BLOCK_SIZE;
        float fz = z * BLOCK_SIZE;

        float fxx = fx + BLOCK_SIZE;
        float fyy = fy + BLOCK_SIZE;
        float fzz = fz + BLOCK_SIZE;

        Vertex vert;
        vert.x = fx; vert.y = fy; vert.z = fzz;
        vbo.vertBuffer->push_back(vert);
        vert.x = fx; vert.y = fy; vert.z = fz;
        vbo.vertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fy; vert.z = fz;
        vbo.vertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fy; vert.z = fzz;
        vbo.vertBuffer->push_back(vert);

        TexVert tvert;
        tvert.u = tex.left; tvert.v = tex.bottom;
        vbo.texBuffer->push_back(tvert);
        tvert.u = tex.left; tvert.v = tex.top;
        vbo.texBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.top;
        vbo.texBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.bottom;
        vbo.texBuffer->push_back(tvert);

        ColVert cvert;
        cvert.r = cvert.g = cvert.b = bottomCol;
        cvert.a = 1.0;
        vbo.colBuffer->push_back(cvert);
        vbo.colBuffer->push_back(cvert);
        vbo.colBuffer->push_back(cvert);
        vbo.colBuffer->push_back(cvert);
    }
    // +x
    void drawNorthFace(VBOChunk &vbo, TexCoords &tex, int x, int y, int z)
    {
        float fx = x * BLOCK_SIZE;
        float fy = y * BLOCK_SIZE;
        float fz = z * BLOCK_SIZE;

        float fxx = fx + BLOCK_SIZE;
        float fyy = fy + BLOCK_SIZE;
        float fzz = fz + BLOCK_SIZE;

        Vertex vert;
        vert.x = fxx; vert.y = fy; vert.z = fz;
        vbo.vertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fyy; vert.z = fz;
        vbo.vertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fyy; vert.z = fzz;
        vbo.vertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fy; vert.z = fzz;
        vbo.vertBuffer->push_back(vert);

        TexVert tvert;
        tvert.u = tex.left; tvert.v = tex.bottom;
        vbo.texBuffer->push_back(tvert);
        tvert.u = tex.left; tvert.v = tex.top;
        vbo.texBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.top;
        vbo.texBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.bottom;
        vbo.texBuffer->push_back(tvert);

        ColVert cvert;
        cvert.r = cvert.g = cvert.b = sideCol;
        cvert.a = 1.0;
        vbo.colBuffer->push_back(cvert);
        vbo.colBuffer->push_back(cvert);
        vbo.colBuffer->push_back(cvert);
        vbo.colBuffer->push_back(cvert);
    }
    // -x
    void drawSouthFace(VBOChunk &vbo, TexCoords &tex, int x, int y, int z)
    {
        float fx = x * BLOCK_SIZE;
        float fy = y * BLOCK_SIZE;
        float fz = z * BLOCK_SIZE;

        float fxx = fx + BLOCK_SIZE;
        float fyy = fy + BLOCK_SIZE;
        float fzz = fz + BLOCK_SIZE;

        Vertex vert;
        vert.x = fx; vert.y = fy; vert.z = fz;
        vbo.vertBuffer->push_back(vert);
        vert.x = fx; vert.y = fy; vert.z = fzz;
        vbo.vertBuffer->push_back(vert);
        vert.x = fx; vert.y = fyy; vert.z = fzz;
        vbo.vertBuffer->push_back(vert);
        vert.x = fx; vert.y = fyy; vert.z = fz;
        vbo.vertBuffer->push_back(vert);

        TexVert tvert;
        tvert.u = tex.left; tvert.v = tex.bottom;
        vbo.texBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.bottom;
        vbo.texBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.top;
        vbo.texBuffer->push_back(tvert);
        tvert.u = tex.left; tvert.v = tex.top;
        vbo.texBuffer->push_back(tvert);

        ColVert cvert;
        cvert.r = cvert.g = cvert.b = sideCol;
        cvert.a = 1.0;
        vbo.colBuffer->push_back(cvert);
        vbo.colBuffer->push_back(cvert);
        vbo.colBuffer->push_back(cvert);
        vbo.colBuffer->push_back(cvert);
    }
    // +z
    void drawEastFace(VBOChunk &vbo, TexCoords &tex, int x, int y, int z)
    {
        float fx = x * BLOCK_SIZE;
        float fy = y * BLOCK_SIZE;
        float fz = z * BLOCK_SIZE;

        float fxx = fx + BLOCK_SIZE;
        float fyy = fy + BLOCK_SIZE;
        float fzz = fz + BLOCK_SIZE;

        Vertex vert;
        vert.x = fx; vert.y = fyy; vert.z = fzz;
        vbo.vertBuffer->push_back(vert);
        vert.x = fx; vert.y = fy; vert.z = fzz;
        vbo.vertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fy; vert.z = fzz;
        vbo.vertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fyy; vert.z = fzz;
        vbo.vertBuffer->push_back(vert);

        TexVert tvert;
        tvert.u = tex.left; tvert.v = tex.top;
        vbo.texBuffer->push_back(tvert);
        tvert.u = tex.left; tvert.v = tex.bottom;
        vbo.texBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.bottom;
        vbo.texBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.top;
        vbo.texBuffer->push_back(tvert);

        ColVert cvert;
        cvert.r = cvert.g = cvert.b = sideCol;
        cvert.a = 1.0;
        vbo.colBuffer->push_back(cvert);
        vbo.colBuffer->push_back(cvert);
        vbo.colBuffer->push_back(cvert);
        vbo.colBuffer->push_back(cvert);
    }
    // -z
    void drawWestFace(VBOChunk &vbo, TexCoords &tex, int x, int y, int z)
    {
        float fx = x * BLOCK_SIZE;
        float fy = y * BLOCK_SIZE;
        float fz = z * BLOCK_SIZE;

        float fxx = fx + BLOCK_SIZE;
        float fyy = fy + BLOCK_SIZE;
        float fzz = fz + BLOCK_SIZE;

        Vertex vert;
        vert.x = fx; vert.y = fy; vert.z = fz;
        vbo.vertBuffer->push_back(vert);
        vert.x = fx; vert.y = fyy; vert.z = fz;
        vbo.vertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fyy; vert.z = fz;
        vbo.vertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fy; vert.z = fz;
        vbo.vertBuffer->push_back(vert);

        TexVert tvert;
        tvert.u = tex.left; tvert.v = tex.bottom;
        vbo.texBuffer->push_back(tvert);
        tvert.u = tex.left; tvert.v = tex.top;
        vbo.texBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.top;
        vbo.texBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.bottom;
        vbo.texBuffer->push_back(tvert);

        ColVert cvert;
        cvert.r = cvert.g = cvert.b = sideCol;
        cvert.a = 1.0;
        vbo.colBuffer->push_back(cvert);
        vbo.colBuffer->push_back(cvert);
        vbo.colBuffer->push_back(cvert);
        vbo.colBuffer->push_back(cvert);
    }

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

    // for perfect transparent cube
    void drawTopFaceTransparent(VBOChunk &vbo, TexCoords &tex, int x, int y, int z)
    {
        float fx = x * BLOCK_SIZE;
        float fy = y * BLOCK_SIZE;
        float fz = z * BLOCK_SIZE;

        float fxx = fx + BLOCK_SIZE;
        float fyy = fy + BLOCK_SIZE;
        float fzz = fz + BLOCK_SIZE;

        Vertex vert;
        vert.x = fx; vert.y = fyy; vert.z = fzz;
        vbo.transVertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fyy; vert.z = fzz;
        vbo.transVertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fyy; vert.z = fz;
        vbo.transVertBuffer->push_back(vert);
        vert.x = fx; vert.y = fyy; vert.z = fz;
        vbo.transVertBuffer->push_back(vert);

        TexVert tvert;
        tvert.u = tex.left; tvert.v = tex.bottom;
        vbo.transTexBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.bottom;
        vbo.transTexBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.top;
        vbo.transTexBuffer->push_back(tvert);
        tvert.u = tex.left; tvert.v = tex.top;
        vbo.transTexBuffer->push_back(tvert);

        ColVert cvert;
        cvert.r = cvert.g = cvert.b = topCol;
        cvert.a = 1.0;
        vbo.transColBuffer->push_back(cvert);
        vbo.transColBuffer->push_back(cvert);
        vbo.transColBuffer->push_back(cvert);
        vbo.transColBuffer->push_back(cvert);
    }
    void drawBottomFaceTransparent(VBOChunk &vbo, TexCoords &tex, int x, int y, int z)
    {
        float fx = x * BLOCK_SIZE;
        float fy = y * BLOCK_SIZE;
        float fz = z * BLOCK_SIZE;

        float fxx = fx + BLOCK_SIZE;
        float fyy = fy + BLOCK_SIZE;
        float fzz = fz + BLOCK_SIZE;

        Vertex vert;
        vert.x = fx; vert.y = fy; vert.z = fzz;
        vbo.transVertBuffer->push_back(vert);
        vert.x = fx; vert.y = fy; vert.z = fz;
        vbo.transVertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fy; vert.z = fz;
        vbo.transVertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fy; vert.z = fzz;
        vbo.transVertBuffer->push_back(vert);

        TexVert tvert;
        tvert.u = tex.left; tvert.v = tex.bottom;
        vbo.transTexBuffer->push_back(tvert);
        tvert.u = tex.left; tvert.v = tex.top;
        vbo.transTexBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.top;
        vbo.transTexBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.bottom;
        vbo.transTexBuffer->push_back(tvert);

        ColVert cvert;
        cvert.r = cvert.g = cvert.b = bottomCol;
        cvert.a = 1.0;
        vbo.transColBuffer->push_back(cvert);
        vbo.transColBuffer->push_back(cvert);
        vbo.transColBuffer->push_back(cvert);
        vbo.transColBuffer->push_back(cvert);
    }
    // +x
    void drawNorthFaceTransparent(VBOChunk &vbo, TexCoords &tex, int x, int y, int z)
    {
        float fx = x * BLOCK_SIZE;
        float fy = y * BLOCK_SIZE;
        float fz = z * BLOCK_SIZE;

        float fxx = fx + BLOCK_SIZE;
        float fyy = fy + BLOCK_SIZE;
        float fzz = fz + BLOCK_SIZE;

        Vertex vert;
        vert.x = fxx; vert.y = fy; vert.z = fz;
        vbo.transVertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fyy; vert.z = fz;
        vbo.transVertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fyy; vert.z = fzz;
        vbo.transVertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fy; vert.z = fzz;
        vbo.transVertBuffer->push_back(vert);

        TexVert tvert;
        tvert.u = tex.left; tvert.v = tex.bottom;
        vbo.transTexBuffer->push_back(tvert);
        tvert.u = tex.left; tvert.v = tex.top;
        vbo.transTexBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.top;
        vbo.transTexBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.bottom;
        vbo.transTexBuffer->push_back(tvert);

        ColVert cvert;
        cvert.r = cvert.g = cvert.b = sideCol;
        cvert.a = 1.0;
        vbo.transColBuffer->push_back(cvert);
        vbo.transColBuffer->push_back(cvert);
        vbo.transColBuffer->push_back(cvert);
        vbo.transColBuffer->push_back(cvert);
    }
    // -x
    void drawSouthFaceTransparent(VBOChunk &vbo, TexCoords &tex, int x, int y, int z)
    {
        float fx = x * BLOCK_SIZE;
        float fy = y * BLOCK_SIZE;
        float fz = z * BLOCK_SIZE;

        float fxx = fx + BLOCK_SIZE;
        float fyy = fy + BLOCK_SIZE;
        float fzz = fz + BLOCK_SIZE;

        Vertex vert;
        vert.x = fx; vert.y = fy; vert.z = fz;
        vbo.transVertBuffer->push_back(vert);
        vert.x = fx; vert.y = fy; vert.z = fzz;
        vbo.transVertBuffer->push_back(vert);
        vert.x = fx; vert.y = fyy; vert.z = fzz;
        vbo.transVertBuffer->push_back(vert);
        vert.x = fx; vert.y = fyy; vert.z = fz;
        vbo.transVertBuffer->push_back(vert);

        TexVert tvert;
        tvert.u = tex.left; tvert.v = tex.bottom;
        vbo.transTexBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.bottom;
        vbo.transTexBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.top;
        vbo.transTexBuffer->push_back(tvert);
        tvert.u = tex.left; tvert.v = tex.top;
        vbo.transTexBuffer->push_back(tvert);

        ColVert cvert;
        cvert.r = cvert.g = cvert.b = sideCol;
        cvert.a = 1.0;
        vbo.transColBuffer->push_back(cvert);
        vbo.transColBuffer->push_back(cvert);
        vbo.transColBuffer->push_back(cvert);
        vbo.transColBuffer->push_back(cvert);
    }
    // +z
    void drawEastFaceTransparent(VBOChunk &vbo, TexCoords &tex, int x, int y, int z)
    {
        float fx = x * BLOCK_SIZE;
        float fy = y * BLOCK_SIZE;
        float fz = z * BLOCK_SIZE;

        float fxx = fx + BLOCK_SIZE;
        float fyy = fy + BLOCK_SIZE;
        float fzz = fz + BLOCK_SIZE;

        Vertex vert;
        vert.x = fx; vert.y = fyy; vert.z = fzz;
        vbo.transVertBuffer->push_back(vert);
        vert.x = fx; vert.y = fy; vert.z = fzz;
        vbo.transVertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fy; vert.z = fzz;
        vbo.transVertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fyy; vert.z = fzz;
        vbo.transVertBuffer->push_back(vert);

        TexVert tvert;
        tvert.u = tex.left; tvert.v = tex.top;
        vbo.transTexBuffer->push_back(tvert);
        tvert.u = tex.left; tvert.v = tex.bottom;
        vbo.transTexBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.bottom;
        vbo.transTexBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.top;
        vbo.transTexBuffer->push_back(tvert);

        ColVert cvert;
        cvert.r = cvert.g = cvert.b = sideCol;
        cvert.a = 1.0;
        vbo.transColBuffer->push_back(cvert);
        vbo.transColBuffer->push_back(cvert);
        vbo.transColBuffer->push_back(cvert);
        vbo.transColBuffer->push_back(cvert);
    }
    // -z
    void drawWestFaceTransparent(VBOChunk &vbo, TexCoords &tex, int x, int y, int z)
    {
        float fx = x * BLOCK_SIZE;
        float fy = y * BLOCK_SIZE;
        float fz = z * BLOCK_SIZE;

        float fxx = fx + BLOCK_SIZE;
        float fyy = fy + BLOCK_SIZE;
        float fzz = fz + BLOCK_SIZE;

        Vertex vert;
        vert.x = fx; vert.y = fy; vert.z = fz;
        vbo.transVertBuffer->push_back(vert);
        vert.x = fx; vert.y = fyy; vert.z = fz;
        vbo.transVertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fyy; vert.z = fz;
        vbo.transVertBuffer->push_back(vert);
        vert.x = fxx; vert.y = fy; vert.z = fz;
        vbo.transVertBuffer->push_back(vert);

        TexVert tvert;
        tvert.u = tex.left; tvert.v = tex.bottom;
        vbo.transTexBuffer->push_back(tvert);
        tvert.u = tex.left; tvert.v = tex.top;
        vbo.transTexBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.top;
        vbo.transTexBuffer->push_back(tvert);
        tvert.u = tex.right; tvert.v = tex.bottom;
        vbo.transTexBuffer->push_back(tvert);

        ColVert cvert;
        cvert.r = cvert.g = cvert.b = sideCol;
        cvert.a = 1.0;
        vbo.transColBuffer->push_back(cvert);
        vbo.transColBuffer->push_back(cvert);
        vbo.transColBuffer->push_back(cvert);
        vbo.transColBuffer->push_back(cvert);
    }
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
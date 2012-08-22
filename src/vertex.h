#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
class VBOChunk;
#include "world.h"
#include "camera.h"

class Vertex
{
    public:
        float x;
        float y;
        float z;
};

class TexVert
{
    public:
        float u;
        float v;
};

class ColVert
{
    public:
        float r;
        float g;
        float b;
        float a;
};

class VBOChunk
{
    private:
        int vertexCount;
        int transVertexCount;

        unsigned int m_VBOverticies;
        unsigned int m_VBOtex;
        unsigned int m_VBOcol;

        unsigned int m_transVBOverticies;
        unsigned int m_transVBOtex;
        unsigned int m_transVBOcol;

        void deleteBuffers();

    public:
        VBOChunk(int xx, int yy, int zz);
        ~VBOChunk();
        bool buildVBO(World &world, std::vector<Vertex> *vb, std::vector<TexVert> *tb, std::vector<ColVert> *cb,
                      std::vector<Vertex> *tvb, std::vector<TexVert> *ttb, std::vector<ColVert> *tcb);
        bool reBuildVBO(World &world, std::vector<Vertex> *vb, std::vector<TexVert> *tb, std::vector<ColVert> *cb,
                        std::vector<Vertex> *tvb, std::vector<TexVert> *ttb, std::vector<ColVert> *tcb);
        void render(Camera &cam);
        void renderTransparent(Camera &cam);
        bool hasTransparentBlocks() { return transVertexCount > 0; }
        int posx;
        int posy;
        int posz;
        std::vector<Vertex> *vertBuffer;
        std::vector<TexVert> *texBuffer;
        std::vector<ColVert> *colBuffer;

        std::vector<Vertex> *transVertBuffer;
        std::vector<TexVert> *transTexBuffer;
        std::vector<ColVert> *transColBuffer;
};

#endif
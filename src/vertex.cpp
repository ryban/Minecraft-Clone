#include <GL/glew.h>
#include <GL/glut.h>

#include <SFML/OpenGL.hpp>

#include "vertex.h"

#include <iostream>

VBOChunk::VBOChunk(int xx, int yy, int zz)
{
    posx = xx;
    posy = yy;
    posz = zz; 
    vertexCount = 0;
    m_VBOverticies = 0;
    m_VBOtex = 0;
    m_VBOcol = 0;
    m_transVBOverticies = 0;
    m_transVBOtex = 0;
    m_transVBOcol = 0;
}
VBOChunk::~VBOChunk()
{
    deleteBuffers();
}
// calls each blocks renderToVBO function to create the VBO
bool VBOChunk::buildVBO(World &world, std::vector<Vertex> *vb, std::vector<TexVert> *tb, std::vector<ColVert> *cb,
                        std::vector<Vertex> *tvb, std::vector<TexVert> *ttb, std::vector<ColVert> *tcb)
{
    Block *block;

    vertBuffer = vb;
    texBuffer = tb;
    colBuffer = cb;

    transVertBuffer = tvb;
    transTexBuffer = ttb;
    transColBuffer = tcb;

    for(int xx = 0; xx < 16; xx++)
    {
        for(int yy = 0; yy < 16; yy++)
        {
            for(int zz = 0; zz < 16; zz++)
            {
                block = world.getBlock(xx + posx, yy + posy, zz + posz);
                if(block)
                    block->renderToVBO(world, *this, xx, yy, zz);
            }
        }
    }
    vertexCount = vertBuffer->size();
    transVertexCount = transVertBuffer->size();
    
    bool r = false;

    if(vertexCount > 0)
    {
        r = true;
        std::vector<Vertex>::iterator iter = vertBuffer->begin();
        glGenBuffersARB(1, &m_VBOverticies);                        // get a valid name
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_VBOverticies);       // bind the buffer
        // load the data
        glBufferDataARB(GL_ARRAY_BUFFER_ARB, vertBuffer->size()*3*sizeof(float), &(*iter), GL_STATIC_DRAW_ARB);

        std::vector<TexVert>::iterator titer = texBuffer->begin();
        glGenBuffersARB(1, &m_VBOtex);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_VBOtex);
        glBufferDataARB(GL_ARRAY_BUFFER_ARB, texBuffer->size()*2*sizeof(float), &(*titer), GL_STATIC_DRAW_ARB);

        std::vector<ColVert>::iterator citer = colBuffer->begin();
        glGenBuffersARB(1, &m_VBOcol);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_VBOcol);
        glBufferDataARB(GL_ARRAY_BUFFER_ARB, colBuffer->size()*4*sizeof(float), &(*citer), GL_STATIC_DRAW_ARB);
    }
    if(transVertexCount > 0)
    {
        r = true;
        std::vector<Vertex>::iterator tit = transVertBuffer->begin();
        glGenBuffersARB(1, &m_transVBOverticies);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_transVBOverticies);
        glBufferDataARB(GL_ARRAY_BUFFER_ARB, transVertBuffer->size()*3*sizeof(float), &(*tit), GL_STATIC_DRAW_ARB);

        std::vector<TexVert>::iterator ttit = transTexBuffer->begin();
        glGenBuffersARB(1, &m_transVBOtex);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_transVBOtex);
        glBufferDataARB(GL_ARRAY_BUFFER_ARB, transTexBuffer->size()*2*sizeof(float), &(*ttit), GL_STATIC_DRAW_ARB);

        std::vector<ColVert>::iterator tcit = transColBuffer->begin();
        glGenBuffersARB(1, &m_transVBOcol);
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_transVBOcol);
        glBufferDataARB(GL_ARRAY_BUFFER_ARB, transColBuffer->size()*4*sizeof(float), &(*tcit), GL_STATIC_DRAW_ARB);
    }

    vertBuffer->clear();
    texBuffer->clear();
    colBuffer->clear();

    transVertBuffer->clear();
    transTexBuffer->clear();
    transColBuffer->clear();

    vertBuffer = 0;
    texBuffer = 0;
    colBuffer = 0;

    transVertBuffer = 0;
    transTexBuffer = 0;
    transColBuffer = 0;

    return r;
}
// deletes the current VBOs for the chunk, and rebuilds them
bool VBOChunk::reBuildVBO(World &world, std::vector<Vertex> *vb, std::vector<TexVert> *tb, std::vector<ColVert> *cb,
                              std::vector<Vertex> *tvb, std::vector<TexVert> *ttb, std::vector<ColVert> *tcb)
{
    deleteBuffers();
    return buildVBO(world, vb, tb, cb, tvb, ttb, tcb);
}
// deltes the VBOs
void VBOChunk::deleteBuffers()
{
    if(m_VBOverticies)
        glDeleteBuffersARB(1, &m_VBOverticies);
    if(m_VBOtex)
        glDeleteBuffersARB(1, &m_VBOtex);
    if(m_VBOcol)
        glDeleteBuffersARB(1, &m_VBOcol);
    if(m_transVBOverticies)
        glDeleteBuffersARB(1, &m_transVBOverticies);
    if(m_transVBOtex)
        glDeleteBuffersARB(1, &m_transVBOtex);
    if(m_transVBOcol)
        glDeleteBuffersARB(1, &m_transVBOcol);

    m_VBOverticies = 0;
    m_VBOtex = 0;
    m_VBOcol = 0;
    m_transVBOverticies = 0;
    m_transVBOtex = 0;
    m_transVBOcol = 0;
}
// draws the non transparent VBO on screen
void VBOChunk::render(Camera &cam)
{
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_VBOverticies);
    glVertexPointer(3, GL_FLOAT, 0, (char *) NULL);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_VBOtex);
    glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_VBOcol);
    glColorPointer(4, GL_FLOAT, 0, (char *) NULL);

    sf::Vector3<float> cpos = cam.getPosition();
    cpos.x -= posx*200; // 200 is the size of the blocks
    cpos.z -= posz*200;
    cpos.y -= posy*200;
    glPushMatrix();
        glTranslatef(-cpos.x,-cpos.y,-cpos.z);
        glDrawArrays(GL_QUADS, 0, vertexCount);
    glPopMatrix();
}
// draws the transparent VBO on screen
void VBOChunk::renderTransparent(Camera &cam)
{
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_transVBOverticies);
    glVertexPointer(3, GL_FLOAT, 0, (char *) NULL);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_transVBOtex);
    glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_transVBOcol);
    glColorPointer(4, GL_FLOAT, 0, (char *) NULL);

    sf::Vector3<float> cpos = cam.getPosition();
    cpos.x -= posx*200; // 200 is the size of the blocks
    cpos.z -= posz*200;
    cpos.y -= posy*200;
    glPushMatrix();
        glTranslatef(-cpos.x,-cpos.y,-cpos.z);
        glDrawArrays(GL_QUADS, 0, transVertexCount);
    glPopMatrix();
}
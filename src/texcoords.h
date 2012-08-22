#ifndef TEXCOORDS_H
#define TEXCOORDS_H

// class for turning simple texture coordinates into 
// OpenGL texture UVs.

class TexCoords
{
    public:
        int x;
        int y;

        float top;
        float left;
        float bottom;
        float right;

        void setCoords(int _x, int _y)
        {
            setCoords(_x, _y, 32, 512);
        }
        TexCoords()
        {
            setCoords(0, 0, 32, 512); 
        }
        TexCoords(int _x, int _y)
        {
            setCoords(_x, _y, 32, 512);
        }
        TexCoords(int _x, int _y, int resoluton, int image_size)
        {
            setCoords(_x, _y, resoluton, image_size);
        }
        void setCoords(int _x, int _y, int resoluton, int image_size)
        {
            x = _x * resoluton;
            y = _y * resoluton;

            left = x / (float)image_size;
            right = left + (resoluton / (float)image_size);
            top = y / (float)image_size;
            bottom = top + (resoluton / (float)image_size);
        }
};


#endif
#ifndef SERIALIZER_H
#define SERIALIZER_H
#include "buffer.h"

typedef struct {
   char      idlength        = 0;
   char      colourmaptype   = 0;
   char      datatypecode    = 2;
   short int colourmaporigin = 0;
   short int colourmaplength = 0;
   char      colourmapdepth  = 0;
   short int x_origin        = 0;
   short int y_origin        = 0;
   short     width           = 0;
   short     height          = 0;
   char      bitsperpixel    = 32;
   char      imagedescriptor = 0;
} TGAHeader;

namespace serializer
{
    void bufferToTGA(buffer buf);
}

#endif // SERIALIZER_H

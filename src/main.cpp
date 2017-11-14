#include <iostream>
#include "scanline.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc > 2)
    {
        scanline renderer((int)argv[0],(int)argv[1]);
        renderer.render();
    }
    else
    {
        scanline renderer(1080,1080);
        renderer.render();
    }
    return 0;
}

#ifndef BUFFER_H
#define BUFFER_H


struct buffer
{
    int width, height;

    unsigned int* color;
    float* depth;

    void clear();
    void clearColor();
    void clearDepth();

    void initBuffer(int width, int height);

    void write(int x, int y, unsigned int color, float depth);
};

#endif // BUFFER_H

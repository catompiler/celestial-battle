#ifndef _PIXELATTRIBS_H_
#define _PIXELATTRIBS_H_

struct PixelAttribs{
    bool doubleBuffer;
    int redSize;
    int greenSize;
    int blueSize;
    int alphaSize;
    int depthSize;
    int stencilSize;
    int sampleBuffers;
    int samples;
};

#endif  //_PIXELATTRIBS_H_

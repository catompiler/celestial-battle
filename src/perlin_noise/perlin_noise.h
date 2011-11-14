#ifndef _PERLIN_NOISE_H_
#define _PERLIN_NOISE_H_

namespace noise{

class perlin
{
public:
    static float interpolation(float a, float b, float t);
};

class perlin1d :public perlin
{
public:
    perlin1d(float seed_x_, float amplitude_, float frequency_, float persistence_, int octaves_);
    
    float operator()(float x);

    static float simple_noise(int x);
    static float smooth_noise(int x);
    static float interpolated_noise(float x);
    static float noise(float x, float seed, float amplitude, float frequency, float persistence, int octaves);

private:
    float seed_x;
    float amplitude;
    float frequency;
    float persistence;
    int octaves;
};

class perlin2d :public perlin
{
public:
    perlin2d(float seed_x_, float seed_y_, float amplitude_, float frequency_, float persistence_, int octaves_);
    
    float operator()(float x, float y);

    static float simple_noise(int x, int y);
    static float smooth_noise(int x, int y);
    static float interpolated_noise(float x, float y);
    static float noise(float x, float y, float seed_x, float seed_y, float amplitude, float frequency, float persistence, int octaves);

private:
    float seed_x;
    float seed_y;
    float amplitude;
    float frequency;
    float persistence;
    int octaves;
};

class perlin3d :public perlin
{
public:
    perlin3d(float seed_x_, float seed_y_, float seed_z_, float amplitude_, float frequency_, float persistence_, int octaves_);
    
    float operator()(float x, float y, float z);

    static float simple_noise(int x, int y, int z);
    static float smooth_noise(int x, int y, int z);
    static float interpolated_noise(float x, float y, float z);
    static float noise(float x, float y, float z, float seed_x, float seed_y, float seed_z, float amplitude, float frequency, float persistence, int octaves);

private:
    float seed_x;
    float seed_y;
    float seed_z;
    float amplitude;
    float frequency;
    float persistence;
    int octaves;
};

}

#endif  //_PERLIN_NOISE_H_

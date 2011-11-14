#include "perlin_noise.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


//http://freespace.virgin.net/hugo.elias/models/m_perlin.htm

namespace noise{

float perlin::interpolation(float a, float b, float t)
{
    float t1 = 3.0f * pow(1.0f - t, 2.0f) - 2.0f * pow(1.0f - t, 3.0f);
    float t2 = 3.0f * pow(t, 2.0f) - 2.0f * pow(t, 3.0f);
    return a * t1 + b * t2;
}

//1D

perlin1d::perlin1d(float seed_x_, float amplitude_, float frequency_, float persistence_, int octaves_)
{
    seed_x = seed_x_;
    amplitude = amplitude_;
    frequency = frequency_;
    persistence = persistence_;
    octaves = octaves_;
}

float perlin1d::operator()(float x)
{
    return noise(x, seed_x, amplitude, frequency, persistence, octaves);
}

float perlin1d::simple_noise(int x)
{
    x = (x<<13) ^ x;
    return ( 1.0 - ( (x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0); 
}

float perlin1d::smooth_noise(int x)
{
    return 0.5 * simple_noise(x) + 0.25 * (simple_noise(x - 1) + simple_noise(x + 1));
}

float perlin1d::interpolated_noise(float x)
{
    int int_x = static_cast<int>(floor(x));
    float fract_x = x - int_x;
    
    float v1 = smooth_noise(int_x);
    float v2 = smooth_noise(int_x + 1);
    
    return interpolation(v1, v2, fract_x);
}

float perlin1d::noise(float x, float seed, float amplitude, float frequency, float persistence, int octaves)
{
    float res = 0.0f;
    
    x += seed;
    
    for(int i = 0; i < octaves; ++ i){
        res += interpolated_noise(x * frequency) * amplitude;
        amplitude *= persistence;
        frequency *= 2.0f;
    }
    
    return res;
}

//2D

perlin2d::perlin2d(float seed_x_, float seed_y_, float amplitude_, float frequency_, float persistence_, int octaves_)
{
    seed_x = seed_x_;
    seed_y = seed_y_;
    amplitude = amplitude_;
    frequency = frequency_;
    persistence = persistence_;
    octaves = octaves_;
}

float perlin2d::operator()(float x, float y)
{
    return noise(x, y, seed_x, seed_y, amplitude, frequency, persistence, octaves);
}

float perlin2d::simple_noise(int x, int y)
{
    x = x + y * 65213;//97171 //57
    x = (x<<13) ^ x;
    return ( 1.0 - ( (x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0); 
}

float perlin2d::smooth_noise(int x, int y)
{
    return 0.0625f * (simple_noise(x - 1, y - 1) + simple_noise(x + 1, y - 1) +
                      simple_noise(x - 1, y + 1) + simple_noise(x + 1, y + 1)) +
           0.1250f * (simple_noise(x - 1, y) + simple_noise(x, y - 1) +
                      simple_noise(x + 1, y) + simple_noise(x, y + 1)) +
           0.2500f * (simple_noise(x, y));
}

float perlin2d::interpolated_noise(float x, float y)
{
    int int_x = static_cast<int>(floor(x));
    float fract_x = x - int_x;
    int int_y = static_cast<int>(floor(y));
    float fract_y = y - int_y;
    
    float v1 = smooth_noise(int_x    , int_y    );
    float v2 = smooth_noise(int_x + 1, int_y    );
    float v3 = smooth_noise(int_x    , int_y + 1);
    float v4 = smooth_noise(int_x + 1, int_y + 1);
    
    float v12 = interpolation(v1, v2, fract_x);
    float v34 = interpolation(v3, v4, fract_x);
    
    return interpolation(v12, v34, fract_y);
}

float perlin2d::noise(float x, float y, float seed_x, float seed_y, float amplitude, float frequency, float persistence, int octaves)
{
    float res = 0.0f;
    
    x += seed_x;
    y += seed_y;
    
    for(int i = 0; i < octaves; ++ i){
        res += interpolated_noise(x * frequency, y * frequency) * amplitude;
        amplitude *= persistence;
        frequency *= 2.0f;
    }
    
    return res;
}

//3D

perlin3d::perlin3d(float seed_x_, float seed_y_, float seed_z_, float amplitude_, float frequency_, float persistence_, int octaves_)
{
    seed_x = seed_x_;
    seed_y = seed_y_;
    seed_z = seed_z_;
    amplitude = amplitude_;
    frequency = frequency_;
    persistence = persistence_;
    octaves = octaves_;
}

float perlin3d::operator()(float x, float y, float z)
{
    return noise(x, y, z, seed_x, seed_y, seed_z, amplitude, frequency, persistence, octaves);
}

float perlin3d::simple_noise(int x, int y, int z)
{
    x = x + ((y + z * 2053) * 2053);//57 //65213 //97171
    x = (x<<13) ^ x;
    return ( 1.0 - ( (x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0); 
}

float perlin3d::smooth_noise(int x, int y, int z)
{
    return 0.03125f * (simple_noise(x - 1, y - 1, z - 1) +
                       simple_noise(x + 1, y - 1, z - 1) +
                       simple_noise(x - 1, y + 1, z - 1) +
                       simple_noise(x + 1, y + 1, z - 1) +
                       simple_noise(x - 1, y - 1, z + 1) +
                       simple_noise(x + 1, y - 1, z + 1) +
                       simple_noise(x - 1, y + 1, z + 1) +
                       simple_noise(x + 1, y + 1, z + 1)) +
           0.06250f * (simple_noise(x - 1, y    , z    ) +
                       simple_noise(x + 1, y    , z    ) +
                       simple_noise(x    , y - 1, z    ) +
                       simple_noise(x    , y + 1, z    ) +
                       simple_noise(x    , y    , z - 1) +
                       simple_noise(x    , y    , z + 1)) +
           0.37500f * (simple_noise(x, y, z));
}

float perlin3d::interpolated_noise(float x, float y, float z)
{
    int int_x = static_cast<int>(floor(x));
    float fract_x = x - int_x;
    int int_y = static_cast<int>(floor(y));
    float fract_y = y - int_y;
    int int_z = static_cast<int>(floor(z));
    float fract_z = z - int_z;
    
    float v1 = smooth_noise(int_x    , int_y    , int_z    );
    float v2 = smooth_noise(int_x + 1, int_y    , int_z    );
    float v3 = smooth_noise(int_x    , int_y + 1, int_z    );
    float v4 = smooth_noise(int_x + 1, int_y + 1, int_z    );
    float v5 = smooth_noise(int_x    , int_y    , int_z + 1);
    float v6 = smooth_noise(int_x + 1, int_y    , int_z + 1);
    float v7 = smooth_noise(int_x    , int_y + 1, int_z + 1);
    float v8 = smooth_noise(int_x + 1, int_y + 1, int_z + 1);
    
    float v12 = interpolation(v1, v2, fract_x);
    float v34 = interpolation(v3, v4, fract_x);
    float v56 = interpolation(v5, v6, fract_x);
    float v78 = interpolation(v7, v8, fract_x);
    
    float v1234 = interpolation(v12, v34, fract_y);
    float v5678 = interpolation(v56, v78, fract_y);
    
    return interpolation(v1234, v5678, fract_z);
}

float perlin3d::noise(float x, float y, float z, float seed_x, float seed_y, float seed_z, float amplitude, float frequency, float persistence, int octaves)
{
    float res = 0.0f;
    
    x += seed_x;
    y += seed_y;
    z += seed_z;
    
    for(int i = 0; i < octaves; ++ i){
        res += interpolated_noise(x * frequency, y * frequency, z * frequency) * amplitude;
        amplitude *= persistence;
        frequency *= 2.0f;
    }
    
    return res;
}

}


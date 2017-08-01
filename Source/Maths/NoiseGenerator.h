#ifndef NOISEGENERATOR_H_INCLUDED
#define NOISEGENERATOR_H_INCLUDED

struct NoiseParameters
{
    int octaves;
    int amplitude;
    int smoothness;
    int heightOffset;

    double roughness;
};

class NoiseGenerator
{
    public:
        NoiseGenerator(int seed);

        double getHeight(int x, int z, int chunkX, int chunkZ) const;

        void setParameters(const NoiseParameters& params);

    private:
        double getNoise(int  n) const;
        double getNoise(double  x, double  z) const;

        double lerp(double a, double b, double z) const;

        double noise(double  x, double  z) const;

        NoiseParameters m_noiseParameters;

        int m_seed;
};

#endif // NOISEGENERATOR_H_INCLUDED

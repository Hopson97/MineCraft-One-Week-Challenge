#include "GeneralMaths.h"

float bilinearInterpolation(float bottomLeft, float topLeft, float bottomRight, float topRight,
                            float xMin, float xMax,
                            float zMin, float zMax,
                            float x, float z)
{
    float   width               = xMax - xMin,
            height              = zMax - zMin,

            xDistanceToMaxValue = xMax - x,
            zDistanceToMaxValue = zMax - z,

            xDistanceToMinValue = x - xMin,
            zDistanceToMinValue = z - zMin;

    return 1.0f / (width * height) *
    (
        bottomLeft      *   xDistanceToMaxValue * zDistanceToMaxValue +
        bottomRight     *   xDistanceToMinValue * zDistanceToMaxValue +
        topLeft         *   xDistanceToMaxValue * zDistanceToMinValue +
        topRight        *   xDistanceToMinValue * zDistanceToMinValue
    );
}

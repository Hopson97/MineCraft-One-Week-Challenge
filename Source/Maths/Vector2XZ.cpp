#include "Vector2XZ.h"

bool operator==(const VectorXZ& left, const VectorXZ& right)
{
    return  (left.x == right.x) &&
            (left.z == right.z);
}

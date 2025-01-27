#include <utility.hpp>
#include <cmath>

namespace VectorFunction {
    FReal64 Length(const FRealVector2D &v){
        return sqrt(v.x * v.x + v.y * v.y);
    }
    // The direction range is [-Pi, Pi]
    FReal64 Direction(const FRealVector2D &v){
        return atan2(v.x, v.y);
    }
    FRealVector2D ToPolarAxis(const FRealVector2D &v){
        return FRealVector2D(Direction(v), Length(v));
    }
}
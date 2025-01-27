#ifndef ENGINE_FRAME_INCLUDED
#define ENGINE_FRAME_INCLUDED
#include <env.hpp>

namespace Engine {

class Frame {
public:
    static FInt framesPerSecond;
    static FReal64 secondsPerFrame;
};

}
#endif
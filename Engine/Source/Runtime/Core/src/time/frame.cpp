#include <time/frame.hpp>
namespace Engine {

FInt Frame::framesPerSecond = 120;
FReal64 Frame::secondsPerFrame = 1. / Frame::framesPerSecond;

}
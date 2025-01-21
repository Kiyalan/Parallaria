#ifndef ENGINE_TIME_INCLUDED
#define ENGINE_TIME_INCLUDED
#include <env.hpp>
#include <GLFW/glfw3.h>

namespace Engine {

class Time {
public:
    static FReal64 GetCurrentTime(){
        return glfwGetTime();
    }
};

}
#endif
#ifndef ENGINE_INPUT_INCLUDED
#define ENGINE_INPUT_INCLUDED

#include <functional>
#include <utility>
#include <unordered_map>
#include <vector>
#include <GLFW/glfw3.h>
#include <env.hpp>
#include <window/window.hpp>

namespace Engine {

enum class EKey {
    A = GLFW_KEY_A, B = GLFW_KEY_B, C = GLFW_KEY_C, D = GLFW_KEY_D, E = GLFW_KEY_E, 
    F = GLFW_KEY_F, G = GLFW_KEY_G, H = GLFW_KEY_H, I = GLFW_KEY_I, J = GLFW_KEY_J, 
    K = GLFW_KEY_K, L = GLFW_KEY_L, M = GLFW_KEY_M, N = GLFW_KEY_N, O = GLFW_KEY_O, 
    P = GLFW_KEY_P, Q = GLFW_KEY_Q, R = GLFW_KEY_R, S = GLFW_KEY_S, T = GLFW_KEY_T, 
    U = GLFW_KEY_U, V = GLFW_KEY_V, W = GLFW_KEY_W, X = GLFW_KEY_X, Y = GLFW_KEY_Y, 
    Z = GLFW_KEY_Z, Space = GLFW_KEY_SPACE, Enter = GLFW_KEY_ENTER, Escape = GLFW_KEY_ESCAPE,
    LeftShift = GLFW_KEY_LEFT_SHIFT, RightShift = GLFW_KEY_RIGHT_SHIFT,
    LeftControl = GLFW_KEY_LEFT_CONTROL, RightControl = GLFW_KEY_RIGHT_CONTROL, 
    LeftAlt = GLFW_KEY_LEFT_ALT, RightAlt = GLFW_KEY_RIGHT_ALT,
    LeftMouseButton = GLFW_MOUSE_BUTTON_1, RightMouseButton = GLFW_MOUSE_BUTTON_2

};

enum class EAction {
    Press = GLFW_PRESS, Release = GLFW_RELEASE, Repeat = GLFW_REPEAT
};

enum class EModifier {
    Shift = GLFW_MOD_SHIFT, Control = GLFW_MOD_CONTROL, Alt = GLFW_MOD_ALT
};

using KeyCallback = std::function<void(EKey, EAction, EModifier)>;

class Input {

public:
    
    Input() = delete;

    static void Init(Window& window);
    static bool IsKeyPressed(EKey key);
    static bool IsMouseButtonPressed(EKey button);

    static bool IsShiftPressed();
    static bool IsCtrlPressed();
    static bool IsAltPressed();

    static FReal64 GetKeyPressTime(EKey key);

    static std::pair<FReal64, FReal64> GetCursorPosition();

    static void SetKeyCallback(KeyCallback callback);
     
private:

    static bool _bInitialized;
    static GLFWwindow* _window;
    static std::unordered_map<EKey, FReal64> KeyPressTimesMap;
    static std::vector<KeyCallback> KeyCallbacksVector;
    friend void InputBindWindow(Window& window);
    friend void CallTriger(GLFWwindow* window, int key, int scancode, int action, int mods);
    friend void KeyPressTimeCounter(EKey key, EAction action, EModifier mods);
};

}

#endif 
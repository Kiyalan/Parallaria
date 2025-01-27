#include <input/input.hpp>

namespace Engine{

GLFWwindow* Input::_window = nullptr;
bool Input::_bInitialized = false;
std::unordered_map<EKey, FReal64> Input::KeyPressTimesMap = {};
std::vector<KeyCallback> Input::KeyCallbacksVector = {};

void InputBindWindow(Window& TheWindow) {
    Input::_window = TheWindow._windowHandle;
}

void CallTriger(GLFWwindow* window, int key, int scancode, int action, int mods) {
    for (auto& callback : Input::KeyCallbacksVector) {
        callback(static_cast<EKey>(key), static_cast<EAction>(action), static_cast<EModifier>(mods));
    }
}

void KeyPressTimeCounter(EKey key, EAction action, EModifier mods) {
    if (action == EAction::Press) {
        Input::KeyPressTimesMap[key] = glfwGetTime();
    }
    else if (action == EAction::Release) {
        Input::KeyPressTimesMap[key] = 0;
    }
}
void Input::Init(Window& window){
        if (!_bInitialized) {
            InputBindWindow(window);
            glfwSetKeyCallback(_window, CallTriger);
            SetKeyCallback(KeyPressTimeCounter);
            _bInitialized = true;
        }
}
bool Input::IsKeyPressed(EKey key) {
    return glfwGetKey(_window, static_cast<int>(key)) == GLFW_PRESS;
}

bool Input::IsShiftPressed() {
    return glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || 
           glfwGetKey(_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
}

bool Input::IsCtrlPressed() {
    return glfwGetKey(_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || 
           glfwGetKey(_window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS;
}

bool Input::IsAltPressed() {
    return glfwGetKey(_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS || 
           glfwGetKey(_window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS;
}

bool Input::IsMouseButtonPressed(EKey button) {
    return glfwGetMouseButton(_window, static_cast<int>(button)) == GLFW_PRESS;
}

std::pair<FReal64, FReal64> Input::GetCursorPosition() {
    FReal64 x, y;
    glfwGetCursorPos(_window, &x, &y);
    return std::make_pair(x, y);
}

FReal64 Input::GetKeyPressTime(EKey key) {
    if (KeyPressTimesMap[key] == 0) {
        return 0;

  }
    else {
        return glfwGetTime() - KeyPressTimesMap[key];

    }
}

void Input::SetKeyCallback(KeyCallback callback) {
    KeyCallbacksVector.push_back(callback);
}

}        
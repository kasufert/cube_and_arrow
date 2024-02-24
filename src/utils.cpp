#pragma once
#include "utils.hpp"


std::string ReadFile(const char* path)
{
    std::ifstream f(path);
    std::stringstream s;
    s << f.rdbuf();
    return s.str();
}

bool HandleOpenGLError(std::source_location caller, std::string function)
{
    bool noErr = true;
    while (true)
    {
        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            noErr = false;
        }
        else
        {
            return noErr;
        }
        std::string msg;
        switch (err)
        {
        case GL_INVALID_ENUM:

            msg = "An unacceptable value is specified for an enumerated argument.The offending command is ignored and has no other side effect than to set the error flag.";
            break;

        case GL_INVALID_VALUE:

            msg = "A numeric argument is out of range.The offending command is ignored and has no other side effect than to set the error flag.";
            break;

        case GL_INVALID_OPERATION:

            msg = "The specified operation is not allowed in the current state.The offending command is ignored and has no other side effect than to set the error flag.";
            break;

        case GL_INVALID_FRAMEBUFFER_OPERATION:

            msg = "The framebuffer object is not complete.The offending command is ignored and has no other side effect than to set the error flag.";
            break;

        case GL_OUT_OF_MEMORY:

            msg = "There is not enough memory left to execute the command.The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
            break;

        case GL_STACK_UNDERFLOW:

            msg = "An attempt has been made to perform an operation that would cause an internal stack to underflow.";
            break;

        case GL_STACK_OVERFLOW:

            msg = "An attempt has been made to perform an operation that would cause an internal stack to overflow.";
            break;
        }

        fmt::print("Error {} | Caller: Line {}, {}.|\n Function: {}|\n Description:\n {}\n", (UINT)err, caller.line(), caller.file_name(), function, msg);
    }
}

void GLAPIENTRY DebugCallbackGL(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    const char* _source;
    const char* _type;
    const char* _severity;
    using fmt::print, fmt::fg, fmt::color;
    color c;

    switch (source) {
    case GL_DEBUG_SOURCE_API:
        _source = "API";
        break;

    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        _source = "WINDOW SYSTEM";
        break;

    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        _source = "SHADER COMPILER";
        break;

    case GL_DEBUG_SOURCE_THIRD_PARTY:
        _source = "THIRD PARTY";
        break;

    case GL_DEBUG_SOURCE_APPLICATION:
        _source = "APPLICATION";
        break;

    case GL_DEBUG_SOURCE_OTHER:
        _source = "OTHER";
        break;

    default:
        _source = "UNKNOWN";
        break;
    }
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        _type = "ERROR";
        break;

    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        _type = "DEPRECATED BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        _type = "UNDEFINED BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_PORTABILITY:
        _type = "PORTABILITY";
        break;

    case GL_DEBUG_TYPE_PERFORMANCE:
        _type = "PERFORMANCE";
        break;

    case GL_DEBUG_TYPE_OTHER:
        _type = "OTHER";
        break;

    case GL_DEBUG_TYPE_MARKER:
        _type = "MARKER";
        break;

    default:
        _type = "UNKNOWN";
        break;
    }
    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        _severity = "HIGH";
        c = color::red;
        break;

    case GL_DEBUG_SEVERITY_MEDIUM:
        _severity = "MEDIUM";
        c = color::orange;
        break;

    case GL_DEBUG_SEVERITY_LOW:
        _severity = "LOW";
        c = color::yellow;
        break;

    case GL_DEBUG_SEVERITY_NOTIFICATION:
        _severity = "NOTIFICATION";
        c = color::green_yellow;
        break;

    default:
        _severity = "UNKNOWN";
        c = color::sky_blue;
        break;
    }
    print(fg(c), "GL CALLBACK -- {}: {} of {}, raised from {}: {}\n", id, _type, _severity, _source, message);
    __debugbreak();
}

void UnbindallGL()
{
    GLCALL(glBindVertexArray(0));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
    GLCALL(glUseProgram(0));
}

sf::Vector2i screenCenter(sf::Window& w)
{
    return sf::Vector2i(w.getSize().x / 2, w.getSize().y / 2);
}

glm::vec2 s2g(sf::Vector2f vec)
{
    return glm::vec2(vec.x, vec.y);
}
glm::vec2 s2g(sf::Vector2i vec)
{
    return glm::vec2((float)vec.x, (float)vec.y);
}

void ToggleFullscreen(sf::Window& window, WINDOWPLACEMENT& g_wpPrev)
{
#ifdef WINDOWS
    sf::WindowHandle hwnd = window.getSystemHandle();
    DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);
    if (dwStyle & WS_OVERLAPPEDWINDOW) {
        MONITORINFO mi = { sizeof(mi) };
        if (GetWindowPlacement(hwnd, &g_wpPrev) &&
            GetMonitorInfo(MonitorFromWindow(hwnd,
                MONITOR_DEFAULTTOPRIMARY), &mi)) {
            SetWindowLong(hwnd, GWL_STYLE,
                dwStyle & ~WS_OVERLAPPEDWINDOW);
            SetWindowPos(hwnd, HWND_TOP,
                mi.rcMonitor.left, mi.rcMonitor.top,
                mi.rcMonitor.right - mi.rcMonitor.left,
                mi.rcMonitor.bottom - mi.rcMonitor.top,
                SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
        }
    }
    else {
        SetWindowLong(hwnd, GWL_STYLE,
            dwStyle | WS_OVERLAPPEDWINDOW);
        SetWindowPlacement(hwnd, &g_wpPrev);
        SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
            SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
    }
#endif

#ifdef MACOS
#endif

#ifdef LINUX_GNU
#endif
}
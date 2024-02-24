#pragma once
#include "header.hpp"


std::string ReadFile(const char* path);

bool HandleOpenGLError(std::source_location caller, std::string function);

void GLAPIENTRY DebugCallbackGL(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam);

void UnbindallGL();

sf::Vector2i screenCenter(sf::Window& w);

glm::vec2 s2g(sf::Vector2f vec);
glm::vec2 s2g(sf::Vector2i vec);

void ToggleFullscreen(sf::Window& window, WINDOWPLACEMENT& g_wpPrev);
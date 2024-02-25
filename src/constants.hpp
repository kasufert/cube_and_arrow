#pragma once
#include "header.hpp"

static constexpr float PI = 3.1415926535897932384626433832795;
static constexpr float TWOPI = 2 * PI;

const char* const fragShaderPath = "../resources/shaders/frag.glsl";
const char* const vertShaderPath = "../resources/shaders/vert.glsl";

constexpr uint floats_per_vert = 9;
constexpr uint verts_per_tri = 3;
constexpr uint tri_byte_size = floats_per_vert * verts_per_tri * sizeof(GLfloat);

constexpr glm::vec2 noTex(0.0, 0.0);


constexpr glm::vec4 red(1.0, 0.0, 0.0, 1.0);
constexpr glm::vec4 green(0.0, 1.0, 0.0, 1.0);
constexpr glm::vec4 blue(0.0, 0.0, 1.0, 1.0);
constexpr glm::vec4 magenta = red + blue;
constexpr glm::vec4 yellow = red + green;
constexpr glm::vec4 cyan = blue + green;
constexpr glm::vec4 black(0.0, 0.0, 0.0, 1.0);
constexpr glm::vec4 white(1.0, 1.0, 1.0, 1.0);
constexpr glm::vec4 clear(0.0, 0.0, 0.0, 0.0);
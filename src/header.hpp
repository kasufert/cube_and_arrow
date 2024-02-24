#pragma once
#ifdef GLAD_BUILD
#include <glad/glad.h>
#endif
#ifdef GLEW_BUILD
#include <gl/glew.h>
#endif
#include <SFML/OpenGL.hpp>
#include <fmt/format.h>
#include <fmt/color.h>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <source_location>

#ifdef GLAD_BUILD
#include "glad.c"
#endif

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long long u64;
typedef long long i64;

#include "macros.hpp"

#include "constants.hpp"
#include "shader.hpp"
#include "utils.hpp"
#include "texture.hpp"
#include "vertex.hpp"
#include "ShapeData.hpp"
#include "ShapeGenerator.hpp"
#include "buffer.hpp"
#include "Camera.hpp"
#include "Transform.hpp"
#include "Shape.hpp"
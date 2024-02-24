#pragma once
#include "header.hpp"

#define NUM_ELEMS(x) sizeof(x) / sizeof(*x)

#define ASSERT(x) if (!x) { __debugbreak(); }

#define CHECK_GL_ERRORS HandleOpenGLError(std::source_location::current());

#define GLCALL(x) \
	x; \
	ASSERT(HandleOpenGLError(std::source_location::current(), #x));
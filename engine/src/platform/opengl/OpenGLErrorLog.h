#pragma once
#include <glad/glad.h>

//Linux specific assert, header should be determined by the macros
#include <csignal>

//OpenGL debug macros (temporary)
#define ASSERT(x) if (!(x)) raise(SIGTRAP)
#define glCall(x) glClearError();\
    x;\
    ASSERT(glLogCall(#x, __FILE__, __LINE__));

void glClearError();
bool glLogCall(const char *function, const char *file, int line);

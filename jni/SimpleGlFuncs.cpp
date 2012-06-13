/*
 * SimpleGlFuncs.cpp
 *
 *  Created on: 24.05.2012
 *      Author: trex
 */

#include "SimpleGlFuncs.h"

#include <GLES2/gl2.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "AndroidLogs.h"


void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

#define EXIT_ON_GL_ERROR

void checkGlError(const char* op) {
        bool hasError = false;

    for (GLint error = glGetError(); error; error = glGetError())
    {
        LOGI("after %s() glError (0x%x)\n", op, error);
        hasError = true;
    }

#ifdef EXIT_ON_GL_ERROR
    if(hasError)
    {
        exit(-1);
    }
#endif

}

GLuint loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    checkGlError("glCreateShader");
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGI("Could not compile shader %d:\n%s\n",
                            shaderType, buf);
                    free(buf);

                    exit(-2);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint createProgram(
        const char* pVertexSource,
        const char* pFragmentSource
)
{
        checkGlError("start createProgram");
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    checkGlError("loadShader_vertex");
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    checkGlError("loadShader_fragment");
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    checkGlError("glCreateProgram");

    if (program) {
        glAttachShader(program, vertexShader);
        checkGlError("glAttachShader_vertex");

        glAttachShader(program, pixelShader);
        checkGlError("glAttachShader_pixel");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

/*
 * SimpleGlFuncs.h
 *
 *  Created on: 24.05.2012
 *      Author: trex
 */

#ifndef SIMPLEGLFUNCS_H_
#define SIMPLEGLFUNCS_H_

#include <GLES2/gl2.h>

bool setupGraphics(int w, int h);
void checkGlError(const char* op);

GLuint createProgram(
        const char* pVertexSource,
        const char* pFragmentSource
);

#endif /* SIMPLEGLFUNCS_H_ */

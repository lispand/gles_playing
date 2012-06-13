/*
 * GLTriangle.h
 *
 *  Created on: 24.05.2012
 *      Author: trex
 */

#ifndef GLTRIANGLE_H_
#define GLTRIANGLE_H_

#include "IDrawable.h"
#include "DrawConfig.h"

#include <GLES2/gl2.h>

class GLTriangle: public IDrawable
{
public:
	GLTriangle(DrawConfig config);
	GLTriangle(int x, int y, DrawConfig config);
	virtual ~GLTriangle();

	virtual void draw();//IDrawable

	void setA(const float* xyz);
	void setB(const float* xyz);
	void setC(const float* xyz);
private:
	void init();
	GLuint m_program;
	GLuint m_position;
	GLuint m_color;
	GLuint m_textureLocation;
	GLuint m_texturePosition;

	void bufferSetup();
	void bufferSetup(int x, int y);
	GLuint m_buffer;

	void useTexture();
	GLuint m_texture;

	DrawConfig m_drawConfig;
};

#endif /* GLTRIANGLE_H_ */

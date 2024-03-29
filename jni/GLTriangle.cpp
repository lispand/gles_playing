/*
 * GLTriangle.cpp
 *
 *  Created on: 24.05.2012
 *      Author: trex
 */

#include "GLTriangle.h"

#include "SimpleGlFuncs.h"
#include "AndroidLogs.h"

#include "picture.c"
//#include "love-heart.c"


static const char gVertexShader[] =
	"attribute vec4 vPosition;\n"
	"attribute vec4 vColor;\n"
	"attribute vec4 vTexPosition;\n"
	"\n"
	"varying mediump vec4 fColor;"
	"varying mediump vec2 fTexPosition;\n"
	"\n"
	"void main() {\n"
	"  gl_Position = vPosition;\n"
	"  fColor = vColor;\n"
	"  fTexPosition = vTexPosition.xy;\n"
	"}\n";

static const char gFragmentShader[] =
	"precision mediump float;\n"
	"\n"
	"varying mediump vec4 fColor;\n"
	"varying mediump vec2 fTexPosition;\n"
	"\n"
	"uniform sampler2D fTexture;\n"
	"\n"
	"vec4 texColor;\n"
	"\n"
	"void main() {\n"
	"  texColor = texture2D(fTexture, fTexPosition);"
	"  gl_FragColor = texColor;\n"
	"}\n";

static const GLfloat gTriangleVertices[] = {
	 //vertex position
	 0.0f,  0.9f, 0.0f,
	-0.9f, -0.9f, 0.0f,
	 0.9f, -0.9f,  0.0f,
	 //vertex color
	 0.8f, 0.5f,  0.5f,
	 0.8f, 0.5f, 0.5f,
	 0.8f, 0.5f, 0.5f,
	 //texture coord
	 0.0, 0.0,
	 0.0, 1.0,
	 1.0, 0.0
};

GLTriangle::GLTriangle(DrawConfig config)
	:m_drawConfig(config)
{
	this->init();

	this->bufferSetup();
	this->useTexture();
}

GLTriangle::GLTriangle(int x, int y, DrawConfig config)
	:m_drawConfig(config)
{
	this->init();

	this->bufferSetup(x,y);
	this->useTexture();
}

GLTriangle::~GLTriangle() {
	// TODO Auto-generated destructor stub
}

void GLTriangle::init()
{
	m_program = createProgram(gVertexShader, gFragmentShader);

	m_position = glGetAttribLocation(m_program, "vPosition");
	checkGlError("glGetAttribLocation");

	m_color = glGetAttribLocation(m_program, "vColor");
	checkGlError("glGetAttribLocation(vColor)");

	m_texturePosition = glGetAttribLocation(m_program,"vTexPosition");
	checkGlError("glGetAttribLocation(vTexPosition)");

	m_textureLocation = glGetUniformLocation(m_program, "fTexture");
	checkGlError("glGetUniformLocation(fTexture)");

	glGenBuffers(1,&m_buffer);
	checkGlError("GLTriangle::bufferSetup glGenBuffers");
}

void GLTriangle::bufferSetup()
{
	glBindBuffer(GL_ARRAY_BUFFER,m_buffer);
	checkGlError("GLTriangle::bufferSetup glBufferData");

	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(float)* ( (3+3)*3 + 3*2),
		gTriangleVertices,
		GL_DYNAMIC_DRAW
	);
	checkGlError("GLTriangle::bufferSetup glBufferData");
}

void GLTriangle::bufferSetup(int x, int y)
{
	GLfloat data[] = {
		//vertex position
		 0.0f,  0.1f, 0.0f,
		-0.1f, -0.1f, 0.0f,
		 0.1f, -0.1f,  0.0f,
		 //vertex color
		 0.8f, 0.5f,  0.5f,
		 0.8f, 0.5f, 0.5f,
		 0.8f, 0.5f, 0.5f,
		 //texture coord
		 0.0, 0.0,
		 0.0, 1.0,
		 1.0, 0.0
	};

	float width = (float) m_drawConfig.getWidth();
	float height = (float) m_drawConfig.getHeight();

	float widthDelta = 2 * ( (float)x  - width/2.0f ) / width;
	float heightDelta = 2* ( height / 2.0f - (float)y ) / height;

	data[0] += widthDelta;
	data[1] += heightDelta;

	data[3] += widthDelta;
	data[4] += heightDelta;

	data[6] += widthDelta;
	data[7] += heightDelta;

	glBindBuffer(GL_ARRAY_BUFFER,m_buffer);
	checkGlError("GLTriangle::bufferSetup glBufferData");

	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(float)* ( (3+3)*3 + 3*2),
		data,
		GL_DYNAMIC_DRAW
	);
	checkGlError("GLTriangle::bufferSetup glBufferData");
}

void GLTriangle::setA(const float* xyz)
{
	glBindBuffer(GL_ARRAY_BUFFER,m_buffer);
	checkGlError("GLTriangle::setA glBindBuffer");

	glBufferSubData(GL_ARRAY_BUFFER,sizeof(float)*0*3 ,sizeof(float)*3,xyz);
	checkGlError("GLTriangle::setA glBufferSubData");
}

void GLTriangle::setB(const float* xyz)
{
	glBindBuffer(GL_ARRAY_BUFFER,m_buffer);
	glBufferSubData(GL_ARRAY_BUFFER,sizeof(float)*1*3,sizeof(float)*3,xyz);
}

void GLTriangle::setC(const float* xyz)
{
	glBindBuffer(GL_ARRAY_BUFFER,m_buffer);
	glBufferSubData(GL_ARRAY_BUFFER,sizeof(float)*2*3,sizeof(float)*3,xyz);
}


void GLTriangle::draw()
{
	checkGlError("Start GLTriangle::draw()");


	glUseProgram(m_program);
	checkGlError("glUseProgram");


	glBindBuffer(GL_ARRAY_BUFFER,m_buffer);
	checkGlError("GLTriangle::draw glBindBuffer");

	{
		glVertexAttribPointer(m_position, 3, GL_FLOAT, GL_FALSE, 0, 0);
		checkGlError("GLTriangle::bufferSetup glVertexAttribPointer(m_position,...");

		glEnableVertexAttribArray(m_position);
		checkGlError("GLTriangle::bufferSetup glEnableVertexAttribArray(m_position);");

		glVertexAttribPointer(m_color, 3, GL_FLOAT, GL_FALSE, 0, (void*) (3*3*sizeof(float)) );
		checkGlError("GLTriangle::bufferSetup glVertexAttribPointer(m_color,...");

		glEnableVertexAttribArray(m_color);
		checkGlError("GLTriangle::bufferSetup glEnableVertexAttribArray(m_color);");

		glVertexAttribPointer(m_texturePosition, 2, GL_FLOAT, GL_FALSE, 0, (void* ) ( (3+3)*3*sizeof(float)) );
		checkGlError("GLTriangle::bufferSetup glVertexAttribPointer(m_texturePosition,...");

		glEnableVertexAttribArray(m_texturePosition);
		checkGlError("GLTriangle::bufferSetup glEnableVertexAttribArray(m_texturePosition);");
	}

	{
		glActiveTexture(GL_TEXTURE0);
		checkGlError("GLTriangle::draw glActiveTexture");

		glBindTexture(GL_TEXTURE_2D, m_texture);
		checkGlError("GLTriangle::draw glBindTexture");

		glUniform1i(m_textureLocation,0);
		checkGlError("GLTriangle::draw glUniform1i");
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);
	checkGlError("GLTriangle::draw glDrawArrays");
}

void GLTriangle::useTexture()
{
	glGenTextures(1,&m_texture);
	checkGlError("GLTriangle::useTexture GenTexture");

	glBindTexture(GL_TEXTURE_2D, m_texture);
	checkGlError("GLTriangle::useTexture glBindTexture");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	checkGlError("GLTriangle::useTexture glTexParameteri");

	glTexImage2D(
		(GLenum) GL_TEXTURE_2D,
		(GLint) 0,
		(GLint) GL_RGB,
		(GLsizei) gimp_image.width,
		(GLsizei) gimp_image.height,
		(GLint) 0,
		(GLenum) GL_RGB,
		(GLenum) GL_UNSIGNED_BYTE,
		(const GLvoid*) gimp_image.pixel_data
	);
	checkGlError("GLTriangle::useTexture glTexImage2D");
}

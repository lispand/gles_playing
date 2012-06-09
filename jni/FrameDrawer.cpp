/*
 * FrameDrawer.cpp
 *
 *  Created on: 08.06.2012
 *      Author: trex
 */

#include "FrameDrawer.h"
#include "SimpleGlFuncs.h"
#include "AndroidLogs.h"

FrameDrawer::FrameDrawer()
{
	m_grey = 0.0f;
}

FrameDrawer::~FrameDrawer()
{

}


void FrameDrawer::drawFrame(std::vector<IDrawable*> drawables)
{
	m_grey += 0.01f;
	if (m_grey > 1.0f) {
		m_grey = 0.0f;
	}

	glClearColor(0, m_grey, m_grey, 1.0f);
	checkGlError("glClearColor");

	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	checkGlError("glClear");

	int i = 0;
	for(std::vector<IDrawable*>::iterator drawable = drawables.begin();
		drawable != drawables.end();
		++drawable)
	{
		++i;
		(*drawable)->draw();
	}
}










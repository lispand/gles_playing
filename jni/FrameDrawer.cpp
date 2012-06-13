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
	m_grey = 0.5f;
}

FrameDrawer::~FrameDrawer()
{

}


void FrameDrawer::drawFrame(std::vector<IDrawable*> drawables)
{
	glClearColor(0, m_grey, m_grey, 1.0f);
	checkGlError("glClearColor");

	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	checkGlError("glClear");

	for(std::vector<IDrawable*>::iterator drawable = drawables.begin();
		drawable != drawables.end();
		++drawable)
	{
		(*drawable)->draw();
	}
}










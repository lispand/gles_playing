/*
 * DrawConfigPrivate.cpp
 *
 *  Created on: 12.06.2012
 *      Author: trex
 */

#include "DrawConfigPrivate.h"

DrawConfigPrivate::DrawConfigPrivate(int w, int h)
	:m_witdh(w)
	,m_height(h)
{

}

DrawConfigPrivate::~DrawConfigPrivate()
{

}

int DrawConfigPrivate::getHeight()
{
	return m_height;
}

void DrawConfigPrivate::setHeight(int h)
{
	m_height = h;
}

int DrawConfigPrivate::getWidth()
{
	return m_witdh;
}

void DrawConfigPrivate::setWidth(int w)
{
	m_witdh = w;
}

/*
 * DrawConfig.cpp
 *
 *  Created on: 12.06.2012
 *      Author: trex
 */

#include "DrawConfig.h"

#include "DrawConfigPrivate.h"

DrawConfig::DrawConfig(DrawConfigPrivate* config)
	:m_config(config)
{
	// TODO Auto-generated constructor stub

}

DrawConfig::~DrawConfig()
{
	// TODO Auto-generated destructor stub
}

int DrawConfig::getHeight()
{
	return m_config->getHeight();
}

int DrawConfig::getWidth()
{
	return m_config->getWidth();
}

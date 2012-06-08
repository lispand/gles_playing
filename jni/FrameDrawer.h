/*
 * FrameDrawer.h
 *
 *  Created on: 08.06.2012
 *      Author: trex
 */

#ifndef FRAMEDRAWER_H_
#define FRAMEDRAWER_H_

#include <vector>

#include "IDrawable.h"

class FrameDrawer
{
public:
	FrameDrawer();
	~FrameDrawer();

	void drawFrame(std::vector<IDrawable*> drawables);
private:
	float m_grey;
};

#endif /* FRAMEDRAWER_H_ */

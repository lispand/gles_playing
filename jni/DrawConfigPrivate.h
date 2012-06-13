#ifndef DRAWCONFIGPRIVATE_H_
#define DRAWCONFIGPRIVATE_H_

/*
 * DrawConfigPrivate.h
 *
 *  Created on: 12.06.2012
 *      Author: trex
 */

class DrawConfigPrivate
{
public:
	DrawConfigPrivate(int w = 1, int h = 1);
	virtual ~DrawConfigPrivate();

	int getHeight();
	void setHeight(int h);

	int getWidth();
	void setWidth(int w);
private:
	int m_witdh;
	int m_height;
};

#endif /* DRAWCONFIGPRIVATE_H_ */

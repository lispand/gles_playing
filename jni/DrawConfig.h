#ifndef DRAWCONFIG_H_
#define DRAWCONFIG_H_

/*
 * DrawConfig.h
 *
 *  Created on: 12.06.2012
 *      Author: trex
 */

class DrawConfigPrivate;

class DrawConfig
{
public:
	DrawConfig(DrawConfigPrivate* config);
	virtual ~DrawConfig();

	int getHeight();
	int getWidth();
private:
	DrawConfigPrivate* m_config;
};

#endif /* DRAWCONFIG_H_ */

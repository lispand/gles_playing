/*
 * IDrawable.h
 *
 *  Created on: 08.06.2012
 *      Author: trex
 */

#ifndef IDRAWABLE_H_
#define IDRAWABLE_H_

#include <vector>

class IDrawable
{
public:
  virtual ~IDrawable();
  virtual void draw() = 0;

};

#endif /* IDRAWABLE_H_ */

#ifndef __SIMILARITY__H_
#define __SIMILARITY__H_

#include "Image.h"

class Similarity {
private:
	float colorWeight;
	float shapeWeight;

publlic:
	Similarity();
	Similarity(float color, float shape);
	float similarity(Image a, Image b);
	float similarity(Histogram hisa, Histogram hisb);
};

#endif
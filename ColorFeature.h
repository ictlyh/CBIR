#ifndef __COLORFEATURE__H_
#define __COLORFEATURE__H_

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "Histogram.h"

class ColorFeature {
private:
	Histogram h;
	Histogram s;
	Histogram v;
	Histogram grey;

public:
	void calcH(IplImage* hplane);
	void calcS(IplImage* splane);
	void calcV(IplImage* vplane);
	void calsGrey(IplImage* greyplane);
	void calcHSV(IplImage** planes);
};

#endif
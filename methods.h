#ifndef __METHODS_H__
#define __METHODS_H__

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "Histogram.h"

void calcHist(IplImage *plane, Histogram &h, int dim);

#endif
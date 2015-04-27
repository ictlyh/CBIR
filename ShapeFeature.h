#ifndef __SHAPEFEATURE__H_
#define __SHAPEFEATURE__H_

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "Histogram.h"

class ShapeFeature {
private:
	Histogram vertical;
	Histogram horizontal;

public:
	void calcVertical(int*** matrix, int row, int col);
	void calcHorizontal(int** matrix, int row, int col);
};

#endif
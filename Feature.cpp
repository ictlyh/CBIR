#include "Feature.h"

ColorFeature Feature::getColorFeature()
{
	return colorFeature;
}

ShapeFeature Feature::getShapeFeature()
{
	return shapeFeature;
}

void Feature::calcColorFeature(IplImage ** planes)
{
	colorFeature.calcHSV(planes);
	colorFeature.calcGray(planes[3]);
}

void Feature::calcShapeFeature(IplImage * grayplane)
{
	shapeFeature.calcHorizontal(grayplane);
	shapeFeature.calcVertical(grayplane);
}
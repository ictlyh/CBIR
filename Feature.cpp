#include "Feature.h"

Feature::~Feature()
{
}

ColorFeature Feature::getColorFeature()
{
	return colorFeature;
}

ShapeFeature Feature::getShapeFeature()
{
	return shapeFeature;
}

void Feature::setColorFeature(Histogram * color)
{
	colorFeature.setH(color[0]);
	colorFeature.setS(color[1]);
	colorFeature.setV(color[2]);
	colorFeature.setGray(color[3]);
}

void Feature::setShapeFeature(Histogram * shape)
{
	shapeFeature.setHorizontal(shape[0]);
	shapeFeature.setVertival(shape[1]);
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
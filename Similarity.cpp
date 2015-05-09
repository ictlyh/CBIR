#include "Similarity.h"

Similarity::Similarity()
{
	colorWeight = 0.5;
	shapeWeight = 0.5;
}

Similarity::Similarity(float color, float shape)
{
	colorWeight = color;
	shapeWeight = shape;
}

void Similarity::setColorWeight(float color)
{
	colorWeight = color;
}

void Similarity::setShapeWeight(float shape)
{
	shapeWeight = shape;
}

float Similarity::getColorWeight()
{
	return colorWeight;
}

float Similarity::getShapeWeight()
{
	return shapeWeight;
}

float Similarity::similarity(Histogram a, Histogram b)
{

	return 0.0;
}

float Similarity::similarity(Image a, Image b)
{
	return 0.0;
}
#include "Histogram.h"

Histogram::Histogram()
{
	dim = 0;
	feature = NULL;
}

Histogram::Histogram(int d)
{
	dim = d;
	feature = (float *) malloc (sizeof(float) * dim);
	for(int i = 0; i < dim; i++)
		feature[i] = 0;
}

void Histogram::setDim(int d)
{
	dim = d;
	feature = (float *) malloc (sizeof(float) * dim);
	for(int i = 0; i < dim; i++)
		feature[i] = 0;
}

void Histogram::setFeature(int index, float value)
{
	feature[index] = value;
}

void Histogram::setFeature(float *values)
{
	for(int i = 0; i < dim; i++)
		feature[i] = values[i];
}

int Histogram::getDim()
{
	return dim;
}

float Histogram::getFeature(int index)
{
	return feature[index];
}

float* Histogram::getFeature()
{
	return feature;
}
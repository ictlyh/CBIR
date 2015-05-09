#include "ColorFeature.h"
#include "methods.h"

ColorFeature::~ColorFeature()
{
}

Histogram ColorFeature::getH()
{
	return h;
}

Histogram ColorFeature::getS()
{
	return s;
}

Histogram ColorFeature::getV()
{
	return v;
}

Histogram ColorFeature::getGray()
{
	return gray;
}

void ColorFeature::setH(Histogram histH)
{
	h.setDim(histH.getDim());
	h.setFeature(histH.getFeature());
}

void ColorFeature::setS(Histogram histS)
{
	s.setDim(histS.getDim());
	s.setFeature(histS.getFeature());
}

void ColorFeature::setV(Histogram histV)
{
	v.setDim(histV.getDim());
	v.setFeature(histV.getFeature());
}

void ColorFeature::setGray(Histogram histGray)
{
	gray.setDim(histGray.getDim());
	gray.setFeature(histGray.getFeature());
}

void ColorFeature::calcH(IplImage * hplane)
{
	calcHist(hplane, h, 181);		// H分量的取值范围为[0,180]
}

void ColorFeature::calcS(IplImage * splane)
{
	calcHist(splane, s, 256);		// S分量的取值范围为[0,255]
	
}

void ColorFeature::calcV(IplImage * vplane)
{
	calcHist(vplane, v, 256);		// V分量的取值范围为[0,255]
}

void ColorFeature::calcGray(IplImage * grayplane)
{
	calcHist(grayplane, gray, 256);	// 灰度值取值范围为[0,255]
}

void ColorFeature::calcHSV(IplImage **planes)
{
	calcHist(planes[0], h, 181);		// H分量的取值范围为[0,180]
	calcHist(planes[1], s, 256);		// S分量的取值范围为[0,255]
	calcHist(planes[2], v, 256);		// V分量的取值范围为[0,255]
}
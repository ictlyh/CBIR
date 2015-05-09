#include "ColorFeature.h"
#include "methods.h"

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

void ColorFeature::calcH(IplImage * hplane)
{
	calcHist(hplane, h, 181);		// H������ȡֵ��ΧΪ[0,180]
}

void ColorFeature::calcS(IplImage * splane)
{
	calcHist(splane, s, 256);		// S������ȡֵ��ΧΪ[0,255]
	
}

void ColorFeature::calcV(IplImage * vplane)
{
	calcHist(vplane, v, 256);		// V������ȡֵ��ΧΪ[0,255]
}

void ColorFeature::calcGray(IplImage * grayplane)
{
	calcHist(grayplane, gray, 256);	// �Ҷ�ֵȡֵ��ΧΪ[0,255]
}

void ColorFeature::calcHSV(IplImage **planes)
{
	calcHist(planes[0], h, 181);		// H������ȡֵ��ΧΪ[0,180]
	calcHist(planes[1], s, 256);		// S������ȡֵ��ΧΪ[0,255]
	calcHist(planes[2], v, 256);		// V������ȡֵ��ΧΪ[0,255]
}
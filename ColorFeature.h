#ifndef __COLORFEATURE__H_
#define __COLORFEATURE__H_

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "Histogram.h"

/*
 * (HSV�ռ�)��ɫ������
 */
class ColorFeature {
private:
	Histogram h;		// H����ֱ��ͼ
	Histogram s;		// S����ֱ��ͼ
	Histogram v;		// V����ֱ��ͼ
	Histogram grey;		// �Ҷ�ֱ��ͼ

public:
	Histogram getH();					// ��ȡH����ֱ��ͼ
	Histogram getS();					// ��ȡS����ֱ��ͼ
	Histogram getV();					// ��ȡV����ֱ��ͼ
	Histogram getGrey();				// ��ȡ�Ҷ�ֱ��ͼ
	void calcH(IplImage* hplane);		// ����H����ֱ��ͼ
	void calcS(IplImage* splane);		// ����S����ֱ��ͼ
	void calcV(IplImage* vplane);		// ����V����ֱ��ͼ
	void calsGrey(IplImage* greyplane);	// ����Ҷ�ֱ��ͼ
	void calcHSV(IplImage** planes);	// ����HSVֱ��ͼ
};

#endif
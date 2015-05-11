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
	Histogram gray;		// �Ҷ�ֱ��ͼ

public:
	~ColorFeature();
	Histogram getH();					// ��ȡH����ֱ��ͼ
	Histogram getS();					// ��ȡS����ֱ��ͼ
	Histogram getV();					// ��ȡV����ֱ��ͼ
	Histogram getGray();				// ��ȡ�Ҷ�ֱ��ͼ
	void setH(Histogram histH);			// ����H����ֱ��ͼ
	void setS(Histogram histS);			// ����S����ֱ��ͼ
	void setV(Histogram histV);			// ����V����ֱ��ͼ
	void setGray(Histogram histGray);	// ���ûҶ�ֱ��ͼ
	void calcH(IplImage* hplane);		// ����H����ֱ��ͼ
	void calcS(IplImage* splane);		// ����S����ֱ��ͼ
	void calcV(IplImage* vplane);		// ����V����ֱ��ͼ
	void calcGray(IplImage* grayplane);	// ����Ҷ�ֱ��ͼ
	void calcHSV(IplImage** planes);	// ����HSVֱ��ͼ
};

#endif
#ifndef __SHAPEFEATURE__H_
#define __SHAPEFEATURE__H_

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "Histogram.h"

/*
 * ��״�����࣬��������Ե�㷽��ֱ��ͼ����
 */
class ShapeFeature {
private:
	Histogram vertical;		// �Ҷ�ͼ���Ե����ֱ����ֱ��ͼ
	Histogram horizontal;	// �Ҷ�ͼ���Ե��ˮƽ����ֱ��ͼ

public:
	void calcVertical(IplImage* grey);		// ���ݻҶ�ֱ��ͼ������ֱ�����Ե��ֱ��ͼ
	void calcHorizontal(IplImage* grey);	// ���ݻҶ�ֱ��ͼ����ˮƽ�����Ե��ֱ��ͼ
};

#endif
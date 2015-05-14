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
	Histogram vertical;	// �Ҷ�ͼ���Ե����ֱ����ֱ��ͼ
	Histogram horizontal;	// �Ҷ�ͼ���Ե��ˮƽ����ֱ��ͼ

public:
	~ShapeFeature();
	Histogram getVertical();		// ��ȡ��ֱ�����Ե��ֱ��ͼ
	Histogram getHorizontal();		// ��ȡˮƽ�����Ե��ֱ��ͼ
	void setHorizontal(Histogram hori);	// ����ˮƽ�����Ե��ֱ��ͼ
	void setVertival(Histogram verti);	// ������ֱ�����Ե��ֱ��ͼ
	void calcVertical(IplImage* gray);	// ���ݻҶ�ֱ��ͼ������ֱ�����Ե��ֱ��ͼ
	void calcHorizontal(IplImage* gray);	// ���ݻҶ�ֱ��ͼ����ˮƽ�����Ե��ֱ��ͼ
};

#endif

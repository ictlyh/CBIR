#ifndef __FEATURE__H_
#define __FEATURE__H_

#include "ColorFeature.h"
#include "ShapeFeature.h"

/*
 * ͼ��������
 */
class Feature {
private:
	ColorFeature colorFeature;		// ��ɫ����
	ShapeFeature shapeFeature;		// ��״����
public:
	ColorFeature getColorFeature();	// ��ȡ��ɫ����
	ShapeFeature getShapeFeature();	// ��ȡ��״����
	void calcColorFeature(IplImage** planes);	// ������ɫ����
	void calcColorFeature(IplImage* greyplane);	// ������״����
};

#endif
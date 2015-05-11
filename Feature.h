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
	~Feature();
	ColorFeature getColorFeature();				// ��ȡ��ɫ����
	ShapeFeature getShapeFeature();				// ��ȡ��״����
	void setColorFeature(Histogram * color);	// ������ɫ����
	void setShapeFeature(Histogram * shape);	// ������״����
	void calcColorFeature(IplImage** planes);	// ������ɫ����
	void calcShapeFeature(IplImage* grayplane);	// ������״����
};

#endif
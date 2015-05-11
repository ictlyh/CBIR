#ifndef __SIMILARITY__H_
#define __SIMILARITY__H_

#include "Image.h"

/*
 * ���ƶȼ����࣬��������ͼ�����ƶȺ�ֱ��ͼ���ƶ�
 */
class Similarity {
private:
	float colorWeight;		// ��ɫ����Ȩ��
	float shapeWeight;		// ��״����Ȩ��

public:
	Similarity();										// �޲ι��캯��
	Similarity(float color, float shape);				// ָ��Ȩ�ع��캯��
	~Similarity();
	void setColorWeight(float color);					// ������ɫ����Ȩ��
	void setShapeWeight(float shape);					// ������״����Ȩ��
	float getColorWeight();								// ��ȡ��ɫ����Ȩ��
	float getShapeWeight();								// ��ȡ��״����Ȩ��
	float similarity(Image a, Image b);					// ��������ͼ������ƶ�
	float similarity(Histogram a, Histogram b);			// ��������ֱ��ͼ�����ƶ�
};

#endif
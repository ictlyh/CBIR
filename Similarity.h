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
	float similarity(Image a, Image b);					// ��������ͼ������ƶ�
	float similarity(Histogram hisa, Histogram hisb);	// ��������ֱ��ͼ�����ƶ�
};

#endif
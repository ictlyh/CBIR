#ifndef __HISTGRAM__H_
#define __HISTGRAM__H_

#include <cstdlib>

/*
 * ֱ��ͼ��
 */
class Histogram {
private:
	int dim;		// ֱ��ͼ bin ��Ŀ
	float *feature;		// ֱ��ͼ bin �߶�(0-1)

public:
	Histogram();
	Histogram(int dim);
	~Histogram();
	
	void setDim(int d);				// ����ֱ��ͼ bin ��Ŀ
	void setFeature(int index, float value);	// ����ֱ��ͼĳ�� bin �߶�
	void setFeature(float *values);			// ����ֱ��ͼ���� bin �߶�
	int getDim();					// ��ȡֱ��ͼ bin ��Ŀ
	float getFeature(int index);			// ��ȡֱ��ͼĳ�� bin �߶�
	float* getFeature();				// ��ȡֱ��ͼ���� bin �߶�
};

#endif

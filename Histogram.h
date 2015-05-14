#ifndef __HISTGRAM__H_
#define __HISTGRAM__H_

#include <cstdlib>

/*
 * 直方图类
 */
class Histogram {
private:
	int dim;		// 直方图 bin 数目
	float *feature;		// 直方图 bin 高度(0-1)

public:
	Histogram();
	Histogram(int dim);
	~Histogram();
	
	void setDim(int d);				// 设置直方图 bin 数目
	void setFeature(int index, float value);	// 设置直方图某个 bin 高度
	void setFeature(float *values);			// 设置直方图所有 bin 高度
	int getDim();					// 获取直方图 bin 数目
	float getFeature(int index);			// 获取直方图某个 bin 高度
	float* getFeature();				// 获取直方图所有 bin 高度
};

#endif

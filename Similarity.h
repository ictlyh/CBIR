#ifndef __SIMILARITY__H_
#define __SIMILARITY__H_

#include "Image.h"

/*
 * 相似度计算类，包括计算图像相似度和直方图相似度
 */
class Similarity {
private:
	float colorWeight;		// 颜色特征权重
	float shapeWeight;		// 形状特征权重

public:
	Similarity();										// 无参构造函数
	Similarity(float color, float shape);				// 指定权重构造函数
	~Similarity();
	void setColorWeight(float color);					// 设置颜色特征权重
	void setShapeWeight(float shape);					// 设置形状特征权重
	float getColorWeight();								// 获取颜色特征权重
	float getShapeWeight();								// 获取形状特征权重
	float similarity(Image a, Image b);					// 计算两个图像的相似度
	float similarity(Histogram a, Histogram b);			// 计算两个直方图的相似度
};

#endif
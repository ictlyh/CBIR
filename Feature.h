﻿#ifndef __FEATURE__H_
#define __FEATURE__H_

#include "ColorFeature.h"
#include "ShapeFeature.h"

/*
 * 图像特征类
 */
class Feature {
private:
	ColorFeature colorFeature;		// 颜色特征
	ShapeFeature shapeFeature;		// 形状特征
public:
	ColorFeature getColorFeature();	// 获取颜色特征
	ShapeFeature getShapeFeature();	// 获取形状特征
	void calcColorFeature(IplImage** planes);	// 计算颜色特征
	void calcColorFeature(IplImage* greyplane);	// 计算形状特征
};

#endif
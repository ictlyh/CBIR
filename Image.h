﻿#ifndef __IMAGE__H_
#define __IMAGE__H_

#include "Feature.h"

/*
 * 图像(文件)类
 */
class Image {
private:
	char path[200];		// 图像路径
	Feature feature;	// 图像特征

public:
	Image(char* p);
	~Image();
	char* getPath();						// 获取图像路径
	Feature getFeature();					// 获取图像特征
	void setFeature(Histogram* features);	// 设置特征
	void showImage();						// 显示图像
	void calcColorFeature();				// 计算颜色特征
	void calcShapeFeature();				// 计算形状特征
	void calcFeature();						// 计算特征
};

#endif
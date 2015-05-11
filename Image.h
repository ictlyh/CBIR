#ifndef __IMAGE__H_
#define __IMAGE__H_

#include <string>
#include "Feature.h"
using namespace std;

/*
 * 图像(文件)类
 */
class Image {
private:
	char path[200];		// 图像路径
	Feature feature;	// 图像特征

public:
	Image();
	Image(char* p);
	~Image();
	char* getPath();						// 获取图像路径
	Feature getFeature();					// 获取图像特征
	void setPath(string p);					// 设置路径
	void setFeature(Histogram features[]);	// 设置特征
	void showImage();						// 显示图像
	bool calcColorFeature();				// 计算颜色特征
	bool calcShapeFeature();				// 计算形状特征
	bool calcFeature();						// 计算特征
};

#endif
#ifndef __SHAPEFEATURE__H_
#define __SHAPEFEATURE__H_

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "Histogram.h"

/*
 * 形状特征类，由两个边缘点方向直方图构成
 */
class ShapeFeature {
private:
	Histogram vertical;		// 灰度图像边缘点竖直方向直方图
	Histogram horizontal;	// 灰度图像边缘点水平方向直方图

public:
	void calcVertical(IplImage* grey);		// 根据灰度直方图计算竖直方向边缘点直方图
	void calcHorizontal(IplImage* grey);	// 根据灰度直方图计算水平方向边缘点直方图
};

#endif
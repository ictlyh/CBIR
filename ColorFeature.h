#ifndef __COLORFEATURE__H_
#define __COLORFEATURE__H_

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include "Histogram.h"

/*
 * (HSV空间)颜色特征类
 */
class ColorFeature {
private:
	Histogram h;		// H分量直方图
	Histogram s;		// S分量直方图
	Histogram v;		// V分量直方图
	Histogram grey;		// 灰度直方图

public:
	Histogram getH();					// 获取H分量直方图
	Histogram getS();					// 获取S分量直方图
	Histogram getV();					// 获取V分量直方图
	Histogram getGrey();				// 获取灰度直方图
	void calcH(IplImage* hplane);		// 计算H分量直方图
	void calcS(IplImage* splane);		// 计算S分量直方图
	void calcV(IplImage* vplane);		// 计算V分量直方图
	void calsGrey(IplImage* greyplane);	// 计算灰度直方图
	void calcHSV(IplImage** planes);	// 计算HSV直方图
};

#endif
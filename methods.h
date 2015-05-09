#ifndef __METHODS_H__
#define __METHODS_H__

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <list>
#include <sstream>
#include <io.h>
#include "Histogram.h"
#include "Image.h"
using namespace std;

/*
 * 公用工具函数
 */
void calcHist(IplImage *plane, Histogram &h, int dim);			// 根据图像计算直方图
void dfsDirectory(char* dir, list<string> &listPath);			// 深度优先遍历文件夹
void lineToFeature(char* line, list<string> &liststr);			// 将读取的行数据转化为一个特征数组
Image newQueryByFeedback(list<Image> feedback, Image query);	// 根据反馈计算二次查询图像
list<Image>::iterator getImage(list<Image> images, int index);	// 获取图像库列表某个位置的迭代器

#endif
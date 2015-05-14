#ifndef __METHODS_H__
#define __METHODS_H__

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <list>
#include <sstream>
#include <io.h>
#include <stdio.h>
#include<windows.h>
#include<iostream>
#include<string>
#include <QMainWindow>
#include <QDir>
#include <QDirIterator>
#include "Histogram.h"
#include "Image.h"
using namespace std;

/*
 * 公用工具函数
 */
void calcHist(IplImage *plane, Histogram &h, int dim);	// 根据图像计算直方图
void dfsDirectory(char* dir, list<string> &listPath);	// 深度优先遍历文件夹
void lineToFeature(char* line, list<string> &liststr);	// 将读取的行数据转化为一个特征数组
Image newQueryByFeedback(list<string> feedbacks, Image query);	// 根据反馈计算二次查询图像
string getImagePath(list<Image> images, int index);	// 获取图像库列表某个图像的路径
void showHistogram(Histogram h);			// 输出直方图
string convertToString(QString src);
QString convertToQString(string);
bool containsString(list<string> listString, string str);

#endif

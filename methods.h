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
 * ���ù��ߺ���
 */
void calcHist(IplImage *plane, Histogram &h, int dim);	// ����ͼ�����ֱ��ͼ
void dfsDirectory(char* dir, list<string> &listPath);	// ������ȱ����ļ���
void lineToFeature(char* line, list<string> &liststr);	// ����ȡ��������ת��Ϊһ����������
Image newQueryByFeedback(list<string> feedbacks, Image query);	// ���ݷ���������β�ѯͼ��
string getImagePath(list<Image> images, int index);	// ��ȡͼ����б�ĳ��ͼ���·��
void showHistogram(Histogram h);			// ���ֱ��ͼ
string convertToString(QString src);
QString convertToQString(string);
bool containsString(list<string> listString, string str);

#endif

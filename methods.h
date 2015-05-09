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
 * ���ù��ߺ���
 */
void calcHist(IplImage *plane, Histogram &h, int dim);			// ����ͼ�����ֱ��ͼ
void dfsDirectory(char* dir, list<string> &listPath);			// ������ȱ����ļ���
void lineToFeature(char* line, list<string> &liststr);			// ����ȡ��������ת��Ϊһ����������
Image newQueryByFeedback(list<Image> feedback, Image query);	// ���ݷ���������β�ѯͼ��
list<Image>::iterator getImage(list<Image> images, int index);	// ��ȡͼ����б�ĳ��λ�õĵ�����

#endif
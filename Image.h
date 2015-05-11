#ifndef __IMAGE__H_
#define __IMAGE__H_

#include <string>
#include "Feature.h"
using namespace std;

/*
 * ͼ��(�ļ�)��
 */
class Image {
private:
	char path[200];		// ͼ��·��
	Feature feature;	// ͼ������

public:
	Image();
	Image(char* p);
	~Image();
	char* getPath();						// ��ȡͼ��·��
	Feature getFeature();					// ��ȡͼ������
	void setPath(string p);					// ����·��
	void setFeature(Histogram features[]);	// ��������
	void showImage();						// ��ʾͼ��
	bool calcColorFeature();				// ������ɫ����
	bool calcShapeFeature();				// ������״����
	bool calcFeature();						// ��������
};

#endif
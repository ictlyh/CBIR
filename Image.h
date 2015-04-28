#ifndef __IMAGE__H_
#define __IMAGE__H_

#include "Feature.h"

/*
 * ͼ��(�ļ�)��
 */
class Image {
private:
	char* path;			// ͼ��·��
	Feature feature;	// ͼ������

public:
	Image(char* p);
	char* getPath();			// ��ȡͼ��·��
	void showImage();			// ��ʾͼ��
	void calcColorFeature();	// ������ɫ����
	void calcShapeFeature();	// ������״����
	void calcFeature();			// ��������
};

#endif
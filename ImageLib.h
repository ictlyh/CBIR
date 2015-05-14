#ifndef __IMAGELIB__H_
#define __IMAGELIB__H_

#include <list>
#include <cstdio>
#include <fstream>
#include "Image.h"

using namespace std;

/*
 * ͼ�����
 */
class ImageLib {
private:
	char libDir[256];	// ͼ��ⶥ���ļ�������
	char libFile[256];	// ͼ���������ļ�����
	list<Image> imageList;	// ͼ������

public:
	ImageLib(char* dir, char* file);
	ImageLib(char* dir);
	ImageLib();
	~ImageLib();

	char* getLibDir();	// ��ȡͼ����ļ�������
	char* getLibFile();	// ��ȡͼ���������ļ�����
	list<Image> getImageList();	// ��ȡͼ������
	void setLibDir(char* dir);	// ����ͼ����ļ�������
	void setLibFile(char* file);	// ����ͼ���������ļ�����
	void buildImageLib();		// ����ͼ��������
	bool loadImageLib();		// ��ͼ���������ļ�����ͼ��������
	bool saveImageLib();		// ����ͼ�������⵽ͼ���������ļ�
};

#endif

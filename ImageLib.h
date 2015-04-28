#ifndef __IMAGELIB__H_
#define __IMAGELIB__H_

#include <list>
#include "Image.h"

/*
 * ͼ�����
 */
class ImageLib {
private:
	char* libDir;			// ͼ��ⶥ���ļ�������
	char* libFile;			// ͼ���������ļ�����
	list<Image> imageList;	// ͼ������

public:
	ImageLib(char* dir, char* lib);
	ImageLib(char* dir);

	char* getLibDir();				// ��ȡͼ����ļ�������
	char* getLibFile();				// ��ȡͼ���������ļ�����
	void setLibDir(char* dir);		// ����ͼ����ļ�������
	void setLibFile(char* file);	// ����ͼ���������ļ�����
	void buildImageLib();			// ����ͼ��������
	void loadImageLib();			// ��ͼ���������ļ�����ͼ��������
	void saveImageLib();			// ����ͼ�������⵽ͼ���������ļ�
};

#endif
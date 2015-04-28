#ifndef __SEARCHER__H_
#define __SEARCHER__H_

#include <list>
#include "Image.h"
#include "ImageLib.h"

/*
 * ������
 */
class Searcher {
private:
	char* queryImage;		// ����ͼ��·��
	ImageLib imageLib;		// ͼ��������
public:
	list<Image> search();							// ͼ�����
	list<Image> reSearch(list<Image>  feedback);	// ����ͼ�����
};

#endif
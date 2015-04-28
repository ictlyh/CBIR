#ifndef __SEARCHER__H_
#define __SEARCHER__H_

#include <list>
#include "Image.h"
#include "ImageLib.h"

/*
 * 搜索类
 */
class Searcher {
private:
	char* queryImage;		// 检索图像路径
	ImageLib imageLib;		// 图像特征库
public:
	list<Image> search();							// 图像检索
	list<Image> reSearch(list<Image>  feedback);	// 二次图像检索
};

#endif
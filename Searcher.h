#ifndef __SEARCHER__H_
#define __SEARCHER__H_

#include <list>
#include "Image.h"
#include "ImageLib.h"

/*
 * 搜索类
 */
class Searcher {
public:
	list<Image> search(Image query, ImageLib imageLib, int k = 8);								// 图像检索
	list<Image> reSearch(Image query, list<Image>  feedback, ImageLib imageLib, int k = 8);		// 二次图像检索
};

#endif
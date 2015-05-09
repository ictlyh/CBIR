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
	list<Image> search(Image img, ImageLib imageLib);					// 图像检索
	list<Image> reSearch(list<Image>  feedback, ImageLib imageLib);	// 二次图像检索
};

#endif
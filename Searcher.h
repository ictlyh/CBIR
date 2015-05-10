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
	int TopK;
public:
	Searcher();
	Searcher(int k);
	~Searcher();
	void setTopK(int k);
	int getTopK();
	list<string> search(Image query, ImageLib imageLib);							// 图像检索
	list<string> reSearch(Image query, list<string>  feedback, ImageLib imageLib);	// 二次图像检索
};

#endif
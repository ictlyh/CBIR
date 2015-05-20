#ifndef __SEARCHER__H_
#define __SEARCHER__H_

#include <list>
#include "Image.h"
#include "ImageLib.h"
#include "Similarity.h"
/*
 * 搜索类
 */
class Searcher {
private:
	int TopK;
	Similarity similarity;
public:
	Searcher();
	Searcher(int k);
	~Searcher();
	void setTopK(int k);		    // 设置 TopK
	int getTopK();			    // 获取 TopK
	void setColorWeight(float weight);  // 设置颜色权重
	void setShapeWeight(float weight);  // 设置形状权重
	float getColorWeight();		    // 获取颜色权重
	float getShapeWeight();		    // 获取形状权重
	list<string> search(Image query, ImageLib imageLib);	// 图像检索
	list<string> reSearch(Image query, list<string>  feedback, ImageLib imageLib);	// 二次图像检索
};

#endif

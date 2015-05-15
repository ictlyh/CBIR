#ifndef __SEARCHER__H_
#define __SEARCHER__H_

#include <list>
#include "Image.h"
#include "ImageLib.h"
#include "Similarity.h"
/*
 * ������
 */
class Searcher {
private:
	int TopK;
	Similarity similarity;
public:
	Searcher();
	Searcher(int k);
	~Searcher();
	void setTopK(int k);
	int getTopK();
	void setColorWeight(float weight);
	void setShapeWeight(float weight);
	float getColorWeight();
	float getShapeWeight();
	list<string> search(Image query, ImageLib imageLib);							// ͼ�����
	list<string> reSearch(Image query, list<string>  feedback, ImageLib imageLib);	// ����ͼ�����
};

#endif

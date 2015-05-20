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
	void setTopK(int k);		    // ���� TopK
	int getTopK();			    // ��ȡ TopK
	void setColorWeight(float weight);  // ������ɫȨ��
	void setShapeWeight(float weight);  // ������״Ȩ��
	float getColorWeight();		    // ��ȡ��ɫȨ��
	float getShapeWeight();		    // ��ȡ��״Ȩ��
	list<string> search(Image query, ImageLib imageLib);	// ͼ�����
	list<string> reSearch(Image query, list<string>  feedback, ImageLib imageLib);	// ����ͼ�����
};

#endif

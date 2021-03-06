#include "Searcher.h"
#include "Similarity.h"
#include "methods.h"

Searcher::Searcher()
{
	TopK = 8;
}

Searcher::Searcher(int k)
{
	TopK = k;
}

Searcher::~Searcher()
{
}

void Searcher::setTopK(int k)
{
	TopK = k;
}

int Searcher::getTopK()
{
	return TopK;
}

void Searcher::setColorWeight(float weight)
{
  similarity.setColorWeight(weight);
}

void Searcher::setShapeWeight(float weight)
{
  similarity.setShapeWeight(weight);
}

float Searcher::getColorWeight()
{
  return similarity.getColorWeight();
}

float Searcher::getShapeWeight()
{
  return similarity.getShapeWeight();
}

list<string> Searcher::search(Image query, ImageLib imgLib)
{
	list<string> result;
	list<Image> images = imgLib.getImageList();

	// 用于保存图像库中每个图像和查询图像的相似度
	float *sim = (float*)malloc(sizeof(float) * images.size());
	// 计算图像库中每个图像和查询图像的相似度
	list<Image>::iterator ite = images.begin();
	for(int i = 0; i < images.size() && ite != images.end(); i++, ite++)
	{
		sim[i] = similarity.similarity(query, *ite);
	}
	// 获取相似度最高的K个图像
	// 由于K一般远远小于图像库中图像数目，故不需要进行全排序，只需要用选择排序选择最大的K个即可
	bool *topK = (bool*)malloc(sizeof(bool) * images.size());
	for(int i = 0; i < images.size(); i++)
		topK[i] = false;
	
	// 获取第 i 相关的图片
	for(int i = 0; i < TopK; i++)
	{
		float max = 0.0;
		int index = -1;
		for(int j = 0; j < images.size(); j++)
		{
			if(sim[j] > max && topK[j] == false)
			{
				max = sim[j];
				index = j;
			}
		}
		// 图像库数目小于 TopK
		if(index == -1)
		  break ;
		topK[index] = true;
		string str = getImagePath(images, index);
		if(str.length() != 0)
			result.push_back(str);
	}
	return result;
}

list<string> Searcher::reSearch(Image query, list<string> feedback, ImageLib imageLib)
{
	Image newQuery = newQueryByFeedback(feedback, query);
	return search(newQuery, imageLib);
}

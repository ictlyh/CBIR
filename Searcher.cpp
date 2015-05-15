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

	// ���ڱ���ͼ�����ÿ��ͼ��Ͳ�ѯͼ������ƶ�
	float *sim = (float*)malloc(sizeof(float) * images.size());
	// ����ͼ�����ÿ��ͼ��Ͳ�ѯͼ������ƶ�
	list<Image>::iterator ite = images.begin();
	for(int i = 0; i < images.size() && ite != images.end(); i++, ite++)
	{
		sim[i] = similarity.similarity(query, *ite);
	}
	// ��ȡ���ƶ���ߵ�K��ͼ��
	// ����Kһ��ԶԶС��ͼ�����ͼ����Ŀ���ʲ���Ҫ����ȫ����ֻ��Ҫ��ѡ������ѡ������K������
	bool *topK = (bool*)malloc(sizeof(bool) * images.size());
	for(int i = 0; i < images.size(); i++)
		topK[i] = false;
	
	// ��ȡ�� i ��ص�ͼƬ
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
		// ͼ�����ĿС�� TopK
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

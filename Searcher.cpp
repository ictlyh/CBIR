#include "Searcher.h"
#include "Similarity.h"
#include "methods.h"

list<Image> Searcher::search(Image query, ImageLib imgLib, int k = 8)
{
	list<Image> result;
	list<Image> images = imgLib.getImageList();
	Similarity similarity;
	float *sim = (float*)malloc(sizeof(float) * images.size());
	list<Image>::iterator ite = images.begin();
	for(int i = 0; i < images.size() && ite != images.end(); i++, ite++)
	{
		sim[i] = similarity.similarity(query, *ite);
	}
	// sort the sim values and get top K
	bool *topK = (bool*)malloc(sizeof(bool) * images.size());
	for(int i = 0; i < images.size(); i++)
		topK[i] = false;
	// 获取第 i 相关的图片
	for(int i = 0; i < k; i++)
	{
		float max = 0.0;
		int index = 0;
		for(int j = 0; j < images.size(); j++)
		{
			if(sim[j] > max && topK[j] == false)
			{
				max = sim[j];
				index = j;
			}
		}
		topK[index] = true;
		list<Image>::iterator ite = getImage(images, index);
		if(ite != images.end())
		{
			/*Image tmp = *ite;
			image img(tmp.getpath());
			colorfeature tmpcolor = tmp.getfeature().getcolorfeature();
			shapefeature tmpshape = tmp.getfeature().getshapefeature();
			histogram features[] = { tmpcolor.geth(), tmpcolor.gets(), tmpcolor.getv(),
				tmpcolor.getgray(), tmpshape.gethorizontal(), tmpshape.getvertical() };
			img.setfeature(features);
			free(features);*/
			result.push_back(*ite);
		}
	}
	return result;
}

list<Image> Searcher::reSearch(list<Image> feedback, ImageLib imageLib, int k = 8)
{
	Image query = newQueryByFeedback(feedback);
	return search(query, imageLib);
}
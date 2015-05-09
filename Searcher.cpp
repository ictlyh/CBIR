#include "Searcher.h"
#include "Similarity.h"
#include "methods.h"

list<Image> Searcher::search(Image query, ImageLib imgLib)
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
	return result;
}

list<Image> Searcher::reSearch(list<Image> feedback, ImageLib imageLib)
{
	Image query = newQueryByFeedback(feedback);
	return search(query, imageLib);
}
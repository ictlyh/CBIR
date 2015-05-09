#include "Searcher.h"
#include "ImageLib.h"

int main()
{
	ImageLib imageLib("Image Lib Directory here");
	imageLib.buildImageLib();
	//imageLib.loadImageLib();
	char queryImage[] = "path to query image";
	Image query(queryImage);
	query.calcFeature();

	Searcher searcher;
	list<Image> result = searcher.search(query, imageLib);
	return 0;
}
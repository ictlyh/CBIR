#ifndef __SEARCHER__H_
#define __SEARCHER__H_

#include <list>
#include "Image.h"
#include "ImageLib.h"

class Searcher {
private:
	char* queryImage;
	ImageLib imageLib;
public:
	list<Image> search();
	list<Image> reSearch(list<Image>  feedback);
};

#endif
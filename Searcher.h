#ifndef __SEARCHER__H_
#define __SEARCHER__H_

#include <list>
#include "Image.h"
#include "ImageLib.h"

/*
 * ËÑË÷Àà
 */
class Searcher {
private:
	char* queryImage;		// ¼ìË÷Í¼ÏñÂ·¾¶
	ImageLib imageLib;		// Í¼ÏñÌØÕ÷¿â
public:
	list<Image> search();							// Í¼Ïñ¼ìË÷
	list<Image> reSearch(list<Image>  feedback);	// ¶ş´ÎÍ¼Ïñ¼ìË÷
};

#endif
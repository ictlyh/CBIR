#ifndef __IMAGELIB__H_
#define __IMAGELIB__H_

#include <list>
#include "Image.h"

class ImageLib {
private:
	char* libDir;
	char* libFile;
	list<Image> imageList;

public:
	ImageLib(char* dir, char* lib);
	ImageLib(char* dir);

	char* getLibDir();
	char* getLibFile();
	void setLibDir(char* dir);
	void setLibFile(char* file);
	void buildImageLib();
	void loadImageLib();
	void saveImageLib();
};

#endif
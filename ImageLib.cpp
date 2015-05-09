#include "ImageLib.h"
#include "methods.h"

ImageLib::ImageLib(char* dir, char* file)
{
	libDir = dir;
	libFile = file;
}

ImageLib::ImageLib(char* dir)
{
	libDir = dir;
	libFile = "imagefeaturelib.txt";
}

char* ImageLib::getLibDir()
{
	return libDir;
}

char* ImageLib::getLibFile()
{
	return libFile;
}

list<Image> ImageLib::getImageList()
{
	return imageList;
}

void ImageLib::setLibDir(char* dir)
{
	libDir = dir;
}

void ImageLib::setLibFile(char* file)
{
	libFile = file;
}

void ImageLib::buildImageLib()
{
	imageList.clear();
	list<string> files;
	dfsDirectory(libDir, files);
	while(!files.empty())
	{
		Image img(files.front);
		files.pop_front();
		img.calcFeature();
		imageList.push_back(img);
	}
}


void ImageLib::loadImageLib()
{
}

void ImageLib::saveImageLib()
{
}
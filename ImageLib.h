#ifndef __IMAGELIB__H_
#define __IMAGELIB__H_

#include <list>
#include "Image.h"

/*
 * 图像库类
 */
class ImageLib {
private:
	char* libDir;			// 图像库顶层文件夹名称
	char* libFile;			// 图像特征库文件名称
	list<Image> imageList;	// 图像链表

public:
	ImageLib(char* dir, char* lib);
	ImageLib(char* dir);

	char* getLibDir();				// 获取图像库文件夹名称
	char* getLibFile();				// 获取图像特征库文件名称
	void setLibDir(char* dir);		// 设置图像库文件夹名称
	void setLibFile(char* file);	// 设置图像特征库文件名称
	void buildImageLib();			// 构建图像特征库
	void loadImageLib();			// 从图像特征库文件加载图像特征库
	void saveImageLib();			// 保存图像特征库到图像特征库文件
};

#endif
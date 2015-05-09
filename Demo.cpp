#include "Searcher.h"
#include "ImageLib.h"

int main()
{
	// 从文件夹中构造图像库
	ImageLib imageLib("Image Lib Directory here");
	imageLib.buildImageLib();
	// 如果已有图像库特征数据，直接从特征库文件读入
	//imageLib.loadImageLib();

	// 构造查询图像
	char queryImage[] = "path to query image";
	Image query(queryImage);
	query.calcFeature();

	// 构造查询器
	Searcher searcher;
	list<Image> result = searcher.search(query, imageLib);
	// 根据用户反馈进行二次查询
	list<Image> feedback;
	list<Image> reResult = searcher.reSearch(feedback,imageLib);
	return 0;
}
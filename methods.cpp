#include "methods.h"

void calcHist(IplImage *plane, Histogram &h, int dim)
{
	h.setDim(dim);
	int width = plane->width;
	int height = plane->height;
	int step = plane->widthStep;
	uchar * data = (uchar * )plane->imageData;
	// 统计每个值的数量
	for(int i = 0; i < height; i ++ )
	{
		int tmp = i * step;
		for(int j = 0; j < width; j ++ )
		{
			h.setFeature(data[tmp + j], h.getFeature(data[tmp + j]) + 1);
		}
	}

	// 归一化直方图
	int tmp = width * height;
	for(int i = 0; i < h.getDim(); i++)
	{
		h.setFeature(i, h.getFeature(i) / tmp);
	}

	// 转换为累加直方图
	for(int i = 1; i < h.getDim(); i++)
	{
		h.setFeature(i, h.getFeature(i - 1) + h.getFeature(i));
	}
}

void dfsDirectory(char* dir, list<string> &listPath)
{
	char szFile[MAX_PATH] = {0};
	char szFind[MAX_PATH];
	char root[MAX_PATH];

	WIN32_FIND_DATA FindFileData;
	strcpy(szFind,dir);
	strcat(szFind,"\\*.*");
	HANDLE hFind = FindFirstFile(szFind,&FindFileData);

	if(INVALID_HANDLE_VALUE == hFind)
		return ;
	while(TRUE)
	{
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(FindFileData.cFileName[0]!='.')
			{
				strcpy(szFile,dir);
				strcat(szFile,"\\");
				strcat(szFile,FindFileData.cFileName);
				dfsDirectory(szFile, listPath);
			}
		}
		else
		{
			// 只处理 .jpg 文件
			string tmp(FindFileData.cFileName);
			if(strcmp(tmp.substr(tmp.length() - 4, 4).c_str(), ".jpg") == 0)
			{
				strcpy(root, dir);
				strcat(root, "\\");
				strcat(root,FindFileData.cFileName);
				listPath.push_back(root);
			}
		}
		if(!FindNextFile(hFind,&FindFileData))
			break;
	}
	FindClose(hFind);
}

void lineToFeature(char* line, list<string> &liststr)
{
	liststr.clear();
	stringstream ss(line);
	string buf;
	while(ss >> buf)
	{
		liststr.push_back(buf);
	}
}

/*
 * 根据反馈生成二次查询图像
 * 现在是将原查询和反馈图像进行平均，也可以通过调整颜色和形状权重获得新的查询图像
 */
Image newQueryByFeedback(list<string> feedbacks, Image query)
{
	list<Image> feedback;
	for(list<string>::iterator ite = feedbacks.begin(); ite != feedbacks.end(); ite++)
	{
		Image tmp;
		tmp.setPath(*ite);
		tmp.calcFeature();
		feedback.push_back(tmp);
	}
	// 实例化二次查询图像
	Image img;
	//Histogram h, s, v, gray, horizontal, vertical;
	Histogram features[6];

	int size = (int)feedback.size();

	// 设置二次查询图像各个特征的维数
	features[0].setDim(query.getFeature().getColorFeature().getH().getDim());
	features[1].setDim(query.getFeature().getColorFeature().getS().getDim());
	features[2].setDim(query.getFeature().getColorFeature().getV().getDim());
	features[3].setDim(query.getFeature().getColorFeature().getGray().getDim());
	features[4].setDim(query.getFeature().getShapeFeature().getHorizontal().getDim());
	features[5].setDim(query.getFeature().getShapeFeature().getVertical().getDim());

	ColorFeature queryColor = query.getFeature().getColorFeature();
	ShapeFeature queryShape = query.getFeature().getShapeFeature();

	// 分配用于保存各个特征每个位置累加和的空间并初始化
	float *hSum = (float*)malloc(sizeof(float) * features[0].getDim());
	float *sSum = (float*)malloc(sizeof(float) * features[1].getDim());
	float *vSum = (float*)malloc(sizeof(float) * features[2].getDim());
	float *graySum = (float*)malloc(sizeof(float) * features[3].getDim());
	float *horiSum = (float*)malloc(sizeof(float) * features[4].getDim());
	float *vertiSum = (float*)malloc(sizeof(float) * features[5].getDim());
	for(int i = 0; i < features[0].getDim(); i++)
		hSum[i] = 0;
	for(int i = 0; i < features[1].getDim(); i++)
	{
		sSum[i] = 0;
		vSum[i] = 0;
		graySum[i] = 0;
	}		
	for(int i = 0; i < features[4].getDim(); i++)
	{
		horiSum[i] = 0;
		vertiSum[i] = 0;
	}
	
	// 对反馈图像的每个特征的每个位置累加求和
	for(list<Image>::iterator ite = feedback.begin(); ite != feedback.end(); ite++)
	{
		Image tmp = *ite;

		// 获取一幅反馈图像的各个分量的特征数组
		float *hValues = tmp.getFeature().getColorFeature().getH().getFeature();
		float *sValues = tmp.getFeature().getColorFeature().getS().getFeature();
		float *vValues = tmp.getFeature().getColorFeature().getV().getFeature();
		float *grayValues = tmp.getFeature().getColorFeature().getGray().getFeature();
		float *horivalues = tmp.getFeature().getShapeFeature().getHorizontal().getFeature();
		float *vertiValues = tmp.getFeature().getShapeFeature().getVertical().getFeature();

		// 对每个特征的各个位置累加求和
		for(int i = 0; i < features[0].getDim(); i++)
			hSum[i] += hValues[i];
		for(int i = 0; i < features[1].getDim(); i++)
			sSum[i] += sValues[i];
		for(int i = 0; i < features[2].getDim(); i++)
			vSum[i] += vValues[i];
		for(int i = 0; i < features[3].getDim(); i++)
			graySum[i] += grayValues[i];
		for(int i = 0; i < features[4].getDim(); i++)
			horiSum[i] += horivalues[i];
		for(int i = 0; i < features[5].getDim(); i++)
			vertiSum[i] += vertiValues[i];
	}
	// 对每个特征的各个位置进行平均获得二次查询图像的特征
	for(int i = 0; i < features[0].getDim(); i++)
		features[0].setFeature(i, (hSum[i] + queryColor.getH().getFeature(i)) / (size + 1));
	for(int i = 0; i < features[1].getDim(); i++)
		features[1].setFeature(i, (sSum[i] + queryColor.getS().getFeature(i)) / (size + 1));
	for(int i = 0; i < features[2].getDim(); i++)
		features[2].setFeature(i, (vSum[i] + queryColor.getV().getFeature(i)) / (size + 1));
	for(int i = 0; i < features[3].getDim(); i++)
		features[3].setFeature(i, (graySum[i] + queryColor.getGray().getFeature(i)) / (size + 1));
	for(int i = 0; i < features[4].getDim(); i++)
		features[4].setFeature(i, (horiSum[i] + queryShape.getHorizontal().getFeature(i)) / (size + 1));
	for(int i = 0; i < features[5].getDim(); i++)
		features[5].setFeature(i, (vertiSum[i] + queryShape.getVertical().getFeature(i)) / (size + 1));

	// 设置二次查询图像的特征
	img.setFeature(features);
	return img;
}

string getImagePath(list<Image> images, int index)
{
	list<Image>::iterator ite = images.begin();
	for(int i = 0; i < index && ite != images.end(); i++, ite++)
		;
	return ite->getPath();
}

void showHistogram(Histogram h)
{
	cout << "Dimension: " << h.getDim() << endl;
	for(int i = 0; i < h.getDim(); i++)
		cout << h.getFeature(i) << " ";
	cout << endl;
}
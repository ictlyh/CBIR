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
	_finddata_t FileInfo;
	char* strfind = (char*)malloc(sizeof(char) * (strlen(dir) + 3));
	strcpy(strfind, dir);
	strcat(strfind, "\\*");
	long Handle = _findfirst(strfind, &FileInfo);

	if (Handle == -1L)
	{
		cerr << "Can not match the folder path: " << dir << endl;
		exit(-1);
	}
	do{
		//判断是否有子目录
		if (FileInfo.attrib & _A_SUBDIR)    
		{
			// 判断是否为 . 和 ..
			if( (strcmp(FileInfo.name,".") != 0 ) &&(strcmp(FileInfo.name,"..") != 0))   
			{
				char* subdir = (char*) malloc (sizeof(char) * (strlen(dir) + 2 + strlen(FileInfo.name)));
				strcpy(subdir, dir);
				strcat(subdir, "\\");
				strcat(subdir, FileInfo.name);
				dfsDirectory(subdir, listPath);
				free(subdir);
			}
		}
		// 文件
		else
		{
			char* tmp = (char*) malloc (sizeof(char) * (strlen(dir) + 2 + strlen(FileInfo.name)));
			strcpy(tmp, dir);
			strcat(tmp, "\\");
			strcat(tmp, FileInfo.name);
			listPath.push_back(tmp);
			free(tmp);
		}
	}while (_findnext(Handle, &FileInfo) == 0);
	_findclose(Handle);
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
Image newQueryByFeedback(list<Image> feedback, Image query)
{
	// 实例化二次查询图像
	Image img("");
	Histogram h, s, v, gray, horizontal, vertical;
	Histogram features[] = { h, s, v, gray, horizontal, vertical };

	int size = feedback.size();

	// 设置二次查询图像各个特征的维数
	h.setDim(query.getFeature().getColorFeature().getH().getDim());
	s.setDim(query.getFeature().getColorFeature().getS().getDim());
	v.setDim(query.getFeature().getColorFeature().getV().getDim());
	gray.setDim(query.getFeature().getColorFeature().getGray().getDim());
	horizontal.setDim(query.getFeature().getShapeFeature().getHorizontal().getDim());
	vertical.setDim(query.getFeature().getShapeFeature().getVertical().getDim());

	ColorFeature queryColor = query.getFeature().getColorFeature();
	ShapeFeature queryShape = query.getFeature().getShapeFeature();

	// Initialize ??
	float *hSum = (float*)malloc(sizeof(float) * h.getDim());
	float *sSum = (float*)malloc(sizeof(float) * s.getDim());
	float *vSum = (float*)malloc(sizeof(float) * v.getDim());
	float *graySum = (float*)malloc(sizeof(float) * gray.getDim());
	float *horiSum = (float*)malloc(sizeof(float) * horizontal.getDim());
	float *vertiSum = (float*)malloc(sizeof(float) * vertical.getDim());
	
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
		for(int i = 0; i < h.getDim(); i++)
			hSum[i] += hValues[i];
		for(int i = 0; i < s.getDim(); i++)
			sSum[i] += sValues[i];
		for(int i = 0; i < v.getDim(); i++)
			vSum[i] += vValues[i];
		for(int i = 0; i < gray.getDim(); i++)
			graySum[i] += grayValues[i];
		for(int i = 0; i < horizontal.getDim(); i++)
			horiSum[i] += horivalues[i];
		for(int i = 0; i < vertical.getDim(); i++)
			vertiSum[i] += vertiValues[i];
	}
	// 对每个特征的各个位置进行平均获得二次查询图像的特征
	for(int i = 0; i < h.getDim(); i++)
		h.setFeature(i, (hSum[i] + queryColor.getH().getFeature(i)) / (h.getDim() + 1));
	for(int i = 0; i < s.getDim(); i++)
		s.setFeature(i, (sSum[i] + queryColor.getS().getFeature(i)) / (s.getDim() + 1));
	for(int i = 0; i < v.getDim(); i++)
		v.setFeature(i, (vSum[i] + queryColor.getV().getFeature(i)) / (v.getDim() + 1));
	for(int i = 0; i < gray.getDim(); i++)
		gray.setFeature(i, (graySum[i] + queryColor.getGray().getFeature(i)) / (gray.getDim() + 1));
	for(int i = 0; i < horizontal.getDim(); i++)
		horizontal.setFeature(i, (horiSum[i] + queryShape.getHorizontal().getFeature(i)) / (horizontal.getDim() + 1));
	for(int i = 0; i < vertical.getDim(); i++)
		vertical.setFeature(i, (vertiSum[i] + queryShape.getVertical().getFeature(i)) / (vertical.getDim() + 1));

	// 设置二次查询图像的特征
	img.setFeature(features);
	return img;
}

list<Image>::iterator getImage(list<Image> images, int index)
{
	list<Image>::iterator ite = images.begin();
	for(int i = 0; i < index && ite != images.end(); i++, ite++)
		;
	return ite;
}
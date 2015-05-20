#include "methods.h"

void calcHist(IplImage *plane, Histogram &h, int dim)
{
	h.setDim(dim);
	int width = plane->width;
	int height = plane->height;
	int step = plane->widthStep;
	uchar * data = (uchar * )plane->imageData;
	// ͳ��ÿ��ֵ������
	for(int i = 0; i < height; i ++ )
	{
		int tmp = i * step;
		for(int j = 0; j < width; j ++ )
		{
			h.setFeature(data[tmp + j], h.getFeature(data[tmp + j]) + 1);
		}
	}

	// ��һ��ֱ��ͼ
	int tmp = width * height;
	for(int i = 0; i < h.getDim(); i++)
	{
		h.setFeature(i, h.getFeature(i) / tmp);
	}

	// ת��Ϊ�ۼ�ֱ��ͼ
	for(int i = 1; i < h.getDim(); i++)
	{
		h.setFeature(i, h.getFeature(i - 1) + h.getFeature(i));
	}
}

void dfsDirectory(char* path, list<string> &listPath)
{
    //�ж�·���Ƿ����
    QDir dir(convertToQString(path));
    if(!dir.exists())
    {
          return;
    }
    //��ȡ��ѡ�ļ����͹�����
    QStringList filters;
    filters<< QString("*.jpeg") << QString("*.jpg") << QString("*.png") << QString("*.tiff") << QString("*.gif") << QString("*.bmp");
    //��������������ù�����
    QDirIterator dirIte(convertToQString(path), filters, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while(dirIte.hasNext())
    {
        dirIte.next();
        QFileInfo fileInfo = dirIte.fileInfo();
        QString absoluteFilePath = fileInfo.absoluteFilePath();
        listPath.push_back(convertToString(absoluteFilePath));
    }
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
 * ���ݷ������ɶ��β�ѯͼ��
 * �����ǽ�ԭ��ѯ�ͷ���ͼ�����ƽ����Ҳ����ͨ��������ɫ����״Ȩ�ػ���µĲ�ѯͼ��
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
	// ʵ�������β�ѯͼ��
	Image img;
	//Histogram h, s, v, gray, horizontal, vertical;
	Histogram features[6];

	int size = (int)feedback.size();

	// ���ö��β�ѯͼ�����������ά��
	features[0].setDim(query.getFeature().getColorFeature().getH().getDim());
	features[1].setDim(query.getFeature().getColorFeature().getS().getDim());
	features[2].setDim(query.getFeature().getColorFeature().getV().getDim());
	features[3].setDim(query.getFeature().getColorFeature().getGray().getDim());
	features[4].setDim(query.getFeature().getShapeFeature().getHorizontal().getDim());
	features[5].setDim(query.getFeature().getShapeFeature().getVertical().getDim());

	ColorFeature queryColor = query.getFeature().getColorFeature();
	ShapeFeature queryShape = query.getFeature().getShapeFeature();

	// �������ڱ����������ÿ��λ���ۼӺ͵Ŀռ䲢��ʼ��
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
	
	// �Է���ͼ���ÿ��������ÿ��λ���ۼ����
	for(list<Image>::iterator ite = feedback.begin(); ite != feedback.end(); ite++)
	{
		Image tmp = *ite;

		// ��ȡһ������ͼ��ĸ�����������������
		float *hValues = tmp.getFeature().getColorFeature().getH().getFeature();
		float *sValues = tmp.getFeature().getColorFeature().getS().getFeature();
		float *vValues = tmp.getFeature().getColorFeature().getV().getFeature();
		float *grayValues = tmp.getFeature().getColorFeature().getGray().getFeature();
		float *horivalues = tmp.getFeature().getShapeFeature().getHorizontal().getFeature();
		float *vertiValues = tmp.getFeature().getShapeFeature().getVertical().getFeature();

		// ��ÿ�������ĸ���λ���ۼ����
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
	// ��ÿ�������ĸ���λ�ý���ƽ����ö��β�ѯͼ�������
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

	// ���ö��β�ѯͼ�������
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

string convertToString(QString src)
{
    QString tmp(src);
    if(tmp.contains("/"))
      tmp.replace("/", "\\", Qt::CaseInsensitive);
    string str(tmp.toLocal8Bit().data());
    return str;
}

QString convertToQString(string src)
{
    QString tmp(QString::fromLocal8Bit(src.c_str()));
    if(tmp.contains("\\"))
      tmp.replace("\\", "/", Qt::CaseInsensitive);
    return tmp;
}

bool containsString(list<string> listString, string str)
{
  for(list<string>::iterator ite = listString.begin(); ite != listString.end(); ite++)
    {
      string tmp(*ite);
      if(strcmp(str.c_str(), tmp.c_str()) == 0)
        return true;
    }
  return false;
}

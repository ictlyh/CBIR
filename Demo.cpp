#include "Searcher.h"
#include "ImageLib.h"

int main()
{
	// ���ļ����й���ͼ���
	ImageLib imageLib("Image Lib Directory here");
	imageLib.buildImageLib();
	// �������ͼ����������ݣ�ֱ�Ӵ��������ļ�����
	//imageLib.loadImageLib();

	// �����ѯͼ��
	char queryImage[] = "path to query image";
	Image query(queryImage);
	query.calcFeature();

	// �����ѯ��
	Searcher searcher;
	list<Image> result = searcher.search(query, imageLib);
	// �����û��������ж��β�ѯ
	list<Image> feedback;
	list<Image> reResult = searcher.reSearch(feedback,imageLib);
	return 0;
}
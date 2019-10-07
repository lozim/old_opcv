// test6.cpp : �������̨Ӧ�ó������ڵ㡣
//

// test9.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <list>
#include <vector>


using namespace cv;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Mat input = imread("f:\\a38.tif");
	Mat origin = input.clone();//findcontours֮��ͼ���ı䣬��origin������ԭͼ��
	Mat rot_image;//��ת�����Ƭ��
	cvtColor(input, input, CV_BGR2GRAY);//ת���Ҷ�
	threshold(~input, input, 0, 255, THRESH_BINARY | THRESH_OTSU);//��ֵ��

	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	findContours(input, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_NONE);//������

	vector<Point> allpoint;
	for (int i = 0; i < contours.size(); i++)
	{
		for (int j = 0; j < contours[i].size(); j++)
			allpoint.push_back(contours[i][j]);

	}
	RotatedRect BoudingRect = minAreaRect(allpoint);//�����ĵ��������飬����Ӿ���

	Point2f center = BoudingRect.center;
	Mat rot_mat = getRotationMatrix2D(center, BoudingRect.angle, 1.0);//����ת����
	Size dst_sz(input.size());
	warpAffine(origin, rot_image, rot_mat, dst_sz);//����任��ԭͼ����ת
	Mat result1 = rot_image(Rect(center.x - (BoudingRect.size.width / 2), center.y - (BoudingRect.size.height / 2), BoudingRect.size.width, BoudingRect.size.height));//��ȡROI

	//���������ת���У�ϣ���ж��ĸ��ǵ�Ļ��ߣ��ж������ߵ�ֱ�ߣ�Ϊ����Ҫ�������ֳ��ĸ��ǵ������ֱ�ߡ�

	Mat temp = result1.clone();
	cvtColor(temp, temp, CV_BGR2GRAY);//ת���Ҷ�
	threshold(~temp, temp, 0, 255, THRESH_BINARY | THRESH_OTSU);//��ֵ��

	vector<vector<Point>> contours1;
	vector<Vec4i> hierachy1;
	findContours(temp, contours1, hierachy1, RETR_EXTERNAL, CHAIN_APPROX_NONE);//������

	
	vector<vector<Point>> coner(4);
	vector<vector<Point>> line(4);

	for (int i = 0; i < contours1[0].size(); i++)
	{
		if (contours1[0][i].x <= 4)
			line[0].push_back(contours1[0][i]);
		if (contours1[0][i].x <= 15 && contours1[0][i].y < 100)
			coner[0].push_back(contours1[0][i]);
		if (contours1[0][i].x <= 15 && contours1[0][i].y>100)
			coner[1].push_back(contours1[0][i]);
		if (contours1[0][i].x <= 239 && contours1[0][i].y < 100)
			line[1].push_back(contours1[0][i]);
		if (contours1[0][i].x <= 239 && contours1[0][i].y>100)
			line[2].push_back(contours1[0][i]);
		if (contours1[0][i].x <= 255 && contours1[0][i].y < 100)
			coner[2].push_back(contours1[0][i]);
		if (contours1[0][i].x <= 255 && contours1[0][i].y>100)
			coner[3].push_back(contours1[0][i]);
		if (contours1[0][i].x > 255)
			line[3].push_back(contours1[0][i]);

	}

	Mat test = Mat::zeros(result1.size(), result1.type());
	Scalar color = Scalar(0, 0, 255);
	drawContours(test, coner, 3, color, 1, 8);


	//for (int i = 0; i < contours1[0].size(); i++)
	//	cout << contours1[0][i] << endl;
	namedWindow("kk", CV_WINDOW_NORMAL);
	imshow("kk", test);
	waitKey(0);

}


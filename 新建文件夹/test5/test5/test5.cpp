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
	Mat input = imread("f:\\k2.bmp");
	if (input.empty())
	{
		cout << "cant read" << endl;
		int i;
		cin >> i;
		return -1;

	}
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
	//Mat result1 = rot_image(Rect(center.x - (BoudingRect.size.width / 2), center.y - (BoudingRect.size.height / 2), BoudingRect.size.width, BoudingRect.size.height));//��ȡROI

	/*namedWindow("kk", CV_WINDOW_NORMAL);
	imshow("kk", result1);
	waitKey(0);*/


}


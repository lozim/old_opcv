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
	Mat input = imread("f:\\15.tif");
	if (input.empty())
	{
		cout << "cant read";
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
		if (contourArea(contours[i],false)>20000)
		for (int j = 0; j < contours[i].size(); j++)
			allpoint.push_back(contours[i][j]);

	}
	RotatedRect BoudingRect = minAreaRect(allpoint);//�����ĵ��������飬����Ӿ���

	double boudingrect_height;
	double boudingrect_width;

	if (BoudingRect.size.width < BoudingRect.size.height)
	{
		boudingrect_height = BoudingRect.size.width;
		boudingrect_width = BoudingRect.size.height;
	}
	else 
	{	
		boudingrect_height = BoudingRect.size.height; 
		boudingrect_width=BoudingRect.size.width;
	}

	float angle;
	angle = BoudingRect.angle;
	if (angle < 0)
		angle += 90;
	



	Point2f center = BoudingRect.center;
	Mat rot_mat = getRotationMatrix2D(center, angle, 1.0);//����ת����
	Size dst_sz(input.size());
	warpAffine(origin, rot_image, rot_mat, dst_sz);//����任��ԭͼ����ת
	Mat result1 = rot_image(Rect(center.x - (boudingrect_width / 2)-10, center.y - (boudingrect_height / 2)-10, boudingrect_width+20, boudingrect_height+20));//��ȡROI


	namedWindow("kk", CV_WINDOW_NORMAL);
	imshow("kk", result1);
	waitKey(0);

	imwrite("15.jpg", result1);
	

}


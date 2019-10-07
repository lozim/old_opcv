// test6.cpp : 定义控制台应用程序的入口点。
//

// test9.cpp : 定义控制台应用程序的入口点。
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

	Mat origin = input.clone();//findcontours之后图像会改变，用origin来保持原图。
	Mat rot_image;//旋转后的照片。
	cvtColor(input, input, CV_BGR2GRAY);//转换灰度
	threshold(~input, input, 0, 255, THRESH_BINARY | THRESH_OTSU);//二值化

	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	findContours(input, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_NONE);//找轮廓

	vector<Point> allpoint;
	for (int i = 0; i < contours.size(); i++)
	{
		if (contourArea(contours[i],false)>20000)
		for (int j = 0; j < contours[i].size(); j++)
			allpoint.push_back(contours[i][j]);

	}
	RotatedRect BoudingRect = minAreaRect(allpoint);//轮廓的点输入数组，求外接矩形

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
	Mat rot_mat = getRotationMatrix2D(center, angle, 1.0);//求旋转矩阵
	Size dst_sz(input.size());
	warpAffine(origin, rot_image, rot_mat, dst_sz);//仿射变换，原图像旋转
	Mat result1 = rot_image(Rect(center.x - (boudingrect_width / 2)-10, center.y - (boudingrect_height / 2)-10, boudingrect_width+20, boudingrect_height+20));//提取ROI


	namedWindow("kk", CV_WINDOW_NORMAL);
	imshow("kk", result1);
	waitKey(0);

	imwrite("15.jpg", result1);
	

}


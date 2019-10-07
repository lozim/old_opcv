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
	Mat input = imread("f:\\a38.tif");
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
		for (int j = 0; j < contours[i].size(); j++)
			allpoint.push_back(contours[i][j]);

	}
	RotatedRect BoudingRect = minAreaRect(allpoint);//轮廓的点输入数组，求外接矩形

	Point2f center = BoudingRect.center;
	Mat rot_mat = getRotationMatrix2D(center, BoudingRect.angle, 1.0);//求旋转矩阵
	Size dst_sz(input.size());
	warpAffine(origin, rot_image, rot_mat, dst_sz);//仿射变换，原图像旋转
	Mat result1 = rot_image(Rect(center.x - (BoudingRect.size.width / 2), center.y - (BoudingRect.size.height / 2), BoudingRect.size.width, BoudingRect.size.height));//提取ROI

	//至此完成旋转裁切，希望判断四个角点的弧线，判断四条边的直线，为此需要将轮廓分成四个角点和四条直线。

	Mat temp = result1.clone();
	cvtColor(temp, temp, CV_BGR2GRAY);//转换灰度
	threshold(~temp, temp, 0, 255, THRESH_BINARY | THRESH_OTSU);//二值化

	vector<vector<Point>> contours1;
	vector<Vec4i> hierachy1;
	findContours(temp, contours1, hierachy1, RETR_EXTERNAL, CHAIN_APPROX_NONE);//找轮廓

	
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


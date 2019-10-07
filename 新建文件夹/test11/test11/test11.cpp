// test11.cpp : 定义控制台应用程序的入口点。
//

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

//Mat temp;
//int value = 1;

int _tmain(int argc, _TCHAR* argv[])
{

	Mat input = imread("f:\\a25.tif");
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

	Mat kkl = result1.clone();

	//sdf

	Mat left;
	Mat middle;
	Mat right;
	
	Scalar color = Scalar(0, 0, 255);

	left = result1(Rect(10, 30, 70, 160));
	right = result1(Rect(174, 30, 80, 160));
	middle = result1(Rect(84, 22, 87, 150));

	Mat left_show = left.clone();
	Mat middle_show = middle.clone();
	Mat right_show = right.clone();

	medianBlur(middle, middle, 3);
	medianBlur(middle, middle, 3);
	//Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	//filter2D(middle, middle, CV_8UC3, kernel);
	cvtColor(middle, middle, CV_BGR2GRAY);
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	erode(middle, middle, element);
	//threshold(middle, middle, 0, 255, CV_THRESH_OTSU | THRESH_BINARY);
	Mat gray_imag;//这个要保留
	Canny(middle, gray_imag, 43, 43 * 2, 3, false);

	vector<vector<Point>> contours_middle;
	vector<Vec4i> hierachy_middle;
	findContours(gray_imag, contours_middle, hierachy_middle, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(middle_show, contours_middle, -1, color, 1, 8);
	

	//left
	cvtColor(left, left, CV_BGR2GRAY);
	//threshold(left, left, 0, 255, CV_THRESH_OTSU | THRESH_BINARY);
	Canny(left, gray_imag, 208, 208 * 2, 3, false);

	vector<vector<Point>> contours_left;
	vector<Vec4i> hierachy_left;
	findContours(gray_imag, contours_left, hierachy_left, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(left_show, contours_left, 2, color, 1, 8);
	drawContours(left_show, contours_left, 3, color, 1, 8);

	//right
	cvtColor(right, right, CV_BGR2GRAY);
	erode(right, right,element);
	//threshold(left, left, 0, 255, CV_THRESH_OTSU | THRESH_BINARY);
	Canny(right, gray_imag, 180, 180 * 2, 3, false);

	vector<vector<Point>> contours_right;
	vector<Vec4i> hierachy_right;
	findContours(gray_imag, contours_right, hierachy_right, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(right_show, contours_right, 3, color, 1, 8);
	drawContours(right_show, contours_right, 4, color, 1, 8);
	drawContours(right_show, contours_right, 5, color, 1, 8);
	drawContours(right_show, contours_right, 6, color, 1, 8);
	drawContours(right_show, contours_right, 7, color, 1, 8);
	drawContours(right_show, contours_right, 8, color, 1, 8);
			
	




	namedWindow("origin", CV_WINDOW_NORMAL);
	imshow("origin", kkl);
	namedWindow("left_show", CV_WINDOW_NORMAL);
	imshow("left_show", left_show);
	namedWindow("middle_show", CV_WINDOW_NORMAL);
	imshow("middle_show", middle_show);
	namedWindow("right_show", CV_WINDOW_NORMAL);
	imshow("right_show", right_show);
	waitKey(0);


	//temp = left.clone();
	//void canny_demo(int, void*);
	//namedWindow("kk", CV_WINDOW_NORMAL);
	//int max_value = 255;

	//createTrackbar("sdfse", "kk", &value, max_value, canny_demo);
	//canny_demo(0, 0);

	//waitKey(0);
}


//void canny_demo(int, void*)
//{
//	Mat gray_imag;
//	Canny(temp, gray_imag, value, 2 * value, 3,false);
//
//	
//	imshow("kk", gray_imag);
//
//}


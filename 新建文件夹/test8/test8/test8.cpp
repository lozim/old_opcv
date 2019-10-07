// test8.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include <iostream>
#include <list>
#include <vector>

using namespace cv;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Mat input = imread("f:\\a38.tif");

	cvtColor(input, input, CV_BGR2GRAY);
	Mat draw = input.clone();

	namedWindow("show", CV_WINDOW_NORMAL);
	
	
	
	


	//to find the contours of input
	vector<vector<Point>> contours;
	vector <Vec4i> hierachy;

	findContours(input, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_NONE);


	Scalar color = Scalar(0, 0, 255);
	//drawContours(draw, contours, -1, color, 1, 8);
	Rect kk = Rect(50, 50, 100, 100);
	rectangle(draw, kk, color, 1, 8);
	

	namedWindow("drr", CV_WINDOW_NORMAL);
	imshow("drr", draw);

	imshow("show", input);
	waitKey(0);
}


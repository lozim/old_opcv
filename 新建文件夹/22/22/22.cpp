
#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <list>
#include <vector>


using namespace cv;
using namespace std;

int main(int argc, _TCHAR* argv[])
{
	Mat input;
	String name;
	cout << "请输入输入要检测图片的路径" << endl;;
	cin >> name;

	input = imread(name);
	if (input.empty())
	{
		cout << "can not read....";
		return -1;
	}
	Mat test;
	double start = getTickCount();
	test = input.clone();
	cvtColor(input, input, CV_BGR2GRAY);
	threshold(input, input, 0, 255, CV_THRESH_OTSU | THRESH_BINARY);

	//findcontours
	Mat dst;
	dst = input.clone();

	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	findContours(dst, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<Rect> boundRect(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		boundRect[i] = boundingRect(contours[i]);
	}
	Scalar color = Scalar(0, 0, 255);
	Scalar color2 = Scalar(255, 0, 0);
	rectangle(test, boundRect[0], color, 1, 8);
	rectangle(test, boundRect[1], color, 1, 8);

	drawContours(test, contours, -1, color2, 1, 8);
	
		double rate1 = contourArea(contours[0], false) / boundRect[0].area();
		cout << "左边的"  << "轮廓的面积占比率为%" << rate1 << endl;
		double rate2 = contourArea(contours[1], false) / boundRect[1].area();
		cout << "右边的" << "轮廓的面积占比率为%" << rate2 << endl;

	double end = getTickCount();
	double time = (end - start) / cvGetTickFrequency() / 1000000;
	cout << "运行时间为" << time << "秒" << endl;
	namedWindow("gg", CV_WINDOW_NORMAL);
	imshow("gg", test);
	/*namedWindow("input", CV_WINDOW_NORMAL);
	imshow("input", input);*/
	waitKey(0);
}
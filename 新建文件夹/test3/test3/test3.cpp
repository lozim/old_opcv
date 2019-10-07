// test3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include <iostream>
#include <list>


using namespace cv;
using namespace std;



int threshold_value = 127;
int threshold_max = 255;
Mat dog;
Mat dst;
int main(int argc, _TCHAR* argv[])
{
	void demo(int, void*);
	dog = imread("f:\\good.bmp");
	if (!dog.data)
	{
		cout << "could ";
		return-1;
	}
	namedWindow("input_image", CV_WINDOW_AUTOSIZE);
	namedWindow("output_image", CV_WINDOW_AUTOSIZE);

	imshow("input_image", dog);
	cvtColor(dog, dog, CV_BGR2GRAY);

	string title = "threshold value";
	createTrackbar(title, "output_image", &threshold_value, threshold_max, demo);
	demo(0, 0);
	waitKey(0);
	return 0;
}

void demo(int, void*)
{
	Mat canny_outpt;
	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;

	Canny(dog, canny_outpt, threshold_value, threshold_value * 2, 3, false);
	findContours(canny_outpt, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	Mat dst;
	dst = Mat::zeros(dog.size(), CV_8UC3);
	RNG rng(12345);
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dst, contours, i, color, 0.1, 8, hierachy, 0, Point(0, 0));
	}
	imshow("output_image", dst);

	printf("%.2f", contourArea(contours[0]));
	cout << endl;
	printf("%.2f", contourArea(contours[1]));




}

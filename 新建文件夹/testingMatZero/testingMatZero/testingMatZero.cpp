
#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <list>
#include <vector>


using namespace cv;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Mat input = imread("f:\\a25.jpg");
	cvtColor(input, input, CV_BGR2GRAY);
	
	for (int i = 0; i < input.rows;i++)
	for (int j = 0; j < input.cols; j++)
	{
		if (input.at<uchar>(i, j)>150)
			input.at<uchar>(i, j) = 0;

	}

	imwrite("f:\\outputa25.jpg", input);

	namedWindow("kk", CV_WINDOW_AUTOSIZE);
	imshow("kk", input);
	waitKey(0);

	
}


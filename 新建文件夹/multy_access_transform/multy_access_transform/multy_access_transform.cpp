// multy_access_transform.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include <math.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, _TCHAR* argv[])
{
	Mat dog = imread("f:\\dog.jpg");
	Mat dst;

	/*dst=Mat::zeros(dog.size(), dog.type());

	const float afa = 1.1;
	const float  beta = 30;
	for (int i = 0; i < dog.rows; i++)
	{
		for (int j = 0; j < dog.cols; j++)
		{
			int b = dog.at<Vec3b>(i, j)[0];
			int g = dog.at<Vec3b>(i, j)[1];
			int r = dog.at<Vec3b>(i, j)[2];

			dst.at<Vec3b>(i, j)[0] = saturate_cast<uchar> (afa*b + beta);
			dst.at<Vec3b>(i, j)[1] = saturate_cast<uchar> (afa*g + beta);
			dst.at<Vec3b>(i, j)[2] = saturate_cast<uchar> (afa*r + beta);
		}
	}
		imshow("original", dog);
		imshow("output", dst);
		waitKey(0);
*/

	Mat kernal = (Mat_<int>(3, 3) << 1,1,1,1,1,1,1,1,1);
	filter2D(dog, dst, -1, kernal, Point(-1, -1));
	imshow
		("sfddffdf", dog);
	imshow("ss", dst);
	waitKey(0);
}




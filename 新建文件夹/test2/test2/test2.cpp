// test2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <math.h>
#include <iostream>
#include <random>
#include <list>

using namespace cv;
using namespace std;


list<int> random;

int main(int argc, _TCHAR* argv[])
{
	void salt(Mat, int);
	Mat origin = imread("f:\\dog.jpg");if (origin.empty())
	{
		cout << "could not" << endl;
		return -1;
	}
	cvtColor(origin, origin, CV_BGR2GRAY);
	imshow("original", origin);

	/*salt(origin, 1000);*/

	waitKey(0);
	

	
}

//void salt(Mat input, int  count)
//{
//	for (int i = 0; i < count; i++)
//	{
//		int row = rand() % count + 1;
//		int 
//
//	}
//
//}
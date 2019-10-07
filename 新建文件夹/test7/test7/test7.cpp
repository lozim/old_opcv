//师弟最近要使用四旋翼进行桥梁探伤，主要是用运动相机搭载在四轴上检测裂缝，就顺便搞了一下有关于裂缝检测的图像处理。
//
//算法比较简单，没有考虑太多复杂情况，在简单墙面背景下基本可以找到裂缝并框定。
//
//基本思路为，先转换彩色图为灰度图，然后进行自适应局部阈值化，目的是为了减少光照与阴影对阈值的影响，然后进行膨胀操作，尽量放大凸显裂缝，在用中值滤波平滑一下，去除一些高频噪声。然后调用寻找轮廓函数寻找所有轮廓，寻找连通域最大的那个轮廓，然后在原图画框即可。
//
//先上算法代码，之后还有Qt界面加图像传输完整版。


#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <vector>
#include<time.h> 

using namespace cv;
using namespace std;

void location(Mat &srcImg, Mat &binImg)
{

	vector< vector<Point> > contours;
	if (binImg.data)
	{
		findContours(binImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	}

	if (contours.size() > 1)
	{
		double maxArea = 0;
		vector <Point> maxContour;
		for (size_t i = 0; i < contours.size(); i++)
		{
			double area = contourArea(contours[i]);
			if (area > maxArea)
			{
				maxArea = area;
				maxContour = contours[i];
			}
		}
		Rect maxRect;
		Mat ROI;
		if (maxContour.size() != 0)
		{
			maxRect = boundingRect(maxContour);
		}

		rectangle(srcImg, maxRect, cv::Scalar(0, 0, 255));
	}
}


void preProcessing(Mat &srcImg, Mat &binImg, int elementSize = 7)
{
	Mat grayImg;
	cvtColor(srcImg, grayImg, CV_RGB2GRAY);
	int blockSize = 25;
	int constValue = 35;
	adaptiveThreshold(grayImg, binImg, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, blockSize, constValue);
	//threshold(grayImg,binImg,150,255,THRESH_BINARY_INV);
	Mat element = getStructuringElement(MORPH_RECT, Size(elementSize, elementSize));
	dilate(binImg, binImg, element);
	medianBlur(binImg, binImg, 9);
}

int _tmain(int argc, _TCHAR* argv[])
{

	clock_t start, finish;
	double totaltime;
	start = clock();

	Mat srcImg = imread("f:\\a38.tif");

	Mat binImg;
	preProcessing(srcImg, binImg);
	imshow("binImg", binImg);
	location(srcImg, binImg);
	imshow("ansImg", srcImg);

	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "\n此程序的运行时间为" << totaltime << "秒！" << endl;
	//system("pause");

	waitKey();

	return 0;
}


// testingmatchshape.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <list>
#include <vector>


using namespace cv;
using namespace std;

//若点a大于点b,即点a在点b顺时针方向,返回true,否则返回false
bool PointCmp(const Point &a, const Point &b, const Point &center)
{
	if (a.x >= 0 && b.x < 0)
		return true;
	if (a.x == 0 && b.x == 0)
		return a.y > b.y;
	//向量OA和向量OB的叉积
	int det = (a.x - center.x) * (b.y - center.y) - (b.x - center.x) * (a.y - center.y);
	if (det < 0)
		return true;
	if (det > 0)
		return false;
	//向量OA和向量OB共线，以距离判断大小
	int d1 = (a.x - center.x) * (a.x - center.x) + (a.y - center.y) * (a.y - center.y);
	int d2 = (b.x - center.x) * (b.x - center.y) + (b.y - center.y) * (b.y - center.y);
	return d1 > d2;
}
void ClockwiseSortPoints(std::vector<Point> &vPoints)
{
	//计算重心
	cv::Point center;
	double x = 0, y = 0;
	for (int i = 0; i < vPoints.size(); i++)
	{
		x += vPoints[i].x;
		y += vPoints[i].y;
	}
	center.x = (int)x / vPoints.size();
	center.y = (int)y / vPoints.size();

	//冒泡排序
	for (int i = 0; i < vPoints.size() - 1; i++)
	{
		for (int j = 0; j < vPoints.size() - i - 1; j++)
		{
			if (PointCmp(vPoints[j], vPoints[j + 1], center))
			{
				cv::Point tmp = vPoints[j];
				vPoints[j] = vPoints[j + 1];
				vPoints[j + 1] = tmp;
			}
		}
	}
}




int _tmain(int argc, _TCHAR* argv[])
{
	Mat  input1 = imread("f:\\1.jpg");
	Mat  input2 = imread("f:\\3.jpg");
	Mat  input4 = imread("f:\\4.jpg");
	Mat  input10 = imread("f:\\10.jpg");
	Mat  input15 = imread("f:\\15.jpg");
	Mat origin1 = input1.clone();
	Mat origin2 = input2.clone();
	Mat empty1 = Mat::zeros(input1.size(), input1.type());
	Mat empty2 = Mat::zeros(input2.size(), input2.type());
	Mat empty4 = Mat::zeros(input4.size(), input4.type());
	Mat empty10 = Mat::zeros(input10.size(), input10.type());
	Mat empty15 = Mat::zeros(input15.size(), input15.type());
	

	Scalar color = Scalar(0, 0, 255);

	/*namedWindow("input1", CV_WINDOW_NORMAL);
	namedWindow("input2", CV_WINDOW_NORMAL);
	namedWindow("input4", CV_WINDOW_NORMAL);
	namedWindow("input10", CV_WINDOW_NORMAL);
	namedWindow("input15", CV_WINDOW_NORMAL);
	
	imshow("input1", input1);
	imshow("input2", input2);
	imshow("input4", input4);
	imshow("input10", input10);
	imshow("input15", input15);*/
	
	



	cvtColor(input1, input1, CV_BGR2GRAY);
	cvtColor(input2, input2, CV_BGR2GRAY);
	cvtColor(input4, input4, CV_BGR2GRAY);
	cvtColor(input10, input10, CV_BGR2GRAY);
	cvtColor(input15, input15, CV_BGR2GRAY);
	

	threshold(~input1, input1, 50, 255, CV_THRESH_BINARY);
	threshold(~input2, input2, 50, 255, CV_THRESH_BINARY);
	threshold(~input4, input4, 50, 255, CV_THRESH_BINARY);
	threshold(~input10, input10, 50, 255, CV_THRESH_BINARY);
	threshold(~input15, input15, 50, 255, CV_THRESH_BINARY);
	

	vector<vector<Point>> contour1;
	vector<Vec4i> hierachy1;
	findContours(input1, contour1,hierachy1, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(empty1, contour1, 1, color, 1, 8);

	vector<vector<Point>> contour2;
	vector<Vec4i> hierachy2;
	findContours(input2, contour2, hierachy2, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(empty2, contour2, 1, color, 1, 8);

	vector<vector<Point>> contour4;
	vector<Vec4i> hierachy4;
	findContours(input4, contour4, hierachy4, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(empty4, contour4, 2, color, 1, 8);

	/*vector<vector<Point>> contour10;
	vector<Vec4i> hierachy10;
	findContours(input10, contour10, hierachy10, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(empty10, contour10, -1, color, 1, 8);*/

	vector<vector<Point>> contour15;
	vector<Vec4i> hierachy15;
	findContours(input15, contour15, hierachy15, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(empty15, contour15, 1, color, 1, 8);


	double result1_2;
	double result1_4;
	double result1_15;
	double result2_4;
	double result2_15;
	double result4_15;

	/*cout << "1,2的相似系数为" << matchShapes(contour1[0], contour2[0], CV_CONTOURS_MATCH_I1, 0) << "（完全相同返回0，返回最大值是1）" << endl;
	cout << "1,4的相似系数为" << matchShapes(contour1[0], contour4[1], CV_CONTOURS_MATCH_I1, 0) << "（完全相同返回0，返回最大值是1）" << endl;
	cout << "1,15的相似系数为" << matchShapes(contour1[0], contour15[0], CV_CONTOURS_MATCH_I1, 0) << "（完全相同返回0，返回最大值是1）" << endl;
	cout << "2,4的相似系数为" << matchShapes(contour2[0], contour4[0], CV_CONTOURS_MATCH_I1, 0) << "（完全相同返回0，返回最大值是1）" << endl;
	cout << "2,15的相似系数为" << matchShapes(contour2[0], contour15[0], CV_CONTOURS_MATCH_I1, 0) << "（完全相同返回0，返回最大值是1）" << endl;
	cout << "4,15的相似系数为" << matchShapes(contour4[1], contour15[0], CV_CONTOURS_MATCH_I1, 0) << "（完全相同返回0，返回最大值是1）" << endl;
	*/


	

	int counter = 0;


	int Line_i[170];
	int Line_j[170];
	vector<Point> allcontour;

	for (int i = 0; i < contour1.size(); i++)
	for (int j = 0; j < contour1[i].size(); j++)
	{
		allcontour.push_back(contour1[i][j]);
	}

	ClockwiseSortPoints(allcontour);

	for (int i = 0; i <allcontour.size(); i++)
	
	{
		//cout << contour1[i][j] << endl;
		
		Line_i[counter] = allcontour[i].x;
		Line_j[counter] = allcontour[i].y;
		counter++;
	}
	cout << counter << endl;
	
	for (int i = 0; i < 170; i++)
		cout << Line_i[i] << endl;

	for (int i = 0; i < 170; i++)
		cout << Line_j[i] << endl;


int 	linenum = 170;
Scalar colorr = Scalar(255, 0, 0);

for (int i = 1; i < linenum; i++)
{
	namedWindow("output1", CV_WINDOW_NORMAL);
	//namedWindow("output2", CV_WINDOW_NORMAL);
	//namedWindow("output4", CV_WINDOW_NORMAL);
	////namedWindow("output10", CV_WINDOW_NORMAL);
	//namedWindow("output15", CV_WINDOW_NORMAL);
	imshow("output1", empty1);
	cvWaitKey(100);
	//imshow("output2", empty2);
	//imshow("output4", empty4);
	////imshow("output10", empty10);
	//imshow("output15", empty15);
	cvDestroyWindow("output1");
	circle(empty1, allcontour[i], 10, colorr, 1, 8);
}
	int qq = 5;
	int nn = 0;
	double * nnn = (double *)calloc(linenum - qq, sizeof(double));//平均值滤波后中轴点对倾角，相差5像素
	if (nnn == 0)
	{
		return 1;
	}
	for (int i = 0; i<linenum - qq; i++)
	{
		double xx1, yy1, xx2, yy2, k;
		double pi = 3.14159;
		yy1 = (double)Line_j[i]; xx1 = (double)Line_i[i];//20151020
		yy2 = (double)Line_j[i + qq]; xx2 = (double)Line_i[i + qq];//20151020

		if ((yy2 >= yy1) && (xx2 >= xx1))
			k = 180 * atan((yy2 - yy1) / (xx2 - xx1)) / pi;
		else if ((yy2 >= yy1) && (xx2 <= xx1))
			k = 180 - 180 * atan((yy2 - yy1) / (xx1 - xx2)) / pi;
		else if ((yy1 >= yy2) && (xx2 <= xx1))
			k = 180 + 180 * atan((yy1 - yy2) / (xx1 - xx2)) / pi;
		else if ((yy1 >= yy2) && (xx1 <= xx2))
			k = 360 - 180 * atan((yy1 - yy2) / (xx2 - xx1)) / pi;
		nnn[nn] = k;
		nn++;
	}


	

//	double **nnnn = xibobianhuan(nnn, linenum - qq);//atuous变换




	waitKey(0);
}




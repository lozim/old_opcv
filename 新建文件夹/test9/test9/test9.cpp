// test9.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <list>
#include <vector>


using namespace cv;
using namespace std;

int canny_low_value = 1;
int canny_max_value = 255;
Mat canny;
Mat edge;

int _tmain(int argc, _TCHAR* argv[])
{
	Mat input = imread("f:\\a38.tif");


	Mat con = input.clone();


	//1.boudingrect
	cvtColor(input, input, CV_BGR2GRAY);

	threshold(~input, input, 0, 255,  THRESH_BINARY|THRESH_OTSU);

	/*namedWindow("input", CV_WINDOW_NORMAL);
	imshow("input", input);*/

	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;

	findContours(input, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	
	vector<Point> allpoint;
	for (int i = 0; i < contours.size(); i++)
	{
		for (int j = 0; j < contours[i].size(); j++)
			allpoint.push_back(contours[i][j]);
		
	}
	RotatedRect kk = minAreaRect(allpoint);

	


	Scalar color = Scalar(255, 0, 0);
	

	/*Point2f cooo[4];
	kk.points(cooo);
	vector<Point> coo;
	for (int i = 0; i < 4; i++)
	{
		coo.push_back(cooo[i]);
	}
	vector<vector<Point>> cl;
	cl.push_back(coo);
	drawContours(con, cl,-1, color, 1, 8);*/

	




	Point2f center = kk.center;
	Mat rot_mat = getRotationMatrix2D(center, kk.angle, 1.0);//求旋转矩阵
	Mat rot_image;
	Size dst_sz(input.size());
	warpAffine(con, rot_image, rot_mat, dst_sz);//原图像旋转
	//imshow("rot_image", rot_image);
	Mat result1 = rot_image(Rect(center.x - (kk.size.width / 2)+30, center.y - (kk.size.height / 2)+30, kk.size.width-50, kk.size.height-50));//提取ROI
	//imshow("result", result1);

	Mat color_cut;
	color_cut = result1.clone();

	namedWindow("origin", CV_WINDOW_NORMAL);
	imshow("origin", result1);

	cvtColor(result1, result1, CV_BGR2GRAY);

	








	//至此终于完成了图像的旋转与分割

	Mat copy;
	copy = result1.clone();
	
	Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(copy, copy,CV_8UC3,kernel);

	

	medianBlur(copy, copy, 3);
	medianBlur(copy, copy, 3);
	
	//medianBlur(copy, copy, 3);
	//GaussianBlur(copy, copy, Size(3,3),0,0);
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	//erode(copy, copy, element);

	
	morphologyEx(copy, copy,MORPH_BLACKHAT, element);


	/*Mat binary_edge;
	Canny(copy, binary_edge, 46, 1.5 * 46, 3, true);
	namedWindow("binary_edge", CV_WINDOW_NORMAL);
	imshow("binary_edge", binary_edge);

	vector<vector<Point>> edege_contours;
	vector<Vec4i> edege_hierachy;
	findContours(binary_edge, edege_contours, edege_hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(color_cut, edege_contours, -1, color, 1, 8);
	namedWindow("color_cut", CV_WINDOW_NORMAL);
	imshow("color_cut", color_cut);*/



	
	//threshold(copy, copy, 0, 255, THRESH_OTSU);
	namedWindow("output", CV_WINDOW_NORMAL);
	imshow("output", copy);

	/*canny = copy;
	namedWindow("canny", CV_WINDOW_NORMAL);
	void canny_demo(int, void*);


	createTrackbar("canny_value", "canny", &canny_low_value, canny_max_value, canny_demo);
	canny_demo(0, 0);*/
	


	waitKey(0);


}

//void canny_demo(int, void*)
//{
//	Canny(canny, edge, canny_low_value, 1.5*canny_low_value, 3, true);
//
//	imshow("canny", edge);
//
//
//}
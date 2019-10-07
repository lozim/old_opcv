
#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <list>
#include <vector>


using namespace cv;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

	Scalar colorr = Scalar(255, 0, 0);
	Mat input = imread("f:\\a25.tif");
	Mat origin = input.clone();//findcontours֮��ͼ���ı䣬��origin������ԭͼ��
	Mat rot_image;//��ת�����Ƭ��
	Mat rect_rotate;
	cvtColor(input, input, CV_BGR2GRAY);//ת���Ҷ�
	threshold(~input, input, 0, 255, THRESH_BINARY | THRESH_OTSU);//��ֵ��

	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	findContours(input, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_NONE);//������


	//draw
	/*Scalar color = Scalar(0, 0, 255);
	drawContours(origin, contours, -1, color, 1, 8);

	namedWindow("output", CV_WINDOW_NORMAL);
	imshow("output", origin);
	waitKey(0);*/



	//������contourarea
	//judge the area of each contour

	

	vector<Point> need_points;
	for (int i = 0; i < contours.size(); i++)
	{
		if (contourArea(contours[i], false)>40000)
			for (int j = 0; j < contours[i].size(); j++)
				need_points.push_back(contours[i][j]);

	}
	RotatedRect BoudingRect = minAreaRect(need_points);//�����ĵ��������飬����Ӿ���


	//������arclength

	/*cout<<arcLength(contours[0], false);
	int i;
	cin >> i;*/

	Point2f ver[4];
	BoudingRect.points(ver);
	Mat origin_minarearect;
	origin_minarearect = Mat::zeros(origin.size(), origin.type());

	vector<Point> kkkiu;
	kkkiu.push_back(ver[0]);
	kkkiu.push_back(ver[1]);
	kkkiu.push_back(ver[2]);
	kkkiu.push_back(ver[3]);

	vector<vector<Point>> con_rotarect;
	con_rotarect.push_back(kkkiu);

	

	drawContours(origin_minarearect, con_rotarect, -1, colorr, 1, 8);
	

	

	Point2f center = BoudingRect.center;
	double angle = abs(  BoudingRect.angle);
	Mat rot_mat = getRotationMatrix2D(center, BoudingRect.angle,1.0);//����ת����



	/*Point2f dst[4];
	for (int i = 0; i < 4; i++)
	{
		int x = ver[i].x - center.x;
		int y = ver[i].y - center.y;

		dst[i].x = cvRound(x * cos(angle) + y * sin(angle) + center.x);
		dst[i].y = cvRound(-x * sin(angle) + y * cos(angle) + center.y);


	}*/

	//��ķ���任���֮��ʹ�ñ���ѭ���ķ�ʽ����ĸ������е���С����󣬻��Ƴɾ��Σ������������Ϊrote_mat��ROI

	/*int min, max;
	min = 0; max = 0;

	for (int i = 1; i < 4; i++)
	{
		if (dst[i].x >= dst[max].x&&dst[i].y >= dst[max].y)
			max = i;
		if (dst[i].x <= dst[min].x&&dst[i].y <= dst[min].y)
			min = i;

	}
*/
	
		

	//Rect temppp = Rect(Point(dst[min].x, dst[min].y), Point(dst[max].x, dst[max].y));



	Size dst_sz(input.size());
	warpAffine(origin, rot_image, rot_mat, dst_sz);//����任��ԭͼ����ת
	warpAffine(origin_minarearect, rect_rotate, rot_mat, dst_sz);

	cvtColor(rect_rotate, rect_rotate, CV_BGR2GRAY);
	vector<vector<Point>> contours_t;
	vector<Vec4i> hierachy_t;
	findContours(rect_rotate, contours_t, hierachy_t, RETR_EXTERNAL, CHAIN_APPROX_NONE);//������

	vector<Point> need_pointss;
	for (int i = 0; i < contours_t.size(); i++)
	{
		if (contourArea(contours_t[i], false)>20000)
		for (int j = 0; j < contours_t[i].size(); j++)
			need_pointss.push_back(contours_t[i][j]);

	}
	RotatedRect ROI_rect = minAreaRect(need_pointss);//�����ĵ��������飬����Ӿ���

	Point2f vert[4];
	ROI_rect.points(vert);


	int min, max;
	min = 0; max = 0;

	for (int i = 1; i < 4; i++)
	{
		if (vert[i].x >= vert[max].x&&vert[i].y >= vert[max].y)
			max = i;
		if (vert[i].x <= vert[min].x&&vert[i].y <= vert[min].y)
			min = i;

	}
	Rect temppp = Rect(Point(vert[min].x, vert[min].y), Point(vert[max].x, vert[max].y));

	Mat resulttt = rot_image(temppp);




	//Rect temppp = Rect((dst[0].x, dst[0].y), (dst[1].x, dst[1].y), (dst[2].x, dst[2].y), (dst[3].x, dst[3].y));
	//Rect temppp = Rect((ver[0].x, ver[0].y), (ver[1].x, ver[1].y), (ver[2].x, ver[2].y), (ver[3].x, ver[3].y));
	/*Rect temppp = Rect(Point(50, 50), Point(100, 100) );
	Rect tempp = Rect(50, 50, 50, 50);*/
	
	
	/*Scalar color = Scalar(0, 0, 255);
	rectangle(origin, temppp, colorr, 2, 8);
	rectangle(origin, tempp, color, 1, 8);*/

	/*circle(rot_image, dst[0], 10, colorr, 1, 8);
	circle(rot_image, dst[1], 10, colorr, 1, 8);
	circle(rot_image, dst[2], 10, colorr, 1, 8);
	circle(rot_image, dst[3], 10, colorr, 1, 8);*/
	


	//����ת�õ�ͼƬ�����ϵ㡣�����������У���Ϊ��ת���ͼƬ��ȥ��ֵ���Ľ�������ںڱߵ�Ӱ�쵼�£���ֵ���Ľ��������ת���ľ��Σ��÷������С�
	//Mat temp = rot_image.clone();
	//cvtColor(temp, temp, CV_BGR2GRAY);
	//threshold(temp, temp, 0, 255, THRESH_BINARY | THRESH_OTSU);
	//vector<vector<Point>> contours_t;
	//vector<Vec4i> hierachy_t;
	//findContours(temp, contours_t, hierachy_t, RETR_EXTERNAL, CHAIN_APPROX_NONE);//������
	//vector<Point> min_point;
	//for (int i = 0; i < contours_t.size(); i++)
	//{
	//	if (contourArea(contours_t[i], false)>40000)
	//	for (int j = 0; j < contours_t[i].size(); j++)
	//		min_point.push_back(contours_t[i][j]);

	//}
	//Rect kk = boundingRect(min_point);
	//Mat result1 = rot_image(kk);//��ȡROI


	/*cout << center.x << endl;
	cout << BoudingRect.size.width / 2 << endl;
	cout << center.y << endl;
	cout << BoudingRect.size.height / 2 << endl;
	cout << BoudingRect.size.width << endl;
	cout << BoudingRect.size.height << endl;
	int i;
	cin >> i;*/



	namedWindow("outpu", CV_WINDOW_NORMAL);
	imshow("outpu", resulttt);
	

	namedWindow("outputt",CV_WINDOW_AUTOSIZE);
	imshow("outputt", rect_rotate);

	namedWindow("output", CV_WINDOW_AUTOSIZE);
	imshow("output", rot_image);
	waitKey(0);

}


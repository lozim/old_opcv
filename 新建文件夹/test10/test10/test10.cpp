// test10.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int _tmain(int argc, _TCHAR* argv[])
{
	Mat *img_01 = new Mat(400, 400, CV_8UC3);
	Mat *img_02 = new Mat(400, 400, CV_8UC3);
	*img_01 = Scalar::all(0);
	*img_02 = Scalar::all(0);
	// ��������ɵ�����
	vector<Point> points_01, points_02;


	// �������鸳ֵ
	points_01.push_back(Point(10, 10)); points_01.push_back(Point(10, 390));
	points_01.push_back(Point(390, 390)); points_01.push_back(Point(150, 250));
	points_02.push_back(Point(10, 10)); points_02.push_back(Point(10, 390));
	points_02.push_back(Point(390, 390)); points_02.push_back(Point(250, 150));

	vector<int> hull_01, hull_02;
	// ����͹��
	convexHull(points_01, hull_01, true);
	convexHull(points_02, hull_02, true);

	// ��������
	for (int i = 0; i < 4; ++i)
	{
		circle(*img_01, points_01[i], 3, Scalar(0, 255, 255), CV_FILLED, CV_AA);
		circle(*img_02, points_02[i], 3, Scalar(0, 255, 255), CV_FILLED, CV_AA);
	}
	// ����͹������
	CvPoint poi_01 = points_01[hull_01[hull_01.size() - 1]];
	for (int i = 0; i < hull_01.size(); ++i)
	{
		line(*img_01, poi_01, points_01[i], Scalar(255, 255, 0), 1, CV_AA);
		poi_01 = points_01[i];
	}
	CvPoint poi_02 = points_02[hull_02[hull_02.size() - 1]];
	for (int i = 0; i < hull_02.size(); ++i)
	{
		line(*img_02, poi_02, points_02[i], Scalar(255, 255, 0), 1, CV_AA);
		poi_02 = points_02[i];
	}

	vector<Vec4i> defects;
	// �����͹ȱ�ݾͰ���������
	if (isContourConvex(points_01))
	{
		cout << "img_01��������͹��" << endl;
	}
	else{
		cout << "img_01����������͹��" << endl;
		convexityDefects(
			points_01,
			Mat(hull_01),
			defects
			);
		// ����ȱ��
		cout << "��" << defects.size() << "��ȱ��" << endl;
		for (int i = 0; i < defects.size(); ++i)
		{
			circle(*img_01, points_01[defects[i][0]], 6, Scalar(255, 0, 0), 2, CV_AA);
			circle(*img_01, points_01[defects[i][1]], 6, Scalar(255, 0, 0), 2, CV_AA);
			circle(*img_01, points_01[defects[i][2]], 6, Scalar(255, 0, 0), 2, CV_AA);
			line(*img_01, points_01[defects[i][0]], points_01[defects[i][1]], Scalar(255, 0, 0), 1, CV_AA);
			line(*img_01, points_01[defects[i][1]], points_01[defects[i][2]], Scalar(255, 0, 0), 1, CV_AA);
			line(*img_01, points_01[defects[i][2]], points_01[defects[i][0]], Scalar(255, 0, 0), 1, CV_AA);
			cout << "��" << i << "ȱ��<" << points_01[defects[i][0]].x << "," << points_01[defects[i][0]].y
				<< ">,<" << points_01[defects[i][1]].x << "," << points_01[defects[i][1]].y
				<< ">,<" << points_01[defects[i][2]].x << "," << points_01[defects[i][2]].y << ">�������ľ���Ϊ��" << defects[i][3] / 256 << "px" << endl;
		}
		defects.clear();
	}
	if (isContourConvex(points_02))
	{
		cout << "img_02��������͹��" << endl;
	}
	else{
		cout << "img_02����������͹��" << endl;
		vector<Vec4i> defects;
		convexityDefects(
			points_01,
			Mat(hull_01),
			defects
			);
		// ���Ƴ�ȱ�ݵ�����
		for (int i = 0; i < defects.size(); ++i)
		{
			circle(*img_02, points_01[defects[i][0]], 6, Scalar(255, 0, 0), 2, CV_AA);
			circle(*img_02, points_01[defects[i][1]], 6, Scalar(255, 0, 0), 2, CV_AA);
			circle(*img_02, points_01[defects[i][2]], 6, Scalar(255, 0, 0), 2, CV_AA);
			line(*img_02, points_01[defects[i][0]], points_01[defects[i][1]], Scalar(255, 0, 0), 1, CV_AA);
			line(*img_02, points_01[defects[i][1]], points_01[defects[i][2]], Scalar(255, 0, 0), 1, CV_AA);
			line(*img_02, points_01[defects[i][2]], points_01[defects[i][0]], Scalar(255, 0, 0), 1, CV_AA);
			// ��Ϊ img_02 û��ȱ�����Ծ�����д��Щ���������
		}
		defects.clear();
	}

	imshow("img_01 ��������͹����", *img_01);
	imshow("img_02 ��������͹����", *img_02);
	cvWaitKey();

	return 0;
}
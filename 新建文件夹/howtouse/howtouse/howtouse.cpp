// howtouse.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <math.h>
#include <iostream>
#include <random>
#include <list>

using namespace cv;
using namespace std;


list <int> random;

int main(int argc, _TCHAR* argv[])
{
	random.push_back(1);
	random.push_back(2);
	random.push_back(3);

	for (int i = 0; i < random.size(); i++)
	{
		cout << random[i] << endl;

	}
	

	int kk;
	cin >> kk;

}


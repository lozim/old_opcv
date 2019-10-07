// testpolyfit.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <list>
#include <vector>
#include <fstream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

	vector<int> kk;
	kk.push_back(1);
	kk.push_back(2);
	kk.push_back(3);
	kk.push_back(4);
	kk.push_back(5);
	kk.push_back(6);
	kk.push_back(7);
	kk.push_back(8);
	kk.push_back(9);
	kk.push_back(10);

	int insert = 5;//创建insert为要补的点的数量
	vector<int> beginning;
	vector<int> ending;
	for (int i = 0; i < insert; i++)
	{
		beginning.push_back(kk[i]);
		ending.push_back(kk[kk.size() - 1 - i]);

	}
	for (int i = 0; i < insert; i++)
	{
		kk.push_back(beginning[i]);
		kk.insert(kk.begin(), ending[i]);

	}

	for (int i = 0; i < kk.size(); i++)
	{
		cout << kk[i] << endl;

	}
	int i;
	cin >> i;
	
	ofstream outfile("eee.txt");

	outfile << "This is a Test12!";
	outfile.close();
	


}


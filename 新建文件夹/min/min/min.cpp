// min.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include<random>
#include<time.h>
using namespace std;





int _tmain(int argc, _TCHAR* argv[])
{
	int a = 10;
	int &b = a;
	int &c = a;

	b += 4;

	c += 10;

	cout << b << "ss" << c;



	int x;
	cin >> x;
}
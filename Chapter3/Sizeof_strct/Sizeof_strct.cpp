// Sizeof_strct.cpp : 定义控制台应用程序的入口点。
// CSAPP P239 Data alignment

#include "stdafx.h"
#include <iostream>
using namespace std;

struct P1
{
	int i;
	char c;
	int j;
	char d;
};

struct P2
{
	int i;
	char c;
	char d;
	long j;
};

struct P3
{
	short w[3];
	char c[3];
};

struct P4
{
	short w[5];
	char *c[3];
};

struct P5
{
	struct P3 a[2];
	struct P2 t;
};

void main()
{
	cout << "sizeof P1: " << sizeof(P1) << endl;
	cout << "sizeof P2: " << sizeof(P2) << endl;
	cout << "sizeof P3: " << sizeof(P3) << endl;
	cout << "sizeof P4: " << sizeof(P4) << endl;
	cout << "sizeof P5: " << sizeof(P5) << endl;

}
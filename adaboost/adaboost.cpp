// adaboost.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include "stdlib.h"
#include "irisprocess.h"

using namespace std;


int main()
{
	string name = "E:\\Project\\Github\\adaboost VS iris\\iris.csv";
	adaboost_trainer csv(name);
	//csv._output();
	csv.show();
	system("pause");
    return 0;
}


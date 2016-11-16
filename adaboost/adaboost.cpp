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
	//fstream open(name,ios::in);
	//if (!open.is_open()) {
	//	cerr << "File is not opened" << endl;
	//	return -1;
	//}
	//while (!open.eof()) {
	//	const int length = 50;
	//	char str[length];
	//	open.getline(str, length);
	//	cout << str << endl;
	//}
	//open.close();
	csv_process_for_iris csv(name);
	csv.Split();
	csv._output();
	system("pause");
    return 0;
}


// adaboost.cpp : �������̨Ӧ�ó������ڵ㡣
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
	csv_process_for_iris csv(name);
	csv.Split();
	csv._dataset_establish();
	csv._output();
	system("pause");
    return 0;
}


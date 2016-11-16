#pragma once
#ifndef __IRISPROCESS_H_
#define __IRISPROCESS_H_
#include <fstream>
#include <iostream>
#include <list>
#include <CString>
#include <string>
using namespace std;

struct _line {
	float _data[4];
	string _name;
};

class csv_process_for_iris {
//data:
private:
	fstream _file;//file
	list<_line> _data;
	bool FILE_READ_SUCCESS = false;
//initial
public:
	csv_process_for_iris(string &name);
	~csv_process_for_iris();
//function
	int Split(void);//²ð·ÖÊý¾Ý
	void splitcomma(string &_readline, _line &_tostr);
	void _output(void);
};

#endif
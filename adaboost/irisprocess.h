#pragma once
#ifndef __IRISPROCESS_H_
#define __IRISPROCESS_H_
#include <fstream>
#include <iostream>
#include <list>
#include <CString>
#include <string>
#include <map>
using namespace std;

//基本数据结构类型--------------------------------------------
struct _line {
	float _data[4];
	string _name;
};
struct _singlelist {
	float _data;
	string _name;
	bool operator <(const _singlelist& right) {
		return (_data < right._data);
	}//重载
};
void _linecpy(_line &_line1, _line &_line2);

//原始数据处理----------------------------------------------------------------
class csv_process_for_iris {
//data:
private:
	fstream _file;//file
	list<_line> _data;
	list<_line> _train;
	list<_line> _test;
	map<string, string> _map;
	bool FILE_READ_SUCCESS = false;
	int Split(void);//拆分数据
	void splitcomma(string &_readline, _line &_tostr);
	int _dataset_establish(void);//处理数据
public:
	csv_process_for_iris(string &name);//initial
	~csv_process_for_iris();
//function
	int _output(void);//输出处理好的数据，调试用
	//数据输出
	list<_line> _get_trained_data_established(void);//取训练数据
	list<_line> _get_test_data_established(void);//取测试集数据
	list<_singlelist> _get_a_list_of_element(int i=1);//取一列
	map<string, string> _get_the_map(void);//取map
};
//单个特征数据类----------------------------------------------
class _Eigen {
private:
	//数据项
	list<_singlelist> primitive_data;//原始数据
	list<_singlelist> data_on_use;//数据的各种处理都放在这里搞
	bool DATA_READ_SUCCESS=false;
	bool DATA_INITIALED = false;//bool变量
	//函数项
	void normalize(void);//归一化处理
	void data_on_use_initial(void);//数据初始化处理
	void _sort(void);//使用自带排序法
public:
	_Eigen(list<_singlelist> _list);
	//~_Eigen();
	void save(void);//输出成txt，调试用
	//数据输出
	list<_singlelist> _output_data_processed();//输出处理好的数据
};
//训练器类-------------------------
class adaboost_trainer: public csv_process_for_iris {
private:
	list<_Eigen> eigen;//特征数据
	list<list<float> >	weights;//权重
public:
	adaboost_trainer(string &name);//构造函数
	//~adaboost_trainer()
};


#endif
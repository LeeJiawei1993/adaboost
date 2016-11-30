#pragma once
#ifndef __IRISPROCESS_H_
#define __IRISPROCESS_H_
#include <fstream>
#include <iostream>
#include <list>
#include <CString>
#include <string>
#include <map>
#include <math.h>
using namespace std;

#define STEP 50;

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
	int get_size(void);
	//~_Eigen();
	void save(void);//输出成txt，调试用
	//数据输出
	list<_singlelist> _output_data_processed();//输出处理好的数据
};

//训练器类-------------------------
//针对一个类的权重与阈值、系数等的集合结构体，每个类别、每个特征都要用到
struct basic_classifier {
	list<float> 	weights;//权重
	list<int>		is_the_label;//此类的是非表
	list<float> threshold;//阈值
	list<float>	coefficient;//系数
	string _name;			//类别的名字
	//重载等号，用于赋值初始化
	basic_classifier& operator =(const basic_classifier &right) {
		weights = right.weights;
		threshold = right.threshold;
		is_the_label = right.is_the_label;
		coefficient = right.coefficient;
		_name = right._name;
		return *this;
	}
};
//简单分类器
//class weak
//
class adaboost_trainer: public csv_process_for_iris {
private:
	list<_Eigen> eigen;//特征数据
	list<list<basic_classifier>> single_classifier;//不同特征下有三个这样的分类器
	basic_classifier clfer;//测试用
	bool CLASS_INITIALIZED = false;
	//训练函数
	int single_train(_Eigen eg,int i=20);//训练单个特征，内有三类，所以有三个分类器，一次训练三个
	float highest_accureacy_value();
	//基本函数
	list<int > adaboost_trainer::is_the_label(_Eigen eg, string s);//是非表的建立
	int adaboost_trainer::single_train(_Eigen eg, int j, string s);
	basic_classifier adaboost_trainer::single_train_t(_Eigen eg, int j, string s);
	void adaboost_trainer::renew(_Eigen eg, basic_classifier &cfer);
public:
	adaboost_trainer(string &name);//构造函数
	void show(void);
	
	//~adaboost_trainer()
};


#endif
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

//�������ݽṹ����--------------------------------------------
struct _line {
	float _data[4];
	string _name;
};
struct _singlelist {
	float _data;
	string _name;
	bool operator <(const _singlelist& right) {
		return (_data < right._data);
	}//����
};
void _linecpy(_line &_line1, _line &_line2);

//ԭʼ���ݴ���----------------------------------------------------------------
class csv_process_for_iris {
//data:
private:
	fstream _file;//file
	list<_line> _data;
	list<_line> _train;
	list<_line> _test;
	map<string, string> _map;
	bool FILE_READ_SUCCESS = false;
	int Split(void);//�������
	void splitcomma(string &_readline, _line &_tostr);
	int _dataset_establish(void);//��������
public:
	csv_process_for_iris(string &name);//initial
	~csv_process_for_iris();
//function
	int _output(void);//�������õ����ݣ�������
	//�������
	list<_line> _get_trained_data_established(void);//ȡѵ������
	list<_line> _get_test_data_established(void);//ȡ���Լ�����
	list<_singlelist> _get_a_list_of_element(int i=1);//ȡһ��
	map<string, string> _get_the_map(void);//ȡmap
};

//��������������----------------------------------------------
class _Eigen {
private:
	//������
	list<_singlelist> primitive_data;//ԭʼ����
	list<_singlelist> data_on_use;//���ݵĸ��ִ������������
	bool DATA_READ_SUCCESS=false;
	bool DATA_INITIALED = false;//bool����
	//������
	void normalize(void);//��һ������
	void data_on_use_initial(void);//���ݳ�ʼ������
	void _sort(void);//ʹ���Դ�����
public:
	_Eigen(list<_singlelist> _list);
	int get_size(void);
	//~_Eigen();
	void save(void);//�����txt��������
	//�������
	list<_singlelist> _output_data_processed();//�������õ�����
};

//ѵ������-------------------------
//���һ�����Ȩ������ֵ��ϵ���ȵļ��Ͻṹ�壬ÿ�����ÿ��������Ҫ�õ�
struct basic_classifier {
	list<float> 	weights;//Ȩ��
	list<int>		is_the_label;//������ǷǱ�
	list<float> threshold;//��ֵ
	list<float>	coefficient;//ϵ��
	string _name;			//��������
	//���صȺţ����ڸ�ֵ��ʼ��
	basic_classifier& operator =(const basic_classifier &right) {
		weights = right.weights;
		threshold = right.threshold;
		is_the_label = right.is_the_label;
		coefficient = right.coefficient;
		_name = right._name;
		return *this;
	}
};
//�򵥷�����
//class weak
//
class adaboost_trainer: public csv_process_for_iris {
private:
	list<_Eigen> eigen;//��������
	list<list<basic_classifier>> single_classifier;//��ͬ�����������������ķ�����
	basic_classifier clfer;//������
	bool CLASS_INITIALIZED = false;
	//ѵ������
	int single_train(_Eigen eg,int i=20);//ѵ�������������������࣬������������������һ��ѵ������
	float highest_accureacy_value();
	//��������
	list<int > adaboost_trainer::is_the_label(_Eigen eg, string s);//�ǷǱ�Ľ���
	int adaboost_trainer::single_train(_Eigen eg, int j, string s);
	basic_classifier adaboost_trainer::single_train_t(_Eigen eg, int j, string s);
	void adaboost_trainer::renew(_Eigen eg, basic_classifier &cfer);
public:
	adaboost_trainer(string &name);//���캯��
	void show(void);
	
	//~adaboost_trainer()
};


#endif
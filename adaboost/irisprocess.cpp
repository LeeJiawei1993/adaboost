#include "stdafx.h"
#include "irisprocess.h"


void _linecpy(_line &_line2, _line &_line1) {
	for (int i = 0; i < 4; i++) {
		_line2._data[i] = _line1._data[i];
	}
	_line2._name = _line1._name;
}
csv_process_for_iris::csv_process_for_iris(string &name) {
	csv_process_for_iris::_file.open(name, ios::in);
	if (!_file.is_open()) {
		cerr << "Cannot open file!" << endl;
	}
	cout << "File is read success!" << endl;
	csv_process_for_iris::FILE_READ_SUCCESS = true;
	_dataset_establish();
}
csv_process_for_iris::~csv_process_for_iris() {
	csv_process_for_iris::_file.close();
}

void  csv_process_for_iris::splitcomma(string &_readline, _line &_readdata) {
	std::size_t spos=0, epos=0;
	int i = 0;
	while (1) {
		epos = _readline.find(',',spos);
		if (epos != string::npos&&i<4) {
			char str[10];
			strcpy_s(str, _readline.substr(spos, epos - spos).c_str());
			_readdata._data[i++] = atof(str);
			spos = epos + 1;
		}
		else {
			_readdata._name = _readline.substr(spos, _readline.size() - spos);
			break;
		}
	}
	cout << endl;
}
int csv_process_for_iris::Split() {
	if (!csv_process_for_iris::FILE_READ_SUCCESS) {
		cerr << "file is not read!" << endl;
		return -1;
	}
	const int length = 60;
	while (1) {
		char str[length];
		_line _tempread;
		_file.getline(str, length);
		if (csv_process_for_iris::_file.eof()) break;
		string STR = str;
		csv_process_for_iris::splitcomma(STR, _tempread);
		_data.push_back(_tempread);
	}
	return 0;
}
int  csv_process_for_iris::_output() {
	if (!csv_process_for_iris::FILE_READ_SUCCESS) {
		cerr << "file is not read!" << endl;
		return -1;
	}
	list<_line>::iterator it;
	int i = 0;
	for (it=csv_process_for_iris::_data.begin(); it!=csv_process_for_iris::_data.end(); it++) {
		cout << "line " << i << " :";
		for (int i = 0; i < 4; i++) {
			cout << it->_data[i] << '\t';
		}
		cout << it->_name << endl;
		i++;
	}
	map<string, string>::iterator it2;
	for (it2 = csv_process_for_iris::_map.begin(); it2 != csv_process_for_iris::_map.end(); it2++) {
		cout << it2->first << ":" << it2->second << endl;
	}
	return 0;
}
int csv_process_for_iris::_dataset_establish() {
	csv_process_for_iris::Split();
	if (!csv_process_for_iris::FILE_READ_SUCCESS) {
		cerr << "file is not read!" << endl;
		return -1;
	}
	if (csv_process_for_iris::_data.size() < 150) {
		cerr << "data seems not enough" << endl;
		return -1;
	}
	int i = 0;
	list<_line>::iterator it = csv_process_for_iris::_data.begin();
	for (i = 0; it !=_data.end(); i++,it++) {
		_line temp;
		_linecpy(temp, *it);
		if (i < 50 && i >=0) {
			if (i < 40) {
				temp._name.assign("1"); csv_process_for_iris::_train.push_back(temp); 
				_map.insert(pair<string, string>(temp._name, it->_name));
			}
			else {
				temp._name.assign("-1"); csv_process_for_iris::_test.push_back(temp);
			}
		}
		else if (i >= 50 && i < 100) {
			if (i < 90) {
				temp._name.assign("2"); csv_process_for_iris::_train.push_back(temp);
				_map.insert(pair<string, string>(temp._name, it->_name));
			}
			else {
				temp._name.assign("-1"); csv_process_for_iris::_test.push_back(temp);
			}
		}
		else{
			if (i < 140) {
				temp._name.assign("3"); csv_process_for_iris::_train.push_back(temp); 
				_map.insert(pair<string, string>(temp._name, it->_name));
			}
			else {
				temp._name.assign("-1"); csv_process_for_iris::_test.push_back(temp);
			}
		}
	}
	return 0;
}
list<_line>  csv_process_for_iris::_get_trained_data_established(void) {
	return csv_process_for_iris::_train;
}
list<_line>  csv_process_for_iris::_get_test_data_established(void) {
	return csv_process_for_iris::_test;
}
list<_singlelist> csv_process_for_iris::_get_a_list_of_element(int i) {
	if (i < size(csv_process_for_iris::_data.begin()->_data)) {
		cerr << "invalid data" << endl;
		exit;
	}
	list<_singlelist> _element;
	list<_line>::iterator it;
	for (it = csv_process_for_iris::_data.begin(); it != csv_process_for_iris::_data.end(); it++) {
		_singlelist ele;
		ele._data = it->_data[i - 1];
		ele._name = it->_name;
		_element.push_back(ele);
	}
	return _element;
}
map<string, string> csv_process_for_iris::_get_the_map(void) {
	return csv_process_for_iris::_map;
}

 _Eigen:: _Eigen(list<_singlelist> _list) {
	list<_singlelist>::iterator it;
	for (it = _list.begin(); it != _list.end(); it++) {
		 _Eigen::primitive_data.push_back(*it);
	}
	 _Eigen::DATA_READ_SUCCESS = true;
	 _Eigen::data_on_use_initial();
	 _Eigen::_sort();
	return;
}
void  _Eigen::data_on_use_initial(void) {
	if (!DATA_READ_SUCCESS) {
		cerr << "data is not read successfully!" << endl;
		return;
	}
	list<_singlelist>::iterator it;
	for (it =  _Eigen::primitive_data.begin(); it !=  _Eigen::primitive_data.end(); it++) {
		 _Eigen::data_on_use.push_back(*it);
	}
	 _Eigen::DATA_INITIALED = true;
	return;
}
void  _Eigen::_sort() {
	if (! _Eigen::DATA_INITIALED) {
		cerr << "data is not initialized!" << endl;
		return;
	}
	 _Eigen::data_on_use.sort();
	 _Eigen::normalize();
	int i = 0;
	list<_singlelist>::iterator it =  _Eigen::data_on_use.begin();
	cout.precision(2);
	cout.setf(ios::showpoint);
	for (; it !=  _Eigen::data_on_use.end(); it++) {
		cout << "the " << i << "th number: \t";
		cout << it->_data << '\t';
		cout << it->_name << endl;
		i++;
	}
	cout.precision(6);
	cout.unsetf(ios::showpoint);
	return;
}
void  _Eigen::normalize(void) {
	list<_singlelist>::iterator it =  _Eigen::data_on_use.begin();
	float maximum =  _Eigen::data_on_use.rbegin()->_data;
	for (; it !=  _Eigen::data_on_use.end(); it++) {
		float temp=it->_data/maximum;
		it->_data = temp;
	}
	return;
}
void  _Eigen::save(void) {
	ofstream save("output.txt");
	list<_singlelist>::iterator it =  _Eigen::primitive_data.begin();
	for (; it !=  _Eigen::primitive_data.end(); it++) {
		save << it->_data << '\t';
		save << it->_name << endl;
	}
	save.close();
}
list<_singlelist> _Eigen::_output_data_processed(void) {
	return _Eigen::data_on_use;
}
int _Eigen::get_size(void) {
	return _Eigen::primitive_data.size();
}

adaboost_trainer::adaboost_trainer(string &name):csv_process_for_iris(name){
	//_Eigen列表的建立
	int i = 1, j = _get_a_list_of_element().size();
	for (; i <= 4; i++) {
		_Eigen temp(_get_a_list_of_element(i));
		adaboost_trainer::eigen.push_back(temp);
	}
	adaboost_trainer::CLASS_INITIALIZED = true;
}
//返回最大准确率的分界值
//判断是否是这个标签的,返回一个数组List（真值表），表示是否属于这一类（1，-1）
list<int > adaboost_trainer::is_the_label(_Eigen eg,string s) {
	list<_singlelist> templist=eg._output_data_processed();
	list<int> is_in_the_group;
	list<_singlelist>::iterator it = templist.begin();
	for (; it != templist.end(); it++) {
		if (it->_name == s) {
			is_in_the_group.push_back(1);
		}
		else {
			is_in_the_group.push_back(-1);
		}
	}
	return is_in_the_group;
}
//函数：权值更新
void adaboost_trainer::renew(_Eigen eg,basic_classifier &cfer) {
	list<float> unique;//储存各个唯一的值
	list<_singlelist> lst = eg._output_data_processed();
	for (list<_singlelist>::iterator it=lst.begin(); it != lst.end();it++) {
		unique.push_back(it->_data);
	}//提取数据
	unique.unique();//让值不再重复
	list<float> weight_sum;
	for (list<float>::iterator it = unique.begin(); it != unique.end(); it++) {
		list<int>::iterator it1 = cfer.is_the_label.begin();
		list<float>::iterator it2 = cfer.weights.begin();//是非表，权重的正迭代器
		float wsum = 0;
		for (list<_singlelist>::iterator it3 = lst.begin(); it3 != lst.end(); it3++) {
			if(it3->_data<=*it){
				if (*it1 >0 ) {
					wsum += *it2;
				}
			}
			else {
				if (it3->_data < 0) {
					wsum += *it2;
				}
			}
			it2++;
			it1++;
		}
		weight_sum.push_back(wsum);
	}
	//这时应该得到一个正确率的list了，接下来取最大值以及相应的阈值
	list<float>::iterator it = unique.begin();
	float maxval = 0,thres = 0;//最大值(最大正确率)，阈值
	int x = 0;//位置偏移量
	for (list<float>::iterator p = weight_sum.begin();p!=weight_sum.end();p++) {
		if (*p > (maxval+0.001)) {
			maxval = *p;
			x++;
		}
	}
	for (; x >= 0; x--) {
		it++;
	}
	thres = *it;
	cfer.threshold.push_back(thres);//找到阈值并存入list
	float coef = 0.5*log(maxval / (1 - maxval));//系数
	cfer.coefficient.push_back(coef);//保存系数
	//更新权值分布
	//计算规范化因子
	float Z = 0.0;
	x = 0;
	list<_singlelist>::iterator it3 = lst.begin();
	list<int>::iterator it1 = cfer.is_the_label.begin();
	for (list<float>::iterator it = cfer.weights.begin(); it != cfer.weights.end(); it++) {
		float ygx = 0.0;
		if (it3->_data <= thres) {
			if (*it1 > 0)
				ygx = 1;
			else
				ygx = -1;
		}
		else {
			if (*it1 < 0)
				ygx = 1;
			else
				ygx = -1;
		}
		float j = -1 * coef*ygx;
		Z += (*it*exp(j));
		if (it1 != cfer.is_the_label.end())	it1++;
		if (it3 != lst.end())			it3++;
		x++;
	}
	//更新权值分布
	list<_singlelist>::iterator it4 = lst.begin();
	list<int>::iterator it5 = cfer.is_the_label.begin();
	for (list<float>::iterator it = cfer.weights.begin(); it != cfer.weights.end(); it++) {
		float ygx = 0.0;
		float val = 0.0;
		if (it4->_data <= thres) {
			if (*it5 > 0)
				ygx = 1;
			else
				ygx = -1;
		}
		else {
			if (*it5 < 0)
				ygx = 1;
			else
				ygx = -1;
		}
		float j = -1 * coef*ygx;
		*it = *it*exp(j) / Z;
		if (it5 != cfer.is_the_label.end())	it5++;
		if (it4 != lst.end())			it4++;
	}
}


basic_classifier adaboost_trainer::single_train_t(_Eigen eg,int j,string s){
	if (!adaboost_trainer::CLASS_INITIALIZED) {
		cerr << "calss adaboost_trainer is not initialized!" << endl;
	}
	int Arraysize = eg.get_size();//长度
	//权重初始化
	basic_classifier clfer;
	list<float> initial_weight(Arraysize,1.0/ Arraysize);
	clfer.weights = initial_weight;
	clfer.is_the_label = adaboost_trainer::is_the_label(eg, s);//是非表初始化
	//接下来开始训练
	for (int i = 0; i < j; i++) {
		adaboost_trainer::renew(eg,clfer);
	}
	return clfer;
}
void adaboost_trainer::show(void) {
	string s = "setosa";
	basic_classifier c;
	c=single_train_t(*eigen.begin(), 100, s);
	cout << "Type name:"<<'\t'<<c._name << endl;
	int i = 0;
	for (list<float>::iterator it11 = c.coefficient.begin(); it11 != c.coefficient.end(); it11++) {
		cout << "The " << i << " th coef:  " << *it11 << endl;
		i++;
	}
}
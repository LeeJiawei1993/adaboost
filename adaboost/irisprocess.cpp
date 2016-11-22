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

adaboost_trainer::adaboost_trainer(string &name):csv_process_for_iris(name){
	//_Eigen列表的建立以及权重初始化
	int i = 1, j = _get_a_list_of_element().size();
	list<float> initial_weight(j, 1.0 / j);
	for (; i <= 4; i++) {
		_Eigen temp(_get_a_list_of_element(i));
		adaboost_trainer::eigen.push_back(temp);
		adaboost_trainer::weights.push_back(initial_weight);
	}
}
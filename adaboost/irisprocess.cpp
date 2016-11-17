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
}
csv_process_for_iris::~csv_process_for_iris() {
	csv_process_for_iris::_file.close();
}

void  csv_process_for_iris::splitcomma(string &_readline, _line &_readdata) {
	char str[10];
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
	while (!csv_process_for_iris::_file.eof()) {
		char str[length];
		_line _tempread;
		_file.getline(str, length);
		string STR = str;
		csv_process_for_iris::splitcomma(STR, _tempread);
		_data.push_back(_tempread);
	}

}
int  csv_process_for_iris::_output() {
	if (!csv_process_for_iris::FILE_READ_SUCCESS) {
		cerr << "file is not read!" << endl;
		return -1;
	}
	list<_line>::iterator it;
	for (it=csv_process_for_iris::_data.begin(); it!=csv_process_for_iris::_data.end(); it++) {
		for (int i = 0; i < 4; i++) {
			cout << it->_data[i] << '\t';
		}
		cout << it->_name << endl;
	}
	return 0;
}
int csv_process_for_iris::_dataset_establish() {
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
			}
			else {
				temp._name.assign("-1"); csv_process_for_iris::_test.push_back(temp);
			}
		}
		else if (i >= 50 && i < 100) {
			if (i < 90) {
				temp._name.assign("2"); csv_process_for_iris::_train.push_back(temp);
			}
			else {
				temp._name.assign("-1"); csv_process_for_iris::_test.push_back(temp);
			}
		}
		else{
			if (i < 140) {
				temp._name.assign("3"); csv_process_for_iris::_train.push_back(temp);
			}
			else {
				temp._name.assign("-1"); csv_process_for_iris::_test.push_back(temp);
			}
		}
	}
	return 0;
}
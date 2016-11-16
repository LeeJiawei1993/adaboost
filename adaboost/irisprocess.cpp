#include "stdafx.h"
#include "irisprocess.h"

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
void  csv_process_for_iris::_output() {
	list<_line>::iterator it;
	for (it=csv_process_for_iris::_data.begin(); it!=csv_process_for_iris::_data.end(); it++) {
		for (int i = 0; i < 4; i++) {
			cout << it->_data[i] << '\t';
		}
		cout << it->_name << endl;
	}
}
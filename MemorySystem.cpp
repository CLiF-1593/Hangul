#include "MemorySystem.h"
#include <iostream>
using namespace std;

void Variable::SetDataSize(int size) {
	int cnt = size - (int)(this->data.size());
	for (int i = 0; i < cnt; i++) {
		this->data.insert(this->data.begin(), this->data.front());
	}
}

void Variable::FitDataSize() {
	bool d = this->data[0];
	while (this->data.size() > 1) {
		if (this->data[1] == d)
			this->data.erase(this->data.begin() + 1);
		else
			break;
	}
}

Variable::Variable() {
	this->data.clear();
	this->data.push_back(0);
}

Variable::Variable(long long int data) {
	int dat = abs(data);
	this->data.clear();
	this->data.push_back(0);
	while (dat) {
		this->data.insert(this->data.begin() + 1, dat % 2);
		dat /= 2;
	}
	if (data < 0) {
		bool change = false;
		for (int i = this->data.size() - 1; i >= 0; i--) {
			if (change) {
				this->data[i] = !this->data[i];
			}
			else if (this->data[i]) {
				change = true;
			}
		}
	}
}

Variable::Variable(const Variable& v) { 
	this->data = v.data;
}

Variable::Variable(CodeString data) {
	this->data.clear();
	for (int i = 0; i < data.size(); i++) {
		if (data[i] == '0') {
			this->data.push_back(false);
		}
		else if (data[i] == '1') {
			this->data.push_back(true);
		}
	}
}

Variable::Variable(string data) {
	this->data.clear();
	for (int i = 0; i < data.size(); i++) {
		if (data[i] == '0') {
			this->data.push_back(false);
		}
		else if (data[i] == '1') {
			this->data.push_back(true);
		}
	}
}

Variable Variable::operator=(const Variable& v) {
	this->data.clear();
	this->data = v.data;
	return *this;
}

Variable Variable::operator&(const Variable& v) {
	Variable var1 = v;
	Variable var2 = *this;
	var1.SetDataSize(this->data.size());
	var2.SetDataSize(v.data.size());
	for (int i = 0; i < var2.data.size(); i++) {
		var2.data[i] = var2.data[i] && var1.data[i];
	}
	var2.FitDataSize();
	return var2;
}

Variable Variable::operator|(const Variable& v) {
	Variable var1 = v;
	Variable var2 = *this;
	var1.SetDataSize(this->data.size());
	var2.SetDataSize(v.data.size());
	for (int i = 0; i < var2.data.size(); i++) {
		var2.data[i] = var2.data[i] || var1.data[i];
	}
	var2.FitDataSize();
	return var2;
}

Variable Variable::operator^(const Variable& v) {
	Variable var1 = v;
	Variable var2 = *this;
	var1.SetDataSize(this->data.size());
	var2.SetDataSize(v.data.size());
	for (int i = 0; i < var2.data.size(); i++) {
		var2.data[i] = !(var2.data[i] && var1.data[i]) && (var2.data[i] || var1.data[i]);
	}
	var2.FitDataSize();
	return var2;
}

Variable Variable::operator~() {
	Variable var = *this;
	for (int i = var.data.size() - 1; i >= 0; i--) {
		var.data[i] = !var.data[i];
	}
	return var;
}

Variable Variable::operator<<(const Variable& v) {
	bool change = false;
	Variable var = *this;
	for (int i = 0; i < v.GetDataToInteger(); i++) {
		var.data.push_back(var.data.front());
	}
	return var;
}

Variable Variable::operator>>(const Variable& v) {
	auto len = v.GetDataToInteger();
	bool change = false;
	Variable var = *this;
	var.SetDataSize(this->data.size());
	if (var.data.size() <= v.GetDataToInteger()) {
		var.data.clear();
		var.data.push_back(0);
	}
	else {
		for (int i = 0; i < v.GetDataToInteger(); i++) {
			var.data.pop_back();
		}
	}
	return var;
}



const long long int Variable::GetDataToInteger() const {
	long long int data = 0;
	bool sign = this->data.front();
	for (int i = 1; i < this->data.size(); i++) {
		data <<= 1;
		data += (this->data[i] ^ sign);
	}
	if (sign) {
		data *= -1;
		data -= 1;
	}
	return data;
}

const CodeString Variable::GetDataToCodeString() const {
	CodeString c;
	for (int i = 0; i < this->data.size(); i++) {
		if (this->data[i]) {
			c.push_back('1');
		}
		else {
			c.push_back('0');
		}
	}
	return c;
}

const bool Variable::GetBoolean() const {
	for (int i = 0; i < this->data.size(); i++) {
		if (this->data[i]) {
			return true;
		}
	}
	return false;
}

void Variable::PrintRaw() {
	for (int i = 0; i < this->data.size(); i++) {
		cout << this->data[i];
	}
	cout << endl;
}

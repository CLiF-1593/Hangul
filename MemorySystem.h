#pragma once
#include <vector>
#include "Code.h"
using namespace std;

class MemorySystem {

};

class Variable {
private:
	vector<bool> data;
	void SetDataSize(int size);
	void FitDataSize();

public:
	Variable();
	Variable(long long int data);
	Variable(const Variable &v);
	Variable(CodeString data);
	Variable(string data);
	Variable operator=(const Variable& v);
	Variable operator&(const Variable& v);
	Variable operator|(const Variable& v);
	Variable operator^(const Variable& v);
	Variable operator~();
	Variable operator<<(const Variable& v);
	Variable operator>>(const Variable& v);
	const long long int GetDataToInteger() const;
	const CodeString GetDataToCodeString() const;
	const bool GetBoolean() const;
	void PrintRaw();
};
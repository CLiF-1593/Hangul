#pragma once
#include <vector>
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
	Variable operator=(const Variable& v);
	Variable operator&(const Variable& v);
	Variable operator|(const Variable& v);
	Variable operator^(const Variable& v);
	Variable operator~();
	Variable operator<<(const Variable& v);
	Variable operator>>(const Variable& v);
	const long long int GetDataToInteger() const;
	void PrintRaw();
};

class Array {

};


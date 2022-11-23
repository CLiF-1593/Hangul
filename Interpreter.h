#pragma once
#include "Code.h"
#include "MemorySystem.h"

struct Value {
	Variable* var;
	bool memory;
};

class Interpreter {
private:
	map<CodeString, Variable> var;
	map<CodeString, vector<Variable>> lst;

	Value ExecuteLine(Command cmd, int &line);
	Value GetValue(Command& cmd, int &pos);
	void GetValueList(vector<Value> &var_list, Command& cmd);
	Value Function(Command& cmd, int &pos);
	Value Calculate(Command &cmd, vector<Value> &value_list);
	void Push(Command *left, Command *right, vector<Value> &value_list);
	void Goto(Command *cmp, Command* pos, vector<Value> &value_list, int goto_cnt, int& line);

public:
	void Execute(Code &code);
};
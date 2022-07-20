#include "Interpreter.h"
#include "MemorySystem.h"
#include "ErrorSystem.h"
#include <iostream>
#include <stack>
#include <cstdio>
#include <queue>

map<CodeString, int> oper_priority = {
	{L"<<", 0},
	{L">>", 0},
	{L"&", 1},
	{L"^", 1},
	{L"|", 1},
};

Value Interpreter::GetValue(Command& cmd, int pos) {
	int index = 0;
	switch (cmd[pos].type) {
	case VAR:
		return { &this->var[cmd[pos].data], true };
		break;
	case LST:
		if (pos < cmd.size() - 1) {
			InterpreterError(0);
		}
		else if (cmd[pos + 1].type == NUM) {
			index = Variable(cmd[pos + 1].data).GetDataToInteger();
		}
		else if (cmd[pos + 1].type == VAR || cmd[pos + 1].type == LST) {
			index = GetValue(cmd, pos + 1).var->GetDataToInteger();
		}
		else {
			InterpreterError(0);
		}
		return { &this->lst[cmd[pos].data][index], true };
	case NUM:
		Variable* var = new Variable(cmd[pos].data);
		return  { var, false };
	}
	return { nullptr, true };
}

Value Interpreter::Function(Command &cmd, int &pos) {
	vector<Command> parameter;
	Command part_cmd;
	if (pos + 2 >= cmd.size() || cmd[pos + 1].type != FTN_NAME) {
		InterpreterError(1);
	}

	CodeString name = cmd[pos + 1].data;
	bool ftn_err = true;

	for (int i = pos + 2; i < cmd.size(); i++) {
		if (cmd[i].type == FTN && cmd[i].data == L"F") {
			if (i + 1 < cmd.size() && cmd[i + 1].type == FTN_NAME) {
				Factor factor;
				factor.type = NUM;
				auto ftn = Function(cmd, i);
				factor.data = ftn.var->GetDataToCodeString();
				delete ftn.var;
				Command cmd;
				cmd.push_back(factor);
				parameter.push_back(cmd);
				continue;
			}
			else {
				pos = i;
				ftn_err = false;
				break;
			}
		}
		if (cmd[i].type == FTN && cmd[i].data == L"f") {
			if (!part_cmd.empty()) {
				parameter.push_back(part_cmd);
			}
			part_cmd.clear();
		}
		else {
			part_cmd.push_back(cmd[i]);
		}
	}
	if (ftn_err) {
		InterpreterError(2);
	}
	if (!part_cmd.empty()) {
		parameter.push_back(part_cmd);
	}

	//Print Parameter
	/*for (int i = 0; i < parameter.size(); i++) {
		cout << "par" << i << " : ";
		for (int j = 0; j < parameter[i].size(); j++) {
			wcout << "[" << parameter[i][j].type << ":" << parameter[i][j].data << "]";
		}
		cout << endl;
	}*/

	//Function Execute ...
	wstring loc = L"D:\\Development\\ProgrammingProject\\Tool\\Hangul\\ExternalFunctions\\PreFunctionSets\\";
	loc += name + L' ';
	for (int i = 0; i < parameter.size(); i++) {
		int line = 0;
		if (parameter[i].size() == 1 && parameter[i][0].type == LST) {
			loc += L'[';
			auto list = &this->lst[parameter[i][0].data];
			for (int j = 0; j < list->size(); j++) {
				if (j) {
					loc += L',';
				}
				loc+=(*list)[j].GetDataToCodeString();
			}
			loc += L']';
		}
		else {
			auto ret = this->ExecuteLine(parameter[i], line);
			loc += ret.var->GetDataToCodeString();
			if (!ret.memory) {
				delete ret.var;
			}
		}
		loc += L' ';
	}

	//wcout << loc;
	//_wsystem(loc.c_str());
	FILE* func;
	func = _wpopen(loc.c_str(), L"r");
	wstring output;
	while (!feof(func)) {
		output += (char)fgetc(func);
	}
	_pclose(func);

	wstring ret;
	int ret_pos = 0;
	for (int i = 0; i < output.size(); i++) {
		if (output[i] == L'\n') {
			ret.clear();
			ret_pos = i;
		}
		else {
			ret += output[i];
		}
	}
	output.erase(output.begin() + ret_pos, output.end());
	wcout << output;

	Value ret_v;
	ret_v.memory = false;
	ret_v.var = new Variable();
	wstring data;
	bool get_ret = false;
	ret += L" ";
	for (int i = 0; i < ret.size(); i++) {
		if (ret[i] == L' ') {
			if (!get_ret) {
				get_ret = true;
			*(ret_v.var) = data;
			}
			else if (data[0] == L'[') {
				vector<Variable> in;
				string s;
				for (int i = 1; i < data.size() - 1; i++) {
					if (data[i] == ',') {
						in.push_back(s);
						s.clear();
					}
					else {
						s += data[i];
					}
				}
			}
			else {

			}
		}
		else {
			data += ret[i];
		}
	}
	//wcout << ret_v.var->GetDataToCodeString() << endl;
	return ret_v;
}

void Interpreter::GetValueList(vector<Value> &var_list, Command& cmd) {
	Factor value;
	value.type = VAL;
	for (int i = 0; i < cmd.size(); i++) {
		int prev_i = -1;
		if (cmd[i].type == LST || cmd[i].type == VAR || cmd[i].type == NUM) {
			prev_i = i;
			value.data = to_wstring(var_list.size());
			var_list.push_back(this->GetValue(cmd, i));
		}
		else if (cmd[i].type == FTN) {
			prev_i = i;
			value.data = to_wstring(var_list.size());
			var_list.push_back(Function(cmd, i));
		}
		if (prev_i != -1) {
			cmd.erase(cmd.begin() + prev_i, cmd.begin() + i + 1);
			cmd.insert(cmd.begin() + prev_i, value);
			i = prev_i;
		}
	}
}

Value Calc(Variable* var1, Variable* var2, Factor &oper) {
	Variable* result = new Variable();
	Value put;
	put.memory = false;
	put.var = result;

	if (oper.data == L"&") {
		*result = *var1 & *var2;
	}
	else if (oper.data == L"|") {
		*result = *var1 | *var2;
	}
	else if (oper.data == L"^") {
		*result = *var1 ^ *var2;
	}
	else if (oper.data == L"<<") {
		*result = *var1 << *var2;
	}
	else if (oper.data == L">>") {
		*result = *var1 >> *var2;
	}

	//wcout << result->GetDataToInteger() << " = " << var1->GetDataToInteger() << " " << oper.data << " " << var2->GetDataToInteger() << endl;
	return put;
}

Value Interpreter::Calculate(Command& cmd, vector<Value>& value_list) {
	Value ret;

	stack<Factor> oper_stack; 
	stack<Value> calculate_stack;
	vector<Factor> postfix_exp;

	bool not_oper = false;

	for (int i = 0; i < cmd.size(); i++) {
		if (cmd[i].type == VAL) {
			auto var = value_list[stoi(cmd[i].data)];

			if (not_oper) {
				Value v;
				v.memory = false;
				v.var = new Variable;
				*v.var = ~(*var.var);
				if (!var.memory) {
					delete value_list[stoi(cmd[i].data)].var;
				}
				value_list[stoi(cmd[i].data)] = v;
				not_oper = false;
			}
			
			postfix_exp.push_back(cmd[i]);
		}
		else {
			if (cmd[i].data == L"~") {
				not_oper = !not_oper;
				continue;
			}
			if (!oper_stack.empty() && oper_priority[oper_stack.top().data] <= oper_priority[cmd[i].data]) {
				postfix_exp.push_back(oper_stack.top());
				oper_stack.pop();
				i--;
			}
			else {
				oper_stack.push(cmd[i]);
			}
		}
	}
	while (!oper_stack.empty()) {
		postfix_exp.push_back(oper_stack.top());
		oper_stack.pop();
	}

	//postfix expression
	/*for (int i = 0; i < postfix_exp.size(); i++) {
		wcout << postfix_exp[i].data;
	}
	cout << endl;*/

 	for (int i = 0; i < postfix_exp.size(); i++) {
		if (postfix_exp[i].type == VAL) {
			calculate_stack.push(value_list[stoi(postfix_exp[i].data)]);
		}
		else {
			if (calculate_stack.empty()) {
				InterpreterError(10);
			}
			auto var2 = calculate_stack.top();
			calculate_stack.pop();
			if (calculate_stack.empty()) {
				InterpreterError(10);
			}
			auto var1 = calculate_stack.top();
			calculate_stack.pop();

			auto put = Calc(var1.var, var2.var, postfix_exp[i]);

			value_list.push_back(put);
			calculate_stack.push(put);
		}
	}

	ret.memory = false;
	ret.var = new Variable(*calculate_stack.top().var);
	calculate_stack.pop();

	if (!calculate_stack.empty()) {
		InterpreterError(11);
	}
	return ret;
}

void Interpreter::Push(Command *left, Command *right, vector<Value>& value_list) {
	if (left->empty() || right->empty()) {
		InterpreterError(6);
	}
	else if (left->size() != 1 || (*left)[0].type != VAL || !value_list[stoi((*left)[0].data)].memory) {
		InterpreterError(7);
	}

	Value v = this->Calculate(*right, value_list);
	*(value_list[stoi((*left)[0].data)].var) = *(v.var);
	delete v.var;

}

void Interpreter::Goto(Command* cmp, Command* pos, vector<Value>& value_list, int goto_cnt, int &line) {
	if (pos->empty()) {
		bool go = true;
		if (!cmp->empty()) {
			go = false;
			Value v = this->Calculate(*cmp, value_list);
			if (v.var->GetBoolean()) {
				go = true;
			}
		}
		if (go) {
			line -= goto_cnt - 1;
		}
		else {
			line++;
		}
	}
	else {
		if (goto_cnt != 1) {
			InterpreterError(8);
		}
		bool go = true;
		if (!cmp->empty()) {
			go = false;
			Value v = this->Calculate(*cmp, value_list);
			if (v.var->GetBoolean()) {
				go = true;
			}
		}
		if (go) {
			Value v = this->Calculate(*pos, value_list);
			line = v.var->GetDataToInteger();
			if (line < 0) {
				InterpreterError(9);
			}
			delete v.var;
		}
		else {
			line++;
		}
	}
}

Value Interpreter::ExecuteLine(Command cmd, int &line) {
	vector<Value> var_list;
	this->GetValueList(var_list, cmd);

	/*for (int i = 0; i < cmd.size(); i++) {
		wcout << "[" << cmd[i].type << ":" << cmd[i].data << "]";
	}
	cout << endl;*/

	Command send1, send2;
	int goto_cnt = 0;
	FactorType type = NUL;
	for (int i = 0; i < cmd.size(); i++) {
		if (cmd[i].type == PSH) {
			if (type == PSH) {
				InterpreterError(4, line);
			}
			else if (type == GTO) {
				InterpreterError(3, line);
			}
			type = PSH;
			continue;
		}
		else if (cmd[i].type == GTO) {
			if (type == GTO) {
				InterpreterError(5, line);
			}
			else if (type == PSH) {
				InterpreterError(3, line);
			}
			type = GTO;
			goto_cnt = cmd[i].data.size();
			continue;
		}
		switch(type) {
		case NUL:
			send1.push_back(cmd[i]);
			break;

		default:
			send2.push_back(cmd[i]);
			break;
		}
	}

	Value ret;
	ret.memory = true;
	ret.var = new Variable();

	switch(type) {
		case NUL:
			ret = Calculate(send1, var_list);
			break;
		case PSH:
			this->Push(&send1, &send2, var_list);
			break;
		case GTO:
			this->Goto(&send1, &send2, var_list, goto_cnt, line);
			line--;
			break;
	}
	
	//print calculation process
	/*for (int i = 0; i < cmd.size(); i++) {
		if (cmd[i].type == VAL) {
			cout << var_list[stoi(cmd[i].data)].var->GetDataToInteger();
		}
		else {
			wcout << cmd[i].data;
		}
	}
	cout << endl;*/

	for (int i = 0; i < var_list.size(); i++) {
		if (!var_list[i].memory) {
			delete var_list[i].var;
		}
	}
	var_list.clear();

	return ret;
}

void Interpreter::Execute(Code& code) {
	//Step
	for (int i = 0; i < code.size(); i++) {
		Value ret = ExecuteLine(code[i], i);
		delete ret.var;
	}
}

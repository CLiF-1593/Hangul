#include "FtnIO.h"
#include <iostream>
using namespace std;

void SetInputValue(Hangul* func, int argc, char* argv[]) {
	func->parameter_list.clear();
	func->parameter_value.clear();

	for (int i = 1; i < argc; i++) {
		string data = argv[i];
		if (data[0] == '[') {
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
			in.push_back(s);
			s.clear();
			func->parameter_list.push_back(in);
		}
		else {
			func->parameter_value.push_back(data);
		}
	}
}

wstring SetReturnValue(Hangul* func, Variable &return_value) {
	wstring ret;
	ret += L"\n" + return_value.GetDataToCodeString();
	for (int i = 0; i < func->parameter_value.size(); i++) {
		ret += L" " + func->parameter_value[i].GetDataToCodeString();
	}
	for (int i = 0; i < func->parameter_list.size(); i++) {
		ret += L" [";
		for (int j = 0; j < func->parameter_list[i].size(); j++) {
			if (j) {
				ret += L",";
			}
			ret += func->parameter_list[i][j].GetDataToCodeString();
		}
		ret += L"]";
	}
	return ret;
}

#pragma once
#include <vector>
#include <string>
#include <map>
using namespace std;

enum FactorType { NUL, NUM, VAR, LST, PSH, OPR, GTO, BSZ, FTN }; //number, variable, list, push, operator, goto, bit size, function
typedef wstring FactorData;

struct Factor {
	FactorType type;
	FactorData data;
};

typedef vector<Factor> Command;
typedef vector<Command> Code;

typedef wstring CodeString;
typedef wchar_t CodeUnit;

extern map<CodeUnit, Factor> word_table;
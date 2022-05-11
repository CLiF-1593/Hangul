#pragma once
#include <vector>
#include <string>
#include <map>
using namespace std;

enum FactorType { NUM, VAR, LST, PSH, OPR, GTO, BSZ, FTN, BGN }; //number, variable, list, push, operator, goto, bit size, function, line start
typedef wstring FactorData;

struct Factor {
	FactorType type;
	FactorData data;
};

typedef vector<Factor> Code;

typedef wstring CodeString;
typedef wchar_t CodeUnit;

extern map<CodeUnit, Factor> word_table;
#include "Encoder.h"
#include <sstream>
#include <fstream>
#include <codecvt>
#include <map>

void Encoder::Translate(Command &cmd, CodeString src) {
	//analysis
	Factor factor;
	factor.type = NUL;
	wstring function_name;
	for (int i = 0; i < src.size(); i++) {
		if (word_table.find(src[i]) != word_table.end()) {
			Factor t = word_table[src[i]];
			if (factor.type == FTN_NAME) {
				factor.type = t.type;
				factor.data = t.data;
				cmd.push_back(factor);
				if (!function_name.empty()) {
					factor.type = FTN_NAME;
					factor.data = function_name;
					cmd.push_back(factor);
					function_name.clear();
				}
				factor.type = NUL;
			}
			else if (factor.type != t.type || factor.type == OPR) {
				if (factor.type) {
					cmd.push_back(factor);
				}
				factor.type = t.type;
				factor.data = t.data;
				if (factor.type == FTN) {
					cmd.push_back(factor);
					factor.type = NUL;
				}
			}
			else {
				factor.data += t.data;
			}
		}
		else if(factor.type == FTN_NAME) {
			function_name += src[i];
		}
		else {
			if (factor.type && factor.type != FTN) {
				cmd.push_back(factor);
			}
			factor.type = FTN_NAME;
			factor.data.clear();
			function_name = src[i];
		}
	}
	if (factor.type) {
		cmd.push_back(factor);
	}
}

void Encoder::EncodeFile(string loc, Code& code) {
	std::wifstream wif(loc);
	wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<CodeUnit>));
	std::wstringstream wss;
	wss << wif.rdbuf();
	CodeString raw = wss.str();

	CodeString src;
	Command cmd;
	for (int i = 0; i < raw.size(); i++) {
		CodeUnit c = raw[i];
		if (c == ' ' || c == '\n') {
			if (!src.empty()) {
				this->Translate(cmd, src);
				src.clear();
				code.push_back(cmd);
				cmd.clear();
			}
		}
		else {
			src += c;
		}
	}
	if (!src.empty()) {
		this->Translate(cmd, src);
		src.clear();
		code.push_back(cmd);
		cmd.clear();
	}
}

void Encoder::PrintRawCode(Code& code) {
	for (int i = 0; i < code.size(); i++) {
		for (int j = 0; j < code[i].size(); j++) {
			wcout << "[" << code[i][j].type << ":" << code[i][j].data << "]";
		}
		cout << endl;
	}
}

map<CodeUnit, Factor> word_table = {
	{ L'.',		{NUM, L"0"}	},
	{ L',',		{NUM, L"1"}	},
	{ L'せ',		{VAR, L"v"} },
	{ L'ぞ',		{VAR, L"V"} },
	{ L'ば',		{LST, L"L"} },
	{ L'ぬ',		{LST, L"l"} },
	{ L'ぇ',		{PSH, L"="} },
	{ L'ぉ',		{OPR, L"&"} },
	{ L'ぜ',		{OPR, L"|"} },
	{ L'さ',		{OPR, L"^"} },
	{ L'い',		{OPR, L"~"} },
	{ L'そ',		{OPR, L"<<"} },
	{ L'ず',		{OPR, L">>"} },
	{ L'ぁ',		{GTO, L"G"} },
	{ L'?',		{BSZ, L"S"} },
	{ L'!',		{FTN, L"F"} },
	{ L';',		{FTN, L"f"} },
};
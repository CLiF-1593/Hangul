#include "Encoder.h"
#include <sstream>
#include <fstream>
#include <codecvt>
#include <map>

void Encoder::Translate(Code& code, CodeString cmd) {
	//analysis
	Factor factor;
	factor.type = BGN;
	factor.data = L"NL";
	wstring function_name;
	for (int i = 0; i < cmd.size(); i++) {
		if (word_table.find(cmd[i]) != word_table.end()) {
			Factor t = word_table[cmd[i]];
			if (factor.type != t.type) {
				code.push_back(factor);
				if (factor.type == FTN && !function_name.empty()) {
					factor.data = function_name;
					code.push_back(factor);
					function_name.clear();
				}
				factor.type = t.type;
				factor.data = t.data;
			}
			else {
				factor.data += t.data;
			}
		}
		else if(factor.type == FTN) {
			function_name += cmd[i];
		}
		else {
			code.push_back(factor);
			factor.type = FTN;
			factor.data.clear();
			function_name = cmd[i];
		}
	}
	code.push_back(factor);
}

void Encoder::EncodeFile(string loc, Code& code) {
	std::wifstream wif(loc);
	wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<CodeUnit>));
	std::wstringstream wss;
	wss << wif.rdbuf();
	CodeString raw = wss.str();

	CodeString cmd;
	for (int i = 0; i < raw.size(); i++) {
		CodeUnit c = raw[i];
		if (c == ' ' || c == '\n') {
			if (!cmd.empty()) {
				this->Translate(code, cmd);
				cmd.clear();
			}
		}
		else {
			cmd += c;
		}
	}
	if (!cmd.empty()) {
		this->Translate(code, cmd);
		cmd.clear();
	}
}

void Encoder::PrintRawCode(Code& code) {
	for (int i = 0; i < code.size(); i++) {
		if (code[i].type == BGN) {
			cout << endl;
		}
		wcout << "[" << code[i].type << ":" << code[i].data << "]";
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
	{ L'そ',		{OPR, L"<"} },
	{ L'ず',		{OPR, L">"} },
	{ L'ぁ',		{GTO, L"G"} },
	{ L'?',		{BSZ, L"S"} },
	{ L'!',		{FTN, L"F"} },
	{ L';',		{FTN, L"f"} }
};
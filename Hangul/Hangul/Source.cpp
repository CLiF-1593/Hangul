#include <iostream>
#include <string>
#include <filesystem>
using namespace std;

#define chkp(pos) (pos < argc)
#define chkd(pos, data) (chkp(pos) && CheckStr(argv[pos], data))
#define A2a ('a'-'A')
#define FuncLoc (string)(getenv("APPDATA")) + "Hangul\\FunctionSet\\"

#define Version (string)"0.0.1 Beta"

void PrintErr(string data) {
	cout << "You used the wrong command form. (Please use 'hangul help')" << endl;
	cout << "Command Form : '" << data << "'";
}

bool CheckStr(string str1, string str2) {
	if (str1.size() != str2.size()) {
		return false;
	}
	for (int i = 0; i < str1.size(); i++) {
		if (!(str1[i] == str2[i] || str1[i] + A2a == str2[i] || str1[i] == str2[i] + A2a)) {
			return false;
		}
	}
	return true;
}

bool CheckFileExist(string loc) {
	struct stat buffer;
	if (!(stat(loc.c_str(), &buffer) == 0)) {
		cout << "The file cannot be accessed." << endl;
		cout << "Input Locaton : '" << loc << "'";
		return false;
	}
	return true;
}

int main(int argc, char *argv[]) {
	if (chkd(1, "build") || chkd(1, "b")) {
		string src, bld;
		if (chkp(2) && chkp(3)) {
			src = argv[2];
			bld = argv[3];
			if (CheckFileExist(src)) {
				cout << "Success";
			}
		}
		else {
			PrintErr("hangul build [Source Code Location] [Build Location]");
		}
	}
	else if (chkd(1, "run") || chkd(1, "r")) {
		string src;
		if (chkp(2)) {
			src = argv[2];
			if (CheckFileExist(src)) {
				cout << "Success";
			}
		}
		else {
			PrintErr("hangul run [Source Code Location]");
		}
	}
	else if (chkd(1, "function") || chkd(1, "f")) {
		if (chkd(2, "add")) {
			string src;
			if (chkp(3)) {
				src = argv[3];
				if (CheckFileExist(src)) {
					cout << "Success";
				}
				return 0;
			}
			else {
				PrintErr("hangul function add [Source Function Location]");
			}
			return 0;
		}
		else if (chkd(2, "del") || chkd(2, "delete")) {
			string src;
			if (chkp(3)) {
				src = FuncLoc + argv[3];
				if (CheckFileExist(src)) {
					cout << "Success";
				}
				return 0;
			}
			else {
				PrintErr("hangul function del [Function Name]");
			}
			return 0;
		}
		else if (chkd(2, "rename")) {
			string src, name;
			if (chkp(3) && chkp(4)) {
				src = FuncLoc + argv[3];
				name = argv[4];
				if (CheckFileExist(src)) {
					cout << "Success";
				}
				return 0;
			}
			else {
				PrintErr("hangul function rename [Function Name] [New Name]");
			}
			return 0;
		}
		else if (chkd(2, "library") || chkd(2, "lib")) {
			string src, name;
			if (chkp(3)) {
				src = argv[3];
				if (CheckFileExist(src)) {
					cout << "Success";
				}
				return 0;
			}
			else {
				PrintErr("hangul function lib [Location]");
			}
			return 0;
		}
		else {
			PrintErr("hangul function [Command] [...]");
		}
	}
	else if (chkd(1, "help") || chkd(1, "h")) {
		cout << "Hangul [by CLiF]" << endl;
		cout << "(c) CLiF. All rights reserved." << endl << endl;
		
		cout << "hangul build [Source Code Location] [Build Location]" << endl;
		cout << ": Build your code to the executable file." << endl << endl;
		
		cout << "hangul run [Source Code Location]" << endl;
		cout << ": Run your code with HVM (Hangul Virtual Machine)." << endl << endl;
		
		cout << "hangul function add [Source Function Location]" << endl;
		cout << ": Add your external function in the function set." << endl << endl;

		cout << "hangul function del [Function Name]" << endl;
		cout << ": Delete the function." << endl << endl;

		cout << "hangul function rename [Function Name] [New Name]" << endl;
		cout << ": Rename the function." << endl << endl;

		cout << "hangul function lib [Location]" << endl;
		cout << ": Get HFDL (Hangul Function Development Library) files." << endl << endl;

		cout << "hangul ver" << endl;
		cout << ": Get hangul current version." << endl << endl;

		cout << "hangul help" << endl;
		cout << ": Help" << endl << endl;
	}
	else if (chkd(1, "version") || chkd(1, "ver") || chkd(1, "v")) {
		cout << "Hangul [by CLiF]" << endl;
		cout << "(c) CLiF. All rights reserved." << endl << endl;
		cout << "Version : " + Version;
	}
	else {
		PrintErr("hangul [Command] [...]");
	}
	return 0;
}
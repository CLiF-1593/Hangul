#include <iostream>
#include "Encoder.h"
#include "Interpreter.h"
using namespace std;
int main(int argc, char* argv[]) {
	
	wcout.imbue(locale("kor"));
	Code code;
	Encoder encoder;
	/*if (argc != 2) {
		cout << "[HVM] Excute Error" << endl;
		return 1;
	}*/
	encoder.EncodeFile(/*argv[1]*/"code.txt", code);
	encoder.PrintRawCode(code);
	Interpreter interpreter;
	interpreter.Execute(code);
	return 0;
}
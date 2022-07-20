#include <iostream>
#include "Encoder.h"
#include "Interpreter.h"
using namespace std;
int main() {
	wcout.imbue(locale("kor"));
	Code code;
	Encoder encoder;
	encoder.EncodeFile("code.txt", code);
	//encoder.PrintRawCode(code);
	Interpreter interpreter;
	interpreter.Execute(code);
	return 0;
}
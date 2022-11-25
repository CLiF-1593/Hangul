#include <iostream>
#include "FtnIO.h"
#include "HFDL.h"

using namespace std;

int main(int argc, char* argv[]) {
	Hangul func;
	SetInputValue(&func, argc, argv);
	Variable return_value;
	return_value = func.Function();
	wprintf(SetReturnValue(&func, return_value).c_str());
	return 0;
}
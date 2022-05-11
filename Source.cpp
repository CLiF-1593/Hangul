#include <iostream>
#include "Encoder.h"
using namespace std;
int main() {
	Encoder encoder;
	Code code;
	wcout.imbue(locale("kor"));
	encoder.EncodeFile("code.txt", code);
	encoder.PrintRawCode(code);
	return 0;
}
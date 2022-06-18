#pragma once
#include <iostream>
#include <string>
#include "Code.h"

class Encoder {
private:
	void Translate(Command &code, CodeString src);

public:
	void EncodeFile(string loc, Code &code);
	void PrintRawCode(Code &code);
};


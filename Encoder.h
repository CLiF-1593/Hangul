#pragma once
#include <iostream>
#include <string>
#include "Code.h"

class Encoder {
private:
	void Translate(Code& code, CodeString cmd);

public:
	void EncodeFile(string loc, Code &code);
	void PrintRawCode(Code &code);
};


#include "ErrorSystem.h"
#include <iostream>
#include <string>
using namespace std;

const string err_msg[] = {
	/*00*/	"The index is missing from the list",
	/*01*/	"The function does not have name",
	/*02*/	"The function is not closed",
	/*03*/	"The Assignment Operator and the Goto Operator should not exist in the same line",
	/*04*/	"The Assignment Operator should be the only one in the same line",
	/*05*/	"The Goto Operator should be continuous. Not be cut off",
	/*06*/	"The Assignement Operator needs both left operand and right operands",
	/*07*/	"The left operand of the Assignement Operator should be changeable",
	/*08*/	"The position value is not needed for Multi Goto Operators Syntax",
	/*09*/	"The position of the Goto Operator is negative",
	/*10*/	"There are too many operators in comparison to operands",
	/*11*/	"There are too many operands in comparison to operators",
};

void InterpreterError(int err_code, int line) {
	cout << "Error [Interpreter]" << " ";
	cout << "(error code = " << err_code << ", line = "<< line << ") : ";
	cout << err_msg[err_code] << endl;
	system("pause");
	exit(EXIT_FAILURE);
}

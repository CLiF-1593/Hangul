#include <iostream>
#include "MemorySystem.h"
using namespace std;
int main() {
	Variable a(1), b(5);
	a.PrintRaw();
	b.PrintRaw();
	cout << a.GetDataToInteger() << endl;
	cout << b.GetDataToInteger() << endl;
	a = a ^ 5;
	a.PrintRaw();
	cout << a.GetDataToInteger() << endl;
	return 0;
}
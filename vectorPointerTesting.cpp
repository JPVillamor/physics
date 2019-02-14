#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
int main () {
	vector<string> commands;
	vector<string> *ptrCommands;
	ptrCommands = &commands;
	commands.push_back("Tom");
	commands.push_back("Dick");
	commands.push_back("Larry");
	cout << commands[0] << endl;
	cout << commands[1] << endl;
	cout << commands[2] << endl;
	cout << (*ptrCommands)[0] << endl;
	cout << (*ptrCommands)[1] << endl;
	cout << (*ptrCommands)[2] << endl;
	cout << &commands << endl;
	cout << ptrCommands << endl;
	return 0;
}

/*
K nvm scratch the rings idea.
we use simple conditionals
with the isKnown bools for
possible known values.
OR a bigger function areKnown
that looks at multiple values
and checks if they are known.
From there we branch to
whatever formula fits. 
*/
#include <iostream>
#include <string>
#include <vector>

const double ACCG = -9.8;
const int TABLESIZE1 = 6;
const int TABLESIZE2 = 6;

using namespace std;

class Variable {
protected:
	double value; //holds actual value.
	bool isKnown = false; //whether or not it's known. false by dflt
	string keyword; //the name of the var, like 'force' or 'mass'.
public:
	void setKnown(bool tf) {isKnown = tf;} //sets the isKnown bool.
	void setGiven(double given) {value = given;} //use only if isKnown == true
	virtual void formulaValue() = 0; //virtual function
	double getValue() {return value;} //returns the var's value.
	bool getKnown() {return isKnown;} //returns whether the var is known or not.
	string getkw() {return keyword;} //returns the keyword of the variable.
};

class Force : public Variable {
	public: 
		void formulaValue() {
			;
		}
};

string input() {
	string inputLine;
	cout << ">> ";
	getline(cin, inputLine);

	return inputLine;
}

vector<string> vectorize(string s) {
	vector<string> splitString;
	string term = "";
	int i = 0;
	while (i < s.length()) {
		term += s[i++];
		if (s[i] == ' ' || i == s.length()) {
			splitString.push_back(term);
			term = "";
			i++;
		}
	}

	return splitString;
}

bool areKnown(vector<Variable*> varSet) {
	bool allKnown = true;
	int i = 0;
	do {
		if (varSet[i]->getKnown() == false) {
			allKnown = false;
		}
		i++;
	} while (allKnown == true);

	return allKnown;
}

void interpret(vector<string> &strVect) {
	;
}

int main() {
	vector<string> commands;
	vector<string> *ptrCommands;
	commands = vectorize(input());
	ptrCommands = &commands;	
	return 0;
}

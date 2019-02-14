#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <string>

using namespace std;

const int ACCG = -9.8;

struct Variable {
	double value;
	bool isKnown = false;
	string keyword;
};

class Entity {
private:
	Variable force, mass, acceleration, averageSpeed, distance, time, xPos, xPosInit, xVel, yPos, yPosInit, yVel, yVelInit;
	vector<Variable*> variables;
	vector<Variable*> *ptrVars;
	vector<string> keywords;
public:
	Entity() {
		//assign keywords
		keywords.push_back(force.keyword = "force");
		keywords.push_back(mass.keyword = "mass");
		keywords.push_back(acceleration.keyword = "acc");
		keywords.push_back(averageSpeed.keyword = "avgspd");
		keywords.push_back(distance.keyword = "dist");
		keywords.push_back(time.keyword = "time");
		keywords.push_back(xPos.keyword = "x");
		keywords.push_back(xPosInit.keyword = "xi");
		keywords.push_back(xVel.keyword = "vx");
		keywords.push_back(yPos.keyword = "y");
		keywords.push_back(yPosInit.keyword = "yi");
		keywords.push_back(yVel.keyword = "vy");
		keywords.push_back(yVelInit.keyword = "vyi");
		
		variables.push_back(&force);
		variables.push_back(&mass);
		variables.push_back(&acceleration);
		variables.push_back(&averageSpeed);
		variables.push_back(&distance);
		variables.push_back(&time);
		variables.push_back(&xPos);
		variables.push_back(&xPosInit);
		variables.push_back(&xVel);
		variables.push_back(&yPos);
		variables.push_back(&yPosInit);
		variables.push_back(&yVel);
		variables.push_back(&yVelInit);
		
		ptrVars = &variables;
	}
	bool isNumber(string s);
	bool isKeyword(string s);
	Variable *getVar(string kw);
	vector<Variable*> *getPtrVars() {return ptrVars;}
	void interpret(vector<string> *strVect);
	void findVar(Variable *v);
	void findForce();
};

bool Entity::isNumber(string s) {
	if (atof(s.c_str()) == 0 && s != "0") {
		return false;
	} else {
		return true;
	}
}

bool Entity::isKeyword(string s) {
	bool match = false;
	for (int i = 0; i < keywords.size(); i++) {
		if (keywords[i] == s) {
			match = true;
		}
	}
	return match;
}

Variable *Entity::getVar(string kw) {
	for (int word = 0; word < variables.size(); word++) {
		if (variables[word]->keyword == kw) {
			return variables[word];
		}
	}
}

void Entity::interpret(vector<string> *strVect) {
	Variable *chosenVar;
	switch((*strVect).size()) {
	case 1:
		if (isKeyword((*strVect)[0])) {
			chosenVar = getVar((*strVect)[0]);
			if (chosenVar->isKnown == false) {
				findVar(chosenVar);
			}
			if (chosenVar->isKnown == true) {
				cout << "<< " << chosenVar->value << endl;
			}
		}
		break;
	case 2:
		chosenVar = getVar((*strVect)[0]);
		if (isNumber((*strVect)[1])) {
			chosenVar->value = (atof((*strVect)[1].c_str()));
			chosenVar->isKnown = true;
		} else {
			cout << "<< cannot assign " << (*strVect)[1] << " to " << (*strVect)[0] << endl;
		}
		break;
	}
}

void Entity::findVar(Variable *v) {
	if (v->keyword == "force") {
		findForce();
	}
}

void Entity::findForce() {
	if (mass.isKnown == true && acceleration.isKnown == true) {
		force.value = mass.value * acceleration.value;
		force.isKnown = true;
	} else {
		cout << "<< " << "not enough info." << endl;
	}
}

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

int main() {
	Entity Ball;
	
	vector<string> commands;
	vector<string> *ptrCommands;
  do {
    commands = vectorize(input());
    ptrCommands = &commands;
    Ball.interpret(ptrCommands);
  } while (commands[0] != "exit");
	
	return 0;
}

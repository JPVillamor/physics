#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <vector>

const int ACCG = -9.8;

using namespace std;

class Variable {
private:
  double *value;
  string keyword;
public:
  Variable() {value = NULL, keyword = "";}
  double valueVar;
  double *getValue() {return value;}
  string getkw() {return keyword;}
  void setkw(string s) {keyword = s;}
  void setVal(double d) {valueVar = d;}
  void setptrVal() {value = &valueVar;}
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

bool isNumber(string s) {
	if (atof(s.c_str()) == 0 && s != "0") {
		return false;
	} else {
		return true;
	}
}

bool checkKW(vector<string> *strVect, vector<Variable> *ptrVars) {
  bool allKeywords = true;
  for (int word = 0; word < (*strVect).size(); word++) {
      bool match = false;
      for (int var = 0; var < (*ptrVars).size(); var++) {
          if ((*strVect)[word] == (*ptrVars)[var].getkw() || isNumber((*strVect)[word])) {
              match = true;
          }
      }
      if (match == false) {
          cout << "<< \'" << (*strVect)[word] << "\' is not a keyword." << endl;
          allKeywords = false;
      }
  }
  return allKeywords;
}

void interpret(vector<string> *strVect, vector<Variable> *ptrVars) {
  if (checkKW(strVect, ptrVars) == true) {
  	Variable chosenVar;
		switch((*strVect).size()) {
		case 1:
			for (int i = 0; i < (*ptrVars).size(); i++) {
				if ((*strVect)[0] == (*ptrVars)[i].getkw()) {
					chosenVar = (*ptrVars)[i];
				}
			}
			if (chosenVar.getValue() == &chosenVar.valueVar) {
				cout << "<< " << *chosenVar.getValue() << endl;
			} else if (isNumber((*strVect)[0])) {
				cout << "<< " << (*strVect)[0] << endl;
			} else {
				cout << "<< " << chosenVar.getkw() << " is not known." << endl;
			}
		case 2:
			for (int i = 0; i < (*ptrVars).size(); i++) {
				if ((*strVect)[0] == (*ptrVars)[i].getkw()) {
					chosenVar = (*ptrVars)[i];
				}
			}
			if (isNumber((*strVect)[1])) {
				chosenVar.setVal(atof((*strVect)[1].c_str()));
				chosenVar.setptrVal();
			} else {
				cout << "<< cannot assign " << (*strVect)[1] << " to " << (*strVect)[0] << endl;
			}
		}
  }
}

void addVars(vector<Variable> &vVect) {
  Variable force;
  force.setkw("force");
  vVect.push_back(force);

  Variable mass;
  mass.setkw("mass");
  vVect.push_back(mass);

  Variable acceleration;
  acceleration.setkw("acc");
  vVect.push_back(acceleration);

  Variable distance;
  distance.setkw("dist");
  vVect.push_back(distance);

  Variable averageSpeed;
  averageSpeed.setkw("avgspd");
  vVect.push_back(averageSpeed);

  Variable time;
  time.setkw("time");
  vVect.push_back(time);

  Variable xPos;
  xPos.setkw("x");
  vVect.push_back(xPos);

  Variable xPosInit;
  xPosInit.setkw("xi");
  vVect.push_back(xPosInit);

  Variable xVel;
  xVel.setkw("vx");
  vVect.push_back(xVel);

  Variable yPos;
  yPos.setkw("y");
  vVect.push_back(yPos);

  Variable yPosInit;
  yPosInit.setkw("yi");
  vVect.push_back(yPosInit);

  Variable yVel;
  yVel.setkw("vy");
  vVect.push_back(yVel);

  Variable yVelInit;
  yVelInit.setkw("vyi");
  vVect.push_back(yVelInit);
}

int main() {
	vector<string> commands;
	vector<string> *ptrCommands;
	vector<Variable> variables;
	vector<Variable> *ptrVars;
  addVars(variables);
  ptrVars = &variables;
  do {
    commands = vectorize(input());
    ptrCommands = &commands;
    interpret(ptrCommands, ptrVars);
  } while (commands[0] != "exit");
	return 0;
}

#include <iostream>
#include<cstring>
#include <string.h>
#include <vector>
#include "State.h"
using std::string;


#ifndef MACHINE_H
#define MACHINE_H

//Global constant variables
const int MAX_OF_VAR = 10;
const int MAX_OF_STATE = 10;
struct variable {
	string var_name;
	int value;
	bool filled; //A flag
};

class Machine
{
public:
	Machine(string nm);
	~Machine();
	void setVariable(string var);
	void setState(State* a);
	void incrementVariable( string varName);
	State* getState( string name);
	int getNumStates() const;
	int getNumVars() const;
	int getValueVar(string varName) const;
	bool var_exist(string var_name);
	string getName() const;
	void run();



private:
	string name;
	variable all_variables[MAX_OF_VAR];
	State* all_states[MAX_OF_STATE];
	int count_var;
	int count_state;

	
};



#endif
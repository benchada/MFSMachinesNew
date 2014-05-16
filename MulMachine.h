#include <iostream>
#include<cstring>
#include <string.h>
#include <vector>
#include "State.h"
#include "Machine.h"
using std::string;


#ifndef MULMACHINE_H
#define MULMACHINE_H

//Global constant variables
const int MAX_OF_MFSM_VAR = 10;
const int MAX_OF_MACHINE = 10;
struct MFSM_variable 
{
	string var_name;
	int value;
	bool filled; //A flag to know if theis variable is initialized
};

class MulMachine
{
public:
	MulMachine(string nm);
	~MulMachine();
	void setVariable(string var); //Common variables among all the machines
	void setMachine(Machine* a);
	void incrementVar(string varName);
	Machine* getMachine(string name) const;
	Machine* getMachine(int ID) const;
	int getNumMachines() const;
	int getNumVars() const;
	int getValueVar(string varName) const;
	bool var_exist(string var_name);
	string getName() const;
	void run();



private:
	string name;
	MFSM_variable all_variables[MAX_OF_MFSM_VAR];
	Machine* all_machines[MAX_OF_MACHINE];
	int count_var;
	int count_machine;


};



#endif
#include <iostream>
#include "Action.h"
#include "MulMachine.h"
using std::string;

#ifndef INCREMENTVAR_H
#define INCREMENTVAR_H

class incrementVar: public Action
{
public:
	incrementVar(Machine* machine_name, string var_name);
	incrementVar(MulMachine* MFSMmachine_name, string var_name);
	~incrementVar();
	void execute_act();
	
private:
	Machine* my_machine;
	MulMachine* my_MFSM;
	string varName;
	bool MFSM_var;
	
};


#endif
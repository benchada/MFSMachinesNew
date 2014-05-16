#include <iostream>
#include <string>
#include <stdlib.h>
#include <mutex>
#include "Machine.h"
#include "Action.h"
#include "incrementVar.h"


using namespace std;

incrementVar::incrementVar(Machine* machine_ptr, string var_name) : my_machine(machine_ptr), varName (var_name)
{
	MFSM_var = false;
}

incrementVar::incrementVar(MulMachine* MFSMmachine_name, string var_name) : my_MFSM(MFSMmachine_name), varName(var_name)
{
	MFSM_var = true;
}

void incrementVar::execute_act()
{
	mutex m;
	lock_guard<mutex> _(m);

	if (MFSM_var)
	{
		if (my_MFSM->var_exist(varName))
		{
			my_MFSM->incrementVar(varName);
		}
	}
	else
	{
		if (my_machine->var_exist(varName))
		{
			my_machine->incrementVariable(varName);
		}
	}
	
}

incrementVar::~incrementVar()
{
	delete my_machine;
	delete my_MFSM;
}
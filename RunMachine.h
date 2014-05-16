#include <iostream>
#include "Action.h"
#include "Machine.h"

using std::string;

#ifndef RUNMACHINE_H
#define RUNMACHINE_H

class runMachine : public Action
{
public:
	runMachine(Machine* machine_name);
	~runMachine();
	void execute_act();

private:
	Machine* my_machine;
};


#endif
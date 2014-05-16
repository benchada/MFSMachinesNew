#include <iostream>
#include "Action.h"
using std::string;

#ifndef ENDMACHINE_H
#define ENDMACHINE_H

class endMachine: public Action
{
public:
	endMachine( Machine* machine_name);
	~endMachine();
	void execute_act();

private:
	Machine* my_machine;
};


#endif
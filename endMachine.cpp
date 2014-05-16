#include <iostream>
#include <string>
#include <stdlib.h>
#include "Machine.h"
#include "Action.h"
#include "endMachine.h"


using namespace std;

	endMachine::endMachine(Machine* machine_ptr)
	{
		my_machine = machine_ptr;
	}

void endMachine::execute_act()
	{
		//exit (0); I am not exiting the whole program so I don't need to use the function exit ( We may go back to another machine)
	
		cout<<" END OF EXECUTION for machine "<<my_machine->getName()<<" ! "<<endl;
		
		//Terminating successfully
	}

	endMachine::~endMachine()
	{
		delete my_machine;
	}
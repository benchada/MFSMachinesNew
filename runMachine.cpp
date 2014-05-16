#include <iostream>
#include <string>
#include <stdlib.h>
#include "Machine.h"
#include "Action.h"
#include "runMachine.h"


using namespace std;

runMachine::runMachine(Machine* machine_ptr)
{
	my_machine = machine_ptr;
}

void runMachine::execute_act()
{
	cout << " START OF RUNNING the machine " << my_machine->getName() << " ! " << endl;
	//Running this machine
	my_machine->run();
	
}

runMachine::~runMachine()
{
	delete my_machine;
}
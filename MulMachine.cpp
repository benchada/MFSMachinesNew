#include<iostream>
#include <cstring>
#include<string>
#include <vector>
using std::string;

#include "Machine.h"
#include "MulMachine.h"

using namespace std;



MulMachine::MulMachine(string nm)
{
	//Initializing the variables
	name = nm;
	count_var = 0;
	count_machine = 0;

}


MulMachine::~MulMachine()
{
	//Deleting all the states in this machine
	for (int i = 0; i< count_machine; i++)
	{
		delete all_machines[i];
	}
}

void MulMachine::setVariable(string var)
{
	all_variables[count_var].var_name = var; //So that we can index the variables by their numbers directly
	all_variables[count_var].value = 0; //Initializing it by zero
	all_variables[count_var].filled = true;
	count_var++;
}

void MulMachine::setMachine(Machine* a)
{
	all_machines[count_machine++] = a;
}

void MulMachine::incrementVar(string varName)
{
	if (var_exist(varName))
	{
		for (int i = 0; i<count_var; i++)
		{
			if (all_variables[i].filled && all_variables[i].var_name == varName)
				all_variables[i].value++;
		}
	}
	else
		cout << "ERROR: Sorry this variable " << varName << "cannot be incrememnted, because it doesn't exist!" << endl;
}

Machine* MulMachine::getMachine(string name) const
{
	//looping over our array of states and returning back the corresponding 
	for (int i = 0; i<count_machine; i++)
	{
		if (all_machines[i]->getName() == name)
			return all_machines[i];
	}
	//If we looped over all the states and we did not find it, then we dont have it
	cout << "ERROR: The state: " << name << " does not exist!" << endl;
	return NULL;

}

Machine* MulMachine::getMachine(int ID) const
{
	//We retrieve a certain machine accroding to the applied ID
	if (ID > count_machine)
	{
		cout << "Sorry .. Your provided ID for this machine is wrong! Choose a smaller one!" << endl;
		cout << " Null pointer is returned" << endl;
		return NULL;
	}
	else
	{
		return all_machines[ID];
	}
}

int MulMachine::getNumMachines() const
{
	return count_machine;
}

int MulMachine::getNumVars() const
{
	return count_var;
}


bool MulMachine::var_exist(string varName)
{
	for (int i = 0; i< count_var; i++)
	{
		if (all_variables[i].var_name == varName && all_variables[i].filled)
			return true;
	}
	return false;
}

//With the Assumption of all variables are distinct, and the user is not going to enter a single mname of variable twice
int MulMachine::getValueVar(string varName) const
{
	for (int i = 0; i<count_var; i++)
	{
		if (all_variables[i].filled && all_variables[i].var_name == varName)
			return all_variables[i].value;
	}

	cout << "ERROR: The variable " << varName << " does not exist in our machine " << name << " !!" << endl;
	cout << "Returned Value is (-1)" << endl;
	return -1;

}


string MulMachine::getName() const
{
	return name;
}

void MulMachine::run()
{
	for (int i = 0; i < count_machine; i++)
	{
		all_machines[i]->run();
	}
	
}




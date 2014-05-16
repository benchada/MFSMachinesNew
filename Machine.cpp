#include<iostream>
#include <cstring>
#include<string>
#include <vector>
using std::string;

#include "Machine.h"

using namespace std;



Machine::Machine(string nm)
{
	//Initializing the variables
	name = nm;
	count_var = 0;
	count_state = 0;	

}


Machine::~Machine()
{
	//Deleting all the states in this machine
	for ( int i =0; i< count_state; i++)
	{
		delete all_states[i];
	}
}

void Machine::setVariable( string var)
{
	all_variables[count_var].var_name = var; //So that we can index the variables by their numbers directly
	all_variables[count_var].value = 0; //Initializing it by zero
	all_variables[count_var].filled = true;
	count_var++;
}

void Machine::setState(State* a)
{
	all_states[count_state++]= a;
}

void Machine::incrementVariable( string varName)
{
	if ( var_exist(varName))
	{
		for ( int i=0; i<count_var ; i++)
		{
			if ( all_variables[i].filled && all_variables[i].var_name == varName)
				all_variables[i].value++;
		}
	}
	else
		cout<<"ERROR: SOrry this variable "<<varName <<"cannot be incrememnted, because it doesn't exist!"<<endl;
}

State* Machine::getState(string name)
{
	//looping over our array of states and returning back the corresponding 
	for ( int i=0 ; i<count_state ; i++)
	{
		if ( all_states[i]->getName() == name)
			return all_states[i];
	}
	//If we looped over all the states and we did not find it, then we dont have it
	cout<<"ERROR: The state: "<<name<< " does not exist!"<<endl;

}


int Machine::getNumStates() const
{
	return count_state;
}

int Machine::getNumVars() const
{
	return count_var;
}


bool Machine::var_exist(string varName)
{
	for ( int i=0; i< count_var; i++)
	{
		if (all_variables[i].var_name == varName && all_variables[i].filled)
			return true;
	}
	return false;
}

//With the Assumption of all variables are distinct, and the user is not going to enter a single mname of variable twice
int Machine::getValueVar(string var_name) const
{
	for ( int i=0; i<count_var ; i++)
	{
		if ( all_variables[i].filled && all_variables[i].var_name == var_name)
			return all_variables[i].value;
	}

	cout<<"ERROR: The variable "<<var_name << " does not exist in our machine "<< name <<" !!"<<endl;
	return -1;

}

string Machine::getName() const
{
	return name;
}

void Machine::run()
{
	all_states[0]->execute();
}

	


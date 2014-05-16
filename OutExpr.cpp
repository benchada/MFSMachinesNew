#include "OutExpr.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>


using namespace std;


	//A constructor for outputng a constant value
	OutExpr::OutExpr(string stmt)
	{
		output = stmt;
		this_var ="";
		var_type = false;
		myMachine = NULL;
	}

	//A constructor for a variable
	OutExpr::OutExpr(MulMachine* MFSM_nm, Machine* machine_nm, string var)
	{
		var_type = true;
		this_var = var;
		myMachine = machine_nm;
		my_MFSM = MFSM_nm;
	}

	void OutExpr::execute_act()
	{
		cout<<"Implementing the OUT EXPR action for this machine "<<endl;

		//Checking if this variable is acommon one or an individual one
		if (myMachine->var_exist(this_var))
		{
			//getting the integer value of the variable, and convert it to string
			ostringstream convert;
			convert << myMachine->getValueVar(this_var);
			output = convert.str();
		}

		else if (my_MFSM->var_exist(this_var))
		{
			ostringstream convert;
			convert << my_MFSM->getValueVar(this_var);
			output = convert.str();

		}

		//Deciding using the flag, whether we are going to output a variable or an expression
		if ( var_type)
		{
			cout <<"The value of this variable "<<this_var <<" is: "<< output<<endl;
		}
		else
			cout<<" Printing the constant value: "<<output<<endl;
	}
	OutExpr::~OutExpr()
	{
		delete myMachine;
	}
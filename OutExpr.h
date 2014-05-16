#include <iostream>
#include <string>
#include "Action.h"
//#include "Machine.h"
#include "MulMachine.h"

using namespace std;


#ifndef OUTEXPR_H
#define OUTEXPR_H


class OutExpr : public Action
{
public:
	OutExpr(string stmt); //Constructor for only a constant
	OutExpr( MulMachine* MFSM_nm ,Machine* machine_nm, string var);
	~OutExpr();
	void execute_act();

private:
	string output;
	string this_var;
	bool var_type;
	Machine* myMachine;
	MulMachine* my_MFSM;

};

#endif


#include <iostream>
#include <string>
#include "Action.h"

using namespace std;


#ifndef OUTSTRING_H
#define OUTSTRING_H


class OutString : public Action
{
public:
	OutString( string stmt);
	void execute_act();

private:
	string output;


};

#endif
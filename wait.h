

#include <iostream>
#include "Action.h"
#include "State.h"
using std::string;

#ifndef WAIT_H
#define WAIT_H

class wait: public Action
{
public:
	wait(State* newState);
	~wait();
	void execute_act();
	
private:
	State* mystate;
};


#endif
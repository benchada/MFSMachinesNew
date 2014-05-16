#ifndef SLEEP_H
#define SLEEP_H

//#include <iostream>
//#include <string> //we commented this
#include "Action.h"

//using namespace std;


class sleep : public Action
{
public:
	sleep(int amount);
	void execute_act();

private:
	int amount;
};

#endif
#include <iostream>
#include <string>
#include "Action.h"
#include "wait.h"



using namespace std;

	wait::wait(State* newState)
	{
		mystate = newState;
	}

void wait::execute_act()//pass the state itself in order to operate on it
	{
		int input;
		cout<<"The machine is waiting for the user's input. Please provide one!"<<endl;
		cin>>input;

		//Deciding what the next state is: PS: ALl transitions is a data element in the state class not in the action
		if (mystate->getTransition(input) == NULL)
		{
			//Since it has return Null then there is no transition
			cout<<"ERROR: There is no correpongin input for this state."<<endl;
			cout<<"PROGRAM WILL END !"<<endl;

		}
		else
		{		
			mystate->getTransition(input)->execute();
		}

	}

wait::~wait()
{
	delete mystate;
}
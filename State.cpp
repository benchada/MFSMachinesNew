#include<iostream>
#include<cmath>
#include <string>
#include <string.h>
#include "State.h"
#include "Action.h"

using namespace std;



//Definition of the class methods

//The constructor
    State::State(string nm)
    {
        name=nm;
		trans_count = 0; //To count how many transitions this state has
		actions_count = 0;

		//Initialization of our dynamic allocated memomry
		
		for ( int i =0; i< MAX_ACTION_PER_STATE; i++)
		{
			all_actions[i]= NULL;
		}

		for ( int j=0; j< MAX_TRANS_PER_STATE ; j++)
		{
			all_transitions[j].next_state = NULL;
		}

		
    }

    State::~State()
	{
		//Explicitly Deleting all allocated dynamic memeory
		for (int i =0; i<actions_count; i++)
		{
			delete all_actions[i];
		}

		for ( int j=0; j< trans_count; j++)
		{
			delete all_transitions[j].next_state;
		}

	}

	void State::setName(string state_name)
	{
		name = state_name;
	}

	const string State::getName()
	{
		return name;
	}

	
	void State::setAction(Action* OneAction)
	{
		all_actions[actions_count++]= OneAction;
	}
	
	void State::setTransition (State* next_state, int usr_input)
	{
		
		all_transitions[trans_count].next_state = next_state;
		all_transitions[trans_count].user_input = usr_input;
		trans_count++;
	}

	State* State::getTransition( int input) const
	{
		/*
		try {
		return transitions[input];
		}
		catch (...)
		{
			cout<<"This input is wrong!! There is no corresponding state to make this trasition. We have returned NULL"<<endl;
			return NULL;
		}*/

		for ( int i=0; i<trans_count ; i++)
		{
			if ( all_transitions[i].user_input == input)
			{
				return all_transitions[i].next_state;
			}
		}
		//If we did not find this input after loopin through all our entries, then we retinr NULL with an error statement
		cout<<"ERROR: This input is not valid. There is no corresponding state for this input!!"<<endl;
		return NULL;
	
	}

	void State::execute()
	{
		//looping over all our actions in this current state
		for ( int j=0; j<actions_count; j++)
		{
			all_actions[j]->execute_act();
		}


	}



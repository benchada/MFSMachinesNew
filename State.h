/*This is the header file of the state class */

#include <iostream>

//typedef Action NewAction;
using std::string;


#ifndef STATE_H
#define STATE_H

#include "Action.h"
/*DESCRIPTION: A class of a state will have the folowing compomnents: A name, a set of actions, andset of transisiotns */

//-----------------Assumptions:------------
//MAX # of transitions per state is 10     |
//MAX # of actions per state is 7          |
//-----------------------------------------
//Global variables
const int MAX_TRANS_PER_STATE = 10;
const int MAX_ACTION_PER_STATE =7;


class State
{
public:
	State(string nm); //Constructor
	~State(); //Deconstructor
	void setName(string state_name); //Stroing the name of the state
	const string getName (); // retrieving the name of the current state object
	void setAction(Action* ActionsLine); // Storing the set ofactions in the class
	void setTransition (State* next_state, int usr_input); //in the array of transitions we will put the next state
	State* getTransition( int input_usr) const;
	void execute();// Executing the actions of the class


private:
	string name;
	//State* transitions[MAX_TRANS_PER_STATE];
	int trans_count; //To count how many transitions this state has

	struct gotostate{
	int user_input;
	State *next_state;
};
	gotostate all_transitions[MAX_TRANS_PER_STATE]; //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	Action* all_actions[MAX_ACTION_PER_STATE]; //To store all the actions which the state has
	int actions_count; //Number of actual actions in this state
};



#endif
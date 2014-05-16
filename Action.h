

#include<iostream>
#include<string>

using std::string;

#ifndef ACTION_H
#define ACTION_H




class Action // it is beneficial for its common interface
{
public:
	//Action(string name);// >> No need for the constructor, it is by default there now
	virtual void execute_act();
	

private:
	string act_name;

};
#endif
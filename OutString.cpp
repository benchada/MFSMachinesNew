#include <iostream>
#include <string>
#include "Action.h"
#include "OutString.h"

using namespace std;

	OutString::OutString( string stmt)
	{
		output = stmt;
	}


	void OutString::execute_act()
	{
		cout<<"Implementing the OUT STRING action"<<endl;
		cout<<output<<endl;
	}


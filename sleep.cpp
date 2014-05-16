#include "sleep.h"
#include <iostream>
#include <windows.h>
#include <stdio.h>


using namespace std;

	sleep::sleep(int amnt)
	{
		amount = amnt;
	}


	void sleep::execute_act()
	{
		cout<<"Implementing the SLEEP action for "<< amount << " seconds"<<endl;
		Sleep(amount*1000); //Because it takes in milli seconds, so we multiply by thousand
		
	}

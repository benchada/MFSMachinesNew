#define _CRT_SECURE_NO_WARNINGS 1 

#include<iostream>
#include<string>
#include<thread>

using namespace std;

#include <fstream>
using std::ifstream;

#include <cstring>
#include <string>
#include <sstream>
#include <map>

#include "MulMachine.h"
#include "Machine.h"
#include "State.h"

#include "incrementVar.h"
#include "endMachine.h"
#include "RunMachine.h"
#include "OutString.h"
#include "OutExpr.h"
#include "sleep.h"
#include "wait.h"


/*-----Global Variables Declaration & Initialization-----*/


const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = " ,.-:";
const int MAX_VARIABLES_PER_MACHINE = 10; //Any FSM can have a maximun of 10 variables
const int MAX_TRANSITIONS_PER_MACHINE = 10; //Any FSM can have a maximun of 10 transitions
const int MAX_ACTIONS_PER_STATE = 5;
const int MAX_OF_MACHINES = 4;

string MFSMachine_name;
string machine_name;
string state_name;
string real_token;
string temp;
string variables[MAX_VARIABLES_PER_MACHINE]; //An array to store variables of a single machine
string actions[MAX_ACTIONS_PER_STATE]; //An array recording the actions of a signle state

Machine *all_machines[MAX_OF_MACHINES]; //Having an array of pointers to 3 machines
int count_machine = 0;

MulMachine *curr_MFSM_machine;
Machine *curr_machine; //Declaring it as a global variable in order to enable changes for it throughout the program
Machine *this_machine;
State *curr_state;
Action *curr_action;

map <string, Machine> table_machine;
map <string, Action> table_action;

bool states_flag = false;

//Functions Prototypes:
void parse_line(char buf[], int& num_tokens, const char* token[]);
Machine* parse_FSM_file(string input_file);
MulMachine* parse_MFSM_file(string input_file);
void run_one_machine(Machine* cur_FSM);

/*------------------------------------- MAIN FUNCTION -------------------------------------------*/

int main()

{
	string file_name;
	vector<thread*> mythreads;
	//void (to_run*)();

	cout << "Please enter the name of your file" << endl;
	cin >> file_name;


	//Processing
	curr_MFSM_machine = parse_MFSM_file(file_name);

	

	if (curr_MFSM_machine != NULL)
	{
		cout << "Your Multiple FSM machine has been correctly constructed!" << endl;
		cout << " Your MFSM: " << curr_MFSM_machine->getName() << " has" << curr_MFSM_machine->getNumMachines() << " machines inside it." << endl;

		//Creating threads accroding to the number of machines
		for (int i = 0; i < curr_MFSM_machine->getNumMachines(); i++)
		{
			mythreads.push_back(new thread(run_one_machine, curr_MFSM_machine->getMachine(i)));
		}
		
		//Invoking the threads individually
		for (int i = 0; i < mythreads.size(); i++)
		for (std::vector<thread*>::size_type i = 0; i != mythreads.size(); i++)
		{
			mythreads[i]->join();
		}
	}
	else
		cout << "The MFSM was not correctly constructed! There is an error.." << endl; 
	//


}

/*----------------Definition of functions--------------------------*/


//A function to be passed as a thread
void run_one_machine(Machine* cur_FSM)
{
	cur_FSM->run();
}

//A function to parse a single line
void parse_line(char buf[], int& num_tokens, const char* token[])
{
	//const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0

	//Getting the first token
	token[0] = strtok(buf, DELIMITER);

	if (token[0]) // If line is blank, don't do anything
	{
		for (num_tokens = 1; num_tokens < MAX_TOKENS_PER_LINE; num_tokens++)
		{
			token[num_tokens] = strtok(0, DELIMITER); // subsequent tokens
			if (!token[num_tokens]) break; // no more tokens
		}

	}

}

//Parsing the single machine's file
Machine* parse_FSM_file(string input_file)
{
	//Reading the input file name 
	//This variable determins which section of the file, we are in currently ::: 
	// Section 1 == Machine name, Section 2 = variables, Section3 = states, Section (4)= transitions
	//Initial state is always (1)
	int section = 1;

	//string transition= ;

	// create a file-reading object
	ifstream input;
	input.open(input_file); // open a file
	if (!input.good())
	{
		cout << "ERROR: The input file could not be read correctly! Please check it again" << endl;
		return NULL; // exit if file not found
	}

	// Reading the file (eoFile)
	while (!input.eof())
	{

		/*Variables Declaration*/

		char buf[MAX_CHARS_PER_LINE];
		int n = 0; // a for-loop index, number of actual tokens
		const char* token[MAX_TOKENS_PER_LINE] = {};    // array to store memory addresses of the tokens in buf


		//read an entire line into memory (buf)
		input.getline(buf, MAX_CHARS_PER_LINE);

		//Parsing one line, and recording the tokens in the array 
		parse_line(buf, n, token);



		/*Processing*/

		for (int i = 0; i < n; i++) // n = #of tokens
			cout << "Token[" << i << "] = " << token[i] << endl;

		//Checking for machine name, only if we get into a real variable

		if (token[0] != NULL)
		{
			switch (section){

			case (1) :



				machine_name = token[1]; // Because token[0]= FSM

				//Construct a machine, with this name 

				curr_machine = new Machine(machine_name);
				//Adding this machine to our global array of machines
				all_machines[count_machine++] = curr_machine;
				cout << "Machine was constructed correctly!" << endl;


				//updating the state
				section = 2;
				break;

			case (2) :

				//*****Section of VARIABLES******
				/* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CHECK THIS CHADAAAAAAAAAA
				//We will ignore the new variables, and we will set the same variables of the MFSM to each individual FSM
				for (int i = 0; i < curr_MFSM_machine->getNumVars(); i++)
				{

				}
				*/
				//Iterating on all the tokens (variables) available in this line
				for (int i = 1; i<n; i++)
				{
					curr_machine->setVariable(token[i]);
				}

				cout << "All variables, from the common MFSM, are set in the machine!" << endl;

				//updating the state
				section = 3;
				break;

			case (3) :

				//*******Section of STATES *******

				//If the first token is the word " STATE" don't do anything
				if (states_flag)
				{
					//Don't do anything, the following line is what we need

					real_token = token[0];

					//Checking for the end of the section
					if (real_token == "Transitions")
					{
						section = 4; //updating the section, ONLY if we find the word TRANSITION, otherwise we keep it in section = 3, to read the following states
					}
					else
					{
						//Constructing the state
						state_name = token[0];
						curr_state = new State(state_name);

						curr_machine->setState(curr_state);
						cout << "The state number " << curr_machine->getNumStates() << " was successfully constructed inside the current machine " << machine_name << endl;

						//Setting the actions of the state

						for (int j = 1; j<n; j++)
						{
							real_token = token[j];
							temp = real_token[0]; //To use it later in parsing the INCREMENT function (getting variables)

							if (real_token == "out") //>>>>>>>>>>>>>>>>>>>>>>parsing the out!
							{
								//updating the real token, to investigate on the next input
								real_token = token[++j];

								if (real_token == "\"") //>>>>>>>>>We will output string>>>>>>
								{
									//We Escape the token of the quotation mark, and we update
									
									real_token = token[++j]; //taking the token right after the quotation mark

									//Concatinating all the strings together, until finding the other quotation mark
									while (j<n && temp != "\"")
									{
										real_token = real_token + " " + token[++j]; //This one is to concatinate
										temp = token[j];                           // While this one is to get the individula next token
									}

									curr_action = new OutString(real_token);
									curr_state->setAction(curr_action);
								}
								else if (curr_MFSM_machine ->var_exist(real_token)) //We have received a variables in this machine, so we output its value
								{
									curr_action = new OutExpr(curr_MFSM_machine, curr_machine, real_token);
									curr_state->setAction(curr_action);
								}

								else if (curr_machine->var_exist(real_token)) //We have received a variables in this machine, so we output its value
								{
									curr_action = new OutExpr(curr_MFSM_machine,curr_machine, real_token);
									curr_state->setAction(curr_action);
								}
								else //We have received a constant
								{
									curr_action = new OutExpr(real_token);
									curr_state->setAction(curr_action);
								}
							}

							else if (real_token == "sleep") //>>>>>>>>>>>>>>>>>>Parsing SLEEP action
							{
								temp = token[++j];
								curr_action = new sleep(atoi(temp.c_str()));
								curr_state->setAction(curr_action);
							}

							else if (real_token == "wait") //>>>>>>>>>>>>>>>>>>>Parsing WAIT action
							{
								curr_action = new wait(curr_state);
								curr_state->setAction(curr_action);
							}

							else if (real_token == "run") //>>>>>>>>>>>>Parsing the RUN of a new machine
							{
								//Capturing the name of the machine, and updating it to be suitable as file name
								temp = token[++j];
								temp = temp + ".fsm.txt";
								
								//I have to parse this new machine recursively, meaning I pass it to a certain function which receives a file 
								//recursively calling the file parsing function
								all_machines[count_machine] = parse_FSM_file(temp);

								//Saving this action in the current state
								curr_action = new runMachine(all_machines[count_machine]);
								curr_state->setAction(curr_action);

								//Updating the number of our machines
								count_machine++;
							}

							else if (real_token == "end") //>>>>>>>>Parsing the END action
							{
								curr_action = new endMachine(curr_machine);
								curr_state->setAction(curr_action);
							}

							//A common variable from the MFSM
							else if (curr_MFSM_machine->var_exist(temp))
							{
								//Check if the syntaxt is correct

								if (real_token[1] == '=' && real_token[0] == real_token[2] && real_token[3] == '+' && real_token[4] == '1')
								{
									//We have the right syntaxt to increment now

									curr_action = new incrementVar(curr_MFSM_machine, temp);
									curr_state->setAction(curr_action);

								}

							}
							//An FSM variable for only one machine
							else if (curr_machine->var_exist(temp))//>>>>>>>>>>>>INCREMENT .. Is the first charachter of the token, a machine variable?
							{
								//Check if the syntaxt is correct

								if (real_token[1] == '=' && real_token[0] == real_token[2] && real_token[3] == '+' && real_token[4] == '1')
								{
									//We have the right syntaxt to increment now
									
									curr_action = new incrementVar(curr_machine, temp);
									curr_state->setAction(curr_action);

								}

							}
						}


					}


				}
				//now I update the state flag in order to read what is after the word state
				states_flag = true;
				break;


			case (4) :

				real_token = token[2]; //puting the integer into a string in order, to make it easy converting it to an integer

				// When I have transitions ready I set them to my corresponding states
				(curr_machine->getState(token[0]))->setTransition(curr_machine->getState(token[1]), atoi(real_token.c_str()));

				cout << "Trasition form the state \" " << token[0] << " \" to state  \" " << token[1] << " \" Is set! Congrats" << endl;

				/*last part of the prsing file is the transition part, so we are done */
			}
		}


		//Seperating tokens of different lines from each other
		cout << endl;
	}

	//Setting back the flag to its initial status
	states_flag = false;
	//returning the established machine
	return curr_machine;

}

MulMachine* parse_MFSM_file(string input_file)
{
	//Reading the input file name for MFSM
	//The variable "section" determins which section of the file, we are in currently ::: 
	// Section 1 == MFSM Machine name, Section 2 = common machine variables, Section3 = all machines

	//Initial state is always (1)
	int section = 1;
	string file_name;

	// create a file-reading object
	ifstream input;
	input.open(input_file); // open a file
	if (!input.good())
	{
		cout << "ERROR: The input file could not be read correctly! Please check it again" << endl;
		return NULL; // exit if file not found
	}

	// Reading the file (eoFile)
	while (!input.eof())
	{

		/*Variables Declaration*/

		char buf[MAX_CHARS_PER_LINE];
		int n = 0; // a for-loop index, number of actual tokens
		const char* token[MAX_TOKENS_PER_LINE] = {};    // array to store memory addresses of the tokens in buf


		//read an entire line into memory (buf)
		input.getline(buf, MAX_CHARS_PER_LINE);

		//Parsing one line, and recording the tokens in the array 
		parse_line(buf, n, token);



		/*Processing*/

		for (int i = 0; i < n; i++) // n = #of tokens
			cout << "Token[" << i << "] = " << token[i] << endl;

		//Checking for machine name, only if we get into a real variable, which has a value

		if (token[0] != NULL)
		{
			switch (section){

			case (1) :
				MFSMachine_name = token[1]; //Because token [0] = MFSM

				//Now let's Construct an MFSM machine, with this name 
				curr_MFSM_machine = new MulMachine(MFSMachine_name);
				cout << "The MFSM : " << curr_MFSM_machine->getName() << " Machine was constructed correctly!" << endl;

				/* ^^^^^^^^^^^^^^^^^^^^^CHECK THIS AGAIN CHADAAAAA ^^^^^^^^^^^^^^^^^^^^^^^^^^
				//Adding this machine to our global array of machines
				all_machines[count_machine++] = curr_machine;
				
				*/
				
				//updating the state
				section = 2;
				break;

			case(2):

				//Setting the common variables of the machine
				for (int i = 1; i < n; i++)
				{
					curr_MFSM_machine->setVariable(token[i]);
				}

				//updating the state
				section = 3;
				break;
			case(3) :
				real_token = token[0];

				if (real_token != "machines")
				{
					//Adding the extensions of the file
					file_name = token[0];
					file_name = file_name + ".fsm.txt";
					this_machine = parse_FSM_file(file_name);
					curr_MFSM_machine->setMachine(this_machine);

				}



			}

		}




		//Seperating tokens of different lines from each other
		cout << endl;
	}

	return curr_MFSM_machine;
}
#define _CRT_SECURE_NO_WARNINGS 1 

#include <iostream>
using std::cout;
using std::endl;
using namespace std;

#include <fstream>
using std::ifstream;

#include <cstring>
#include <string>
#include <sstream>
#include <map>


#include "Machine.h"
#include "State.h"


#include "endMachine.h"
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

string machine_name;
string state_name;
string real_token;
string temp;
string variables[MAX_VARIABLES_PER_MACHINE] ; //An array to store variables of a single machine
string actions[MAX_ACTIONS_PER_STATE]; //An array recording the actions of a signle state

Machine *all_machines [MAX_OF_MACHINES]; //Having an array of pointers to 3 machines
int count_machine =0;

Machine *curr_machine; //Declaring it as a global variable in order to enable changes for it throughout the program
State *curr_state;
Action *curr_action;

map <string, Machine> table_machine;
map <string, Action> table_action;

bool states_flag = false;

//Functions Prototypes:
void parse_line(char buf[], int& num_tokens, const char* token[]);
Machine* parse_file( string input_file);

  /*-------------- MAIN FUNCTION --------------*/

int main()
{

	string file_name;
	Machine* returned_mchn;

	cout<<" Please enter the name of the file you want to parse and create the machine out of it"<<endl;
	cin>> file_name;

	returned_mchn = parse_file(file_name);

	if( returned_mchn == NULL)
	{
		cout<<"Your file name is wrong!"<<endl;
		return 0;
	}
	else
	{
	//Executing the returned machine
	returned_mchn->run();
	}
	

	 //Deallocating the memmory & handelling exceptions
	  
	try
	{
	  for ( int i=0; i<count_machine; i++)
	  {
		  delete all_machines[i];
	  }
	}
	catch(...)
	{
		cout<<"EXCEPTION while deallocating the memory.. pointers are being deleted twice!"<<endl;
	}

  return 0;
}

//Definition of functions:

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

Machine* parse_file( string input_file)
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
		  cout<<"ERROR: The input file could not be read correctly! Please check it again"<<endl;
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

		if ( token[0] != NULL)
		{
		switch (section){

			case (1):

			
				
						machine_name =token[1]; // Because token[0]= FSM

						//Construct a machine, with this name 
										
						curr_machine = new Machine(machine_name);
						//Adding this machine to our global array of machines
						all_machines[count_machine++] = curr_machine;
						cout<<"Machine was constructed correctly!"<<endl;
				

					//updating the state
					section = 2;
					break;

			case (2): 
				
				//*****Section of VARIABLES******

						//Iterating on all the tokens (variables) available in this line
						for ( int i=1; i<n ; i++)
						{
							curr_machine->setVariable(token[i]) ;
						}
					
						cout<<"All variables are set in the machine!"<<endl;
				
					//updating the state
					section = 3;
					break;

			case (3):

				//*******Section of STATES *******

				//If the first token is the word " STATE" don't do anything
				if ( states_flag)
				{
					//Don't do anything, the following line is what we need

					real_token = token[0];
			
					//Checking for the end of the section
					if ( real_token == "Transitions")	
					{ 
						section = 4; //updating the section, ONLY if we find the word TRANSITION, otherwise we keep it in section = 3, to read the following states
					}
					else
					{
						//Constructing the state
						state_name = token [0];
						curr_state = new State(state_name);

						curr_machine->setState(curr_state);
						cout<<"The state number " << curr_machine->getNumStates() <<" was successfully constructed inside the current machine " << machine_name<<endl;

						//Setting the actions of the state
					
						for ( int j=1; j<n; j++)
						{
							real_token = token[j];
							temp = real_token[0]; //To use it later in parsing the INCREMENT function (getting variables)

							if ( real_token == "out") //>>>>>>>>>>>>>>>>>>>>>>parsing the out!
							{
								//updating the real token, to investigate on the next input
								real_token = token[++j];

								if ( real_token == "\"") //>>>>>>>>>We will output string>>>>>>
								{
									//We Escape the token of the quotation mark, and we update
									//j++;
									real_token = token[++j]; //taking the token right after the quotation mark

									//Concatinating all the strings together, until finding the other quotation mark
									while ( j<n && temp != "\"")
									{
										real_token = real_token + " "+ token[++j]; //This one is to concatinate
										temp = token[j];                           // While this one is to get the individula next token
									}

									curr_action = new OutString(real_token);
									curr_state->setAction(curr_action);
								}

								else if (curr_machine->var_exist(real_token)) //We have received a variables in this machine, so we output its value
								{
									curr_action = new OutExpr(curr_machine, real_token);
									curr_state->setAction(curr_action);								
								}
								else //We have received a constant
								{
									curr_action = new OutExpr(real_token);
									curr_state->setAction(curr_action);
								}
							}

							else if ( real_token == "sleep") //>>>>>>>>>>>>>>>>>>Parsing SLEEP action
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
								temp = token[++j];
								//I have to parse this new machine recursively, meaning I pass it to a certain function which receives a file 
								
								//recursively calling the file parsing function
								all_machines[count_machine]= parse_file(temp);
								
								//Running that machine
								cout<<"Running the following machine" <<all_machines[count_machine]->getName()<<" :"<<endl;
								all_machines[count_machine]->run();
								cout<<"END of running the machine: "<<all_machines[count_machine]->getName()<<endl;

								//Updating the number of our machines
								count_machine++;
							}
							
							else if (real_token =="end") //>>>>>>>>Parsing the END action
							{
								curr_action = new endMachine(curr_machine);
							}

							else if ( curr_machine->var_exist(temp))//>>>>>>>>>>>>INCREMENT .. Is the first charachter of the token, a machine variable?
							{
								//Check if the syntaxt is correct
							
								if( real_token[1] =='=' && real_token[0]==real_token[2] &&  real_token[3]=='+' && real_token[4]=='1')
								{
									//We have the right syntaxt to increment now
									curr_machine->incrementVar(temp);

								}

							}
						}


					}
			

				}
				//now I update the state flag in order to read what is after the word state
				states_flag = true;
					break;


			case (4):

				real_token = token[2]; //puting the integer into a string in order, to make it easy converting it to an integer

				// When I have transitions ready I set them to my corresponding states
				(curr_machine->getState(token[0]))->setTransition(curr_machine->getState(token[1]), atoi(real_token.c_str()));
			
				cout<<"Trasition form the state \" " <<token [0] <<" \" to state  \" "<<token[1]<< " \" Is set! Congrats"<<endl;

				/*last part of the prsing file is the transition part, so we are done */
			}
		}


	

			//If I see the variable state, then each line, is a construction of a new state, until we find Transistions, we go back and we set the transistion for each state





		//Seperating tokens of different lines from each other
		cout << endl;
	  }
	   
	   //returning the established machine
	  return curr_machine;

}

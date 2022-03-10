//***************************************************************************
//
//  Eric Kellogg
//  Z1942596
//  CSCI 330 section 1
//
//  I certify that this is my own work and where appropriate an extension 
//  of the starter code provided for the assignment.
//
//***************************************************************************



#include <iostream>
#include <string>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	
bool endprg = false; // bool to see if the program is to end
while(endprg == false)
{	
	std::string command;
	std::string command2;

	std::cout << "Command 1: ";
	getline(std::cin, command); // pulls the entered commands for the first run
	if(command == "END") // if END is entered it shuts the program off
		endprg = true;
	else
	{
		std::cout << "Command 2: "; // pulls the entered commands for the first run
		getline(std::cin, command2); 
		command.c_str();

		char cpy_arr[256];
		strcpy(cpy_arr,command.c_str()); //converts the command to a usable string for strtok
			
		char *args[255];  
		char *token = strtok(cpy_arr, " "); //breaks apart the string into tokens 
		int i = 0;
		while(token != NULL) //enters the tokens into a character array so that the exec function can use it
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = nullptr;

		char cpy_arr2[256];
		strcpy(cpy_arr2,command2.c_str());
			
		char *args2[255];  
		char *token2 = strtok(cpy_arr2, " ");
		int j = 0;
		while(token2 != NULL)
		{
			args2[j++] = token2;
			token2 = strtok(NULL, " ");
		}
		args2[j] = nullptr;

		int rs;
		int pipefd[2];

		rs = pipe(pipefd);
		if(rs == -1)
		{
			perror("pipe");
			exit(1);
		}
		pid_t pid = fork(); //creates a fork so that we can execute the two seperate commands at the same time
		char *buffer[256];
		if(pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if(pid == 0) //child
		{
			
			close(pipefd[1]);
			close(0);
			dup(pipefd[0]);
			close(pipefd[0]);
			execvp(args2[0], args2);
		}
		else 	//parent
		{
			close(pipefd[0]);
			close(1);
			dup(pipefd[1]);
			close(pipefd[1]);
			execvp(args[0], args);
			wait(nullptr);
		}
	}

}		
	return 0;
}

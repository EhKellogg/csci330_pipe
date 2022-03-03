#include <iostream>
#include <string>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{	
	std::string command;
	std::string command2;

	std::cout << "Command 1: ";
	getline(std::cin, command);
	std::cout << "Command 2: ";
	getline(std::cin, command2);
	command.c_str();

	char cpy_arr[256];
	strcpy(cpy_arr,command.c_str());
		
	char *args[255]; // = {"ls","-l", NULL}; 
	char *token = strtok(cpy_arr, " ");
	int i = 0;
	while(token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = nullptr;

	command2.c_str();
	char cpy_arr2[256];
	strcpy(cpy_arr2,command2.c_str());
		
	char *args2[255]; // = {"ls","-l", NULL}; 
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
	pid_t pid = fork();
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
	//	execlp("wc","wc", nullptr);
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

		
	return 0;
}

#include <iostream>
#include <string>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	
bool endprg = false;
while(endprg == false)
{	
	std::string command;
	std::string command2;

	std::cout << "Command 1: ";
	getline(std::cin, command);
	if(command == "END")
		endprg = true;
	else
	{
		std::cout << "Command 2: ";
		getline(std::cin, command2);
		command.c_str();

		char cpy_arr[256];
		strcpy(cpy_arr,command.c_str());
			
		char *args[255];  
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
		

//while(endprg == false)
//{		
		pid_t pid = fork();
		pid_t pid2 = fork();
		char *buffer[256];
		if(pid == -1 || pid2 == -1)
		{
			perror("fork");
			exit(1);
		}
		else if(pid > 0 && pid2 > 0) //parent
		{
			wait(NULL);
			wait(NULL);
			
		}
		else if(pid == 0 && pid2 > 0) //1st child
		{	
			sleep(2);
			std::cout << "child 1" << std::endl;
			close(pipefd[1]);
			close(0);
			dup(pipefd[0]);
			close(pipefd[0]);
			execvp(args2[0], args2);
		}
		else if(pid > 0 && pid2 ==0) //2nd child
		{	
			std::cout << "2nd child" << std::endl;
			sleep(1);
			close(pipefd[0]);
			close(1);
			dup(pipefd[1]);
			close(pipefd[1]);
			execvp(args[0], args);
		//	wait(nullptr);
		}
		else 	//parent
		{
			std::cout << "grandchild" << std::endl;
		//	close(pipefd[0]);
		//	close(1);
		//	dup(pipefd[1]);
		//	close(pipefd[1]);
		//	execvp(args[0], args);
		//	wait(nullptr);
		}
	}

}		
	return 0;
}

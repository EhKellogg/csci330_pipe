#include <iostream>
#include <string>
#include <unistd.h>
#include <string.h>

int main()
{	
	int fd;
	char buffer[255];
	std::cout << "Command 1: ";
	std::cin >> buffer;
//	std::cin.getline(buffer, sizeof(buffer));	
	char *token = strtok(buffer, " ");
	while(token)
	{
 		std::cout << token << std::endl;
	}	
	execlp(buffer[0], buffer[0], buffer, nullptr);
}

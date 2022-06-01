#include <iostream>
#include <string>
#include <ctime>

#include <vector>
#include <map>
#include <stack>

#define YELLOW "\033[0;33m"
#define DEFAULT "\033[0m"

int	main(void)
{
	clock_t		start;
	clock_t		end;
	double		result;
	std::string	cmd;

/*
	start = clock();
	//
	end = clock();
	result = static_cast<double>(end - start);
	std::cout<<"수행 시간: "<<result<<"ms"<<std::endl;
*/
	std::cout<<YELLOW<<"[ STD_containers ]"<<DEFAULT<<std::endl;
	while (1)
	{
		std::cout<<"> ";
		std::getline(std::cin, cmd);
		if ((cmd == "vector") || (cmd == "v"))
			;
		else if ((cmd == "map") || (cmd == "m"))
			;
		else if ((cmd == "stack") || (cmd == "s"))
			;
		else if (cmd == "exit")
		{
			std::cout<<"exit"<<std::endl;
			break ;
		}
	}
	return (0);
}

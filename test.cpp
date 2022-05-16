#include <iostream>
#include <string>

#include <vector>
#include "vector.hpp"

#define YELLOW "\033[0;33m"
#define DEFAULT "\033[0m"

template <typename T>
void	show_vector(const std::string &str, T t, int size)
{
	std::cout<<"-> "<<str<<std::endl;
	std::cout<<"size: "<<t.size()<<", capacity: "<<t.capacity()<<std::endl;
	for (int i = 0; i < size; ++i)
		std::cout<<t[i]<<" ";
	std::cout<<std::endl;
}

int	main(void)
{
	std::cout<<YELLOW<<"[ constructor - default ]"<<DEFAULT<<std::endl;

	int	size = 0;

	std::vector<int>	svi1;
	ft::vector<int>		fvi1;

	show_vector("std", svi1, size);
	show_vector("ft", fvi1, size);

	std::cout<<YELLOW<<"[ constructor - fill ]"<<DEFAULT<<std::endl;

	int	val = 10;

	size = 4;
	std::vector<int>	svi2(size, val);
	ft::vector<int>		fvi2(size, val);

	show_vector("std", svi2, size);
	std::cout<<std::endl;
	show_vector("ft", fvi2, size);
	std::cout<<std::endl;

	std::cout<<YELLOW<<"[ constructor - range ]"<<DEFAULT<<std::endl;
	int	arr[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};
	int	arr_size = sizeof(arr) / sizeof(int);

	const std::vector<int>	svi3(&arr[0], &arr[arr_size]);
	const ft::vector<int>		fvi3(&arr[0], &arr[arr_size]);

	show_vector("std", svi3, arr_size);
	std::cout<<std::endl;
	show_vector("ft", fvi3, arr_size);
	std::cout<<std::endl;

	std::cout<<YELLOW<<"[ constructor - copy ]"<<DEFAULT<<std::endl;

	std::vector<int>	svi4(svi3);
	ft::vector<int>		fvi4(fvi3);

	std::cout<<"svi4(siv3)"<<std::endl;
	show_vector("std", svi4, arr_size);
	std::cout<<std::endl;
	std::cout<<"fvi4(fiv3)"<<std::endl;
	show_vector("ft", fvi4, arr_size);
	std::cout<<std::endl;

	std::cout<<YELLOW<<"[ vector : revese_iterator ]"<<DEFAULT<<std::endl;

	std::vector<int>::const_iterator	sitb = svi3.begin();
	ft::vector<int>::const_iterator		fitb = fvi3.begin();
	std::vector<int>::const_iterator	site = svi3.end();
	ft::vector<int>::const_iterator		fite = fvi3.end();

	std::vector<int>::const_reverse_iterator	sritb = svi3.rbegin();
	ft::vector<int>::const_reverse_iterator		fritb = fvi3.rbegin();
	std::vector<int>::const_reverse_iterator	srite = svi3.rend();
	ft::vector<int>::const_reverse_iterator		frite = fvi3.rend();

	std::cout<<"------ iterator --------"<<std::endl;
	std::cout<<"std begin ->	"<<*sitb<<std::endl;
	std::cout<<"ft  begin ->	"<<*fitb<<std::endl;
	std::cout<<"std end   ->	"<<*site<<std::endl;
	std::cout<<"ft  end   ->	"<<*fite<<std::endl;

	std::cout<<" std default"<<std::endl;
	for (std::vector<int>::const_iterator tmp = sitb; tmp != site; ++tmp)
		std::cout<<*tmp<<" ";
	std::cout<<std::endl;
	std::cout<<" ft default"<<std::endl;
	for (ft::vector<int>::const_iterator tmp = fitb; tmp != fite; ++tmp)
		std::cout<<*tmp<<" ";
	std::cout<<std::endl;

	std::cout<<"--- reverse_iterator ---"<<std::endl;
	std::cout<<"std rbegin ->	"<<*sritb<<std::endl;
	std::cout<<"ft  rbegin ->	"<<*fritb<<std::endl;
	std::cout<<"std rend   ->	"<<*srite<<std::endl;
	std::cout<<"ft  rend   ->	"<<*frite<<std::endl;

	std::cout<<" std reverse"<<std::endl;
	for (std::vector<int>::const_reverse_iterator tmp = sritb; tmp != srite; ++tmp)
		std::cout<<*tmp<<" ";
	std::cout<<std::endl;
	std::cout<<" ft reverse"<<std::endl;
	for (ft::vector<int>::const_reverse_iterator tmp = fritb; tmp != frite; ++tmp)
		std::cout<<*tmp<<" ";
	std::cout<<std::endl;

	return (0);
}
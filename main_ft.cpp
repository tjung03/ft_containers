#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"

#define YELLOW "\033[0;33m"
#define DEFAULT "\033[0m"

//////////////////////////////////////////////////////////// VECTOR
template <typename Vector>
void	show_vector(Vector &test)
{
	typedef	typename Vector::iterator	iterator;

	iterator	begin = test.begin();
	iterator	end = test.end();

	std::cout<<YELLOW<<"[ VECTOR address: "<<&test<<" ]"<<DEFAULT<<std::endl;
	std::cout<<"-> vector size: "<<test.size()<<std::endl;
	std::cout<<"-> vector capacity: "<<test.capacity()<<std::endl;
	std::cout<<"---------------------------------------"<<std::endl;
	for (iterator tmp = begin; tmp != end; ++tmp)
		std::cout<<"("<<*tmp<<") "<<std::endl;
	std::cout<<std::endl<<std::endl;
}

//////////////////////////////////////////////////////////// MAP

template <typename Map>
void	print_node(ft::rb_node<typename Map::value_type >* node)
{
	std::string	red("R");
	std::string	black("B");

	if (node->_color == 1)
		std::cout<<"("<<red<<", "<<node->_value.first<<")";
	else
		std::cout<<"("<<black<<", "<<node->_value.first<<")";
}

template <typename Map>
void	print_node_line(ft::rb_node<typename Map::value_type >* node, ft::rb_node<typename Map::value_type >* root)
{
	ft::rb_node<typename Map::value_type >*	cur = node;
	int										depth = 0;

	if (node != root)
	{
		while (cur->_parent != NULL)
		{
			depth++;
			cur = cur->_parent;
		}
		for (int i = 0; i < depth; ++i)
			std::cout<<"\t\t";
		std::cout<<"~~";
		print_node<Map>(node);
		std::cout<<std::endl;
	}
	else
	{
		print_node<Map>(root);
		std::cout<<"~~"<<std::endl;
	}
}

template <typename Map>
void	show_tree(typename Map::iterator &begin, typename Map::iterator &end, ft::rb_node<typename Map::value_type>* root)
{
	typedef	typename Map::iterator	iterator;

	iterator	max = --end;

	for (iterator tmp = max; tmp != begin; --tmp)
		print_node_line<Map>(tmp.get_node_ptr(), root);
	print_node_line<Map>(begin.get_node_ptr(), root);
}

template <typename Map>
void	show_map(Map &test)
{
	typedef	typename Map::iterator					iterator;
	typedef	ft::rb_node<typename Map::value_type>*	node_ptr;

	iterator	begin = test.begin();
	iterator	end = test.end();
	node_ptr	root;

	std::cout<<YELLOW<<"[ MAP address: "<<&test<<" ]"<<DEFAULT<<std::endl;
	for (iterator tmp = begin; tmp != end; ++tmp)
	{
		root = tmp.get_node_ptr();
		if (root->_parent == NULL)
		{
			std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
			show_tree<Map>(begin, end, root);
			std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
			break ;
		}
	}

	std::cout<<"-> map size: "<<test.size()<<std::endl;
	for (iterator tmp = begin; tmp != end; ++tmp)
		std::cout<<"("<<(*tmp).first<<") "<<std::endl;
	std::cout<<std::endl<<std::endl;
}

//////////////////////////////////////////////////////////// STACK
template <typename T>
class	MutantStack : public ft::stack<T>
{
public:
	MutantStack(void) { }
	MutantStack(const MutantStack<T> &src) { *this = src; }
	MutantStack<T>&	operator=(const MutantStack<T> &rhs)
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack(void) { }

	typedef	typename ft::stack<T>::container_type::iterator	iterator;

	iterator	begin(void) { return (this->c.begin()); }
	iterator	end(void) { return (this->c.end()); }
};

template <typename MutantStack>
void	show_stack(MutantStack &test)
{
	typedef	typename MutantStack::iterator	iterator;

	iterator	begin = test.begin();
	iterator	end = test.end();

	std::cout<<YELLOW<<"[ STACK address: "<<&test<<" ]"<<DEFAULT<<std::endl;
	std::cout<<"-> stack size: "<<test.size()<<std::endl;
	std::cout<<"---------------------------------------"<<std::endl;
	for (iterator tmp = begin; tmp != end; ++tmp)
		std::cout<<"("<<*tmp<<") "<<std::endl;
	std::cout<<std::endl<<std::endl;
}

//////////////////////////////////////////////////////////// SHOW END

std::string	vec_func[] = {
	"01. default constructor",
	"02. fill constructor",
	"03. range constructor",
	"04. copy constructor",
	"05. operator=",
	"06. begin",
	"07. const begin",
	"08. end",
	"09. const end",
	"10. rbegin",
	"11. const rbegin",
	"12. rend",
	"13. const rend",
	"14. size",
	"15. max size",
	"16. resize",
	"17. capacity",
	"18. empty",
	"19. reserve",
	"20. operator[]",
	"21. const operator[]",
	"22. at",
	"23. const at",
	"24. front",
	"25. const front",
	"26. back",
	"27. const back",
	"28. range assign",
	"29. fill assign",
	"30. push_back",
	"31. single element insert",
	"32. fill insert",
	"33. range insert",
	"34. element erase",
	"35. range erase",
	"36. member swap",
	"37. clear",
	"38. get_allocator",
	"39. operator==",
	"40. operator!=",
	"41. operator<",
	"42. operator<=",
	"43. operator>",
	"44. operator>=",
	"45. non-member swap"
};

std::string	map_func[] = {
	"01. empty constructor",
	"02. range constructor",
	"03. copy constructor",
	"04. operator=",
	"05. begin",
	"06. const begin",
	"07. end",
	"08. const end",
	"09. rbegin",
	"10. const rbegin",
	"11. rend",
	"12. const rend",
	"13. empty",
	"14. size",
	"15. max size",
	"16. operator[]",
	"17. single element insert",
	"18. with hint insert",
	"19. range insert",
	"20. iter element erase",
	"21. key element erase",
	"22. range erase",
	"23. member swap",
	"24. clear",
	"25. key_comp",
	"26. value_comp",
	"27. find",
	"28. const find",
	"29. count",
	"30. lower_bound",
	"31. const lower_bound",
	"32. upper_bound",
	"33. const upper_bound",
	"34. equal_range",
	"35. const equal_range",
	"36. get_allocator",
	"37. operator==",
	"38. operator!=",
	"39. operator<",
	"40. operator<=",
	"41. operator>",
	"42. operator>=",
	"43. non-member swap"
};

std::string	stack_func[] = {
	"01. default constructor",
	"02. empty",
	"03. size",
	"04. top",
	"05. const top",
	"06. push",
	"07. pop",
	"08. operator==",
	"09. operator!=",
	"10. operator<",
	"11. operator<=",
	"12. operator>",
	"13. operator>=",
};

void	print_str(const std::string adr[], int size)
{
	for (int i = 0; i < size; ++i)
		std::cout<<adr[i]<<std::endl;
	std::cout<<std::endl;
}

void	do_vector(void)
{
	std::string	cmd;

	std::cout<<"lv.2) insert"<<std::endl;
	std::cout<<YELLOW<<"00. 'escape' or 'e'"<<DEFAULT<<std::endl;
	print_str(vec_func, 45);
	while (1)
	{
		std::cout<<YELLOW<<"> "<<DEFAULT;
		std::getline(std::cin, cmd);
		system("clear");
		if ((cmd == "escape") || (cmd == "e"))
		{
			std::cout<<"Escape complete"<<std::endl<<std::endl;
			break ;
		}
	}
}

void	do_map(void)
{
	std::string	cmd;

	std::cout<<"lv.2) insert"<<std::endl;
	std::cout<<YELLOW<<"00. 'escape' or 'e'"<<DEFAULT<<std::endl;
	print_str(map_func, 43);
	while (1)
	{
		std::cout<<YELLOW<<"> "<<DEFAULT;
		std::getline(std::cin, cmd);
		system("clear");
		if ((cmd == "escape") || (cmd == "e"))
		{
			std::cout<<"Escape complete"<<std::endl<<std::endl;
			break ;
		}
	}
}

void	do_stack(void)
{
	std::string	cmd;

	std::cout<<"lv.2) insert"<<std::endl;
	std::cout<<YELLOW<<"00. 'escape' or 'e'"<<DEFAULT<<std::endl;
	print_str(stack_func, 13);
	while (1)
	{
		std::cout<<YELLOW<<"> "<<DEFAULT;
		std::getline(std::cin, cmd);
		system("clear");
		if ((cmd == "escape") || (cmd == "e"))
		{
			std::cout<<"Escape complete"<<std::endl<<std::endl;
			break ;
		}
	}
}

int	main(void)
{
	std::string	cmd;

/*
	clock_t		start;
	clock_t		end;
	double		result;

	start = clock();
	//
	end = clock();
	result = static_cast<double>(end - start);
	std::cout<<"수행 시간: "<<result<<"ms"<<std::endl;
*/
	while (1)
	{
		std::cout<<YELLOW<<"[ FT_containers ]"<<DEFAULT<<std::endl<<std::endl;
		std::cout<<"lv.1) insert"<<std::endl;
		std::cout<<"1. 'vector' or 'v'"<<std::endl;
		std::cout<<"2. 'map' or 'm'"<<std::endl;
		std::cout<<"3. 'stack' or 's'"<<std::endl;
		std::cout<<"4. 'exit' or 'e'"<<std::endl<<std::endl;
		std::cout<<YELLOW<<"> "<<DEFAULT;
		std::getline(std::cin, cmd);
		system("clear");
		if ((cmd == "vector") || (cmd == "v"))
			do_vector();
		else if ((cmd == "map") || (cmd == "m"))
			do_map();
		else if ((cmd == "stack") || (cmd == "s"))
			do_stack();
		else if ((cmd == "exit") || (cmd == "e"))
		{
			std::cout<<"Exit complete"<<std::endl<<std::endl;
			break ;
		}
	}
	return (0);
}

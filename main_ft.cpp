#include <iostream>
#include <string>

#include <vector>
#include <map>
#include "vector.hpp"
#include "map.hpp"

#define YELLOW "\033[0;33m"
#define DEFAULT "\033[0m"

typedef	ft::map<int,int>::iterator	ft_iterator;
typedef ft::rb_node<ft::pair<const int,int> >*	node_ptr;

void	print_node(node_ptr node)
{
	std::string	red("R");
	std::string	black("B");

	if (node->_color == 1)
		std::cout<<"("<<red<<", "<<node->_value.first<<")";
	else
		std::cout<<"("<<black<<", "<<node->_value.first<<")";
}

void	print_node_line(node_ptr node, node_ptr root)
{
	node_ptr	cur = node;
	int			depth = 0;

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
		print_node(node);
		std::cout<<std::endl;
	}
	else
	{
		print_node(root);
		std::cout<<"~~"<<std::endl;
	}
}

void	show_tree(ft_iterator &begin, ft_iterator &end, node_ptr root)
{
	ft_iterator	max = --end;

	for (ft_iterator tmp = max; tmp != begin; --tmp)
		print_node_line(tmp.get_node_ptr(), root);
	print_node_line(begin.get_node_ptr(), root);
}

void	show_map(ft::map<int,int> &fm)
{
	ft_iterator	begin = fm.begin();
	ft_iterator	end = fm.end();
	node_ptr	root;

	for (ft_iterator tmp = begin; tmp != end; ++tmp)
	{
		root = tmp.get_node_ptr();
		if (root->_parent == NULL)
		{
			std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
			show_tree(begin, end, root);
			std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
			break ;
		}
	}
}

int	main(void)
{
	ft::map<int,int>	fm;

	for (int i = 0; i < 10; ++i)
		fm.insert(ft::make_pair(i+1, i*10));

	show_map(fm);
	return (0);
}
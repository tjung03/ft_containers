#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <memory>
# include "rb_node.hpp"
# include "iterator.hpp"
# include "utils.hpp"

namespace	ft
{
	template	<
			typename Key, typename Val, typename Compare,
			typename Allocator = std::allocator<Val>
				>
	class	red_black_tree
	{
	public:
		typedef	Key																		key_type;
		typedef	Val																		value_type;
		typedef	Compare																	compare_type;
		typedef	Allocator																pair_allocator;
		typedef	typename pair_allocator::template rebind<rb_node<value_type> >::other	node_allocator;

		typedef	std::ptrdiff_t							difference_type;
		typedef	std::size_t								size_type;

		typedef	rb_node<value_type>*					node_ptr;
		typedef rb_node<value_type>						node;

		typedef	rb_tree_iterator<value_type>			iterator;
		typedef const_rb_tree_iterator<value_type>		const_iterator;
		typedef	ft::reverse_iterator<iterator>			reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		explicit red_black_tree(const Compare &comp, const node_allocator &alloc = node_allocator())
			: _size(0), _comp(comp), _alloc(alloc)
		{
			this->_leaf = this->_alloc.allocate(1);
			this->_alloc.construct(this->_leaf, node(BLACK));
			this->_root = this->_leaf;
		}

		virtual ~red_black_tree(void)
		{
			this->_alloc.destroy(this->_leaf);
			this->_alloc.deallocate(this->_leaf, 1);
		}

		iterator	begin(void)
		{
			if (this->is_leaf(this->_root))
				return (iterator(this->_leaf));

			node_ptr	small = this->_root;

			while (small->_left != this->_leaf)
				small = small->_left;
			return (iterator(small));
		}

		const_iterator	begin(void) const
		{
			if (this->is_leaf(this->_root))
				return (const_iterator(this->_leaf));

			node_ptr	small = this->_root;

			while (small->_left != this->_leaf)
				small = small->_left;
			return (const_iterator(small));
		}

		iterator		end(void) { return (iterator(this->_leaf)); }
		const_iterator	end(void) const { return (const_iterator(this->_leaf)); }

		pair<iterator, bool>	insert_node(const value_type &val)
		{
			if (!this->is_leaf(this->_root))
			{
				iterator	it_b = this->begin();
				iterator	it_e = this->end();
				for (iterator tmp = it_b; tmp != it_e; ++tmp)
				{
					if (tmp->first == val.first)
						return (ft::make_pair(iterator(tmp), false));
				}

				node_ptr	temp = this->_alloc.allocate(1);
				this->_alloc.construct(temp, node(RED, val, NULL, this->_leaf, this->_leaf));

				node_ptr	cur = this->_root;
				while (true)
				{
					if (_comp(temp->_value, cur->_value))
					{
						if (this->is_leaf(cur->_left))
						{
							cur->_left = temp;
							temp->_parent = cur;
						}
						else
						{
							cur = cur->_left;
							continue ;
						}
					}
					else
					{
						if (this->is_leaf(cur->_right))
						{
							cur->_right = temp;
							temp->_parent = cur;
						}
						else
						{
							cur = cur->_right;
							continue ;
						}
					}
					break ;
				}
				insert_case1(temp);
				++this->_size;
				update_root(temp);
				update_leaf_parent(this->_root);
				return (ft::make_pair(iterator(temp), true));
			}
			node_ptr	temp = this->_alloc.allocate(1);
			this->_alloc.construct(temp, node(RED, val, NULL, this->_leaf, this->_leaf));
			this->_root = temp;
			this->_leaf->_parent = this->_root;
			insert_case1(this->_root);
			++this->_size;
			return (ft::make_pair(iterator(temp), true));
		}

		bool	delete_node(const value_type &val)
		{
			node_ptr	cur = this->_root;

			while (cur != this->_leaf)
			{
				if (!this->_comp(val, cur->_value) && !this->_comp(cur->_value, val))
					break ;
				if (this->_comp(val, cur->_value))
					cur = cur->_left;
				else
					cur = cur->_right;
			}
			if (cur == this->_leaf)
				return (false);

			if ((cur->_left != this->_leaf) && (cur->_right != this->_leaf))
			{
				node_ptr	predecessor  = cur->_left;

				while (predecessor->_right != this->_leaf)
					predecessor = predecessor->_right;

				node_ptr	replace = this->_alloc.allocate(1);
				this->_alloc.construct(replace, node(cur->_color, predecessor->_value, \
													cur->_parent, cur->_left, cur->_right));

				if (replace->_parent != NULL)
				{
					if (replace->_parent->_left == cur)
						cur->_parent->_left = replace;
					else
						cur->_parent->_right = replace;
				}
				else
					this->_root = replace;
				if (cur->_left != this->_leaf)
					cur->_left->_parent = replace;
				if (cur->_right != this->_leaf)
					cur->_right->_parent = replace;
				this->_alloc.destroy(cur);
				this->_alloc.deallocate(cur, 1);
				delete_one_child(predecessor);
				update_root(this->_root);
				update_leaf_parent(this->_root);
			}
			else
			{
				if (cur->_parent == NULL)
				{
					node_ptr	child;

					if (cur->_left != this->_leaf)
						child = cur->_left;
					else
						child = cur->_right;
					this->_alloc.destroy(this->_root);
					this->_alloc.deallocate(this->_root, 1);
					this->_root = NULL;
					if (child == this->_leaf)
					{
						this->_root = this->_leaf;
						this->_leaf->_parent = NULL;
					}
					else
					{
						child->_parent = NULL;
						this->_root = child;
						this->_leaf->_parent = this->_root;
					}
				}
				else
				{
					node_ptr	random = cur->_parent;
					delete_one_child(cur);
					update_root(random);
					update_leaf_parent(this->_root);
				}
			}
			--this->_size;
			return (true);
		}

		size_type	size(void) const { return (this->_size); }
		size_type	max_size(void) const { return (this->_alloc.max_size()); }

	private:
		node_ptr		_root;
		node_ptr		_leaf;
		size_type		_size;
		compare_type	_comp;
		node_allocator	_alloc;

		void	update_root(node_ptr cur)
		{
			while (cur->_parent)
				cur = cur->_parent;
			this->_root = cur;
		}

		void	update_leaf_parent(node_ptr cur)
		{
			while (cur->_right != this->_leaf)
				cur = cur->_right;
			this->_leaf->_parent = cur;
		}

		node_ptr	grandparent(node_ptr n)
		{
			if ((n != NULL) && (n->_parent != NULL))
				return (n->_parent->_parent);
			else
				return (NULL);
		}

		node_ptr	uncle(node_ptr n)
		{
			node_ptr	g = grandparent(n);
			if (g == NULL)
				return (NULL);
			if (n->_parent == g->_left)
				return (g->_right);
			else
				return (g->_left);
		}

		static void	rotate_left(node_ptr n)
		{
			node_ptr	c = n->_right;
			node_ptr	p = n->_parent;

			if (c->_left != NULL)
				c->_left->_parent = n;

			n->_right = c->_left;
			n->_parent = c;
			c->_left = n;
			c->_parent = p;

			if (p != NULL)
			{
				if (p->_left == n)
					p->_left = c;
				else
					p->_right = c;
			}
		}

		static void	rotate_right(node_ptr n)
		{
			node_ptr	c = n->_left;
			node_ptr	p = n->_parent;

			if (c->_right != NULL)
				c->_right->_parent = n;

			n->_left = c->_right;
			n->_parent = c;
			c->_right = n;
			c->_parent = p;

			if (p != NULL)
			{
				if (p->_right == n)
					p->_right = c;
				else
					p->_left = c;
			}
		}

		void	insert_case1(node_ptr n)
		{
			if (n->_parent == NULL)
				n->_color = BLACK;
			else
				insert_case2(n);
		}

		void	insert_case2(node_ptr n)
		{
			if (n->_parent->_color == BLACK)
				return ;
			else
				insert_case3(n);
		}

		void	insert_case3(node_ptr n)
		{
			node_ptr	u = uncle(n);
			node_ptr	g;

			if ((u != NULL) && (u->_color == RED))
			{
				n->_parent->_color = BLACK;
				u->_color = BLACK;
				g = grandparent(n);
				g->_color = RED;
				insert_case1(g);
			}
			else
			{
				insert_case4(n);
			}
		}

		void	insert_case4(node_ptr n)
		{
			node_ptr	g = grandparent(n);

			if ((n == n->_parent->_right) && (n->_parent == g->_left))
			{
				rotate_left(n->_parent);
				n = n->_left;
			}
			else if ((n == n->_parent->_left) && (n->_parent == g->_right))
			{
				rotate_right(n->_parent);
				n = n->_right;
			}
			insert_case5(n);
		}

		void	insert_case5(node_ptr n)
		{
			node_ptr	g = grandparent(n);

			n->_parent->_color = BLACK;
			g->_color = RED;
			if (n == n->_parent->_left)
				rotate_right(g);
			else
				rotate_left(g);
		}

		node_ptr	sibling(node_ptr n)
		{
			if (n == n->_parent->_left)
				return (n->_parent->_right);
			else
				return (n->_parent->_left);
		}

		int	is_leaf(node_ptr n) const
		{
			return ((n == this->_leaf) ? 1 : 0);
		}

		void	replace_node(node_ptr n, node_ptr child)
		{
			child->_parent = n->_parent;
			if (n->_parent->_left == n)
				n->_parent->_left = child;
			else if (n->_parent->_right == n)
				n->_parent->_right = child;
		}

		void	delete_one_child(node_ptr n)
		{
			node_ptr	child = is_leaf(n->_right) ? n->_left : n->_right;

			replace_node(n, child);
			if (n->_color == BLACK)
			{
				if (child->_color == RED)
					child->_color = BLACK;
				else
					delete_case1(child);
			}
			this->_alloc.destroy(n);
			this->_alloc.deallocate(n, 1);
		}

		void	delete_case1(node_ptr n)
		{
			if (n->_parent != NULL)
				delete_case2(n);
		}

		void	delete_case2(node_ptr n)
		{
			node_ptr	s = sibling(n);

			if (s->_color == RED)
			{
				n->_parent->_color = RED;
				s->_color = BLACK;
				if (n == n->_parent->_left)
					rotate_left(n->_parent);
				else
					rotate_right(n->_parent);
			}
			delete_case3(n);
		}

		void	delete_case3(node_ptr n)
		{
			node_ptr	s = sibling(n);

			if ((n->_parent->_color == BLACK) &&
				(s->_color == BLACK) &&
				(s->_left->_color == BLACK) &&
				(s->_right->_color == BLACK))
			{
				s->_color = RED;
				delete_case1(n->_parent);
			}
			else
				delete_case4(n);
		}

		void	delete_case4(node_ptr n)
		{
			node_ptr	s = sibling(n);

			if ((n->_parent->_color == RED) &&
				(s->_color == BLACK) &&
				(s->_left->_color == BLACK) &&
				(s->_right->_color == BLACK))
			{
				s->_color = RED;
				n->_parent->_color = BLACK;
			}
			else
				delete_case5(n);
		}

		void	delete_case5(node_ptr n)
		{
			node_ptr	s = sibling(n);

			if  (s->_color == BLACK)
			{
				node_ptr	tmp_parent = NULL;

				if ((n == n->_parent->_left) &&
					(s->_right->_color == BLACK) &&
					(s->_left->_color == RED))
				{
					s->_color = RED;
					s->_left->_color = BLACK;
					if (n == this->_leaf)
						tmp_parent = n->_parent;
					rotate_right(s);
					n->_parent = tmp_parent;
				}
				else if ((n == n->_parent->_right) &&
					(s->_left->_color == BLACK) &&
					(s->_right->_color == RED))
				{
					s->_color = RED;
					s->_right->_color = BLACK;
					if (n == this->_leaf)
						tmp_parent = n->_parent;
					rotate_left(s);
					n->_parent = tmp_parent;
				}
			}
			delete_case6(n);
		}

		void	delete_case6(node_ptr n)
		{
			node_ptr	s = sibling(n);

			s->_color = n->_parent->_color;
			n->_parent->_color = BLACK;

			if (n == n->_parent->_left)
			{
				s->_right->_color = BLACK;
				rotate_left(n->_parent);
			}
			else
			{
				s->_left->_color = BLACK;
				rotate_right(n->_parent);
			}
		}

	};

}

#endif

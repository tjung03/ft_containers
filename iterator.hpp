#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include "rb_node.hpp"

namespace	ft
{
	struct	input_iterator_tag { };
	struct	output_iterator_tag { };
	struct	forward_iterator_tag : public input_iterator_tag { };
	struct	bidirectional_iterator_tag : public forward_iterator_tag { };
	struct	random_access_iterator_tag : public bidirectional_iterator_tag { };

/* ************************************************************************************ */
/*																						*/
/*										iterator										*/
/*																						*/
/* ************************************************************************************ */

	template	<
			typename Category,						// iterator::iterator_category
			typename T,								// iterator::value_type
			typename Distance = std::ptrdiff_t,		// iterator::difference_type
			typename Pointer = T*,					// iterator::pointer
			typename Reference = T&					// iterator::reference
				>
	struct	iterator
	{
		typedef	Category	iterator_category;
		typedef	T			value_type;
		typedef	Distance	difference_type;
		typedef	Pointer		pointer;
		typedef	Reference	reference;
	};

/* ************************************************************************************ */
/*																						*/
/*									iterator_traits										*/
/*																						*/
/* ************************************************************************************ */

	template <typename Iterator>
	struct	iterator_traits
	{
		typedef	typename Iterator::difference_type		difference_type;
		typedef	typename Iterator::value_type			value_type;
		typedef	typename Iterator::pointer				pointer;
		typedef	typename Iterator::reference			reference;
		typedef	typename Iterator::iterator_category	iterator_category;
	};

	template <typename T>
	struct	iterator_traits<T*>
	{
		typedef	std::ptrdiff_t				difference_type;
		typedef	T							value_type;
		typedef	T*							pointer;
		typedef	T&							reference;
		typedef	random_access_iterator_tag	iterator_category;
	};

	template <typename T>
	struct	iterator_traits<const T*>
	{
		typedef	std::ptrdiff_t				difference_type;
		typedef	T							value_type;
		typedef	const T*					pointer;
		typedef	const T&					reference;
		typedef	random_access_iterator_tag	iterator_category;
	};

/* ************************************************************************************ */
/*																						*/
/*								random_access : vector_iterator							*/
/*																						*/
/* ************************************************************************************ */

	template <typename T>
	class	vector_iterator
	{
	public:
		typedef	typename iterator_traits<T*>::iterator_category		iterator_category;
		typedef	typename iterator_traits<T*>::value_type			value_type;
		typedef	typename iterator_traits<T*>::difference_type		difference_type;
		typedef	typename iterator_traits<T*>::pointer				pointer;
		typedef	typename iterator_traits<T*>::reference				reference;

	private:
		pointer	_p;

	public:
		vector_iterator(pointer p) : _p(p) { }

		/* all categories */
		vector_iterator(const vector_iterator &rhs) : _p(rhs._p) { }
		virtual ~vector_iterator(void) { }

		vector_iterator&	operator=(const vector_iterator &rhs) { this->_p = rhs._p; return (*this); }

		vector_iterator&	operator++(void) { ++this->_p; return (*this); }
		vector_iterator	operator++(int) { vector_iterator	tmp(*this); ++this->_p; return (tmp); }

		/* Input */
		bool					operator==(const vector_iterator &rhs) const { return (this->_p == rhs._p); }
		bool					operator!=(const vector_iterator &rhs) const { return (this->_p != rhs._p); }
		reference				operator*(void) { return (*this->_p); }
		pointer					operator->(void) { return (this->_p); }

		/* Output */
		const reference			operator*(void) const { return (*this->_p); }
		const pointer			operator->(void) const { return (this->_p); }

		/* Forward */
		vector_iterator(void) : _p(NULL) { }

		/* Bidirectional */
		vector_iterator&	operator--(void) { --this->_p; return (*this); }
		vector_iterator	operator--(int) { vector_iterator	tmp(*this); --this->_p; return (tmp); }

		/* Random Access */
		vector_iterator		operator+(const difference_type n) const { return (vector_iterator(this->_p + n)); }

		template <typename U>
		friend vector_iterator<U> \
					operator+(const typename vector_iterator<U>::difference_type n, const vector_iterator<U> &rhs);

		vector_iterator		operator-(const difference_type n) const { return (vector_iterator(this->_p - n)); }
		difference_type				operator-(const vector_iterator &rhs) const { return (this->_p - rhs._p); }
		bool						operator<(const vector_iterator &rhs) const { return (this->_p < rhs._p); }
		bool						operator>(const vector_iterator &rhs) const { return (this->_p > rhs._p); }
		bool						operator<=(const vector_iterator &rhs) const { return (this->_p <= rhs._p); }
		bool						operator>=(const vector_iterator &rhs) const { return (this->_p >= rhs._p); }
		vector_iterator&		operator+=(const difference_type n) { this->_p += n; return (*this); }
		vector_iterator&		operator-=(const difference_type n) { this->_p -= n; return (*this); }
		reference					operator[](const difference_type n) const { return (*(this->_p + n)); }
	};

	template <typename T>
	vector_iterator<T> \
			operator+(const typename vector_iterator<T>::difference_type n, const vector_iterator<T> &rhs)
	{
		vector_iterator<T>	tmp;

		tmp._p = n + rhs._p;
		return (tmp);
	}

/* ************************************************************************************ */
/*																						*/
/*							random_access : const_vector_iterator						*/
/*																						*/
/* ************************************************************************************ */

	template <typename T>
	class	const_vector_iterator
	{
	public:
		typedef	typename iterator_traits<const T*>::iterator_category	iterator_category;
		typedef	typename iterator_traits<const T*>::value_type			value_type;
		typedef	typename iterator_traits<const T*>::difference_type		difference_type;
		typedef	typename iterator_traits<const T*>::pointer				pointer;
		typedef	typename iterator_traits<const T*>::reference			reference;

	private:
		pointer	_p;

	public:
		const_vector_iterator(pointer p) : _p(p) { }

		/* all categories */
		const_vector_iterator(const const_vector_iterator &rhs) : _p(rhs._p) { }
		virtual ~const_vector_iterator(void) { }

		const_vector_iterator& \
					operator=(const const_vector_iterator &rhs) { this->_p = rhs._p; return (*this); }

		const_vector_iterator&	operator++(void) { ++this->_p; return (*this); }
		const_vector_iterator	operator++(int) { const_vector_iterator	tmp(*this); ++this->_p; return (tmp); }

		/* Input */
		bool					operator==(const const_vector_iterator &rhs) const { return (this->_p == rhs._p); }
		bool					operator!=(const const_vector_iterator &rhs) const { return (this->_p != rhs._p); }
		reference				operator*(void) { return (*this->_p); }
		pointer					operator->(void) { return (this->_p); }

		/* Output */
		const reference			operator*(void) const { return (*this->_p); }
		const pointer			operator->(void) const { return (this->_p); }

		/* Forward */
		const_vector_iterator(void) : _p(NULL) { }

		/* Bidirectional */
		const_vector_iterator&	operator--(void) { --this->_p; return (*this); }
		const_vector_iterator	operator--(int) { const_vector_iterator	tmp(*this); --this->_p; return (tmp); }

		/* Random Access */
		const_vector_iterator		operator+(const difference_type n) const { return (const_vector_iterator(this->_p + n)); }

		template <typename U>
		friend const_vector_iterator<U> \
					operator+(const typename const_vector_iterator<U>::difference_type n, const const_vector_iterator<U> &rhs);

		const_vector_iterator		operator-(const difference_type n) const { return (const_vector_iterator(this->_p - n)); }
		difference_type						operator-(const const_vector_iterator &rhs) const { return (this->_p - rhs._p); }
		bool								operator<(const const_vector_iterator &rhs) const { return (this->_p < rhs._p); }
		bool								operator>(const const_vector_iterator &rhs) const { return (this->_p > rhs._p); }
		bool								operator<=(const const_vector_iterator &rhs) const { return (this->_p <= rhs._p); }
		bool								operator>=(const const_vector_iterator &rhs) const { return (this->_p >= rhs._p); }
		const_vector_iterator&		operator+=(const difference_type n) { this->_p += n; return (*this); }
		const_vector_iterator&		operator-=(const difference_type n) { this->_p -= n; return (*this); }
		reference							operator[](const difference_type n) const { return (*(this->_p + n)); }
	};

	template <typename T>
	const_vector_iterator<T> \
			operator+(const typename const_vector_iterator<T>::difference_type n, const const_vector_iterator<T> &rhs)
	{
		const_vector_iterator<T>	tmp;

		tmp._p = rhs._p + n;
		return (tmp);
	}

/* ************************************************************************************ */
/*																						*/
/*									reverse_iterator									*/
/*																						*/
/* ************************************************************************************ */

	template <typename Iterator>
	class	reverse_iterator
	{
	public:
		typedef	Iterator												iterator_type;
		typedef	typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef	typename iterator_traits<Iterator>::value_type			value_type;
		typedef	typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef	typename iterator_traits<Iterator>::pointer				pointer;
		typedef	typename iterator_traits<Iterator>::reference			reference;

	protected:
		iterator_type	_current;

	public:
		reverse_iterator(void) : _current(NULL) { }
		explicit reverse_iterator(iterator_type current) : _current(current) { }
		reverse_iterator(const reverse_iterator &rhs) : _current(rhs._current) { }
		virtual ~reverse_iterator(void) { }

		reverse_iterator&	operator=(const reverse_iterator &rhs) { this->_current = rhs._current; return (*this); }

		/* member func */
		iterator_type		base(void) const { return (this->_current); }

		reference			operator*(void) const { iterator_type	tmp = this->_current; return (*(--tmp)); }
		pointer				operator->(void) const { return (&(operator*())); }

		reference			operator[](difference_type n) const { return *(*this + n); }

		reverse_iterator&	operator++(void) { --this->_current; return (*this); }
		reverse_iterator	operator++(int) { reverse_iterator	tmp(*this); --this->_current; return (tmp); }
		reverse_iterator&	operator--(void) { ++this->_current; return (*this); }
		reverse_iterator	operator--(int) { reverse_iterator	tmp(*this); ++this->_current; return (tmp); }
		reverse_iterator	operator+(difference_type n) const { return (reverse_iterator(this->_current - n)); }
		reverse_iterator	operator-(difference_type n) const { return (reverse_iterator(this->_current + n)); }
		reverse_iterator&	operator+=(difference_type n) { this->_current -= n; return (*this); }
		reverse_iterator&	operator-=(difference_type n) { this->_current += n; return (*this); }

	};

	template <typename Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <typename Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename Iterator>
	reverse_iterator<Iterator> \
			operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it)
	{
		return (reverse_iterator<Iterator>(rev_it.base() - n));
	}

	template <typename Iterator>
	typename reverse_iterator<Iterator>::difference_type \
			operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (rhs.base() - lhs.base());
	}

/* ************************************************************************************ */
/*																						*/
/*							bidirectional : rb_tree_iterator							*/
/*																						*/
/* ************************************************************************************ */

	template <typename T>
	class	rb_tree_iterator : public iterator<bidirectional_iterator_tag, T>
	{
	public:
		typedef	typename iterator<bidirectional_iterator_tag, T>::iterator_category		iterator_category;
		typedef	typename iterator<bidirectional_iterator_tag, T>::value_type			value_type;
		typedef	typename iterator<bidirectional_iterator_tag, T>::difference_type		difference_type;
		typedef	typename iterator<bidirectional_iterator_tag, T>::pointer				pointer;
		typedef	typename iterator<bidirectional_iterator_tag, T>::reference				reference;

	private:
		typedef rb_node<value_type>*	node_ptr;

		node_ptr	_node;
		node_ptr	_leaf;

		node_ptr	find_leaf(node_ptr &node)
		{
			node_ptr	tmp = node;

			while (tmp->_left != NULL)
				tmp = tmp->_left;
			return (tmp);
		}

	public:
		node_ptr	get_leaf_ptr(void) { return (this->_leaf); }
		node_ptr	get_node_ptr(void) { return (this->_node); }

		const char*	get_node_color(void)
		{
			if (this->_node->_color == RED)
				return ("RED");
			else
				return ("BLACK");
		}

		rb_tree_iterator(node_ptr node) : _node(node)
		{ _leaf = find_leaf(_node); }

		/* all categories */
		rb_tree_iterator(const rb_tree_iterator &rhs) : _node(rhs._node), _leaf(rhs._leaf) { }
		virtual ~rb_tree_iterator(void) { }

		rb_tree_iterator&	operator=(const rb_tree_iterator &rhs)
		{
			if (this != &rhs)
			{
				this->_node = rhs._node;
				this->_leaf = rhs._leaf;
			}
			return (*this);
		}

		rb_tree_iterator&	operator++(void)
		{
			if (this->_node == this->_leaf)
				this->_node = this->_leaf->_parent;
			else if (this->_node->_right != this->_leaf)
			{
				node_ptr	child = this->_node->_right;

				while (child->_left != this->_leaf)
					child = child->_left;
				this->_node = child;
			}
			else
			{
				node_ptr	ancestor = this->_node->_parent;

				while (ancestor && (this->_node == ancestor->_right))
				{
					this->_node = ancestor;
					ancestor = this->_node->_parent;
				}
				this->_node = ancestor;
				if (this->_node == NULL)
					this->_node = this->_leaf;
			}
			return (*this);
		}

		rb_tree_iterator	operator++(int)
		{
			rb_tree_iterator	tmp(*this);

			++(*this);
			return (tmp);
		}

		/* Input */
		bool				operator==(const rb_tree_iterator &rhs) const { return (this->_node == rhs._node); }
		bool				operator!=(const rb_tree_iterator &rhs) const { return (this->_node != rhs._node); }
		reference			operator*(void) { return (this->_node->_value); }
		pointer				operator->(void) { return (&(this->_node->_value)); }

		/* Output */
		const reference		operator*(void) const { return (this->_node->_value); }
		const pointer		operator->(void) const { return (&(this->_node->_value)); }

		/* Forward */
		rb_tree_iterator(void) : _node(), _leaf() { }

		/* Bidirectional */
		rb_tree_iterator&	operator--(void)
		{
			if (this->_node == this->_leaf)
				this->_node = this->_leaf->_parent;
			else if (this->_node->_left != this->_leaf)
			{
				node_ptr	child = this->_node->_left;

				while (child->_right != this->_leaf)
					child = child->_right;
				this->_node = child;
			}
			else
			{
				node_ptr	ancestor = this->_node->_parent;

				while (ancestor && (this->_node == ancestor->_left))
				{
					this->_node = ancestor;
					ancestor = this->_node->_parent;
				}
				this->_node = ancestor;
				if (this->_node == NULL)
					this->_node = this->_leaf;
			}
			return (*this);
		}

		rb_tree_iterator	operator--(int)
		{
			rb_tree_iterator	tmp(*this);

			--(*this);
			return (tmp);
		}

	};

/* ************************************************************************************ */
/*																						*/
/*							bidirectional : const_rb_tree_iterator						*/
/*																						*/
/* ************************************************************************************ */

	template <typename T>
	class	const_rb_tree_iterator : public iterator<bidirectional_iterator_tag, T>
	{
	public:
		typedef	typename iterator<bidirectional_iterator_tag, T>::iterator_category		iterator_category;
		typedef	typename iterator<bidirectional_iterator_tag, T>::value_type			value_type;
		typedef	typename iterator<bidirectional_iterator_tag, T>::difference_type		difference_type;
		typedef	typename iterator<bidirectional_iterator_tag, T>::pointer				pointer;
		typedef	typename iterator<bidirectional_iterator_tag, T>::reference				reference;

	private:
		typedef rb_node<value_type>*	node_ptr;

		node_ptr	_node;
		node_ptr	_leaf;

		node_ptr	find_leaf(node_ptr &node)
		{
			node_ptr	tmp = node;

			while (tmp->_left != NULL)
				tmp = tmp->_left;
			return (tmp);
		}

	public:
		const_rb_tree_iterator(node_ptr node) : _node(node)
		{ _leaf = find_leaf(_node); }

		/* all categories */
		const_rb_tree_iterator(const const_rb_tree_iterator &rhs) : _node(rhs._node), _leaf(rhs._leaf) { }
		virtual ~const_rb_tree_iterator(void) { }

		const_rb_tree_iterator&	operator=(const const_rb_tree_iterator &rhs)
		{
			if (this != &rhs)
			{
				this->_node = rhs._node;
				this->_leaf = rhs._leaf;
			}
			return (*this);
		}

		const_rb_tree_iterator&	operator++(void)
		{
			if (this->_node == this->_leaf)
				this->_node = this->_leaf->_parent;
			else if (this->_node->_right != this->_leaf)
			{
				node_ptr	child = this->_node->_right;

				while (child->_left != this->_leaf)
					child = child->_left;
				this->_node = child;
			}
			else
			{
				node_ptr	ancestor = this->_node->_parent;

				while (ancestor && (this->_node == ancestor->_right))
				{
					this->_node = ancestor;
					ancestor = this->_node->_parent;
				}
				this->_node = ancestor;
				if (this->_node == NULL)
					this->_node = this->_leaf;
			}
			return (*this);
		}

		const_rb_tree_iterator	operator++(int)
		{
			const_rb_tree_iterator	tmp(*this);

			++(*this);
			return (tmp);
		}

		/* Input */
		bool				operator==(const const_rb_tree_iterator &rhs) const { return (this->_node == rhs._node); }
		bool				operator!=(const const_rb_tree_iterator &rhs) const { return (this->_node != rhs._node); }
		reference			operator*(void) { return (this->_node->_value); }
		pointer				operator->(void) { return (&(this->_node->_value)); }

		/* Output */
		const reference		operator*(void) const { return (this->_node->_value); }
		const pointer		operator->(void) const { return (&(this->_node->_value)); }

		/* Forward */
		const_rb_tree_iterator(void) : _node(), _leaf() { }

		/* Bidirectional */
		const_rb_tree_iterator&	operator--(void)
		{
			if (this->_node == this->_leaf)
				this->_node = this->_leaf->_parent;
			else if (this->_node->_left != this->_leaf)
			{
				node_ptr	child = this->_node->_left;

				while (child->_right != this->_leaf)
					child = child->_right;
				this->_node = child;
			}
			else
			{
				node_ptr	ancestor = this->_node->_parent;

				while (ancestor && (this->_node == ancestor->_left))
				{
					this->_node = ancestor;
					ancestor = this->_node->_parent;
				}
				this->_node = ancestor;
				if (this->_node == NULL)
					this->_node = this->_leaf;
			}
			return (*this);
		}

		const_rb_tree_iterator	operator--(int)
		{
			const_rb_tree_iterator	tmp(*this);

			--(*this);
			return (tmp);
		}
	};

}

#endif

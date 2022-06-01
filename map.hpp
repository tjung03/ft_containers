#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include "red_black_tree.hpp"

namespace	ft
{
	template	<
			typename Key,											// map::key_type
			typename T,												// map::mapped_type
			typename Compare = std::less<Key>,						// map::key_compare
			typename Alloc = std::allocator<pair<const Key, T> >	// map::allocator_type
				>
	class	map
	{
	public:
		typedef	Key									key_type;
		typedef	T									mapped_type;
		typedef	pair<const key_type, mapped_type>	value_type;
		typedef	Compare								key_compare;	// defaults to: less<key_type>

		//////////////////////////////////////////////////////////////////////////
		class	value_compare : std::binary_function<value_type, value_type, bool>
		{
			friend class map;

		protected:
			key_compare	_value_comp;

		protected:
			value_compare(key_compare c) : _value_comp(c) { }

		public:
			bool	operator()(const value_type &x, const value_type &y) const
			{ return (this->_value_comp(x.first, y.first)); }
		};
		//////////////////////////////////////////////////////////////////////////

		typedef	Alloc														allocator_type;
		typedef	typename allocator_type::reference							reference;
		typedef	typename allocator_type::const_reference					const_reference;
		typedef	typename allocator_type::pointer							pointer;
		typedef	typename allocator_type::const_pointer						const_pointer;

		typedef	ft::red_black_tree<key_type, value_type, value_compare>		rb_tree;
		typedef	typename rb_tree::iterator									iterator;
		typedef	typename rb_tree::const_iterator							const_iterator;
		typedef	typename rb_tree::reverse_iterator							reverse_iterator;
		typedef	typename rb_tree::const_reverse_iterator					const_reverse_iterator;

		typedef	std::ptrdiff_t												difference_type;
		typedef	std::size_t													size_type;

	private:
		rb_tree			_tree;
		key_compare		_comp;
		allocator_type	_alloc;

	public:
	/* Member functions */
		// (constructor)
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _tree(rb_tree(value_compare(comp))), _comp(comp), _alloc(alloc)
		{ }

		template <class InputIterator>
		map(InputIterator first, InputIterator last, \
				const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(), \
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0)
			: _tree(rb_tree(value_compare(comp))), _comp(comp), _alloc(alloc)
		{
			this->insert(first, last);
		}

		map(const map &x)
			: _tree(rb_tree(value_compare(key_compare()))), _comp(x._comp), _alloc(x._alloc)
		{ this->insert(x.begin(), x.end()); }

		// (destructor)
		virtual ~map(void)
		{
			this->clear();
		}

		// operator=
		map&	operator=(const map &x)
		{
			if (this != &x)
			{
				this->clear();
				this->insert(x.begin(), x.end());
			}
			return (*this);
		}

		// Iterators:
		iterator		begin(void) { return (this->_tree.begin()); }
		const_iterator	begin(void) const { return (this->_tree.begin()); }
		iterator		end(void) { return (this->_tree.end()); }
		const_iterator	end(void) const { return (this->_tree.end()); }

		reverse_iterator		rbegin(void) { return (reverse_iterator(this->end())); }
		const_reverse_iterator	rbegin(void) const { return (const_reverse_iterator(this->end())); }
		reverse_iterator		rend(void) { return (reverse_iterator(this->begin())); }
		const_reverse_iterator	rend(void) const { return (const_reverse_iterator(this->begin())); }

		// Capacity:
		bool		empty(void) const { return (this->_tree.size() == 0); }
		size_type	size(void) const { return (this->_tree.size()); }
		size_type	max_size(void) const { return (this->_tree.max_size()); }

		// Element access:
		mapped_type&	operator[](const key_type &k)
		{
			return ((*((this->insert(ft::make_pair(k, mapped_type()))).first)).second);
		}

		// Modifiers:
		pair<iterator, bool>	insert(const value_type &val)
		{
			return (this->_tree.insert_node(val));
		}

		iterator	insert(iterator position, const value_type &val)
		{
			(void)position;
			return (insert(val).first);
		}

		template <class InputIterator>
		void	insert(InputIterator first, InputIterator last, \
			typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			while (first != last)
			{
				insert(*first);
				++first;
			}
		}

		void	erase(iterator position)
		{
			this->erase((*position).first);
		}

		size_type	erase(const key_type &k)
		{
			if (this->_tree.delete_node(ft::make_pair(k, mapped_type())))
				return (1);
			return (0);
		}

		void	erase(iterator first, iterator last)
		{
			iterator	begin = first;

			while (begin != last)
				this->erase((*(begin++)).first);
		}

		void	swap(map &x)
		{
			if (this == &x)
				return ;

			this->_tree.swap(x._tree);

			key_compare		tmp_comp = x._comp;
			allocator_type	tmp_alloc = x._alloc;

			x._comp = this->_comp;
			x._alloc = this->_alloc;

			this->_comp = tmp_comp;
			this->_alloc = tmp_alloc;
		}

		void	clear(void)
		{ this->erase(this->begin(), this->end()); }

		// Observers:
		key_compare		key_comp(void) const { return (this->_comp); }
		value_compare	value_comp(void) const { return (value_compare(this->_comp)); }

		// Operations:
		iterator	find(const key_type &k)
		{
			iterator	begin = this->begin();
			iterator	end = this->end();

			while (begin != end)
			{
				if (!this->_comp((*begin).first, k) && !this->_comp(k, (*begin).first))
					break ;
				++begin;
			}
			return (iterator(begin));
		}

		const_iterator	find(const key_type &k) const
		{
			const_iterator	begin = this->begin();
			const_iterator	end = this->end();

			while (begin != end)
			{
				if (!this->_comp((*begin).first, k) && !this->_comp(k, (*begin).first))
					break ;
				++begin;
			}
			return (const_iterator(begin));
		}

		size_type	count(const key_type &k) const
		{
			const_iterator	begin = this->begin();
			const_iterator	end = this->end();

			while (begin != end)
			{
				if (begin->first == k)
					return (1);
				++begin;
			}
			return (0);
		}

		iterator	lower_bound(const key_type &k)
		{
			iterator	begin = this->begin();
			iterator	end = this->end();

			while (begin != end)
			{
				if (!this->_comp((*begin).first, k))
					break ;
				++begin;
			}
			return (iterator(begin));
		}

		const_iterator	lower_bound(const key_type &k) const
		{
			const_iterator	begin = this->begin();
			const_iterator	end = this->end();

			while (begin != end)
			{
				if (!this->_comp((*begin).first, k))
					break ;
				++begin;
			}
			return (const_iterator(begin));
		}

		iterator	upper_bound(const key_type &k)
		{
			iterator	begin = this->begin();
			iterator	end = this->end();

			while (begin != end)
			{
				if (this->_comp(k, (*begin).first))
					break ;
				++begin;
			}
			return (iterator(begin));
		}

		const_iterator	upper_bound(const key_type &k) const
		{
			const_iterator	begin = this->begin();
			const_iterator	end = this->end();

			while (begin != end)
			{
				if (this->_comp(k, (*begin).first))
					break ;
				++begin;
			}
			return (const_iterator(begin));
		}

		pair<const_iterator,const_iterator>	equal_range(const key_type &k) const
		{
			return (make_pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k)));
		}

		pair<iterator,iterator>	equal_range(const key_type &k)\
		{
			return (ft::make_pair<iterator,iterator>(lower_bound(k), upper_bound(k)));
		}

		// Allocator:
		allocator_type	get_allocator(void) const { return (this->_alloc); }

	}; // class map template

	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return ((lhs.size() == rhs.size) && (equal(lhs.begin(), lhs.end(), rhs.begin())));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	void	swap(ft::map<Key, T, Compare, Alloc> &lhs, ft::map<Key, T, Compare, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}

} // namespace ft

#endif

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace	ft
{
	template <class T, class Container = ft::vector<T> >
	class	stack
	{
	public:
		typedef T				value_type;
		typedef Container		container_type;
		typedef std::size_t		size_type;

	protected:
		container_type	c;

	public:
	/* Member functions */
		explicit stack(const container_type &ctnr = container_type()) : c(ctnr) { }

		// Element access
		value_type&			top(void) { return (this->c.back()); }
		const value_type&	top(void) const { return (this->c.back()); }

		// Capacity
		bool		empty(void) const { return (this->c.empty()); };
		size_type	size(void) const { return (this->c.size()); };

		// Modifiers
		void push (const value_type& val) { this->c.push_back(val); };
		void pop(void) { this->c.pop_back(); };

	/* Non-member function overloads */
		template <class U, class C>
		friend bool	operator==(const stack<U, C> &lhs, const stack<U, C> &rhs);
		template <class U, class C>
		friend bool	operator<(const stack<U, C> &lhs, const stack<U, C> &rhs);

	}; // class stack template

	template <class T, class Container>
	bool	operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{ return (lhs.c == rhs.c); }

	template <class T, class Container>
	bool	operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{ return (!(lhs == rhs)); }

	template <class T, class Container>
	bool	operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{ return (lhs.c < rhs.c); }

	template <class T, class Container>
	bool	operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{ return (!(rhs < lhs)); }

	template <class T, class Container>
	bool	operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{ return (rhs < lhs); }

	template <class T, class Container>
	bool	operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{ return (!(lhs < rhs)); }

} // namespace ft

#endif

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "iterator.hpp"

namespace	ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class	vector
	{
	public:
		typedef				T										value_type;
		typedef				Alloc									allocator_type;		// allocator<value_type>
		typedef typename	allocator_type::reference				reference;			// value_type&
		typedef typename	allocator_type::const_reference			const_reference;	// const value_type&
		typedef typename	allocator_type::pointer					pointer;			// value_type*
		typedef typename	allocator_type::const_pointer			const_pointer;		// const value_type*

		typedef 			ft::random_access_iterator<T>			iterator;
		typedef 			ft::const_random_access_iterator<T>		const_iterator;
		typedef				ft::reverse_iterator<iterator>			reverse_iterator;
		typedef				ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef				std::ptrdiff_t							difference_type;
		typedef				std::size_t								size_type;

		/* public member function */
		explicit vector(const allocator_type &alloc = allocator_type());
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type());

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());

		vector(const vector &x);

		/* non-member function overloads */
	}; // class Vector template
} // namespace ft

#endif

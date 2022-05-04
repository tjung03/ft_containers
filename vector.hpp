#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "Iterator.hpp"

namespace	ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class	Vector
	{
	public:
		typedef				T								value_type;
		typedef				Alloc							allocator_type;		// allocator<value_type>
		typedef typename	allocator_type::reference		reference;			// value_type&
		typedef typename	allocator_type::const_reference	const_reference;	// const value_type&
		typedef typename	allocator_type::pointer			pointer;			// value_type*
		typedef typename	allocator_type::const_pointer	const_pointer;		// const value_type*
	}; // class Vector template
} // namespace ft

#endif

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <algorithm>
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

	private:
		pointer			_vecptr;
		allocator_type	_alloc;
		size_type		_size;
		size_type		_capacity;

	public:
		/* public member function */
		explicit vector(const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _size(0), _capacity(0)
		{
			this->_vecptr = this->_alloc.allocate(this->_capacity);
		}
		
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _size(n), _capacity(n)
		{
			this->_vecptr = this->_alloc.allocate(n);
			this->_alloc.construct(&_vecptr[0], val);
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _size(last - first), _capacity(last - first)
		{
			this->_vecptr = this->_alloc.allocate(this->_capacity);
			std::copy(first, last, this->begin());
		}

		vector(const vector &x)
			: _alloc(x._alloc), _size(x._size), _capacity(x._capacity)
		{
			this->_vecptr = this->alloc.allocate(this->_capacity);
			std::copy(first, last, this->begin());
		}

		/* non-member function overloads */
	}; // class Vector template
} // namespace ft

#endif

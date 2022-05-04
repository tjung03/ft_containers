#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace	ft
{
	struct	input_iterator_tag { };
	struct	output_iterator_tag { };
	struct	forward_iterator_tag : public input_iterator_tag { };
	struct	bidirectional_iterator_tag : public forward_iterator_tag { };
	struct	random_access_iterator_tag : public bidirectional_iterator_tag { };

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

	template <typename Iterator>
	struct	iterator_traits
	{
		typedef typename	Iterator::difference_type		difference_type;
		typedef typename	Iterator::value_type			value_type;
		typedef typename	Iterator::pointer				pointer;
		typedef typename	Iterator::reference				reference;
		typedef typename	Iterator::iterator_category		iterator_category;
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

	template <typename T>
	class	random_access_iterator : public iterator<random_access_iterator_tag, T>
	{
	public:
		typedef typename	iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename	iterator<random_access_iterator_tag, T>::value_type			value_type;
		typedef typename	iterator<random_access_iterator_tag, T>::difference_type	difference_type;
		typedef typename	iterator<random_access_iterator_tag, T>::pointer			pointer;
		typedef typename	iterator<random_access_iterator_tag, T>::reference			reference;

	private:
		pointer	_p;

	public:
		random_access_iterator(pointer p) : _p(p) { }

		/* all categories */
		random_access_iterator(const random_access_iterator &rhs) : _p(rhs._p) { }
		random_access_iterator&	operator=(const random_access_iterator &rhs) { if (this != rhs) this->_p = rhs._p; return (*this); }
		virtual ~random_access_iterator(void) { }
		random_access_iterator&	operator++(void) { ++this->_p; return (*this); }
		random_access_iterator	operator++(int) { random_access_iterator	tmp(*this); ++this->_p; return (tmp); }

		/* Input */
		bool					operator==(const random_access_iterator& rhs) const { return (this->_p == rhs._p); }
		bool					operator!=(const random_access_iterator& rhs) const { return (this->_p != rhs._p); }
		reference				operator*(void) { return (*this->_p); }
		pointer					operator->(void) { return (this->_p); }

		/* Output */
		const reference			operator*(void) const { return (*this->_p); }
		const pointer			operator->(void) const { return (this->_p); }

		/* Forward */
		random_access_iterator(void) : _p(NULL) { }

		/* Bidirectional */
		random_access_iterator&	operator--(void) { --this->_p; return (*this); }
		random_access_iterator<T>	operator--(int) { random_access_iterator	tmp(*this); --this->_p; return (tmp); }

		/* Random Access */
		random_access_iterator			operator+(const difference_type n) const { return (random_access_iterator(this->_p + n)); }
		friend random_access_iterator	operator+(const difference_type n, const random_access_iterator &rhs);
		random_access_iterator			operator-(const difference_type n) const { return (random_access_iterator(this->_p - n)); }
		difference_type					operator-(const random_access_iterator &rhs) const { return (this->_p - rhs._p); }
		bool							operator<(const random_access_iterator& rhs) const { return (this->_p < rhs._p); }
		bool							operator>(const random_access_iterator& rhs) const { return (this->_p > rhs._p); }
		bool							operator<=(const random_access_iterator& rhs) const { return (this->_p <= rhs._p); }
		bool							operator>=(const random_access_iterator& rhs) const { return (this->_p >= rhs._p); }
		random_access_iterator&			operator+=(const difference_type n) { this->_p += n; return (*this); }
		random_access_iterator&			operator-=(const difference_type n) { this->_p -= n; return (*this); }
		reference						operator[](const difference_type n) const { return (*(this->_p + n)); }
	};

	template <typename T>
	random_access_iterator<T>	operator+(const typename random_access_iterator<T>::difference_type n, const random_access_iterator<T> &rhs)
	{
		random_access_iterator<T>	tmp;

		tmp._p = rhs._p + n;
		return (tmp);
	}

	template <typename Iterator>
	class	reverse_iterator : public iterator<random_access_iterator_tag, Iterator>
	{
	public:
		typedef				Iterator										iterator_type;
		typedef typename	iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename	iterator_traits<Iterator>::value_type			value_type;
		typedef typename	iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename	iterator_traits<Iterator>::pointer				pointer;
		typedef typename	iterator_traits<Iterator>::reference			reference;

	private:
		iterator_type	_p;

	public:
		reverse_iterator(void) : _p(NULL) { }
		explicit reverse_iterator(iterator_type p) : _p(p) { }
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &rhs) : _p(rhs._p) { }
		virtual ~reverse_iterator(void) { }

		reverse_iterator&	operator=(const reverse_iterator &rhs) { if (this != rhs) this->_p = rhs._p; return (*this); }
	};
}

#endif

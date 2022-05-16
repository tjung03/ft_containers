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

/* ************************************************************************************ */
/*																						*/
/*								random_access_iterator									*/
/*																						*/
/* ************************************************************************************ */

	template <typename T>
	class	random_access_iterator : public iterator<random_access_iterator_tag, T>
	{
	public:
		typedef typename	iterator_traits<T*>::iterator_category	iterator_category;
		typedef typename	iterator_traits<T*>::value_type			value_type;
		typedef typename	iterator_traits<T*>::difference_type	difference_type;
		typedef typename	iterator_traits<T*>::pointer			pointer;
		typedef typename	iterator_traits<T*>::reference			reference;

	private:
		pointer	_p;

	public:
		random_access_iterator(pointer p) : _p(p) { }

		/* all categories */
		random_access_iterator(const random_access_iterator &rhs) : _p(rhs._p) { }
		virtual ~random_access_iterator(void) { }

		random_access_iterator&	operator=(const random_access_iterator &rhs) { this->_p = rhs._p; return (*this); }

		random_access_iterator&	operator++(void) { ++this->_p; return (*this); }
		random_access_iterator	operator++(int) { random_access_iterator	tmp(*this); ++this->_p; return (tmp); }

		/* Input */
		bool					operator==(const random_access_iterator &rhs) const { return (this->_p == rhs._p); }
		bool					operator!=(const random_access_iterator &rhs) const { return (this->_p != rhs._p); }
		reference				operator*(void) { return (*this->_p); }
		pointer					operator->(void) { return (this->_p); }

		/* Output */
		const reference			operator*(void) const { return (*this->_p); }
		const pointer			operator->(void) const { return (this->_p); }

		/* Forward */
		random_access_iterator(void) : _p(NULL) { }

		/* Bidirectional */
		random_access_iterator&	operator--(void) { --this->_p; return (*this); }
		random_access_iterator	operator--(int) { random_access_iterator	tmp(*this); --this->_p; return (tmp); }

		/* Random Access */
		random_access_iterator		operator+(const difference_type n) const { return (random_access_iterator(this->_p + n)); }

		template <typename U>
		friend random_access_iterator<U> \
					operator+(const typename random_access_iterator<U>::difference_type n, const random_access_iterator<U> &rhs);

		random_access_iterator		operator-(const difference_type n) const { return (random_access_iterator(this->_p - n)); }
		difference_type				operator-(const random_access_iterator &rhs) const { return (this->_p - rhs._p); }
		bool						operator<(const random_access_iterator &rhs) const { return (this->_p < rhs._p); }
		bool						operator>(const random_access_iterator &rhs) const { return (this->_p > rhs._p); }
		bool						operator<=(const random_access_iterator &rhs) const { return (this->_p <= rhs._p); }
		bool						operator>=(const random_access_iterator &rhs) const { return (this->_p >= rhs._p); }
		random_access_iterator&		operator+=(const difference_type n) { this->_p += n; return (*this); }
		random_access_iterator&		operator-=(const difference_type n) { this->_p -= n; return (*this); }
		reference					operator[](const difference_type n) const { return (*(this->_p + n)); }
	};

	template <typename T>
	random_access_iterator<T> \
			operator+(const typename random_access_iterator<T>::difference_type n, const random_access_iterator<T> &rhs)
	{
		random_access_iterator<T>	tmp;

		tmp._p = n + rhs._p;
		return (tmp);
	}

/* ************************************************************************************ */
/*																						*/
/*							const_random_access_iterator								*/
/*																						*/
/* ************************************************************************************ */

	template <typename T>
	class	const_random_access_iterator : public iterator<random_access_iterator_tag, T>
	{
	public:
		typedef typename	iterator_traits<const T*>::iterator_category	iterator_category;
		typedef typename	iterator_traits<const T*>::value_type			value_type;
		typedef typename	iterator_traits<const T*>::difference_type		difference_type;
		typedef typename	iterator_traits<const T*>::pointer				pointer;
		typedef typename	iterator_traits<const T*>::reference			reference;

	private:
		pointer	_p;

	public:
		const_random_access_iterator(pointer p) : _p(p) { }

		/* all categories */
		const_random_access_iterator(const const_random_access_iterator &rhs) : _p(rhs._p) { }
		virtual ~const_random_access_iterator(void) { }

		const_random_access_iterator& \
					operator=(const const_random_access_iterator &rhs) { this->_p = rhs._p; return (*this); }

		const_random_access_iterator&	operator++(void) { ++this->_p; return (*this); }
		const_random_access_iterator	operator++(int) { const_random_access_iterator	tmp(*this); ++this->_p; return (tmp); }

		/* Input */
		bool					operator==(const const_random_access_iterator &rhs) const { return (this->_p == rhs._p); }
		bool					operator!=(const const_random_access_iterator &rhs) const { return (this->_p != rhs._p); }
		reference				operator*(void) { return (*this->_p); }
		pointer					operator->(void) { return (this->_p); }

		/* Output */
		const reference			operator*(void) const { return (*this->_p); }
		const pointer			operator->(void) const { return (this->_p); }

		/* Forward */
		const_random_access_iterator(void) : _p(NULL) { }

		/* Bidirectional */
		const_random_access_iterator&	operator--(void) { --this->_p; return (*this); }
		const_random_access_iterator	operator--(int) { const_random_access_iterator	tmp(*this); --this->_p; return (tmp); }

		/* Random Access */
		const_random_access_iterator		operator+(const difference_type n) const { return (const_random_access_iterator(this->_p + n)); }

		template <typename U>
		friend const_random_access_iterator<U> \
					operator+(const typename const_random_access_iterator<U>::difference_type n, const const_random_access_iterator<U> &rhs);

		const_random_access_iterator		operator-(const difference_type n) const { return (const_random_access_iterator(this->_p - n)); }
		difference_type						operator-(const const_random_access_iterator &rhs) const { return (this->_p - rhs._p); }
		bool								operator<(const const_random_access_iterator &rhs) const { return (this->_p < rhs._p); }
		bool								operator>(const const_random_access_iterator &rhs) const { return (this->_p > rhs._p); }
		bool								operator<=(const const_random_access_iterator &rhs) const { return (this->_p <= rhs._p); }
		bool								operator>=(const const_random_access_iterator &rhs) const { return (this->_p >= rhs._p); }
		const_random_access_iterator&		operator+=(const difference_type n) { this->_p += n; return (*this); }
		const_random_access_iterator&		operator-=(const difference_type n) { this->_p -= n; return (*this); }
		reference							operator[](const difference_type n) const { return (*(this->_p + n)); }
	};

	template <typename T>
	const_random_access_iterator<T> \
			operator+(const typename const_random_access_iterator<T>::difference_type n, const const_random_access_iterator<T> &rhs)
	{
		const_random_access_iterator<T>	tmp;

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
		typedef				Iterator										iterator_type;
		typedef typename	iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename	iterator_traits<Iterator>::value_type			value_type;
		typedef typename	iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename	iterator_traits<Iterator>::pointer				pointer;
		typedef typename	iterator_traits<Iterator>::reference			reference;

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

		reference			operator*(void) const { iterator_type	tmp(*this); return (*(--tmp)); }
		pointer				operator->(void) const { iterator_type	tmp(*this); return (--tmp); }

		reference			operator[](difference_type n) const { return *(*this + n); }

		reverse_iterator&	operator++(void) { --this->_current; return (*this); }
		reverse_iterator	operator++(int) { reverse_iterator	tmp(*this); --this->_current; return (tmp); }
		reverse_iterator&	operator--(void) { ++this->_current; return (*this); }
		reverse_iterator	operator--(int) { reverse_iterator	tmp(*this); ++this->_current; return (tmp); }
		reverse_iterator	operator+(difference_type n) const { return (reverse_iterator(this->_current - n)); }
		reverse_iterator	operator-(difference_type n) const { return (reverse_iterator(this->_current + n)); }
		reverse_iterator&	operator+=(difference_type n) { this->_current -= n; return (*this); }
		reverse_iterator&	operator-=(difference_type n) { this->_current += n; return (*this); }

		/* non-member func overloads */
		template <typename Itr>
		friend bool	operator==(const reverse_iterator<Itr> &lhs, const reverse_iterator<Itr> &rhs);
		template <typename Itr>
		friend bool	operator!=(const reverse_iterator<Itr> &lhs, const reverse_iterator<Itr> &rhs);
		template <typename Itr>
		friend bool	operator<(const reverse_iterator<Itr> &lhs, const reverse_iterator<Itr> &rhs);
		template <typename Itr>
		friend bool	operator>(const reverse_iterator<Itr> &lhs, const reverse_iterator<Itr> &rhs);
		template <typename Itr>
		friend bool	operator<=(const reverse_iterator<Itr> &lhs, const reverse_iterator<Itr> &rhs);
		template <typename Itr>
		friend bool	operator>=(const reverse_iterator<Itr> &lhs, const reverse_iterator<Itr> &rhs);

		template <typename Itr>
		friend reverse_iterator<Itr> \
						operator+(typename reverse_iterator<Itr>::difference_type n, const reverse_iterator<Itr> &rev_it);
		template <typename Itr>
		friend typename reverse_iterator<Itr>::difference_type \
						operator-(const reverse_iterator<Itr>& lhs, const reverse_iterator<Itr>& rhs);
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
		return (lhs.base() > rhs.base());
	}

	template <typename Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <typename Iterator>
	reverse_iterator<Iterator> \
			operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it)
	{
		return (reverse_iterator<Iterator>(rev_it.base() - n));
	}

	template <typename Iterator>
	typename reverse_iterator<Iterator>::difference_type \
			operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (reverse_iterator<Iterator>(rhs.base() - lhs.base()));
	}
}

#endif

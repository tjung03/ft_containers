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
		reverse_iterator(iterator_type p) : _p(p) { }
		reverse_iterator(const reverse_iterator &rhs) : _p(rhs._p) { }
		virtual ~reverse_iterator(void) { }

		reverse_iterator&	operator=(const reverse_iterator &rhs)
		{
			this->_p = rhs._p;
			return (*this);
		}
	};

	template <typename T>
	class	VectorIt : public iterator<random_access_iterator_tag, T>
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
		VectorIt(void) : _p(NULL) { }
		VectorIt(pointer p) : _p(p) { }
		VectorIt(const VectorIt &rhs) : _p(rhs._p) { }
		virtual ~VectorIt(void) { }

		VectorIt&	operator=(const VectorIt &rhs)
		{
			this->_p = rhs._p;
			return (*this);
		}

		reference	operator*(void) const { return (*this->_p); }
		pointer		operator->(void) const { return (this->_p); }
		reference	operator[](difference_type n) const { return (*(this->_p + n)); }
		bool		operator==(const VectorIt& rhs) const { return (this->_p == rhs._p); }
		bool		operator!=(const VectorIt& rhs) const { return (this->_p != rhs._p); }
		bool		operator<(const VectorIt& rhs) const { return (this->_p < rhs._p); }
		bool		operator>(const VectorIt& rhs) const { return (this->_p > rhs._p); }
		bool		operator<=(const VectorIt& rhs) const { return (this->_p <= rhs._p); }
		bool		operator>=(const VectorIt& rhs) const { return (this->_p >= rhs._p); }
		VectorIt&	operator++(void) { ++this->_p; return (*this); }
		VectorIt	operator++(int) { VectorIt	tmp(*this); ++this->_p; return (tmp); }
		VectorIt&	operator--(void) { --this->_p; return (*this); }
		VectorIt	operator--(int) { VectorIt	tmp(*this); --this->_p; return (tmp); }
		VectorIt	operator+(difference_type n) const { return (VectorIt(this->_p + n)); }
		VectorIt	operator-(difference_type n) const { return (VectorIt(this->_p - n)); }
		VectorIt&	operator+=(difference_type n) { this->_p += n; return (*this); }
		VectorIt&	operator-=(difference_type n) { this->_p -= n; return (*this); }
	};
}

#endif

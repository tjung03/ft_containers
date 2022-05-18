#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <limits>
# include <stdexcept>
# include "iterator.hpp"
# include "utils.hpp"

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
		// (constructor)
		explicit vector(const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _size(0), _capacity(0)
		{
			this->_vecptr = this->_alloc.allocate(this->_capacity);
		}

		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _size(n), _capacity(n)
		{
			this->_vecptr = this->_alloc.allocate(this->_capacity);
			for (size_type i = 0; i < this->_size; ++i)
				this->_alloc.construct(this->_vecptr + i, val);
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), \
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0)
			: _alloc(alloc), _size(last - first), _capacity(last - first)
		{
			this->_vecptr = this->_alloc.allocate(this->_capacity);
			for (size_type i = 0; first != last; )
			{
				this->_alloc.construct(this->_vecptr + i, *first);
				++i; ++first;
			}
		}

		vector(const vector &x)
			: _alloc(x._alloc), _size(x._size), _capacity(x._capacity)
		{
			this->_vecptr = this->_alloc.allocate(this->_capacity);
			for (size_type i = 0; i < this->_size; ++i)
				this->_alloc.construct(this->_vecptr + i, *(x._vecptr + i));
		}

		// (destructor)
		virtual ~vector(void)
		{
			for (size_type i = 0; i < this->_size; ++i)
				this->_alloc.destroy(this->_vecptr + i);
			this->_alloc.deallocate(this->_vecptr, this->_capacity);
		}

		// operator=
		vector&	operator=(const vector &x)
		{
			if (&x != this)
			{
				for (size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(this->_vecptr + i);
				this->_alloc.deallocate(this->_vecptr, this->_capacity);

				this->_alloc = x._alloc;
				this->_vecptr = this->_alloc.allocate(x._capacity);
				for (size_type i = 0; i < x._size; ++i)
					this->_alloc.construct(this->_vecptr + i, *(x._vecptr + i));
				this->_size = x._size;
				this->_capacity = x._capacity;
			}
			return (*this);
		}

		// Iterators:
		iterator				begin(void) { return (iterator(this->_vecptr)); }
		const_iterator			begin(void) const { return (const_iterator(this->_vecptr)); }
		iterator				end(void) { return (iterator(this->_vecptr + this->_size)); }
		const_iterator			end(void) const { return (const_iterator(this->_vecptr + this->_size)); }
		reverse_iterator		rbegin(void) { return (reverse_iterator(iterator(this->_vecptr + this->_size))); }
		const_reverse_iterator	rbegin(void) const { return (const_reverse_iterator(const_iterator(this->_vecptr + this->_size))); }
		reverse_iterator		rend(void) { return (reverse_iterator(iterator(this->_vecptr))); }
		const_reverse_iterator	rend(void) const { return (const_reverse_iterator(const_iterator(this->_vecptr))); }

		// Capacity:
		size_type	size(void) const { return (this->_size); }
		size_type	max_size(void) const { return (std::min((std::numeric_limits<size_type>::max() / sizeof(value_type)), this->_alloc.max_size())); }

		void		resize(size_type n, value_type val = value_type())
		{
			if (n == this->_size)
				return ;
			else if (n > this->_capacity)
			{
				pointer	tmp_ = this->_alloc.allocate(n);

				for (size_type i = 0; i < n; ++i)
				{
					if (i < this->_size)
						this->_alloc.construct(tmp_ + i, *(this->_vecptr + i));
					else
						this->_alloc.construct(tmp_ + i, val);
				}

				for (size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(this->_vecptr + i);
				this->_alloc.deallocate(this->_vecptr, this->_capacity);

				this->_vecptr = tmp_;
				this->_capacity = n;
			}
			else if (n > this->_size)
			{
				for (size_type i = this->_size; i < n; ++i)
					this->_alloc.construct(this->_vecptr + i, val);
			}
			else
			{
				for (size_type i = n; i < this->_size; ++i)
					this->_alloc.destroy(this->_vecptr + i);
			}
			this->_size = n;
		}

		size_type	capacity(void) const { return (this->_capacity); }
		bool		empty(void) const { return (this->_size == 0); }

		void		reserve(size_type n)
		{
			if (n <= this->_capacity)
				return ;
			if (n > this->max_size())
				throw (std::length_error("length_error"));

			pointer	tmp_ = this->_alloc.allocate(n);

			for (size_type i = 0; i < this->_size; ++i)
			{
				this->_alloc.construct(tmp_ + i, *(this->_vecptr + i));
				this->_alloc.destroy(this->_vecptr + i);
			}
			this->_alloc.deallocate(this->_vecptr, this->_capacity);

			this->_vecptr = tmp_;
			this->_capacity = n;
		}

		// Element access:
		reference		operator[](size_type n) { return (*(this->_vecptr + n)); }
		const_reference	operator[](size_type n) const { return (*(this->_vecptr + n)); }

		reference		at(size_type n)
		{
			if (n >= this->_size)
				throw (std::out_of_range("out_of_range"));
			return (*(this->_vecptr + n));
		}

		const_reference	at(size_type n) const
		{
			if (n >= this->_size)
				throw (std::out_of_range("out_of_range"));
			return (*(this->_vecptr + n));
		}

		reference		front(void) { return (*(this->_vecptr)); }
		const_reference	front(void) const { return (*(this->_vecptr)); }
		reference		back(void) { return (*(this->_vecptr + this->_size - 1)); }
		const_reference	back(void) const { return (*(this->_vecptr + this->_size - 1)); }

		// Modifiers:
		template <typename InputIterator>
		void	assign(InputIterator first, InputIterator last, \
			typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			const size_type	n = last - first;

			if (n > this->_capacity)
			{
				pointer	tmp_ = this->_alloc.allocate(n);

				for (size_type i = 0; i < n; ++i)
					this->_alloc.construct(tmp_ + i, *(first + i));

				for (size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(this->_vecptr + i);
				this->_alloc.deallocate(this->_vecptr, this->_capacity);

				this->_vecptr = tmp_;
				this->_capacity = n;
			}
			else if (n > this->_size)
			{
				for (size_type i = 0; i < n; ++i)
				{
					if (i < this->_size)
						this->_alloc.destroy(this->_vecptr + i);
					this->_alloc.construct(this->_vecptr + i, *(first + i));
				}
			}
			else
			{
				for (size_type i = 0; i < this->_size; ++i)
				{
					this->_alloc.destroy(this->_vecptr + i);
					if (i < n)
						this->_alloc.construct(this->_vecptr + i, *(first + i));
				}
			}
			this->_size = n;

		}

		void	assign(size_type n, const value_type &val)
		{
			if (n > this->_capacity)
			{
				pointer	tmp_ = this->_alloc.allocate(n);

				for (size_type i = 0; i < n; ++i)
					this->_alloc.construct(tmp_ + i, val);

				for (size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(this->_vecptr + i);
				this->_alloc.deallocate(this->_vecptr, this->_capacity);

				this->_vecptr = tmp_;
				this->_capacity = n;
			}
			else if (n > this->_size)
			{
				for (size_type i = 0; i < n; ++i)
				{
					if (i < this->_size)
						this->_alloc.destroy(this->_vecptr + i);
					this->_alloc.construct(this->_vecptr + i, val);
				}
			}
			else
			{
				for (size_type i = 0; i < this->_size; ++i)
				{
					this->_alloc.destroy(this->_vecptr + i);
					if (i < n)
						this->_alloc.construct(this->_vecptr + i, val);
				}
			}
			this->_size = n;
		}

		void	push_back(const value_type &val)
		{
			if (this->_size < this->_capacity)
				this->_alloc.construct(this->_vecptr + this->_size, val);
			else
			{
				size_type	tmp_capa_ = this->_capacity;

				if (tmp_capa_ > 0)
					tmp_capa_ = tmp_capa_ * 2;
				else
					++(tmp_capa_);

				pointer	tmp_ = this->_alloc.allocate(tmp_capa_);

				for (size_type i = 0; i < this->_size; ++i)
				{
					this->_alloc.construct(tmp_ + i, *(this->_vecptr + i));
					this->_alloc.destroy(this->_vecptr + i);
				}
				this->_alloc.construct(tmp_ + this->_size, val);
				this->_alloc.deallocate(this->_vecptr, this->_capacity);

				this->_vecptr = tmp_;
				this->_capacity = tmp_capa_;
			}
			++(this->_size);
		}

		void	pop_back(void)
		{
			if (this->_size)
				this->_alloc.destroy(this->_vecptr + --(this->_size));
		}

		iterator	insert(iterator position, const value_type &val)
		{
			size_type	offset_ = position - this->begin();

			if (this->_size < this->_capacity)
			{
				if (position == this->end())
					this->_alloc.construct(this->_vecptr + offset_, val);
				else
				{
					value_type	tmp_;

					for (size_type i = this->_size - 1; i >= offset_; --i)
					{
						tmp_ = *(this->_vecptr + i);
						this->_alloc.destroy(this->_vecptr + i);
						this->_alloc.construct(this->_vecptr + i + 1, tmp_);
						if (i == 0) break ;
					}
					this->_alloc.construct(this->_vecptr + offset_, val);
				}
			}
			else // realloc
			{
				size_type	tmp_capa_ = this->_capacity;

				if (tmp_capa_ > 0)
					tmp_capa_ = tmp_capa_ * 2;
				else
					++(tmp_capa_);

				pointer	tmp_ = this->_alloc.allocate(tmp_capa_);

				for (size_type i = 0; i <= this->_size; ++i)
				{
					if (offset_ <= this->_size)
					{
						if (i < offset_)
							this->_alloc.construct(tmp_ + i, *(this->_vecptr + i));
						else if (i == offset_)
							this->_alloc.construct(tmp_ + i, val);
						else if (i > offset_)
							this->_alloc.construct(tmp_ + i, *(this->_vecptr + i - 1));
					}
					else
					{
						if (i < this->_size)
							this->_alloc.construct(tmp_ + i, *(this->_vecptr + i));
						else
							this->_alloc.construct(tmp_ + this->_size, value_type());
					}
				}

				for (size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(this->_vecptr + i);
				this->_alloc.deallocate(this->_vecptr, this->_capacity);

				this->_vecptr = tmp_;
				this->_capacity = tmp_capa_;
			}
			++(this->_size);

			return (iterator(this->_vecptr + offset_));
		}

		void	insert(iterator position, size_type n, const value_type &val)
		{
			size_type	offset_ = position - this->begin();

			if (this->_size + n <= this->_capacity)
			{
				if (position == this->end())
				{
					for (size_type i = 0; i < n; ++i)
						this->_alloc.construct(this->_vecptr + offset_ + i, val);
				}
				else
				{
					value_type	tmp_;

					for (size_type i = this->_size - 1; i >= offset_; --i)
					{
						tmp_ = *(this->_vecptr + i);
						this->_alloc.destroy(this->_vecptr + i);
						this->_alloc.construct(this->_vecptr + i + n, tmp_);
						if (i == 0) break ;
					}
					for (size_type i = 0; i < n; ++i)
						this->_alloc.construct(this->_vecptr + offset_ + i, val);
				}
			}
			else // realloc
			{
				size_type	tmp_capa_ = this->_capacity;

				tmp_capa_ += n;
				if (this->_capacity > 0)
				{
					if ((this->_capacity * 2) >= (this->_size + n))
						tmp_capa_ = this->_capacity * 2;
				}

				pointer	tmp_ = this->_alloc.allocate(tmp_capa_);

				for (size_type i = 0; i < this->_size + n; ++i)
				{
					if (offset_ <= this->_size)
					{
						if (i < offset_)
							this->_alloc.construct(tmp_ + i, *(this->_vecptr + i));
						else if (i == offset_)
						{
							for (size_type j = 0; j < n; ++j)
								this->_alloc.construct(tmp_ + i + j, val);
							i += (n - 1);
						}
						else if (i > offset_)
							this->_alloc.construct(tmp_ + i, *(this->_vecptr + i - n));
					}
					else
					{
						if (i < this->_size)
							this->_alloc.construct(tmp_ + i, *(this->_vecptr + i));
						else
							this->_alloc.construct(tmp_ + this->_size, value_type());
					}
				}

				for (size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(this->_vecptr + i);
				this->_alloc.deallocate(this->_vecptr, this->_capacity);

				this->_vecptr = tmp_;
				this->_capacity = tmp_capa_;
			}
			this->_size += n;
		}

		template <typename InputIterator>
		void	insert(iterator position, InputIterator first, InputIterator last,
			typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			size_type	offset_ = position - this->begin();

			if (first != last)
			{
				const size_type	n = last - first;

				if (this->_size + n <= this->_capacity)
				{
					if (position == this->end())
					{
						for (size_type i = 0; i < n; ++i)
							this->_alloc.construct(this->_vecptr + offset_ + i, *(first + i));
					}
					else
					{
						value_type	tmp_;

						for (size_type i = this->_size - 1; i >= offset_; --i)
						{
							tmp_ = *(this->_vecptr + i);
							this->_alloc.destroy(this->_vecptr + i);
							this->_alloc.construct(this->_vecptr + i + n, tmp_);
							if (i == 0) break ;
						}
						for (size_type i = 0; i < n; ++i)
							this->_alloc.construct(this->_vecptr + offset_ + i, *(first + i));
					}
				}
				else // realloc
				{
					size_type	tmp_capa_ = this->_capacity;

					tmp_capa_ += n;
					if (this->_capacity > 0)
					{
						if ((this->_capacity * 2) >= (this->_size + n))
							tmp_capa_ = this->_capacity * 2;
					}

					pointer	tmp_ = this->_alloc.allocate(tmp_capa_);

					for (size_type i = 0; i < this->_size + n; ++i)
					{
						if (offset_ <= this->_size)
						{
							if (i < offset_)
								this->_alloc.construct(tmp_ + i, *(this->_vecptr + i));
							else if (i == offset_)
							{
								for (size_type j = 0; j < n; ++j)
									this->_alloc.construct(tmp_ + i + j, *(first + j));
								i += (n - 1);
							}
							else if (i > offset_)
								this->_alloc.construct(tmp_ + i, *(this->_vecptr + i - n));
						}
						else
						{
							if (i < this->_size)
								this->_alloc.construct(tmp_ + i, *(this->_vecptr + i));
							else
								this->_alloc.construct(tmp_ + this->_size, value_type());
						}
					}

					for (size_type i = 0; i < this->_size; ++i)
						this->_alloc.destroy(this->_vecptr + i);
					this->_alloc.deallocate(this->_vecptr, this->_capacity);

					this->_vecptr = tmp_;
					this->_capacity = tmp_capa_;
				}
				this->_size += n;
			}
		}

		iterator	erase(iterator position)
		{
			size_type	offset_ = position - this->begin();

			this->_alloc.destroy(this->_vecptr + offset_);
			for (size_type i = offset_ + 1; i < this->_size; ++i)
			{
				this->_alloc.construct(this->_vecptr + i - 1, *(this->_vecptr + i));
				this->_alloc.destroy(this->_vecptr + i);
			}
			--(this->_size);

			return (iterator(this->_vecptr + offset_));
		}

		iterator	erase(iterator first, iterator last)
		{
			size_type	offset_ = first - this->begin();

			if (first != last)
			{
				const size_type	n = last - first;

				for (size_type i = 0; i < n; ++i)
					this->_alloc.destroy(this->_vecptr + offset_ + i);
				for (size_type i = offset_ + n; i < this->_size; ++i)
				{
					this->_alloc.construct(this->_vecptr + i - n, *(this->_vecptr + i));
					this->_alloc.destroy(this->_vecptr + i);
				}
				this->_size -= n;
			}

			return (iterator(this->_vecptr + offset_));
		}

		void	swap(vector &x)
		{
			pointer			tmp_ptr_ = x._vecptr;
			allocator_type	tmp_alloc_ = x._alloc;
			size_type		tmp_size_ = x._size;
			size_type		tmp_capa_ = x._capacity;

			x._vecptr = this->_vecptr;
			x._alloc = this->_alloc;
			x._size = this->_size;
			x._capacity = this->_capacity;

			this->_vecptr = tmp_ptr_;
			this->_alloc = tmp_alloc_;
			this->_size = tmp_size_;
			this->_capacity = tmp_capa_;
		}

		void	clear(void)
		{
			for (size_type i = 0; i < this->_size; ++i)
				this->_alloc.destroy(this->_vecptr + i);
			this->_size = 0;
		}

		// Allocator:
		allocator_type	get_allocator(void) const { return (this->_alloc); }

	/* non-member function overloads */
		// relational operators
		template <class U, class A>
		friend bool	operator==(const vector<U, A> &lhs, const vector<U, A> &rhs);
		template <class U, class A>
		friend bool	operator!=(const vector<U, A> &lhs, const vector<U, A> &rhs);
		template <class U, class A>
		friend bool	operator<(const vector<U, A> &lhs, const vector<U, A> &rhs);
		template <class U, class A>
		friend bool	operator<=(const vector<U, A> &lhs, const vector<U, A> &rhs);
		template <class U, class A>
		friend bool	operator>(const vector<U, A> &lhs, const vector<U, A> &rhs);
		template <class U, class A>
		friend bool	operator>=(const vector<U, A> &lhs, const vector<U, A> &rhs);

		// swap
		template <class U, class A>
		friend void	swap(vector<U, A> &x, vector<U, A> &y);
	}; // class vector template

	template <class T, class Alloc>
	bool	operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() == rhs.size())
		{
			typename vector<T, Alloc>::const_iterator	first1 = lhs.begin();
			typename vector<T, Alloc>::const_iterator	last1 = lhs.end();
			typename vector<T, Alloc>::const_iterator	first2 = rhs.begin();

			return (equal(first1, last1, first2));
		}
		return (false);
	}

	template <class T, class Alloc>
	bool	operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool	operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool	operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool	operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool	operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void	swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}

} // namespace ft

#endif

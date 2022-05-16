#ifndef UTILS_HPP
# define UTILS_HPP

namespace	ft
{

/* ************************************************************************************ */
/*																						*/
/*										enable_if										*/
/*																						*/
/* ************************************************************************************ */

	template <bool Cond, class T = void>
	struct	enable_if { };

	template <class T>
	struct	enable_if<true, T>
	{
		typedef T	type;
	};

/* ************************************************************************************ */
/*																						*/
/*										is_integral										*/
/*																						*/
/* ************************************************************************************ */

	template <class T, T v>
	struct	integral_constant
	{
		static const T				value = v;
		typedef T					value_type;
		typedef integral_constant	type;

		operator value_type(void)
		{
			return (v);
		}
	};

	typedef integral_constant<bool,true>	true_type;
	typedef integral_constant<bool,false>	false_type;

	template <class T>
	struct	is_integral : public false_type { };

	template<>	struct	is_integral<unsigned short int>	: public true_type	{ };
	template<>	struct	is_integral<int>				: public true_type	{ };
	template<>	struct	is_integral<short int>			: public true_type	{ };
	template<>	struct	is_integral<unsigned int>		: public true_type	{ };
	template<>	struct	is_integral<long int>			: public true_type	{ };
	template<>	struct	is_integral<unsigned long int>	: public true_type	{ };
	template<>	struct	is_integral<bool>				: public true_type	{ };
	template<>	struct	is_integral<signed char>		: public true_type	{ };
	template<>	struct	is_integral<unsigned char>		: public true_type	{ };
	template<>	struct	is_integral<char>				: public true_type	{ };
	template<>	struct	is_integral<wchar_t>			: public true_type	{ };

/* ************************************************************************************ */
/*																						*/
/*										equal											*/
/*																						*/
/* ************************************************************************************ */

	template <class InputIterator1, class InputIterator2>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return (false);
			++first1; ++first2;
		}
		return (true);
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return (false);
			++first1; ++first2;
		}
		return (true);
	}

/* ************************************************************************************ */
/*																						*/
/*								lexicographical_compare									*/
/*																						*/
/* ************************************************************************************ */

	template <class InputIterator1, class InputIterator2>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		 while (first1 != last1)
		{
			if ((first2 == last2) || (*first2 < *first1))
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		 while (first1 != last1)
		{
			if ((first2 == last2) || comp(*first2, *first1))
				return (false);
			else if (comp(*first1, *first2))
				return (true);
			++first1; ++first2;
		}
		return (first2 != last2);
	}

/* ************************************************************************************ */
/*																						*/
/*										std::pair										*/
/*																						*/
/* ************************************************************************************ */

	template <class T1, class T2>
	struct	pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		pair(void) : first(first_type()), second(second_type()) { }
		template <class U, class V>
		pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) { }
		pair(const first_type &a, const second_type &b) : first(a), second(b) { }

		pair&	operator=(const pair &pr)
		{
			if (this != &pr)
			{
				this->first = pr.first;
				this->second = pr.second;
			}
			return (*this);
		}

		template <class U1, class U2>
		friend bool	operator==(const pair<U1, U2> &lhs, const pair<U1, U2> &rhs);
		template <class U1, class U2>
		friend bool	operator!=(const pair<U1, U2> &lhs, const pair<U1, U2> &rhs);
		template <class U1, class U2>
		friend bool	operator<(const pair<U1, U2> &lhs, const pair<U1, U2> &rhs);
		template <class U1, class U2>
		friend bool	operator<=(const pair<U1, U2> &lhs, const pair<U1, U2> &rhs);
		template <class U1, class U2>
		friend bool	operator>(const pair<U1, U2> &lhs, const pair<U1, U2> &rhs);
		template <class U1, class U2>
		friend bool	operator>=(const pair<U1, U2> &lhs, const pair<U1, U2> &rhs);
	};

	template <class T1, class T2>
	bool	operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return ((lhs.first == rhs.first) && (lhs.second == rhs.second));
	}

	template <class T1, class T2>
	bool	operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T1, class T2>
	bool	operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return ((lhs.first < rhs.first) || (!(rhs.first < lhs.first) && (lhs.second < rhs.second)));
	}

	template <class T1, class T2>
	bool	operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T1, class T2>
	bool	operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool	operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(lhs < rhs));
	}

/* ************************************************************************************ */
/*																						*/
/*									std::make_pair										*/
/*																						*/
/* ************************************************************************************ */

	template <class T1,class T2>
	pair<T1, T2>	make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

} // namespace ft

#endif

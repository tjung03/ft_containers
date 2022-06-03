#include <iostream>
#include <string>
#include <chrono>
#include <exception>

#include <vector>
#include <map>
#include <stack>

#define YELLOW "\033[0;33m"
#define DEFAULT "\033[0m"

namespace ft = std;

//////////////////////////////////////////////////////////// VECTOR
template <typename Vector>
void	show_vector(Vector &test)
{
	typedef	typename Vector::iterator	iterator;

	iterator	begin = test.begin();
	iterator	end = test.end();

	std::cout<<YELLOW<<"[ VECTOR ]"<<DEFAULT<<std::endl;
	std::cout<<"-> vector size: "<<test.size()<<std::endl;
	std::cout<<"-> vector capacity: "<<test.capacity()<<std::endl;
	std::cout<<"---------------------------------------"<<std::endl;
	for (iterator tmp = begin; tmp != end; ++tmp)
		std::cout<<"("<<*tmp<<") ";
	std::cout<<std::endl<<std::endl;
}

//////////////////////////////////////////////////////////// MAP

template <typename Map>
void	show_map(Map &test)
{
	typedef	typename Map::iterator					iterator;

	iterator	begin = test.begin();
	iterator	end = test.end();

	std::cout<<YELLOW<<"[ MAP ]"<<DEFAULT<<std::endl;
	std::cout<<"-> map size: "<<test.size()<<std::endl;
	std::cout<<"---------------------------------------"<<std::endl;
	for (iterator tmp = begin; tmp != end; ++tmp)
		std::cout<<"("<<(*tmp).first<<") ";
	std::cout<<std::endl<<std::endl;
}

//////////////////////////////////////////////////////////// STACK
template <typename T>
class	MutantStack : public ft::stack<T>
{
public:
	MutantStack(void) { }
	MutantStack(const MutantStack<T> &src) { *this = src; }
	MutantStack<T>&	operator=(const MutantStack<T> &rhs)
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack(void) { }

	typedef	typename ft::stack<T>::container_type::iterator	iterator;

	iterator	begin(void) { return (this->c.begin()); }
	iterator	end(void) { return (this->c.end()); }
};

template <typename MutantStack>
void	show_stack(MutantStack &test)
{
	typedef	typename MutantStack::iterator	iterator;

	iterator	begin = test.begin();
	iterator	end = test.end();

	std::cout<<YELLOW<<"[ STACK ]"<<DEFAULT<<std::endl;
	std::cout<<"-> stack size: "<<test.size()<<std::endl;
	std::cout<<"---------------------------------------"<<std::endl;
	for (iterator tmp = begin; tmp != end; ++tmp)
		std::cout<<"("<<*tmp<<") ";
	std::cout<<std::endl<<std::endl;
}

//////////////////////////////////////////////////////////// SHOW END

int	main(void)
{
	typedef	std::chrono::system_clock::time_point	time_point;
	typedef	std::chrono::system_clock				clock;
	typedef	std::chrono::microseconds				micro_t;
	typedef	int										type1;
//	typedef	int										type2;

	time_point	start_time;
	time_point	end_time;
	micro_t		micro;
	int64_t		max = 0;

	std::cout<<std::endl;
	std::cout<<YELLOW<<"[ STD_containers ]"<<DEFAULT<<std::endl<<std::endl;

/* ******************************************************************************************************** */
/*																											*/
/*												VECTOR														*/
/*																											*/
/* ******************************************************************************************************** */

	std::cout<<"=============== VECTOR ================"<<std::endl;
	int	arr_size = 10;
	int	arr_v[10];

	int	*n = &arr_size;

	for (int i = 0; i < *n; ++i)
		arr_v[i] = (i + 1) * 100;

	std::cout<<"* arr_v *"<<std::endl;
	for (int i = 0; i < *n; ++i)
		std::cout<<"("<<arr_v[i]<<") ";
	std::cout<<std::endl<<std::endl;

	std::cout<<"--------- default constructor ---------"<<std::endl;
	std::cout<<"* ft::vector<type1>	v1 *"<<std::endl;
	start_time = clock::now();
	ft::vector<type1>	v1;
	end_time = clock::now();
	show_vector(v1);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"----------- fill constructor ----------"<<std::endl;
	std::cout<<"* ft::vector<type1>	v2(*n) *"<<std::endl;
	start_time = clock::now();
	ft::vector<type1>	v2(*n);
	end_time = clock::now();
	show_vector(v2);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"* ft::vector<type1>	v3(*n, arr_v[0]) *"<<std::endl;
	start_time = clock::now();
	ft::vector<type1>	v3(*n, arr_v[0]);
	end_time = clock::now();
	show_vector(v3);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"---------- range constructor ----------"<<std::endl;
	std::cout<<"* ft::vector<type1>	v4(&arr_v[0], &arr_v[*n]) *"<<std::endl;
	start_time = clock::now();
	ft::vector<type1>	v4(&arr_v[0], &arr_v[*n]);
	end_time = clock::now();
	show_vector(v4);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	ft::vector<type1>::iterator	first4 = v4.begin();
	ft::vector<type1>::iterator	last4 = v4.end();
	std::cout<<"* ft::vector<type1>	v5(first1, last1) *"<<std::endl;
	start_time = clock::now();
	ft::vector<type1>	v5(first4, last4);
	end_time = clock::now();
	show_vector(v5);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"----------- copy constructor ----------"<<std::endl;
	std::cout<<"* ft::vector<type1>	v6(v5) *"<<std::endl;
	start_time = clock::now();
	ft::vector<type1>	v6(v5);
	end_time = clock::now();
	show_vector(v6);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"-------------- operator= --------------"<<std::endl;
	std::cout<<"* v1 = v6 *"<<std::endl;
	start_time = clock::now();
	v1 = v6;
	end_time = clock::now();
	show_vector(v1);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"---------------- begin ----------------"<<std::endl;
	std::cout<<"* ft::vector<type1>::iterator first = v.begin() *"<<std::endl;
	start_time = clock::now();
	ft::vector<type1>::iterator first1 = v1.begin();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	ft::vector<type1>::iterator first2 = v2.begin();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	ft::vector<type1>::iterator first3 = v3.begin();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	first4 = v4.begin();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	ft::vector<type1>::iterator first5 = v5.begin();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	ft::vector<type1>::iterator first6 = v6.begin();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();

	std::cout<<"*v1::first1: "<<*first1<<std::endl;
	std::cout<<"*v2::first2: "<<*first2<<std::endl;
	std::cout<<"*v3::first3: "<<*first3<<std::endl;
	std::cout<<"*v4::first4: "<<*first4<<std::endl;
	std::cout<<"*v5::first5: "<<*first5<<std::endl;
	std::cout<<"*v6::first6: "<<*first6<<std::endl<<std::endl;
	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"----------------- end -----------------"<<std::endl;
	std::cout<<"* ft::vector<type1>::iterator last = v.end() *"<<std::endl;
	start_time = clock::now();
	ft::vector<type1>::iterator	last1 = v1.end();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	ft::vector<type1>::iterator	last2 = v2.end();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	ft::vector<type1>::iterator	last3 = v3.end();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	last4 = v4.end();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	ft::vector<type1>::iterator	last5 = v5.end();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	ft::vector<type1>::iterator	last6 = v6.end();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();

	std::cout<<"*v1::last1: "<<*(last1 - 1)<<std::endl;
	std::cout<<"*v2::last2: "<<*(last2 - 1)<<std::endl;
	std::cout<<"*v3::last3: "<<*(last3 - 1)<<std::endl;
	std::cout<<"*v4::last4: "<<*(last4 - 1)<<std::endl;
	std::cout<<"*v5::last5: "<<*(last5 - 1)<<std::endl;
	std::cout<<"*v6::last6: "<<*(last6 - 1)<<std::endl<<std::endl;
	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"--------------- rbegin ----------------"<<std::endl;
	std::cout<<"* ft::vector<type1>::iterator rfirst = v.rbegin() *"<<std::endl;
	start_time = clock::now();
	ft::vector<type1>::reverse_iterator rfirst1 = v1.rbegin();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	ft::vector<type1>::reverse_iterator rfirst2 = v2.rbegin();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	ft::vector<type1>::reverse_iterator rfirst3 = v3.rbegin();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	ft::vector<type1>::reverse_iterator rfirst4 = v4.rbegin();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	ft::vector<type1>::reverse_iterator rfirst5 = v5.rbegin();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	ft::vector<type1>::reverse_iterator rfirst6 = v6.rbegin();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();

	std::cout<<"*v1::rfirst1: "<<*rfirst1<<std::endl;
	std::cout<<"*v2::rfirst2: "<<*rfirst2<<std::endl;
	std::cout<<"*v3::rfirst3: "<<*rfirst3<<std::endl;
	std::cout<<"*v4::rfirst4: "<<*rfirst4<<std::endl;
	std::cout<<"*v5::rfirst5: "<<*rfirst5<<std::endl;
	std::cout<<"*v6::rfirst6: "<<*rfirst6<<std::endl<<std::endl;
	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"---------------- rend -----------------"<<std::endl;
	std::cout<<"* ft::vector<type1>::iterator rlast = v.rend() *"<<std::endl;
	start_time = clock::now();
	ft::vector<type1>::reverse_iterator	rlast1 = v1.rend();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	ft::vector<type1>::reverse_iterator rlast2 = v2.rend();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	ft::vector<type1>::reverse_iterator rlast3 = v3.rend();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	ft::vector<type1>::reverse_iterator rlast4 = v4.rend();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	ft::vector<type1>::reverse_iterator rlast5 = v5.rend();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	start_time = clock::now();
	ft::vector<type1>::reverse_iterator rlast6 = v6.rend();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();

	std::cout<<"*v1::rlast1: "<<*(rlast1 - 1)<<std::endl;
	std::cout<<"*v2::rlast2: "<<*(rlast2 - 1)<<std::endl;
	std::cout<<"*v3::rlast3: "<<*(rlast3 - 1)<<std::endl;
	std::cout<<"*v4::rlast4: "<<*(rlast4 - 1)<<std::endl;
	std::cout<<"*v5::rlast5: "<<*(rlast5 - 1)<<std::endl;
	std::cout<<"*v6::rlast6: "<<*(rlast6 - 1)<<std::endl<<std::endl;
	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"-------------- max_size ---------------"<<std::endl;
	std::cout<<"* v1.max_size() *"<<std::endl;
	start_time = clock::now();
	size_t	max_size = v1.max_size();
	end_time = clock::now();
	std::cout<<"v1 - max_size: "<<max_size<<std::endl<<std::endl;
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"--------------- resize ----------------"<<std::endl;
	std::cout<<"* v1.resize(5) *"<<std::endl;
	start_time = clock::now();
	v1.resize(5);
	end_time = clock::now();
	show_vector(v1);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"* v1.resize(11, 550) *"<<std::endl;
	start_time = clock::now();
	v1.resize(11, 550);
	end_time = clock::now();
	show_vector(v1);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"---------------- empty ----------------"<<std::endl;
	bool	is_empty;

	std::cout<<"* is_empty = v7.empty() *"<<std::endl;
	ft::vector<type1>	v7;
	start_time = clock::now();
	is_empty = v7.empty();
	end_time = clock::now();
	std::cout<<"-> Is v7 empty? ";
	if (is_empty)
		std::cout<<"true"<<std::endl<<std::endl;
	else
		std::cout<<"false"<<std::endl<<std::endl;
	show_vector(v7);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"* is_empty = v1.empty() *"<<std::endl;
	start_time = clock::now();
	is_empty = v1.empty();
	end_time = clock::now();
	std::cout<<"-> Is v1 empty? ";
	if (is_empty)
		std::cout<<"true"<<std::endl<<std::endl;
	else
		std::cout<<"false"<<std::endl<<std::endl;
	show_vector(v1);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"--------------- reserve ---------------"<<std::endl;
	std::cout<<"* v7.reserve(100) *"<<std::endl;
	std::cout<<"-> 이전 v7 vecptr 주소 확인해보기"<<std::endl;
	start_time = clock::now();
	v7.reserve(100);
	end_time = clock::now();
	show_vector(v7);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"* v7.reserve(50) *"<<std::endl;
	start_time = clock::now();
	v7.reserve(50);
	end_time = clock::now();
	show_vector(v7);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"* v1.reserve(10) *"<<std::endl;
	start_time = clock::now();
	v1.reserve(10);
	end_time = clock::now();
	show_vector(v1);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"------------- operator[] --------------"<<std::endl;
	std::cout<<"original value - v1[2]: "<<v1[2]<<std::endl;
	std::cout<<"* v1[2] = 350 *"<<std::endl;
	start_time = clock::now();
	v1[2] = 350;
	end_time = clock::now();
	std::cout<<" changed value - v1[2]: "<<v1[2]<<std::endl;
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;
	show_vector(v1);

	std::cout<<"original value - v1[8]: "<<v1[8]<<std::endl;
	std::cout<<"* v1[8] = 250 *"<<std::endl;
	start_time = clock::now();
	v1[8] = 250;
	end_time = clock::now();
	std::cout<<" changed value - v1[8]: "<<v1[8]<<std::endl;
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;
	show_vector(v1);

	std::cout<<"----------------- at ------------------"<<std::endl;
	std::cout<<"original value - v1.at(1): "<<v1.at(1)<<std::endl;
	std::cout<<"* v1.at(1) = 2 *"<<std::endl;
	start_time = clock::now();
	v1.at(1) = 2;
	end_time = clock::now();
	std::cout<<" changed value - v1.at(1): "<<v1.at(1)<<std::endl;
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;
	show_vector(v1);

	std::cout<<"original value - v1.at(9): "<<v1.at(9)<<std::endl;
	std::cout<<"* v1.at(9) = 10 *"<<std::endl;
	start_time = clock::now();
	v1.at(9) = 10;
	end_time = clock::now();
	std::cout<<" changed value - v1.at(9): "<<v1.at(9)<<std::endl;
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;
	show_vector(v1);

	std::cout<<"* index: out of range *"<<std::endl;
	std::cout<<"* v1.at(100) *"<<std::endl;
	try {
		v1.at(100);
	} catch (const std::exception &e) {
		std::cout<<"result - v1.at(100): "<<e.what()<<std::endl;
		std::cout<<"So, vector's \"at()\" always needs \"try~catch\"."<<std::endl;
	}
	std::cout<<std::endl;

	std::cout<<"---------------- front -----------------"<<std::endl;
	std::cout<<"original value - v1.front(): "<<v1.front()<<std::endl;
	std::cout<<"* v1.front() = 777 *"<<std::endl;
	start_time = clock::now();
	v1.front() = 777;
	end_time = clock::now();
	std::cout<<" changed value - v1.front(): "<<v1.front()<<std::endl;
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;
	show_vector(v1);

	std::cout<<"----------------- back -----------------"<<std::endl;
	std::cout<<"original value - v1.back(): "<<v1.back()<<std::endl;
	std::cout<<"* v1.back() = 1004 *"<<std::endl;
	start_time = clock::now();
	v1.back() = 1004;
	end_time = clock::now();
	std::cout<<" changed value - v1.back(): "<<v1.back()<<std::endl;
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;
	show_vector(v1);

	std::cout<<"------------ range assign -------------"<<std::endl;
	first1 = v1.begin();
	last1 = v1.end();
	show_vector(v2);
	std::cout<<"* v2.assign(first1, last1) *"<<std::endl<<std::endl;
	start_time = clock::now();
	v2.assign(first1, last1);
	end_time = clock::now();
	show_vector(v2);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"------------- fill assign -------------"<<std::endl;
	std::cout<<"* v2.assign(10, 10) *"<<std::endl<<std::endl;
	start_time = clock::now();
	v2.assign(10, 10);
	end_time = clock::now();
	show_vector(v2);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"-------------- push_back --------------"<<std::endl;
	std::cout<<"* v2.push_back(11) *"<<std::endl<<std::endl;
	start_time = clock::now();
	v2.push_back(11);
	end_time = clock::now();
	show_vector(v2);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"* v2.push_back(-10) *"<<std::endl<<std::endl;
	start_time = clock::now();
	v2.push_back(-10);
	end_time = clock::now();
	show_vector(v2);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"-------------- pop_back ---------------"<<std::endl;
	std::cout<<"* v2.pop_back() *"<<std::endl<<std::endl;
	start_time = clock::now();
	v2.pop_back();
	end_time = clock::now();
	show_vector(v2);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"* v2.pop_back() *"<<std::endl<<std::endl;
	start_time = clock::now();
	v2.pop_back();
	end_time = clock::now();
	show_vector(v2);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"-------- single element insert --------"<<std::endl;
	std::cout<<"* v2.insert(iterator:3, 5) *"<<std::endl<<std::endl;
	ft::vector<int>::iterator	tmp = v2.begin() + 3;
	start_time = clock::now();
	v2.insert(tmp, 5);
	end_time = clock::now();
	show_vector(v2);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"------------ fill insert --------------"<<std::endl;
	std::cout<<"* v2.insert(iterator:2, 4, 7) *"<<std::endl<<std::endl;
	tmp = v2.begin() + 2;
	start_time = clock::now();
	v2.insert(tmp, 4, 7);
	end_time = clock::now();
	show_vector(v2);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"------------ range insert -------------"<<std::endl;
	std::cout<<"* v2.insert(iterator:1, first1, last1) *"<<std::endl<<std::endl;
	tmp = v2.begin() + 1;
	start_time = clock::now();
	v2.insert(tmp, first1, last1);
	end_time = clock::now();
	show_vector(v2);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"-------- single element erase ---------"<<std::endl;
	tmp = v2.begin() + 3;
	std::cout<<"v2 삭제할 위치 값: "<<*tmp<<std::endl;
	std::cout<<"* tmp = v2.erase(tmp) *"<<std::endl;
	start_time = clock::now();
	tmp = v2.erase(tmp);
	end_time = clock::now();
	std::cout<<"v2 삭제 후 반환값: "<<*tmp<<std::endl<<std::endl;
	show_vector(v2);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"------------ range erase --------------"<<std::endl;
	std::cout<<"=> v2 전체 삭제"<<std::endl;
	std::cout<<"* tmp = v2.erase(first2, last2) *"<<std::endl;
	first2 = v2.begin();
	last2 = v2.end();
	start_time = clock::now();
	tmp = v2.erase(first2, last2);
	end_time = clock::now();
	std::cout<<"-> 전체 삭제 완료? ";
	if (tmp == v2.end())
		std::cout<<"tmp == v2.end() : 성공"<<std::endl;
	else
		std::cout<<"tmp != v2.end() : 실패"<<std::endl;
	show_vector(v2);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"------------- member swap -------------"<<std::endl;
	std::cout<<"v1 ->"<<std::endl;
	show_vector(v1);
	std::cout<<"v2 ->"<<std::endl;
	show_vector(v2);
	std::cout<<"* v2.swap(v1) *"<<std::endl<<std::endl;
	start_time = clock::now();
	v2.swap(v1);
	end_time = clock::now();
	std::cout<<"v1 ->"<<std::endl;
	show_vector(v1);
	std::cout<<"v2 ->"<<std::endl;
	show_vector(v2);
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"---------------- clear ----------------"<<std::endl;
	std::cout<<"* v.clear() *"<<std::endl<<std::endl;
	std::cout<<"-> v2.clear()"<<std::endl;
	start_time = clock::now();
	v2.clear();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	show_vector(v2);
	std::cout<<"-> v3.clear()"<<std::endl;
	start_time = clock::now();
	v3.clear();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	show_vector(v3);
	std::cout<<"-> v4.clear()"<<std::endl;
	start_time = clock::now();
	v4.clear();
	end_time = clock::now();
	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
	max = micro.count() < max ? max : micro.count();
	show_vector(v4);

	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

	std::cout<<"---- relational operators (vector) ----"<<std::endl<<std::endl;
	std::cout<<"=> v5"<<std::endl;
	show_vector(v5);
	std::cout<<"=> v6"<<std::endl;
	show_vector(v6);

	std::cout<<"-> operator=="<<std::endl;
	std::cout<<"v5 == v6 ? ";
	if (v5 == v6)
		std::cout<<"true"<<std::endl<<std::endl;
	else
		std::cout<<"false"<<std::endl<<std::endl;
	std::cout<<"-> operator!="<<std::endl;
	std::cout<<"v5 != v6 ? ";
	if (v5 != v6)
		std::cout<<"true"<<std::endl<<std::endl;
	else
		std::cout<<"false"<<std::endl<<std::endl;
	std::cout<<"-> operator<"<<std::endl;
	std::cout<<"v5 < v6 ? ";
	if (v5 < v6)
		std::cout<<"true"<<std::endl<<std::endl;
	else
		std::cout<<"false"<<std::endl<<std::endl;
	std::cout<<"-> operator<="<<std::endl;
	std::cout<<"v5 <= v6 ? ";
	if (v5 <= v6)
		std::cout<<"true"<<std::endl<<std::endl;
	else
		std::cout<<"false"<<std::endl<<std::endl;
	std::cout<<"-> operator>"<<std::endl;
	std::cout<<"v5 > v6 ? ";
	if (v5 > v6)
		std::cout<<"true"<<std::endl<<std::endl;
	else
		std::cout<<"false"<<std::endl<<std::endl;
	std::cout<<"-> operator>="<<std::endl;
	std::cout<<"v5 >= v6 ? ";
	if (v5 >= v6)
		std::cout<<"true"<<std::endl<<std::endl;
	else
		std::cout<<"false"<<std::endl<<std::endl;

// /* ******************************************************************************************************** */
// /*																											*/
// /*													MAP														*/
// /*																											*/
// /* ******************************************************************************************************** */

// 	std::cout<<"================= MAP ================="<<std::endl;
// 	int	pair_size = 10;
// 	ft::pair<type1,type2>	pair_m[10];

// 	n = &pair_size;

// 	for (int i = 0; i < *n; ++i)
// 		pair_m[i] = ft::make_pair((i + 1) * 100, i + 1);

// 	std::cout<<"* pair_m *"<<std::endl;
// 	for (int i = 0; i < *n; ++i)
// 		std::cout<<"("<<pair_m[i].first<<") ";
// 	std::cout<<std::endl<<std::endl;

// 	std::cout<<"---------- empty constructor ----------"<<std::endl;
// 	std::cout<<"* ft::map<type1,type2>	m1 *"<<std::endl;
// 	start_time = clock::now();
// 	ft::map<type1,type2>	m1;
// 	end_time = clock::now();
// 	show_map(m1);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"------------- operator[] --------------"<<std::endl;
// 	std::cout<<"* m1[pair.first] = pair.second *"<<std::endl;
// 	for (int i = 0; i < *n; ++i)
// 	{
// 		start_time = clock::now();
// 		m1[pair_m[i].first] = pair_m[i].second;
// 		end_time = clock::now();
// 		max = micro.count() < max ? max : micro.count();
// 	}
// 	show_map(m1);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"---------- range constructor ----------"<<std::endl;
// 	std::cout<<"* ft::map<type1,type2>	m2(m1.begin(), m1.end()) *"<<std::endl;
// 	start_time = clock::now();
// 	ft::map<type1,type2>	m2(m1.begin(), m1.end());
// 	end_time = clock::now();
// 	show_map(m2);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"----------- copy constructor ----------"<<std::endl;
// 	std::cout<<"* ft::map<type1,type2>	m3(m2) *"<<std::endl;
// 	start_time = clock::now();
// 	ft::map<type1,type2>	m3(m2);
// 	end_time = clock::now();
// 	show_map(m3);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"-------------- operator= --------------"<<std::endl;
// 	std::cout<<"* m4 = m3 *"<<std::endl;
// 	ft::map<type1,type2>	m4;
// 	start_time = clock::now();
// 	m4 = m3;
// 	end_time = clock::now();
// 	show_map(m4);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"---------------- begin ----------------"<<std::endl;
// 	std::cout<<"* ft::map<type1,type2>::iterator m_first = m.begin() *"<<std::endl;
// 	start_time = clock::now();
// 	ft::map<type1,type2>::iterator	mfirst1 = m1.begin();
// 	end_time = clock::now();
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	max = micro.count() < max ? max : micro.count();
// 	start_time = clock::now();
// 	ft::map<type1,type2>::iterator	mfirst2 = m2.begin();
// 	end_time = clock::now();
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	max = micro.count() < max ? max : micro.count();
// 	start_time = clock::now();
// 	ft::map<type1,type2>::iterator	mfirst3 = m3.begin();
// 	end_time = clock::now();
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	max = micro.count() < max ? max : micro.count();
// 	start_time = clock::now();
// 	ft::map<type1,type2>::iterator	mfirst4 = m4.begin();
// 	end_time = clock::now();
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	max = micro.count() < max ? max : micro.count();

// 	std::cout<<"*m1::mfirst1.first: "<<(*mfirst1).first<<std::endl;
// 	std::cout<<"*m2::mfirst2.first: "<<(*mfirst2).first<<std::endl;
// 	std::cout<<"*m3::mfirst3.first: "<<(*mfirst3).first<<std::endl;
// 	std::cout<<"*m4::mfirst4.first: "<<(*mfirst4).first<<std::endl<<std::endl;
// 	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"----------------- end -----------------"<<std::endl;
// 	std::cout<<"* ft::map<type1,type2>::iterator mlast = m.end() *"<<std::endl;
// 	start_time = clock::now();
// 	ft::map<type1,type2>::iterator	mlast1 = m1.end();
// 	end_time = clock::now();
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	max = micro.count() < max ? max : micro.count();
// 	start_time = clock::now();
// 	ft::map<type1,type2>::iterator	mlast2 = m2.end();
// 	end_time = clock::now();
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	max = micro.count() < max ? max : micro.count();
// 	start_time = clock::now();
// 	ft::map<type1,type2>::iterator	mlast3 = m3.end();
// 	end_time = clock::now();
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	max = micro.count() < max ? max : micro.count();
// 	start_time = clock::now();
// 	ft::map<type1,type2>::iterator	mlast4 = m4.end();
// 	end_time = clock::now();
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	max = micro.count() < max ? max : micro.count();

// 	std::cout<<"*m1::mlast1.first: "<<(*mlast1).first<<std::endl;
// 	std::cout<<"*m2::mlast2.first: "<<(*mlast2).first<<std::endl;
// 	std::cout<<"*m3::mlast3.first: "<<(*mlast3).first<<std::endl;
// 	std::cout<<"*m4::mlast4.first: "<<(*mlast4).first<<std::endl<<std::endl;
// 	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"--------------- rbegin ----------------"<<std::endl;
// 	std::cout<<"* ft::map<type1,type2>::reverse_iterator mrfirst = m.rbegin() *"<<std::endl;
// 	start_time = clock::now();
// 	ft::map<type1,type2>::reverse_iterator mrfirst1 = m1.rbegin();
// 	end_time = clock::now();
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	max = micro.count() < max ? max : micro.count();
// 	start_time = clock::now();
// 	ft::map<type1,type2>::reverse_iterator mrfirst2 = m2.rbegin();
// 	end_time = clock::now();
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	max = micro.count() < max ? max : micro.count();
// 	start_time = clock::now();
// 	ft::map<type1,type2>::reverse_iterator mrfirst3 = m3.rbegin();
// 	end_time = clock::now();
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	max = micro.count() < max ? max : micro.count();
// 	start_time = clock::now();
// 	ft::map<type1,type2>::reverse_iterator mrfirst4 = m4.rbegin();
// 	end_time = clock::now();
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	max = micro.count() < max ? max : micro.count();

// 	std::cout<<"*m1::mrfirst1.first: "<<(*mrfirst1).first<<std::endl;
// 	std::cout<<"*m2::mrfirst2.first: "<<(*mrfirst2).first<<std::endl;
// 	std::cout<<"*m3::mrfirst3.first: "<<(*mrfirst3).first<<std::endl;
// 	std::cout<<"*m4::mrfirst4.first: "<<(*mrfirst4).first<<std::endl<<std::endl;
// 	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"---------------- rend -----------------"<<std::endl;
// 	std::cout<<"* ft::map<type1,type2>::reverse_iterator mrlast = m.rend() *"<<std::endl;
// 	start_time = clock::now();
// 	ft::map<type1,type2>::reverse_iterator mrlast1 = m1.rend();
// 	end_time = clock::now();
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	max = micro.count() < max ? max : micro.count();
// 	start_time = clock::now();
// 	ft::map<type1,type2>::reverse_iterator mrlast2 = m2.rend();
// 	end_time = clock::now();
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	max = micro.count() < max ? max : micro.count();
// 	start_time = clock::now();
// 	ft::map<type1,type2>::reverse_iterator mrlast3 = m3.rend();
// 	end_time = clock::now();
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	max = micro.count() < max ? max : micro.count();
// 	start_time = clock::now();
// 	ft::map<type1,type2>::reverse_iterator mrlast4 = m4.rend();
// 	end_time = clock::now();
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	max = micro.count() < max ? max : micro.count();

// 	std::cout<<"m1::*(--mrlast1).first: "<<(*(--mrlast1)).first<<std::endl;
// 	std::cout<<"m2::*(--mrlast2).first: "<<(*(--mrlast2)).first<<std::endl;
// 	std::cout<<"m3::*(--mrlast3).first: "<<(*(--mrlast3)).first<<std::endl;
// 	std::cout<<"m4::*(--mrlast4).first: "<<(*(--mrlast4)).first<<std::endl<<std::endl;
// 	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"---------------- empty ----------------"<<std::endl;
// 	std::cout<<"* is_empty = m5.empty() *"<<std::endl;
// 	ft::map<type1,type2>	m5;
// 	start_time = clock::now();
// 	is_empty = m5.empty();
// 	end_time = clock::now();
// 	std::cout<<"-> Is m5 empty? ";
// 	if (is_empty)
// 		std::cout<<"true"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"false"<<std::endl<<std::endl;
// 	show_map(m5);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"* is_empty = m1.empty() *"<<std::endl;
// 	start_time = clock::now();
// 	is_empty = m1.empty();
// 	end_time = clock::now();
// 	std::cout<<"-> Is m1 empty? ";
// 	if (is_empty)
// 		std::cout<<"true"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"false"<<std::endl<<std::endl;
// 	show_map(m1);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"-------------- max_size ---------------"<<std::endl;
// 	std::cout<<"* m1.max_size() *"<<std::endl;
// 	start_time = clock::now();
// 	max_size = m1.max_size();
// 	end_time = clock::now();
// 	std::cout<<"m1 - max_size: "<<max_size<<std::endl<<std::endl;
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"-------- single element insert --------"<<std::endl;
// 	std::cout<<"* m1.insert(value_type) *"<<std::endl<<std::endl;

// 	std::cout<<"-> m1.insert(ft::make_pair(550, 0))"<<std::endl;
// 	start_time = clock::now();
// 	ft::pair<ft::map<type1,type2>::iterator, bool>	ret = m1.insert(ft::make_pair(550, 0));
// 	end_time = clock::now();
// 	std::cout<<"result -  first: "<<(*ret.first).first<<std::endl;
// 	std::cout<<"result - second: "<<ret.second<<std::endl;
// 	show_map(m1);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"-> m1.insert(ft::make_pair(100, 0))"<<std::endl;
// 	start_time = clock::now();
// 	ret = m1.insert(ft::make_pair(100, 0));
// 	end_time = clock::now();
// 	std::cout<<"result -  first: "<<(*ret.first).first<<std::endl;
// 	std::cout<<"result - second: "<<ret.second<<std::endl;
// 	show_map(m1);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"------------ with hint insert --------------"<<std::endl;
// 	std::cout<<"* m4.insert(hint, value_type) *"<<std::endl<<std::endl;

// 	ft::map<type1,type2>::iterator mtmp = m4.begin();
// 	std::cout<<"-> m4.insert(mtmp, ft::make_pair(550, 0))"<<std::endl;
// 	start_time = clock::now();
// 	mtmp = m4.insert(mtmp, ft::make_pair(550, 0));
// 	end_time = clock::now();
// 	std::cout<<"result -  first: "<<(*mtmp).first<<std::endl;
// 	show_map(m4);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	mtmp = m4.begin();
// 	std::cout<<"-> m4.insert(mtmp, ft::make_pair(100, 0))"<<std::endl;
// 	start_time = clock::now();
// 	mtmp = m4.insert(mtmp, ft::make_pair(100, 0));
// 	end_time = clock::now();
// 	std::cout<<"result -  first: "<<(*mtmp).first<<std::endl;
// 	show_map(m4);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"------------ range insert -------------"<<std::endl;
// 	std::cout<<"* m2.insert(mfirst1, mlast1) *"<<std::endl<<std::endl;
// 	start_time = clock::now();
// 	m2.insert(mfirst1, mlast1);
// 	end_time = clock::now();
// 	show_map(m2);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"-------- single iterator erase ---------"<<std::endl;
// 	mtmp = m1.begin();
// 	std::cout<<"m1 에서 삭제할 키 값: "<<(*mtmp).first<<std::endl;
// 	std::cout<<"* m1.erase(mtmp) *"<<std::endl<<std::endl;
// 	start_time = clock::now();
// 	m1.erase(mtmp);
// 	end_time = clock::now();
// 	show_map(m1);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"-------- single key erase ---------"<<std::endl;
// 	std::cout<<"m1 에서 삭제할 키 값: 550"<<std::endl;
// 	std::cout<<"* size_t = m1.erase(550) : 성공 *"<<std::endl;
// 	start_time = clock::now();
// 	size_t	success = m1.erase(550);
// 	end_time = clock::now();
// 	std::cout<<"success-> "<<success<<std::endl<<std::endl;
// 	show_map(m1);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"m1 에서 삭제할 키 값: 10000"<<std::endl;
// 	std::cout<<"* size_t = m1.erase(10000) : 실패 *"<<std::endl;
// 	start_time = clock::now();
// 	success = m1.erase(10000);
// 	end_time = clock::now();
// 	std::cout<<"failure-> "<<success<<std::endl<<std::endl;
// 	show_map(m1);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"------------ range erase --------------"<<std::endl;
// 	std::cout<<"=> m1 전체 삭제"<<std::endl;
// 	std::cout<<"* m1.erase(mfirst1, mlast1) *"<<std::endl;
// 	mfirst1 = m1.begin();
// 	mlast1 = m1.end();
// 	start_time = clock::now();
// 	m1.erase(mfirst1, mlast1);
// 	end_time = clock::now();
// 	show_map(m1);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"------------- member swap -------------"<<std::endl;
// 	std::cout<<"m1 ->"<<std::endl;
// 	show_map(m1);
// 	std::cout<<"m4 ->"<<std::endl;
// 	show_map(m4);
// 	std::cout<<"* m1.swap(m4) *"<<std::endl<<std::endl;
// 	start_time = clock::now();
// 	m1.swap(m4);
// 	end_time = clock::now();
// 	std::cout<<"m1 ->"<<std::endl;
// 	show_map(m1);
// 	std::cout<<"m4 ->"<<std::endl;
// 	show_map(m4);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"---------------- clear ----------------"<<std::endl;
// 	std::cout<<"* m.clear() *"<<std::endl<<std::endl;
// 	std::cout<<"-> m3.clear()"<<std::endl;
// 	start_time = clock::now();
// 	m3.clear();
// 	end_time = clock::now();
// 	show_map(m3);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"---------------- find -----------------"<<std::endl;
// 	mlast2 = m2.end();
// 	std::cout<<"* iterator = m2.find(key) *"<<std::endl<<std::endl;
// 	start_time = clock::now();
// 	mtmp = m2.find(100);
// 	end_time = clock::now();
// 	std::cout<<"-> find 100 ? ";
// 	if (mtmp == mlast2)
// 		std::cout<<"failure"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"success - "<<mtmp->first<<std::endl<<std::endl;
// 	show_map(m2);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	start_time = clock::now();
// 	mtmp = m2.find(10000);
// 	end_time = clock::now();
// 	std::cout<<"-> find 10000 ? ";
// 	if (mtmp == mlast2)
// 		std::cout<<"failure"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"success - "<<mtmp->first<<std::endl<<std::endl;
// 	show_map(m2);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"---------------- count ----------------"<<std::endl;
// 	std::cout<<"* size_t = m2.count(key) *"<<std::endl<<std::endl;
// 	start_time = clock::now();
// 	success = m2.count(100);
// 	end_time = clock::now();
// 	std::cout<<"-> count 100 ? ";
// 	if (!success)
// 		std::cout<<"failure: "<<success<<std::endl<<std::endl;
// 	else
// 		std::cout<<"success: "<<success<<std::endl<<std::endl;
// 	show_map(m2);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	start_time = clock::now();
// 	success = m2.count(10000);
// 	end_time = clock::now();
// 	std::cout<<"-> count 10000 ? ";
// 	if (!success)
// 		std::cout<<"failure: "<<success<<std::endl<<std::endl;
// 	else
// 		std::cout<<"success: "<<success<<std::endl<<std::endl;
// 	show_map(m2);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"------------- lower_bound -------------"<<std::endl;
// 	std::cout<<"* iterator = m2.lower_bound(key) *"<<std::endl<<std::endl;
// 	start_time = clock::now();
// 	mtmp = m2.lower_bound(10000);
// 	end_time = clock::now();
// 	std::cout<<"-> lower_bound(10000) ? ";
// 	if (mtmp == mlast2)
// 		std::cout<<"failure"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"success: "<<(*mtmp).first<<std::endl<<std::endl;
// 	show_map(m2);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	start_time = clock::now();
// 	mtmp = m2.lower_bound(500);
// 	end_time = clock::now();
// 	std::cout<<"-> lower_bound(500) ? ";
// 	if (mtmp == mlast2)
// 		std::cout<<"failure"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"success: "<<(*mtmp).first<<std::endl<<std::endl;
// 	show_map(m2);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"------------- upper_bound -------------"<<std::endl;
// 	std::cout<<"* iterator = m2.upper_bound(key) *"<<std::endl<<std::endl;
// 	start_time = clock::now();
// 	mtmp = m2.upper_bound(10000);
// 	end_time = clock::now();
// 	std::cout<<"-> upper_bound(10000) ? ";
// 	if (mtmp == mlast2)
// 		std::cout<<"failure"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"success: "<<(*mtmp).first<<std::endl<<std::endl;
// 	show_map(m2);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	start_time = clock::now();
// 	mtmp = m2.upper_bound(500);
// 	end_time = clock::now();
// 	std::cout<<"-> upper_bound(500) ? ";
// 	if (mtmp == mlast2)
// 		std::cout<<"failure"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"success: "<<(*mtmp).first<<std::endl<<std::endl;
// 	show_map(m2);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"------------- equal_range -------------"<<std::endl;
// 	std::cout<<"* pair<iter,iter> = m2.equal_range(key) *"<<std::endl<<std::endl;
// 	start_time = clock::now();
// 	ft::pair<ft::map<type1,type2>::iterator, ft::map<type1,type2>::iterator> \
// 		e_range = m2.equal_range(10000);
// 	end_time = clock::now();
// 	std::cout<<"-> equal_range(10000) ? ";
// 	if ((*e_range.first).first == (*e_range.second).first)
// 		std::cout<<"failure: "<<(*e_range.first).first<<"~"<<(*e_range.second).first<<std::endl<<std::endl;
// 	else
// 		std::cout<<"success: "<<(*e_range.first).first<<"~"<<(*e_range.second).first<<std::endl<<std::endl;
// 	show_map(m2);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	start_time = clock::now();
// 	e_range = m2.equal_range(500);
// 	end_time = clock::now();
// 	std::cout<<"-> equal_range(500) ? ";
// 	if ((*e_range.first).first == (*e_range.second).first)
// 		std::cout<<"failure: "<<(*e_range.first).first<<"~"<<(*e_range.second).first<<std::endl<<std::endl;
// 	else
// 		std::cout<<"success: "<<(*e_range.first).first<<"~"<<(*e_range.second).first<<std::endl<<std::endl;
// 	show_map(m2);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"---- relational operators (vector) ----"<<std::endl<<std::endl;
// 	std::cout<<"=> m1"<<std::endl;
// 	show_map(m1);
// 	std::cout<<"=> m2"<<std::endl;
// 	show_map(m2);

// 	std::cout<<"-> operator=="<<std::endl;
// 	std::cout<<" m1 == m2 ? ";
// 	if (m1 == m2)
// 		std::cout<<"true"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"false"<<std::endl<<std::endl;
// 	std::cout<<"-> operator!="<<std::endl;
// 	std::cout<<"m1 != m2 ? ";
// 	if (m1 != m2)
// 		std::cout<<"true"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"false"<<std::endl<<std::endl;
// 	std::cout<<"-> operator<"<<std::endl;
// 	std::cout<<"m1 < m2 ? ";
// 	if (m1 < m2)
// 		std::cout<<"true"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"false"<<std::endl<<std::endl;
// 	std::cout<<"-> operator<="<<std::endl;
// 	std::cout<<"m1 <= m2 ? ";
// 	if (m1 <= m2)
// 		std::cout<<"true"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"false"<<std::endl<<std::endl;
// 	std::cout<<"-> operator>"<<std::endl;
// 	std::cout<<"m1 > m2 ? ";
// 	if (m1 > m2)
// 		std::cout<<"true"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"false"<<std::endl<<std::endl;
// 	std::cout<<"-> operator>="<<std::endl;
// 	std::cout<<"m1 >= m2 ? ";
// 	if (m1 >= m2)
// 		std::cout<<"true"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"false"<<std::endl<<std::endl;

// /* ******************************************************************************************************** */
// /*																											*/
// /*													STACK													*/
// /*																											*/
// /* ******************************************************************************************************** */

// 	std::cout<<"================ STACK ================"<<std::endl;
// 	std::cout<<"------------- constructor -------------"<<std::endl;
// 	std::cout<<"* MutantStack<int>	s1 *"<<std::endl<<std::endl;
// 	start_time = clock::now();
// 	MutantStack<int>	s1;
// 	end_time = clock::now();
// 	show_stack(s1);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"---------------- empty ----------------"<<std::endl;
// 	std::cout<<"* bool = s1.empty() *"<<std::endl<<std::endl;
// 	start_time = clock::now();
// 	is_empty = s1.empty();
// 	end_time = clock::now();
// 	if (is_empty == 1)
// 		std::cout<<"s1 is empty"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"s1 is not empty"<<std::endl<<std::endl;
// 	show_stack(s1);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"---------------- push -----------------"<<std::endl;
// 	std::cout<<"* s1.push() *"<<std::endl<<std::endl;
// 	for (int i = 0; i < *n; ++i)
// 	{
// 		start_time = clock::now();
// 		s1.push(arr_v[i]);
// 		end_time = clock::now();
// 		micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 		max = micro.count() < max ? max : micro.count();
// 	}
// 	show_stack(s1);
// 	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"----------------- top -----------------"<<std::endl;
// 	std::cout<<"* value_type = s1.top() *"<<std::endl<<std::endl;
// 	start_time = clock::now();
// 	int	top = s1.top();
// 	end_time = clock::now();
// 	std::cout<<"original s1 top: "<<top<<std::endl<<std::endl;
// 	show_stack(s1);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	start_time = clock::now();
// 	s1.top() = 777;
// 	end_time = clock::now();
// 	std::cout<<"changed s1 top: "<<top<<std::endl<<std::endl;
// 	show_stack(s1);
// 	micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 	std::cout<<YELLOW<<"수행 시간: "<<micro.count()<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"----------------- pop -----------------"<<std::endl;
// 	std::cout<<"* s1.pop() *"<<std::endl<<std::endl;
// 	for (int i = 0; i < 5; ++i)
// 	{
// 		start_time = clock::now();
// 		s1.pop();
// 		end_time = clock::now();
// 		micro = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
// 		max = micro.count() < max ? max : micro.count();
// 	}
// 	show_stack(s1);
// 	std::cout<<YELLOW<<"수행 시간: "<<max<<"μs"<<DEFAULT<<std::endl<<std::endl;

// 	std::cout<<"---- relational operators (map) ----"<<std::endl<<std::endl;
// 	MutantStack<int>	s2;
// 	for (int i = 0; i < *n; ++i)
// 		s2.push(arr_v[i]);

// 	std::cout<<"=> s1"<<std::endl;
// 	show_stack(s1);
// 	std::cout<<"=> s2"<<std::endl;
// 	show_stack(s2);

// 	std::cout<<"-> operator=="<<std::endl;
// 	std::cout<<" s1 == s2 ? ";
// 	if (s1 == s2)
// 		std::cout<<"true"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"false"<<std::endl<<std::endl;
// 	std::cout<<"-> operator!="<<std::endl;
// 	std::cout<<"s1 != s2 ? ";
// 	if (s1 != s2)
// 		std::cout<<"true"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"false"<<std::endl<<std::endl;
// 	std::cout<<"-> operator<"<<std::endl;
// 	std::cout<<"s1 < s2 ? ";
// 	if (s1 < s2)
// 		std::cout<<"true"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"false"<<std::endl<<std::endl;
// 	std::cout<<"-> operator<="<<std::endl;
// 	std::cout<<"s1 <= s2 ? ";
// 	if (s1 <= s2)
// 		std::cout<<"true"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"false"<<std::endl<<std::endl;
// 	std::cout<<"-> operator>"<<std::endl;
// 	std::cout<<"s1 > s2 ? ";
// 	if (s1 > s2)
// 		std::cout<<"true"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"false"<<std::endl<<std::endl;
// 	std::cout<<"-> operator>="<<std::endl;
// 	std::cout<<"s1 >= s2 ? ";
// 	if (s1 >= s2)
// 		std::cout<<"true"<<std::endl<<std::endl;
// 	else
// 		std::cout<<"false"<<std::endl<<std::endl;

	return (0);
}

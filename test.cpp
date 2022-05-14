#include <iostream>
#include <vector>
#include <exception>

using namespace std;

int	main(void)
{
	int			arr[] = {1, 2, 3, 4};
	vector<int>	vi;

	vi.assign(arr, arr + 4);
	for (int i = 0; i < 4; ++i)
		cout << vi[i] << " ";
	cout << endl;
	cout << "size: " << vi.size() << endl;
	cout << "capacity: " << vi.capacity() << endl;
	cout << "vecptr: " << &vi[0] << endl << endl;

	// vector<int>::iterator	itb = vi.begin();

	// cout << *(vi.erase(itb)) << endl;

	// vector<int>::iterator	itb1 = vi.begin();
	// vector<int>::iterator	ite1 = vi.end();
	// for (vector<int>::iterator tmp = itb1; tmp != ite1; ++tmp)
	// 	cout << *tmp << " ";
	// cout << endl;
	// cout << "size: " << vi.size() << endl;
	// cout << "capacity: " << vi.capacity() << endl;
	// cout << "vecptr: " << &vi[0] << endl << endl;

	vector<int>::iterator	itb2 = vi.begin();
	vector<int>::iterator	ite2 = vi.end();

	cout << *(vi.erase(itb2 + 1, ite2 - 1)) << endl;

	vector<int>::iterator	itb3 = vi.begin();
	vector<int>::iterator	ite3 = vi.end();
	for (vector<int>::iterator tmp = itb3; tmp != ite3; ++tmp)
		cout << *tmp << " ";
	cout << endl;
	cout << "size: " << vi.size() << endl;
	cout << "capacity: " << vi.capacity() << endl;
	cout << "vecptr: " << &vi[0] << endl;
	return (0);
}
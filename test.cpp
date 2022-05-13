#include <iostream>
#include <cstdint>

#include <vector>
#include <forward_list>
#include <string>
#include <typeinfo>
#include <map>

#include "utils.hpp"
#include "vector.hpp"
#include "map.hpp"

template <class T> struct greater_equal : std::binary_function <T,T,bool> {
	bool operator() (const T& x, const T& y) const {return x>y;}
};

class Test {
	private:
		int n;
	public:
		Test(int _n) : n(_n) {}
		~Test() {
			std::cout << n << "\n";
		}
};

void test_validity_iterator_while_erase() {
	typedef std::map<int, int>::iterator iterator;

	std::map<int, int> m;

	m.insert(std::make_pair<int, int>(5,5));
	m.insert(std::make_pair<int, int>(3,3));
	m.insert(std::make_pair<int, int>(8,8));
	m.insert(std::make_pair<int, int>(6,6));

	iterator it = m.begin();
	m.erase(5);
	it++;
	std::cout << (*it).first << "\n";
}

void test_ft_map_erase() {
	typedef ft::map<int, int>::iterator iterator;
	ft::map<int, int> m;

	m.insert(ft::make_pair<int, int>(5,5));
	m.insert(ft::make_pair<int, int>(3,3));
	m.insert(ft::make_pair<int, int>(8,8));
	m.insert(ft::make_pair<int, int>(6,6));

	iterator it = m.begin();
	m.erase(it);
	iterator it2 = m.begin();
	it2++;
	it2++;
	std::cout << (*it2).first << "\n";
}

void	test_ft_wierd_iterator() {
	ft::vector<int> v;

	v.push_back(5);
	v.push_back(5);
	v.push_back(5);
	v.push_back(5);
	v.push_back(5);

	// v.push_back(*(++(v.begin())));

	ft::vector<int>::iterator it = ++v.begin();
	it++;


}

int main() {
	// test_validity_iterator_while_erase();

	// test_ft_map_erase();

	test_ft_wierd_iterator();
	
	return 0;
}

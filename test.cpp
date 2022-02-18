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

int main() {
	// typedef	std::vector<int>				vector;
	// typedef std::map<int, int>				map;
	// typedef map::iterator					iterator;
	// typedef std::pair<int, int>				pair;
	// vector v;
	// map m;
	// std::pair<iterator, bool> it_ins = m.insert(pair(0, 0));
	// v.push_back((*(it_ins.first)).first);
	// m.insert(it_ins.first, pair(3, 5));
	// m.insert(pair(2, 3));
	// m.insert(pair(1, 0));
	// std::vector<pair> tmp;
	// for (size_t i = 0; i < 10; i++)
	// {
	// 	tmp.push_back(pair(i,i));
	// }
	// m.insert(tmp.begin(), tmp.end());
	// for (iterator it = m.begin(); it != m.end(); it++)
	// {
	// 	std::cout << "(" << (*it).first << ", " << (*it).second << ") ";
	// }
	// std::cout  << "\n";
	// for (size_t i = 0; i < v.size(); i++)
	// {
	// 	std::cout << v[i] << " ";
	// }
	// std::cout << "\n";

	// typedef ft::map<int, int >	_map;
	// typedef _map::iterator					_iterator;
	// typedef ft::pair<int, int>				_pair;
	// vector _v;
	// _map _m;
	// ft::pair<_iterator, bool> _it_ins = _m.insert(_pair(0, 0));
	// _v.push_back((*(_it_ins.first)).first);
	// _m.insert(_it_ins.first, _pair(3, 5));
	// _m.insert(_pair(2, 3));
	// _m.insert(_pair(1, 0));
	// std::vector<_pair> _tmp;
	// for (size_t i = 0; i < 10; i++)
	// {
	// 	_tmp.push_back(_pair(i,i));
	// }
	// _m.insert(_tmp.begin(), _tmp.end());
	// for (_iterator it = _m.begin(); it != _m.end(); it++)
	// {
	// 	std::cout << "(" << (*it).first << ", " << (*it).second << ") ";
	// }
	// std::cout  << "\n";
	// for (size_t i = 0; i < _v.size(); i++)
	// {
	// 	std::cout << _v[i] << " ";
	// }
	// std::cout << "\n";

	// ft::map<int, int> m;
	// m.insert(ft::make_pair<int, int> (0,0));
	// ft::map<int, int>::iterator it;
	// std::size_t i = 1;
	// while (1) {
	// 	std::cout << "size : " << i << "\n";
	// 	it = m.insert(it, ft::make_pair<int, int> (i,i));
	// 	i++;
	// }

	
	return 0;
}

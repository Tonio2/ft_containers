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

int main() {
	Test tmp1(0);
	Test tmp2(1);
	
	return 0;
}

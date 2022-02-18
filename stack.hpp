#pragma once

#include "utils.hpp"
#include "vector.hpp"

namespace ft {
	template <class T, class Container = ft::vector<T> > class stack {
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

			explicit			stack(const container_type& _ctnr = container_type()) {
				ctnr = _ctnr;
			}

			bool				empty() const { return ctnr.empty(); }
			size_type			size() const { return ctnr.size(); }
			value_type&			top() { return ctnr.back(); }
			const value_type&	top() const { return ctnr.back(); }
			void				push(const value_type& val) { ctnr.push_back(val); }
			void				pop() { ctnr.pop_back(); }
		private:
			container_type ctnr;
	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		stack<T, Container> l_cpy(lhs);
		stack<T, Container> r_cpy(rhs);

		if (l_cpy.size() != r_cpy.size()) return false;
		for (size_t i = 0; i < l_cpy.size(); i++) {
			if (l_cpy.top() != r_cpy.top()) return false;
			l_cpy.pop();
			r_cpy.pop();
		}
		return true;
	}

	template <class T, class Container>
	bool operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		size_t max_size;
		size_t i;

		stack<T, Container> l_cpy(lhs);
		stack<T, Container> r_cpy(rhs);
		i = 0;
		while (i < lhs.size() && i < rhs.size()) {
			if (l_cpy.top() < r_cpy.top()) return true;
			if (l_cpy.top() > r_cpy.top()) return false;
			i++;
		}
		return lhs.size() < rhs.size();
	}

	template <class T, class Container>
	bool operator<=  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		size_t max_size;
		size_t i;

		stack<T, Container> l_cpy(lhs);
		stack<T, Container> r_cpy(rhs);
		i = 0;
		while (i < lhs.size() && i < rhs.size()) {
			if (l_cpy.top() < r_cpy.top()) return true;
			if (l_cpy.top() > r_cpy.top()) return false;
			i++;
		}
		return lhs.size() <= rhs.size();
	}

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		size_t max_size;
		size_t i;

		stack<T, Container> l_cpy(lhs);
		stack<T, Container> r_cpy(rhs);
		i = 0;
		while (i < lhs.size() && i < rhs.size()) {
			if (l_cpy.top() > r_cpy.top()) return true;
			if (l_cpy.top() < r_cpy.top()) return false;
			i++;
		}
		return lhs.size() > rhs.size();
	}

	template <class T, class Container>
	bool operator>=  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		size_t max_size;
		size_t i;

		stack<T, Container> l_cpy(lhs);
		stack<T, Container> r_cpy(rhs);
		i = 0;
		while (i < lhs.size() && i < rhs.size()) {
			if (l_cpy.top() > r_cpy.top()) return true;
			if (l_cpy.top() < r_cpy.top()) return false;
			i++;
		}
		return lhs.size() >= rhs.size();
	}
}

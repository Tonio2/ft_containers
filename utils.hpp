/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:23:41 by alabalet          #+#    #+#             */
/*   Updated: 2022/02/17 14:24:36 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	UTILS_H
#define	UTILS_H

#include <iterator>

namespace ft {
	// is_integral
	template <class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T,v> type;
		operator value_type() const { return v; }
	};
	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template <typename T> struct is_integral : public false_type {};
	template <> struct is_integral<bool> : public true_type {};
	template <> struct is_integral<char> : public true_type {};
	template <> struct is_integral<char16_t> : public true_type {};
	template <> struct is_integral<char32_t> : public true_type {};
	template <> struct is_integral<wchar_t> : public true_type {};
	template <> struct is_integral<signed char> : public true_type {};
	template <> struct is_integral<short int> : public true_type {};
	template <> struct is_integral<int> : public true_type {};
	template <> struct is_integral<long int> : public true_type {};
	template <> struct is_integral<long long int> : public true_type {};
	template <> struct is_integral<unsigned char> : public true_type {};
	template <> struct is_integral<unsigned short int> : public true_type {};
	template <> struct is_integral<unsigned int> : public true_type {};
	template <> struct is_integral<unsigned long int> : public true_type {};
	template <> struct is_integral<unsigned long long int> : public true_type {};

	//enable_if
	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };

	//iterator
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

	template <class Iterator> struct iterator_traits {
		typedef typename Iterator::difference_type 	 	difference_type;
		typedef typename Iterator::value_type         	value_type;
		typedef typename Iterator::pointer   			pointer;
		typedef typename Iterator::reference 			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T> struct iterator_traits<T*> {
		typedef ptrdiff_t 	 						difference_type;
		typedef T         							value_type;
		typedef T*   								pointer;
		typedef T& 									reference;
		typedef std::random_access_iterator_tag			iterator_category;
	};

	template <class T> struct iterator_traits<const T*> {
		typedef ptrdiff_t 	 						difference_type;
		typedef T         							value_type;
		typedef const T*   							pointer;
		typedef const T& 							reference;
		typedef std::random_access_iterator_tag			iterator_category;
	};

	template <class Iter>
	class reverse_iterator : 
		public iterator<typename iterator_traits<Iter>::iterator_category,
						typename iterator_traits<Iter>::value_type,
						typename iterator_traits<Iter>::difference_type,
						typename iterator_traits<Iter>::pointer,
						typename iterator_traits<Iter>::reference>
	{
		private:
			Iter _base;
		public:
			typedef Iter											iterator_type;
			typedef typename iterator_traits<Iter>::reference		reference;
			typedef typename iterator_traits<Iter>::difference_type	difference_type;
			typedef typename iterator_traits<Iter>::pointer			pointer;

			reverse_iterator() : _base() {}

			explicit reverse_iterator(Iter it) : _base(it) {}

			template <class _Iter>
  				reverse_iterator (const reverse_iterator<_Iter>& rev_it) : _base(rev_it.base()) {}

			Iter base() const { return _base; }

			reference operator*() const { Iter tmp(_base); return *--tmp; }

			reverse_iterator operator+(difference_type n) const { return reverse_iterator(_base - n); }

			reverse_iterator& operator++() { --_base; return *this; }

			reverse_iterator operator++(int) { reverse_iterator tmp(_base); --_base; return tmp; }

			reverse_iterator& operator+=(difference_type n) { _base -= n; return *this; }

			reverse_iterator operator-(difference_type n) const { return reverse_iterator(_base + n); }

			reverse_iterator& operator--() { ++_base; return *this; }

			reverse_iterator operator--(int) { reverse_iterator tmp(_base); ++_base; return tmp; }

			reverse_iterator& operator-=(difference_type n) { _base += n; return *this; }

			pointer operator->() const { return &(operator*()); }

			reference operator[] (difference_type n) const { return base()[-n-1]; }
	};

	template <class Iterator>
  	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() == rhs.base();
	}

	template <class Iterator>
  	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() != rhs.base();
	}

	template <class Iterator>
  	bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() > rhs.base();
	}

	template <class Iterator>
  	bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() < rhs.base();
	}

	template <class Iterator>
  	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() >= rhs.base();
	}

	template <class Iterator>
  	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template <class Iterator>
  	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
		return rev_it + n;
	}

	template <class Iterator>
  	reverse_iterator<Iterator> operator- (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
		return rev_it - n;
	}
	
	//distance
	template<class InputIter>
	typename iterator_traits<InputIter>::difference_type
	_distance(InputIter first, InputIter last, std::input_iterator_tag) {
		typename iterator_traits<InputIter>::difference_type ret(0);
		for (; first != last; first++)
			ret++;
		return ret;
	}

	template<class InputIter>
	typename iterator_traits<InputIter>::difference_type
	_distance(InputIter first, InputIter last, std::random_access_iterator_tag) {
		return last - first;
	}

	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last) {
		return _distance(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
	}

	template <class T1, class T2> struct pair {
		typedef T1	first_type;
		typedef T2	second_type;
		first_type first;
		second_type second;
		
		pair() : first(first_type()), second(second_type()) {}

		template <class U, class V>
		pair(const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
		
		pair(const first_type& a, const second_type& b) : first(a), second(b) {}
		
		pair& operator=(const pair& pr) {
			first = pr.first;
			second = pr.second;
			return *this;
		}
	};

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);}

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs<lhs; }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs<rhs); }

	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
  	{
    	return ( pair<T1,T2>(x,y) );
	}
}

#endif

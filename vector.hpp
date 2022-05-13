#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include "utils.hpp"

namespace ft {

	template <class T> class vec_const_iterator;
	// template <class T> vec_iterator<T> operator+ (int n, vec_iterator<T>& x);
	// template <class T> vec_iterator<T> operator- (int n, vec_iterator<T>& x);

	template <class T>
	class vec_iterator : public iterator<std::random_access_iterator_tag, T> {
		public:
			typedef T			value_type;
			typedef T*			pointer;
			typedef T&			reference;

			typedef	ptrdiff_t	difference_type;


			vec_iterator() : ptr(0) {}
			vec_iterator(pointer _ptr) : ptr(_ptr) {}
			vec_iterator(const vec_iterator &x) : ptr(x.ptr) {}
			~vec_iterator() {}
			vec_iterator& operator= (const vec_iterator& x) {
				ptr = x.ptr;
				return *this;
			}

			reference operator*() const { return *ptr; }

			pointer operator->() const { return ptr; }

			vec_iterator& operator++() {
				ptr++;
				return *this;
			}

			vec_iterator operator++(int) {
				vec_iterator ret(*this);
				ptr++;
				return ret;
			}

			vec_iterator& operator--() {
				ptr--;
				return *this;
			}

			vec_iterator operator--(int) {
				vec_iterator ret(*this);
				ptr--;
				return ret;
			}

			vec_iterator operator+ (difference_type n) const {
				vec_iterator ret(*this);
				ret.ptr += n;
				return ret;
			}

			vec_iterator operator- (difference_type n) const {
				vec_iterator ret(*this);
				ret.ptr -= n;
				return ret;
			}

			difference_type operator- (const vec_iterator& x) const {
				return ptr - x.ptr;
			}

			difference_type operator- (const vec_const_iterator<T>& x) const {
				return ptr - &(*x);
			}

			vec_iterator& operator+= (difference_type n) {
				ptr += n;
				return *this;
			}

			vec_iterator& operator-= (difference_type n) {
				ptr -= n;
				return *this;
			}

			reference operator[] (difference_type n) const {
				return *(ptr + n);
			}

			bool operator== (const vec_iterator& y) const { return ptr == y.ptr; }
			bool operator!= (const vec_iterator& y) const { return ptr != y.ptr; }
			bool operator== (const vec_const_iterator<T>& y) const { return ptr == &(*y); }
			bool operator!= (const vec_const_iterator<T>& y) const { return ptr != &(*y); }
			bool operator< (const vec_iterator& y) const { return ptr < y.ptr; }
			bool operator<= (const vec_iterator& y) const { return ptr <= y.ptr; }
			bool operator> (const vec_iterator& y) const { return ptr > y.ptr; }
			bool operator>= (const vec_iterator& y) const { return ptr >= y.ptr; }
			bool operator< (const vec_const_iterator<T>& y) const { return ptr < &(*y); }
			bool operator<= (const vec_const_iterator<T>& y) const { return ptr <= &(*y); }
			bool operator> (const vec_const_iterator<T>& y) const { return ptr > &(*y); }
			bool operator>= (const vec_const_iterator<T>& y) const { return ptr >= &(*y); }

			friend vec_iterator<T> operator+ (int n, vec_iterator<T>& x) {
				vec_iterator<T> ret(x);
				ret.ptr += n;
				return ret;
			}
			friend vec_iterator<T> operator- (int n, vec_iterator<T>& x) {
				vec_iterator<T> ret(x);
				ret.ptr -= n;
				return ret;
			}
		private:
			T*	ptr;
	};

	// template <typename T>
	// vec_iterator<T> operator+ (int n, vec_iterator<T>& x) {
	// 	vec_iterator<T> ret(x);
	// 	ret.ptr += n;
	// 	return ret;
	// }

	// template <typename T>
	// vec_iterator<T> operator- (int n, vec_iterator<T>& x) {
	// 	vec_iterator<T> ret(x);
	// 	ret.ptr -= n;
	// 	return ret;
	// }

	// template <class T> class const_vec_iterator;
	// template <class T> const_vec_iterator<T> operator+ (int n, const_vec_iterator<T>& x);
	// template <class T> const_vec_iterator<T> operator- (int n, const_vec_iterator<T>& x);

	template <class T>
	class vec_const_iterator : public iterator<std::random_access_iterator_tag, T> {
		public:
			typedef const T			value_type;
			typedef const T*		pointer;
			typedef const T&		reference;

			typedef	ptrdiff_t		difference_type;

			vec_const_iterator() : ptr(0) {}
			vec_const_iterator(pointer _ptr) : ptr(_ptr) {}
			vec_const_iterator(const vec_const_iterator &x) : ptr(x.ptr) {}
			vec_const_iterator(const vec_iterator<T> &x) : ptr(&(*x)) {}
			~vec_const_iterator() {}
			vec_const_iterator& operator= (const vec_const_iterator& x) {
				ptr = x.ptr;
				return *this;
			}

			reference operator*() const { return *ptr; }

			pointer operator->() const { return ptr; }

			vec_const_iterator& operator++() {
				ptr++;
				return *this;
			}

			vec_const_iterator operator++(int) {
				vec_const_iterator ret(*this);
				ptr++;
				return ret;
			}

			vec_const_iterator& operator--() {
				ptr--;
				return *this;
			}

			vec_const_iterator operator--(int) {
				vec_const_iterator ret(*this);
				ptr--;
				return ret;
			}

			vec_const_iterator operator+ (difference_type n) const {
				vec_const_iterator ret(*this);
				ret.ptr += n;
				return ret;
			}

			vec_const_iterator operator- (difference_type n) const {
				vec_const_iterator ret(*this);
				ret.ptr -= n;
				return ret;
			}

			difference_type operator- (const vec_const_iterator& x) const {
				return ptr - x.ptr;
			}

			vec_const_iterator& operator+= (difference_type n) {
				ptr += n;
				return *this;
			}

			vec_const_iterator& operator-= (difference_type n) {
				ptr -= n;
				return *this;
			}

			reference operator[] (difference_type n) const {
				return *(ptr + n);
			}

			bool operator== (const vec_const_iterator& y) const { return ptr == y.ptr; }
			bool operator!= (const vec_const_iterator& y) const { return ptr != y.ptr; }
			bool operator< (const vec_const_iterator& y) const { return ptr < y.ptr; }
			bool operator<= (const vec_const_iterator& y) const { return ptr <= y.ptr; }
			bool operator> (const vec_const_iterator& y) const { return ptr > y.ptr; }
			bool operator>= (const vec_const_iterator& y) const { return ptr >= y.ptr; }

			friend vec_const_iterator<T> operator- (int n, vec_const_iterator<T>& x) {
				vec_const_iterator<T> ret(x);
				ret.ptr += n;
				return ret;
			}
			friend vec_const_iterator<T> operator+ (int n, vec_const_iterator<T>& x) {
				vec_const_iterator<T> ret(x);
				ret.ptr -= n;
				return ret;
			}
		private:
			pointer	ptr;
	};

	// template <class T>
	// vec_const_iterator<T> operator+ (int n, vec_const_iterator<T>& x) {
	// 	vec_const_iterator<T> ret(x);
	// 	ret.ptr += n;
	// 	return ret;
	// }

	// template <class T>
	// vec_const_iterator<T> operator- (int n, vec_const_iterator<T>& x) {
	// 	vec_const_iterator<T> ret(x);
	// 	ret.ptr -= n;
	// 	return ret;
	// }

	template <class T, class Allocator = std::allocator<T> >
	class vector {
		public:
			typedef T 												value_type;
			typedef Allocator 										allocator_type;
			typedef typename allocator_type::reference 				reference;
			typedef typename allocator_type::const_reference 		const_reference;
			typedef typename allocator_type::pointer 				pointer;
			typedef typename allocator_type::const_pointer 			const_pointer;
			typedef vec_iterator<value_type> 						iterator;
			typedef vec_const_iterator<value_type>					const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef ptrdiff_t 										difference_type;
			typedef std::size_t 									size_type;

			explicit vector (const allocator_type& alloc = allocator_type()) : _capacity(0), _size(0), _alloc(alloc), _start(0) {}
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _capacity(n), _size(n), _alloc(alloc) {
				T	*tmp;

				_start = _alloc.allocate(n);
				tmp = _start;
				for (size_t i = 0; i < n; i++)
					_alloc.construct(tmp++, val);
			}
			template <class InputIterator>
        	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			: _alloc(alloc) {
				_size = ft::distance(first, last);
				_capacity = _size;
				_start = _alloc.allocate(_size);
				size_type i = 0;
				while (first != last)
					_alloc.construct(_start + i++, *(first++));
			}
			vector(const vector & x) : _capacity(x.capacity()), _size(x.size()), _alloc(x.get_allocator()) {
				T	*tmp;

				if (_size > 0) {
					_start = _alloc.allocate(_capacity);
					tmp = _start;
					for (size_t i = 0; i < _size; i++)
						_alloc.construct(tmp++, x[i]);
				} else {
					_start = 0;
				}
			}

			//destructor
			~vector() {
				T *tmp;

				tmp = _start;
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(tmp++);
				_alloc.deallocate(_start, _capacity);
			}

			//operator =
			vector & operator = (const vector & v) {
				T *tmp;

				tmp = _start;
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(tmp++);
				_alloc.deallocate(_start, _capacity);

				_size = v.size();
				_capacity = _size;
				_start = _alloc.allocate(_size);
				tmp = _start;
				for (size_t i = 0; i < _size; i++)
				{
					_alloc.construct(tmp++, v[i]);
				}
				return *this;
			}

			//iterators
			//begin
			iterator begin() { return iterator(_start); }

			const_iterator begin() const { return const_iterator(_start); }

			iterator end() { return iterator(_start + _size); }

			const_iterator end() const { return const_iterator(_start + _size); }

			reverse_iterator rbegin() { return ft::reverse_iterator<iterator>(end()); }

			const_reverse_iterator rbegin() const { return ft::reverse_iterator<iterator>(end()); }

			reverse_iterator rend() { return ft::reverse_iterator<iterator>(begin()); }

			const_reverse_iterator rend() const { return ft::reverse_iterator<iterator>(begin()); }

			//capacity
			size_type size() const { return _size; }

			size_type max_size() const { return allocator_type().max_size(); }

			void resize (size_type n, value_type val = value_type()) {
				T			*tmp;
				size_type	i;

				while (n > _capacity)
					extend();
				if (n < _size)
				{
					i = n;
					tmp = _start;
					while (tmp + i < _start + _size) 
						_alloc.destroy(tmp + i++);
					_size = n;
				}
				if (n > _size)
				{
					i = _size;
					tmp = _start;
					while (tmp + i < _start + n)
						_alloc.construct(tmp + i++, val);
					_size = n;
				}
			}

			size_type capacity() const { return _capacity; }

			bool empty() const { return _size == 0; }

			void reserve (size_type n) {
				if (n > _capacity) {
					T* new_start = _alloc.allocate(n);
					for (size_t i = 0; i != _size; i++)
						_alloc.construct(new_start + i, _start[i]);
					for (size_t i = 0; i != _size; i++)
						_alloc.destroy(_start + i);
					_alloc.deallocate(_start, _capacity);
					_start = new_start;
					_capacity = n;
				}
			}

			//element access
			reference operator[] (size_type n) { return _start[n]; }

			const_reference operator[] (size_type n) const { return _start[n]; }

			reference at (size_type n) {
				if (n >= _size) { throw(std::out_of_range("at[n]: n is too big")); }
				return _start[n];
			}

			const_reference at (size_type n) const {
				if (n >= _size) { throw(std::out_of_range("at[n]: n is too big")); }
				return _start[n];
			}

			reference front() { return _start[0]; }

			const_reference front() const { return _start[0]; }

			reference back() { return _start[_size - 1]; }

			const_reference back() const { return _start[_size - 1]; }



			//modifiers
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(_start + i);
				size_t dist = ft::distance(first, last);
				if (dist > _capacity)
				{
					_alloc.deallocate(_start, _capacity);
					_start = _alloc.allocate(dist);
					_capacity = dist;
				}
				_size = dist;
				size_t i = 0;
				for(; first != last; first++)
					_alloc.construct(_start + i++, *first);
			}

			void assign (size_type n, const value_type& val) {
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(_start + i);
				if (n > _capacity)
				{
					_alloc.deallocate(_start, _capacity);
					_start = _alloc.allocate(n);
					_capacity = n;
				}
				_size = n;
				for(size_t i = 0; i != _size; i++)
					_alloc.construct(_start + i, val);
			}

			void push_back (const value_type& val) {
				if (_size + 1 > _capacity)
					extend();
				_alloc.construct(_start + _size, val);
				_size++;
			}

			void pop_back() {
				_alloc.destroy(_start + _size);
				_size--;
			}
			
			//if size + 1 > capacity
			//	_capacity *2
			//new_start = allocate(capacity)
			//reconstruire vector
			//detruire ancien vector
			iterator insert(iterator position, const value_type& val) {
				size_t new_capacity = _capacity;
				while (_size + 1 > new_capacity)
					new_capacity = 2 * new_capacity + (new_capacity == 0);
				T* new_start = _alloc.allocate(new_capacity);

				size_t i = 0;
				while (begin() + i != position)
				{
					_alloc.construct(new_start + i, _start[i]);
					i++;
				}
					
				_alloc.construct(new_start + i, val);

				iterator ret = iterator(new_start + i);

				while (i < _size)
				{
					_alloc.construct(new_start + i + 1, _start[i]);
					i++;
				}

				for (i = 0; i < _size; i++)
					_alloc.destroy(_start + i);
				_alloc.deallocate(_start, _capacity);

				_start = new_start;
				_capacity = new_capacity;
				_size++;

				return ret;
			}

			// iterator insert (iterator position, const value_type& val) {
			// 	size_t		i;
			// 	iterator	ret;
			// 	for (i = 0; _start + i != position; i++) {}
			// 	size_type pos_idx = i;
			// 	if (_size + 1 > _capacity)
			// 		extend();
			// 	T* new_start = _alloc.allocate(_size + 1);
			// 	for (i = 0; i != pos_idx; i++)
			// 		_alloc.construct(new_start + i, _start[i]);
			// 	_alloc.construct(new_start + i, val);
			// 	ret = new_start + i;
			// 	while (i <_size) {
			// 		_alloc.construct(new_start + i + 1, _start[i]);
			// 		i++;
			// 	}
			// 	for (i = 0; i < _size; i++)
			// 		_alloc.destroy(_start + i);
			// 	_alloc.deallocate(_start, _size);
			// 	_start = new_start;				
			// 	_size++;
			// 	return ret;
			// }

			void insert(iterator position, size_type n, const value_type& val) {
				size_t new_capacity = _capacity;
				while (_size + n > new_capacity)
					new_capacity = 2 * new_capacity + (new_capacity == 0);
				T* new_start = _alloc.allocate(new_capacity);

				size_t i = 0;
				while (begin() + i != position)
				{
					_alloc.construct(new_start + i, _start[i]);
					i++;
				}

				for (size_t j = 0; j < n; j++)
				{
					_alloc.construct(new_start + i + j, val);
				}

				while (i < _size)
				{
					_alloc.construct(new_start + i + n, _start[i]);
					i++;
				}

				for (i = 0; i < _size; i++)
					_alloc.destroy(_start + i);
				_alloc.deallocate(_start, _capacity);
				
				_start = new_start;
				_capacity = new_capacity;
				_size += n;
			}

			// void insert (iterator position, size_type n, const value_type& val) {
			// 	size_t	i, j;
			// 	for (i = 0; this->begin() + i != position; i++) {}
			// 	size_type pos_idx = i;
			// 	while (_size + n > _capacity)
			// 		extend();
			// 	T* new_start = _alloc.allocate(_size + n);
			// 	for (i = 0; i != pos_idx; i++)
			// 		_alloc.construct(new_start + i, _start[i]);
			// 	for (j = 0; j < n; j++)
			// 	{
			// 		_alloc.construct(new_start + i + j, val);
			// 	}
			// 	while (i < _size) {
			// 		_alloc.construct(new_start + i + n, _start[i]);
			// 		i++;
			// 	}
			// 	for (i = 0; i < _size; i++)
			// 		_alloc.destroy(_start + i);
			// 	_alloc.deallocate(_start, _size);
			// 	_start = new_start;
			// 	_size += n;
			// }

			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
				InputIterator tmp = first;
				difference_type n = 0;
				while (tmp != last)
				{
					n++;
					tmp++;
				}

				size_t new_capacity = _capacity;
				while (_size + n > new_capacity)
					new_capacity = 2 * new_capacity + (new_capacity == 0);
				T* new_start = _alloc.allocate(new_capacity);


				size_t i = 0;
				while (begin() + i != position)
				{
					_alloc.construct(new_start + i, _start[i]);
					i++;
				}

				difference_type j = 0;
				try 
				{
					while (j < n)
					{
						_alloc.construct(new_start + i + j, *first++);
						j++;
					}
				}
				catch(...)
				{
					size_t l = 0;
					while (l < i + j)
					{
						_alloc.destroy(new_start + l);
						l++;
					}
					_alloc.deallocate(new_start, new_capacity);
					throw;
				}
				
				while (i < _size)
				{
					_alloc.construct(new_start + i + n, _start[i]);
					i++;
				}

				for (i = 0; i < _size; i++)
					_alloc.destroy(_start + i);
				_alloc.deallocate(_start, _capacity);
				
				_start = new_start;
				_capacity = new_capacity;
				_size += n;
			}

			// template <class InputIterator>
    		// void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
			// 	size_type	i, j;
			// 	size_type n = 0;
			// 	for (i = 0; this->begin() + i != position; i++) {}
			// 	size_type pos_idx = i;
			// 	for (InputIterator it = first; it != last; it++) { n++; }
			// 	while (_size + n > _capacity)
			// 		extend();
			// 	T* new_start = _alloc.allocate(_size + n);
			// 	for (i = 0; i != pos_idx; i++)
			// 	{
			// 		_alloc.construct(new_start + i, _start[i]);
			// 	}
			// 	for (j = 0; j < n; j++)
			// 	{
			// 		_alloc.construct(new_start + i + j, *first++);
			// 	}
			// 	while (i < _size) {
			// 		_alloc.construct(new_start + i + n, _start[i]);
			// 		i++;
			// 	}
			// 	for (i = 0; i < _size; i++)
			// 		_alloc.destroy(_start + i);
			// 	_alloc.deallocate(_start, _size);
			// 	_start = new_start;
			// 	_size += n;
			// }

			void clear() {
				for (size_t i = 0; i < _size; i++)
				{
					_alloc.destroy(_start + i);
				}
				_size = 0;
			}

			iterator erase(iterator position) {
				size_t idx = position - begin();
				_alloc.destroy(&(*position));

				for (size_t i = idx; i < _size - 1; i++)
				{
					_alloc.construct(&(*(position + i - idx)), *(position + i - idx + 1));
					_alloc.destroy(&(*(position + i - idx + 1)));
					// *(position + i - idx) = *(position + i - idx + 1);
				}

				_alloc.destroy(&(*(position - idx + _size - 1)));
				_size--;

				return position;
			}

			iterator erase(iterator first, iterator last) {
				size_t idx_first = first - begin();
				size_t idx_last = last - begin();

				for (iterator it = first; it != last; it++)
					_alloc.destroy(&(*it));

				for (size_t i = idx_last; i < _size; i++)
				{
					_alloc.construct(&(*(first + i - idx_last)), *(last + i - idx_last));
					_alloc.destroy(&(*(last + i - idx_last)));
				}

				_size -= (idx_last - idx_first);

				return first;
			}

			// iterator erase (iterator first, iterator last) {
			// 	size_t i = 0;
			// 	size_t j = 0;

			// 	while (_start + i != first) { i++; }
				
			// 	while(_start + i + j != last) {
			// 		_alloc.destroy(_start + i + j);
			// 		j++;
			// 	}

			// 	iterator ret = _start + i;

			// 	while (i < _size - j) {
			// 		_alloc.construct(_start + i, _start[i + j]);
			// 		i++;
			// 	}

			// 	_size -= j;

			// 	return ret;
			// }

			void swap (vector& x) {
				// if (*this == x)
				// 	return;
				
				size_type		_size_tmp = this->_size;
				size_type		_capacity_tmp = this->_capacity;
				T*				_start_tmp = this->_start;	

				this->_size = x._size;
				this->_capacity = x._capacity;
				this->_start = x._start;
				
				x._size = _size_tmp;
				x._capacity = _capacity_tmp;
				x._start = _start_tmp;
			}

			//allocator
			allocator_type get_allocator() const { return allocator_type(_alloc); }
		private:
			size_type		_capacity;
			size_type		_size;
			allocator_type	_alloc;
			T*				_start;

			void	extend() {
				T	*new_start;
				T	*tmp;

				if (_capacity == 0)
				{
					_capacity = 1;
					_start = _alloc.allocate(1);
				} 
				else
				{
					new_start = _alloc.allocate(_capacity * 2);
					for (size_t i = 0; i < _size; i++)
						_alloc.construct(new_start + i, _start[i]);
					tmp = _start;
					for (size_t i = 0; i < _size; i++)
						_alloc.destroy(tmp++);
					_alloc.deallocate(_start, _capacity);
					_start = new_start;
					_capacity *= 2;				
				}
			}
	};

	template <class T, class Alloc>
  	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size()) return false;
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i]) return false;
		return true;
	}

	template <class T, class Alloc>
  	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size()) return true;
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i]) return true;
		return false;
	}

	template <class T, class Alloc>
  	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		size_t i = 0;
		while (i < lhs.size() && i < rhs.size()) {
			if (lhs[i] < rhs[i]) return true;
			if (lhs[i] > rhs[i]) return false;
			i++;
		}
		return lhs.size() < rhs.size();
	}

	template <class T, class Alloc>
  	bool operator<=  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		size_t i = 0;
		while (i < lhs.size() && i < rhs.size()) {
			if (lhs[i] < rhs[i]) return true;
			if (lhs[i] > rhs[i]) return false;
			i++;
		}
		return lhs.size() <= rhs.size();
	}

	template <class T, class Alloc>
  	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		size_t i = 0;
		while (i < lhs.size() && i < rhs.size()) {
			if (lhs[i] < rhs[i]) return false;
			if (lhs[i] > rhs[i]) return true;
			i++;
		}
		return lhs.size() > rhs.size();
	}

	template <class T, class Alloc>
  	bool operator>=  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		size_t i = 0;
		while (i < lhs.size() && i < rhs.size()) {
			if (lhs[i] < rhs[i]) return false;
			if (lhs[i] > rhs[i]) return true;
			i++;
		}
		return lhs.size() >= rhs.size();
	}
}

#endif

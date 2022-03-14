#pragma once
#include <iostream>
#include "utils.hpp"
#include "RBbst.hpp"

namespace ft {
	template <	class Key,												// map::key_type
				class T,												// map::mapped_type
				class Compare = std::less<Key>,							// map::key_compare
				class Alloc = std::allocator<ft::pair<const Key, T> > >	// map::allocator_type
	class map {
		public:
			typedef	Key													key_type;
			typedef T													mapped_type;
			typedef	ft::pair<const Key, T>								value_type;
			typedef	Compare												key_compare;
			typedef	Alloc												allocator_type;

			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef	typename allocator_type::pointer					pointer;
			typedef	typename allocator_type::const_pointer				const_pointer;

			typedef tree_iterator<value_type>							iterator;
			typedef tree_const_iterator<value_type>						const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

			typedef	ptrdiff_t											difference_type;
			typedef	std::size_t											size_type;

			class value_compare : std::binary_function<value_type, value_type, bool> {
				// in C++98, it is required to inherit binary_function<value_type,value_type,bool>
				protected:
					Compare comp;
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					value_compare(Compare c) : comp(c) {}
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

			explicit map (	const key_compare& _comp = key_compare(),
              				const allocator_type& _alloc = allocator_type())
				:	rb_bst(value_compare(_comp), _alloc),
					comp(_comp),
					alloc(_alloc) {}

			template <class InputIterator>
			map (	InputIterator first, InputIterator last,
					const key_compare& _comp = key_compare(),
					const allocator_type& _alloc = allocator_type())
				:	rb_bst(first, last, value_compare(_comp), _alloc),
					comp(_comp),
					alloc(_alloc) {}
			
			map (const map& x)
				:	rb_bst(x.rb_bst),
					comp(x.comp),
					alloc(x.alloc) {}

			~map() { this->clear(); }

			map& operator=(const map& m) {
				rb_bst = m.rb_bst;
				return *this;
			}

			iterator begin() { return bst.begin(); }
			iterator end() { return bst.end(); }

			const_iterator begin() const { return bst.begin(); }
			const_iterator end() const { return bst.end(); }

			reverse_iterator rbegin() { return bst.rbegin(); }
			reverse_iterator rend() { return bst.rend(); }

			const_reverse_iterator rbegin() const { return bst.rbegin(); }
			const_reverse_iterator rend() const { return bst.rend(); }

			bool empty() const { return size() == 0; }
			size_type size() const { return rb_bst.size(); }
			size_type max_size() const { return bst.max_size(); }

			mapped_type& operator[] (const key_type& k) {
				return (*((this->insert(make_pair(k,mapped_type()))).first)).second;
			}

			pair<iterator,bool> insert (const value_type& val) {
				return rb_bst.insert(val);
			}

			iterator insert (iterator position, const value_type& val) {
				return rb_bst.insert(val, position).first;
			}

			template <class InputIter>
			void insert(InputIter first, InputIter last) {
				for (InputIter it = first; it != last; it++) bst.insert(*it);
			}

			void erase (iterator position) { rb_bst.erase(position.as_node()); }
			size_type erase (const key_type& k) {
				return rb_bst.erase(ft::make_pair<const key_type, mapped_type> (k, mapped_type()));
			}
     		void erase (iterator first, iterator last) {
				 for (iterator it = first; it != last; ++it) rb_bst.erase(((--it)++).as_node());
			}

			void swap (map& x) { rb_bst.swap(x.rb_bst); }

			//can be hugely optimized if necessary
			void clear() { this->erase(begin(), end()); }

			key_compare key_comp() const { return comp; }
			value_compare	value_comp() const { return value_compare(comp); }

			iterator find (const key_type& k) {
				return rb_bst.find(ft::make_pair<const key_type, mapped_type> (k, mapped_type()));
			}
			const_iterator find (const key_type& k) const {
				return rb_bst.find(ft::make_pair<const key_type, mapped_type> (k, mapped_type()));
			}

			size_type count (const key_type& k) const {
				return (find(k) != end());
			}

			iterator lower_bound (const key_type& k);
			const_iterator lower_bound (const key_type& k) const;



}
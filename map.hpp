#pragma once
#include <iostream>
#include "utils.hpp"
#include "bst.hpp"

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
				:	bst(value_compare(_comp), _alloc),
					comp(_comp),
					alloc(_alloc) {}

			template <class InputIterator>
			map (	InputIterator first, InputIterator last,
					const key_compare& _comp = key_compare(),
					const allocator_type& _alloc = allocator_type())
				:	bst(value_compare(_comp), _alloc),
					comp(_comp),
					alloc(_alloc) { insert(first, last); }
			
			map (const map& x)
				:	bst(value_compare(x.comp), x.alloc),
					comp(x.comp),
					alloc(x.alloc) { insert(x.begin(), x.end()); }

			~map() { this->clear(); }

			iterator begin() { return bst.begin(); }
			iterator end() { return bst.end(); }

			const_iterator begin() const { return bst.begin(); }
			const_iterator end() const { return bst.end(); }

			size_type size() const { return bst.size(); }
			size_type max_size() const { return bst.max_size(); }

			ft::pair<iterator, bool> insert(const value_type& val) {
				ft::pair<iterator, bool> ret = bst.insert(val);
				return ret;
			}

			iterator insert(iterator position, const value_type& val) {
				ft::pair<iterator, bool> ret = bst.insert(val, position);
				return ret.first;
			}

			template <class InputIter>
			void insert(InputIter first, InputIter last) {
				for (InputIter it = first; it != last; it++) { bst.insert(*it); }
			}

			void clear() { this->erase(begin(), end()); }

			void erase(iterator first, iterator last) {
				iterator it_cur = first;
				iterator it_next = first;
				it_next++;
				while (it_cur != last)
				{
					this->erase(it_cur);
					it_cur = it_next;
					it_next++;
				}			
			}

			void erase(iterator position) {
				this->erase(position->first);
			}

			size_type erase(const key_type& k) {
				return bst.erase(ft::make_pair<const key_type, mapped_type> (k, mapped_type()));
			}

			iterator find(const key_type& k) { return bst.find(k); }
			const_iterator find(const key_type& k) const { return bst.find(k); }
		private:
			ft::BST<value_type, value_compare, allocator_type>	bst;
			key_compare											comp;
			allocator_type										alloc;
	};
}
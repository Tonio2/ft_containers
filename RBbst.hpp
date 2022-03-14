#pragma once

#include <iostream>

namespace ft {
	template <class T>
	struct Node {
		T		content;
		Node*	parent, left, right;
		bool	color; // 1 = red; 0 = black;

		Node() {
			std::cout << "empty node constructor\n";
		}

		Node(const T& value) {
			std::cout << "value node constructor\n";
		}

		Node(const Node& n) :
			content(n.content),
			parent(n.parent),
			left(n.left),
			right(n.right),
			color(n.color) {
				std::cout << "copy node constructor\n";
			}

		~Node() {
			std::cout << "node destructor\n";
		}

		Node& operator=(const Node& n) {
			content = n.content;
			parent = n.parent;
			left = n.left;
			right = n.right;
			std::cout << "node operator=()\n";
			return *this;
		}

		//Should I protect if this = 0 ??????
		Node* leftmost() {
			Node* ret = this;
			while(ret->left)
				ret = ret->left;
			return ret;
		}

		Node* rightmost() {
			Node* ret = this;
			while (ret->right)
				ret = ret->right;
			return ret;
		}

		Node* first_right_parent() {
			Node* ret = this;
			while (ret->parent && ret == ret->parent->right)
				ret = ret->parent;
			return ret->parent;
		}

		Node* first_left_parent() {
			Node* ret= this;
			while (ret->parent && ret == ret->parent->left)
				ret = ret->parent;
			return ret->parent;
		}
	};

	template <class T>
	class tree_iterator : public iterator<std::bidirectional_iterator_tag, T> {
		public:
			typedef	typename ft::node<value_type>	node_type;
			typedef	typename node_type&				node_reference;
			typedef	typename node_type*				node_pointer;

			tree_iterator() : n(0) { std::cout << "iterator empty constructor called\n"}
			tree_iterator(node_pointer _n) : n(_n) { std::cout << "iterator value constructor called\n"}
			tree_iterator(const tree_iterator& x) : n(x.n) { std::cout << "iterator copy constructor called\n"}
			~tree_iterator() { std::cout << "iterator destructor called\n"}
			tree_iterator& operator=(const tree_iterator& x) {
				n = x.n;
				std::cout << "iterator operator=() called\n";
				return *this;
			}

			reference operator*() const { return n->content; }

			pointer operator->() const { return &(n->content); }

			node_pointer as_node() const { return n; }

			tree_iterator& operator++() {
				if (n->right)
					n = n->right->leftmost();
				else
					n = n->first_right_parent();
				return *this;
			}

			tree_iterator& operator++(int) {
				tree_iterator& ret = *this;
				this->operator++();
				return ret;
			}

			tree_iterator& operator--() {
				if (n->left)
					n = n->left->rightmost();
				else
					n = n->first_left_parent();
				return *this;
			}

			tree_iterator& operator--(int) {
				tree_iterator& ret = *this;
				this->operator--();
				return ret;
			}

			bool operator==(const tree_iterator& y) { return n == y.n; }
			bool operator!=(const tree_iterator& y) { return n != y.n; }
		private:
			node_pointer 	n;
	};

	template <class T>
	class tree_const_iterator : public iterator<std::bidirectional_iterator_tag, T> {
		public:
			typedef	typename ft::node<value_type>	node_type;
			typedef	typename node_type&				node_reference;
			typedef	typename node_type*				node_pointer;

			tree_const_iterator() : n(0) { std::cout << "iterator empty constructor called\n"}
			tree_const_iterator(node_pointer _n) : n(_n) { std::cout << "iterator value constructor called\n"}
			tree_const_iterator(const tree_const_iterator& x) : n(x.n) { std::cout << "iterator copy constructor called\n"}
			~tree_const_iterator() { std::cout << "iterator destructor called\n"}
			tree_const_iterator& operator=(const tree_const_iterator& x) {
				n = x.n;
				std::cout << "iterator operator=() called\n";
				return *this;
			}

			reference operator*() const { return n->content; }

			pointer operator->() const { return &(n->content); }

			node_pointer as_node() const { return n; }

			tree_const_iterator& operator++() {
				if (n->right)
					n = n->right->leftmost();
				else
					n = n->first_right_parent();
				return *this;
			}

			tree_const_iterator& operator++(int) {
				tree_const_iterator& ret = *this;
				this->operator++();
				return ret;
			}

			tree_const_iterator& operator--() {
				if (n->left)
					n = n->left->rightmost();
				else
					n = n->first_left_parent();
				return *this;
			}

			tree_const_iterator& operator--(int) {
				tree_const_iterator& ret = *this;
				this->operator--();
				return ret;
			}

			bool operator==(const tree_const_iterator& y) { return n == y.n; }
			bool operator!=(const tree_const_iterator& y) { return n != y.n; }
		private:
			node_pointer 	n;
	};

	template <	class T,
				class Comp = std::less<T>,
				class Type_Alloc = std::allocator<T> >
	class RBbst {
		public:
			typedef	T														value_type;
			typedef	Type_Alloc												alloc_type;
			typedef	T*														pointer;
			typedef T&														reference;

			typedef ft::node<T>												node_type;
			typedef	typename Type_Alloc::template rebind<node_type>::other	node_alloc_type;
			typedef	node_type*												node_pointer;
			typedef	node_type&												node_reference;

			typedef tree_iterator<value_type>								iterator;
			typedef tree_const_iterator<value_type>							const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

			typedef	ptrdiff_t												difference_type;
			typedef	std::size_t												size_type;

			RBbst() 
		private:
			node_pointer	root;
			Comp			comp;
			node_alloc_type	node_alloc;
			size_type		_size;
}
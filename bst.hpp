#pragma once
#include <iostream>
#include "utils.hpp"

namespace ft {
	template <class T>
	struct node {
		T		content;
		node*	parent;
		node*	left;
		node*	right;

		node()
			:	content(T()),
				parent(0),
				left(0),
				right(0) {}
		
		node(const T& value)
			:	content(value),
				parent(0),
				left(0),
				right(0) {}
		
		node(const node& x)
			:	content(x.content),
				parent(x.parent),
				left(x.left),
				right(x.right) {}
		
		~node() {}

		node& operator=(const node& x) {
			if (content == x.content)
				return *this;
			
			content = x.content;
			return *this;
		}

		node* leftmost() {
			node* ret = this;
			while(ret->left)
				ret = ret->left;
			return ret;
		}

		node* rightmost() {
			node* ret = this;
			while (ret->right)
				ret = ret->right;
			return ret;
		}

		node* first_right_parent() {
			node* ret = this;
			while (ret->parent && ret == ret->parent->right)
				ret = ret->parent;
			return ret->parent;
		}

		node* first_left_parent() {
			node* ret= this;
			while (ret->parent && ret == ret->parent->left)
				ret = ret->parent;
			return ret->parent;
		}
	};

	template <class T>
	class tree_iterator {
		public:
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef ptrdiff_t						difference_type;

			typedef	T								value_type;
			typedef	T*								pointer;
			typedef T&								reference;

			typedef	ft::node<T>						node_type;
			typedef	node_type*						node_pointer;
			typedef	node_type&						node_reference;

			tree_iterator() : n(0), last(0) {}
			tree_iterator(node_pointer _n, node_pointer _last) : n(_n), last(_last) {}
			tree_iterator(const tree_iterator& x) : n(x.n), last(x.last) {}
			tree_iterator& operator=(const tree_iterator& x)
			{
				n = x.n;
				return *this;
			}
			~tree_iterator() {}

			node_pointer as_node() { return n; }

			reference operator*() const { return n->content; }

			pointer operator->() const { return &(n->content); }

			tree_iterator& operator++() {
				if (last->right == n)
					n = last;
				else if (n->right)
					n = n->right->leftmost();
				else
					n = n->first_right_parent();
				return *this;
			}

			tree_iterator& operator++(int) {
				tree_iterator& ret = *this;
				if (last->right == n)
					n = last;
				else if (n->right)
					n = n->right->leftmost();
				else
					n = n->first_right_parent();
				return ret;
			}

			tree_iterator& operator--() {
				if (n == last)
					n = n->right;
				else if (n->left)
					n = n->left->rightmost();
				else
					n = n->first_left_parent();
				return *this;
			}

			tree_iterator& operator--(int) {
				tree_iterator& ret = *this;
				if (n == last)
					n = n->right;
				else if (n->left)
					n = n->left->rightmost();
				else
					n = n->first_left_parent();
				return ret;
			}

			bool operator==(const tree_iterator& y) { return n == y.n; }
			bool operator!=(const tree_iterator& y) { return n != y.n; }

		private:
			node_pointer 	n;
			node_pointer	last;
	};

	template <	class T,
				class Node = ft::node<T> >
	class tree_const_iterator {
		public:
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef ptrdiff_t						difference_type;

			typedef	T								value_type;
			typedef	T*								pointer;
			typedef T&								reference;

			typedef	Node							node_type;
			typedef	Node*							node_pointer;
			typedef	Node&							node_reference;

			tree_const_iterator() : n(0), last(0) {}
			tree_const_iterator(node_pointer _n, node_pointer _last) : n(_n), last(_last) {}
			tree_const_iterator(const tree_const_iterator& x) : n(x.n), last(x.last) {}
			tree_const_iterator& operator=(const tree_const_iterator& x)
			{
				n = x.n;
				return *this;
			}
			~tree_const_iterator() {}

			node_pointer as_node() { return n; }

			reference operator*() const { return n->content; }

			pointer operator->() const { return &(n->content); }

			tree_const_iterator& operator++() {
				if (last->right == n)
					n = last;
				else if (n->right)
					n = n->right->leftmost();
				else
					n = n->first_right_parent();
				return *this;
			}

			tree_const_iterator& operator++(int) {
				tree_const_iterator& ret = *this;
				if (last->right == n)
					n = last;
				else if (n->right)
					n = n->right->leftmost();
				else
					n = n->first_right_parent();
				return ret;
			}

			tree_const_iterator& operator--() {
				if (n == last)
					n = n->right;
				else if (n->left)
					n = n->left->rightmost();
				else
					n = n->first_left_parent();
				return *this;
			}

			tree_const_iterator& operator--(int) {
				tree_const_iterator& ret = *this;
				if (n == last)
					n = n->right;
				else if (n->left)
					n = n->left->rightmost();
				else
					n = n->first_left_parent();
				return ret;
			}

			bool operator==(const tree_const_iterator& y) { return n == y.n; }
			bool operator!=(const tree_const_iterator& y) { return n != y.n; }

		private:
			node_pointer 	n;
			node_pointer	last;
	};

	template <	class T,
				class Comp = std::less<T>,
				class Type_Alloc = std::allocator<T> >
	class BST {
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

			typedef	ptrdiff_t												difference_type;
			typedef	std::size_t												size_type;
			
			BST(Comp comp_init = Comp(), Type_Alloc alloc_init = alloc_type()) :
				comp(comp_init),
				node_alloc(node_alloc_type(alloc_init)),
				_size(0) {
					last = node_alloc.allocate(1);
					node_alloc.construct(last, node_type());
				}
			
			~BST() {
				iterator cur = begin();
				iterator prev = cur;

				while ( cur != end())
				{
					cur++;
					node_alloc.destroy(prev.as_node());
					node_alloc.deallocate(prev.as_node(), 1);
					prev = cur;
				}

				node_alloc.destroy(last);
				node_alloc.deallocate(last, 1);
			}

			iterator begin() {
				if (_size == 0)
					return iterator(last, last);
				iterator it(last->left, last);
				return it;
			}

			const_iterator begin() const {
				if (_size == 0)
					return const_iterator(last, last);
				const_iterator it(last->left, last);
				return it;
			}

			iterator end() {
				iterator ite(last, last);
				return ite;
			}

			const_iterator end() const {
				const_iterator ite(last, last);
				return ite;
			}

			size_type size() const { return _size; }
			size_type max_size() const { return node_alloc.max_size() - 1; }
			
			ft::pair<iterator, bool>	insert(const value_type& val, iterator position = iterator()) {
				node_type		new_node(val);

				if (!last->parent)
				{
					last->parent = node_alloc.allocate(1);
					node_alloc.construct(last->parent, new_node);
					last->left = last->parent;
					last->right = last->parent;
					_size++;
					return ft::make_pair<iterator, bool> (iterator(last->parent, last), true);
				}
				
				if (comp(val, last->left->content))
				{
					node_pointer tmp = last->left;
					last->left = node_alloc.allocate(1);
					new_node.parent = tmp;
					node_alloc.construct(last->left, new_node);
					tmp->left = last->left;
					_size++;
					return ft::make_pair<iterator, bool> (iterator(last->left, last), true);
				}

				if (comp(last->right->content, val))
				{
					node_pointer tmp = last->right;
					last->right = node_alloc.allocate(1);
					new_node.parent = tmp;
					node_alloc.construct(last->right, new_node);
					tmp->right = last->right;
					_size++;
					return ft::make_pair<iterator, bool> (iterator(last->right, last), true);
				}

				node_pointer	prev;
				node_pointer	cur;
				if (position.as_node())
					cur = position.as_node();
				else
					cur = last->parent;
				bool			side;	// side == false -> left / side == true -> right

				while (cur)
				{
					prev = cur;
					if (comp(val, cur->content))
					{
						cur = cur->left;
						side = false;
					}
					else if (comp(cur->content, val))
					{
						cur = cur->right;
						side = true;
					}
					else
						return ft::make_pair<iterator, bool> (iterator(cur, last), false);
				}
				cur = node_alloc.allocate(1);
				new_node.parent = prev;
				node_alloc.construct(cur, new_node);
				if (side)
					prev->right = cur;
				else
					prev->left = cur;
				_size++;
				return ft::make_pair<iterator, bool> (iterator(cur, last), true);
			}

			// size_type erase(const value_type& k) {
			// 	node_pointer to_remove = find(k).as_node();
			// 	if (!to_remove)
			// 		return 0;

			// 	node_pointer tmp_parent, tmp_left, tmp_right;
			// 	tmp_parent = to_remove->parent;
			// 	tmp_left = to_remove->left;
			// 	tmp_right = to_remove->right;

			// 	node_pointer replace_with = 0;
			// 	if (tmp_right)
			// 		replace_with = tmp_right->leftmost();
			// 	else if (tmp_left)
			// 		replace_with = tmp_left->rightmost();
			// 	if (!replace_with)
			// 	{
			// 		if (last->left == to_remove)
			// 		{
			// 			last->left = tmp_parent;
			// 			tmp_parent->left =
			// 		}
						
			// 		if (last->right == to_remove)
			// 			last->right = tmp_parent;
			// 		if (last->parent == to_remove)
			// 			last->parent = tmp_parent;
			// 	}
			// 	else
			// 	{
			// 		node_pointer tmp_parent2 = replace_with->parent;
			// 		node_pointer tmp_right2 = replace_with->right;
			// 		node_pointer tmp_left2 = replace_with->left;

			// 		if (!tmp_parent)
			// 			last->parent = replace_with;
			// 		else if (to_remove == tmp_parent->left)
			// 			tmp_parent->left = replace_with;
			// 		else if (to_remove == tmp_parent->right)
			// 			tmp_parent->right = replace_with;
					
			// 		replace_with->left = tmp_left;
			// 		if (replace_with->left == replace_with)
			// 			replace_with->left = tmp_left2;
			// 		replace_with->right = tmp_right;
			// 		if (replace_with->right == replace_with)
			// 			replace_with->right = tmp_right2;
			// 		replace_with->parent = tmp_parent;

			// 		tmp_parent2->left = tmp_left2;
			// 		tmp_parent2->right = tmp_right2;
			// 	}
			// 	node_alloc.destroy(to_remove);
			// 	node_alloc.deallocate(to_remove, 1);
			// 	_size--;
			// 	return 1;
			// }

			size_type erase(const value_type& k) {
				node_pointer to_remove = find(k).as_node();
				if (!to_remove)
					return 0;
				node_pointer tmp_parent, tmp_left, tmp_right;
				tmp_parent = to_remove->parent;
				tmp_left = to_remove->left;
				tmp_right = to_remove->right;

				node_pointer replacement_node = 0;
				if (tmp_right)
					replacement_node = tmp_right->leftmost();
				else if (tmp_left)
					replacement_node = tmp_left->rightmost();
				
				if (to_remove == last->parent)
					last->parent = replacement_node;

				if (to_remove == last->left)
					last->left = replacement_node;
				
				if (to_remove == last->right)
					last->right = replacement_node;

				//if not root
				if (to_remove->parent)
				{
					if (to_remove->parent->right == to_remove)
						to_remove->parent->right = replacement_node;
					if (to_remove->parent->left == to_remove)
						to_remove->parent->left = replacement_node;
				}

				if (replacement_node)
				{
					node_pointer tmp_parent2, tmp_left2, tmp_right2;
					tmp_parent2 = replacement_node->parent;
					tmp_left2 = replacement_node->left;
					tmp_right2 = replacement_node->right;
					replacement_node->parent = to_remove->parent;
					if (tmp_parent2 != to_remove)
					{
						replacement_node->right = tmp_right;
						replacement_node->left = tmp_left;
						if (tmp_right)
							tmp_right->parent = replacement_node;
						if (tmp_left)
							tmp_left->parent = replacement_node;
						
						node_pointer child = 0;
						if (tmp_right2)
							child = tmp_right2;
						if (tmp_left2)
							child = tmp_left2;
						
						if (child)
							child->parent = tmp_parent2;
						
						if (tmp_parent2->left == replacement_node)
							tmp_parent2->left = child;
						else if (tmp_parent2->right == replacement_node)
							tmp_parent2->right = child;						
					}
				}

				node_alloc.destroy(to_remove);
				node_alloc.deallocate(to_remove, 1);
				_size--;
				return 1;
			}

			iterator find(const value_type& k) {
				node_pointer cur = last->parent;

				while (cur)
				{
					if (comp(k, cur->content))
						cur = cur->left;
					else if (comp(cur->content, k))
						cur = cur->right;
					else
					{
						iterator it(cur, last);
						return it;
					}
				}
				return end();
			}

			void ft_print_node(node_pointer n) {
				std::cout << " value: " << n->content.first;
				if (n->left)
					std::cout << " | left : " << n->left->content.first;
				else
					std::cout << " | left : X";
				if (n->right)
					std::cout << " | right : " << n->right->content.first;
				else
					std::cout << " | right : X";
				std::cout << "\n";
			}

			void ft_print(node_pointer n) {
				if (!n)
					n = last->parent;
				ft_print_node(n);
				if (n->left)
					ft_print(n->left);
				if (n->right)
					ft_print(n->right);
			}

		private:
			node_pointer		last;
			Comp				comp;
			node_alloc_type		node_alloc;
			size_type			_size;
	};
}
#pragma once
#include <iostream>

namespace ft {
	template <class T>
	struct Node {
		T		content;
		Node*	parent;
		Node*	left;
		Node*	right;
		int		color; // 1 = red; 0 = black; -1 = double black

		Node()	:	content(T()),
					parent(0),
					left(0),
					right(0),
					color(1)
		{
			// std::cout << "empty node constructor\n";
		}

		Node(const T& value)	:	content(value),
									parent(0),
									left(0),
									right(0),
									color(1)
		{
			// std::cout << "value node constructor\n";
		}

		Node(const Node& n) :
			content(n.content),
			parent(n.parent),
			left(n.left),
			right(n.right),
			color(n.color) {
				// std::cout << "copy node constructor\n";
			}

		~Node() {
			// std::cout << "node destructor\n";
		}

		Node& operator=(const Node& n) {
			content = n.content;
			parent = n.parent;
			left = n.left;
			right = n.right;
			// std::cout << "node operator=()\n";
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

		Node* rotateLeft()
		{
			Node* x = this->right;
			Node* y = x->left;
			x->left = this;
			this->right = y;
			this->parent = x;
			if(y)
				y->parent = this;
			return(x);
		}

		Node* rotateRight()
		{
			Node* x = this->left;
			Node* y = x->right;
			x->right = this;
			this->left = y;
			this->parent = x;
			if(y)
				y->parent = this;
			return(x);
		}
	};

	template <class T>
	class tree_const_iterator;

	template <class T>
	class tree_set_iterator : public iterator<std::bidirectional_iterator_tag, T> {
		public:
			typedef	T								value_type;
			typedef	T*								pointer;
			typedef T&								reference;

			typedef	typename ft::Node<T>	node_type;
			typedef node_type&				node_reference;
			typedef node_type*				node_pointer;

			tree_set_iterator() : n(0) {}
			tree_set_iterator(node_pointer _n) : n(_n) {}
			tree_set_iterator(const tree_set_iterator& x) : n(x.n) {}
			tree_set_iterator(const tree_const_iterator<T>& x) : n(x.as_node()) {}
			~tree_set_iterator() {}
			tree_set_iterator& operator=(const tree_set_iterator& x) {
				n = x.n;
				return *this;
			}

			reference operator*() const { return n->content; }

			pointer operator->() const { return &(n->content); }

			node_pointer as_node() const { return n; }

			tree_set_iterator& operator++() {
				if (n->right)
					n = n->right->leftmost();
				else
					n = n->first_right_parent();
				return *this;
			}

			tree_set_iterator operator++(int) {
				tree_set_iterator ret(*this);
				if (n->right)
					n = n->right->leftmost();
				else
					n = n->first_right_parent();
				return ret;
			}

			tree_set_iterator& operator--() {
				if (n->left)
					n = n->left->rightmost();
				else
					n = n->first_left_parent();
				return *this;
			}

			tree_set_iterator operator--(int) {
				tree_set_iterator ret(*this);
				if (n->left)
					n = n->left->rightmost();
				else
					n = n->first_left_parent();
				return ret;
			}

			bool operator==(const tree_set_iterator& y) const { return n == y.n; }
			bool operator!=(const tree_set_iterator& y) const { return n != y.n; }
		private:
			node_pointer 	n;
	};

	template <class T>
	class tree_iterator : public iterator<std::bidirectional_iterator_tag, T> {
		public:
			typedef	T								value_type;
			typedef	T*								pointer;
			typedef T&								reference;

			typedef	typename ft::Node<T>	node_type;
			typedef node_type&				node_reference;
			typedef node_type*				node_pointer;

			tree_iterator() : n(0) {}
			tree_iterator(node_pointer _n) : n(_n) {}
			tree_iterator(const tree_iterator& x) : n(x.n) {}
			~tree_iterator() {}
			tree_iterator& operator=(const tree_iterator& x) {
				n = x.n;
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

			tree_iterator operator++(int) {
				tree_iterator ret(*this);
				if (n->right)
					n = n->right->leftmost();
				else
					n = n->first_right_parent();
				return ret;
			}

			tree_iterator& operator--() {
				if (n->left)
					n = n->left->rightmost();
				else
					n = n->first_left_parent();
				return *this;
			}

			tree_iterator operator--(int) {
				tree_iterator ret(*this);
				if (n->left)
					n = n->left->rightmost();
				else
					n = n->first_left_parent();
				return ret;
			}

			bool operator==(const tree_iterator& y) const { return n == y.n; }
			bool operator!=(const tree_iterator& y) const { return n != y.n; }
		private:
			node_pointer 	n;
	};

	template <class T>
	class tree_const_iterator : public iterator<std::bidirectional_iterator_tag, T> {
		public:
			typedef	const T								value_type;
			typedef	const T*								pointer;
			typedef const T&								reference;

			typedef	typename ft::Node<T>	node_type;
			typedef node_type&				node_reference;
			typedef node_type*				node_pointer;

			tree_const_iterator() : n(0) {}
			tree_const_iterator(node_pointer _n) : n(_n) {}
			tree_const_iterator(const tree_const_iterator& x) : n(x.n) {}
			tree_const_iterator(const tree_iterator<T>& x) : n(x.as_node()) {}
			tree_const_iterator(const tree_set_iterator<T>& x) : n(x.as_node()) {}
			~tree_const_iterator() {}
			tree_const_iterator& operator=(const tree_const_iterator& x) {
				n = x.n;
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

			tree_const_iterator operator++(int) {
				tree_const_iterator ret(*this);
				if (n->right)
					n = n->right->leftmost();
				else
					n = n->first_right_parent();
				return ret;
			}

			tree_const_iterator& operator--() {
				if (n->left)
					n = n->left->rightmost();
				else
					n = n->first_left_parent();
				return *this;
			}

			tree_const_iterator operator--(int) {
				tree_const_iterator ret(*this);
				if (n->left)
					n = n->left->rightmost();
				else
					n = n->first_left_parent();
				return ret;
			}

			bool operator==(const tree_const_iterator& y) const { return n == y.n; }
			bool operator!=(const tree_const_iterator& y) const { return n != y.n; }
		private:
			node_pointer 	n;
	};

	template <	class T,
				class Comp = std::less<T>,
				class Type_Alloc = std::allocator<T>,
				class IT = tree_iterator<T> >
	class RBbst {
		public:
			typedef	T														value_type;
			typedef	Type_Alloc												alloc_type;
			typedef	T*														pointer;
			typedef T&														reference;

			typedef ft::Node<T>												node_type;
			typedef	typename Type_Alloc::template rebind<node_type>::other	node_alloc_type;
			typedef	node_type*												node_pointer;
			typedef	node_type&												node_reference;

			typedef IT														iterator;
			typedef tree_const_iterator<value_type>							const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

			typedef	ptrdiff_t												difference_type;
			typedef	std::size_t												size_type;

			explicit RBbst(Comp _comp = Comp())
				:	comp(_comp),
					node_alloc(),
					_size(0) {
						root = node_alloc.allocate(1);
						node_type new_node;
						node_alloc.construct(root, new_node);
					}

			RBbst(iterator first, iterator last, Comp _comp = Comp())
				:	comp(_comp),
					node_alloc(),
					_size(0) {
						root = node_alloc.allocate(1);
						node_type new_node;
						node_alloc.construct(root, new_node);
						for (iterator it = first; it != last; it++)
							insert(*it);
					}
			
			RBbst(const RBbst& x)
				:	comp(x.comp),
					node_alloc(x.node_alloc),
					_size(0) {
						root = node_alloc.allocate(1);
						node_type new_node;
						node_alloc.construct(root, new_node);
						const_iterator itb = x.begin();
						const_iterator ite = x.end();
						for (const_iterator it = itb; it != ite; it++)
							insert(*it);
					}
			
			~RBbst() {
				help_clear(root);
			}
			
			RBbst& operator= (const RBbst& x) {
				comp = x.comp;
				node_alloc = x.node_alloc;
				while (_size)
				{
					erase(begin().as_node());
				}
				const_iterator itb = x.begin();
				const_iterator ite = x.end();
				for (const_iterator it = itb; it != ite; it++)
					insert(*it);
				return *this;
			}

			void help_clear(node_pointer n) {
				if (n->left)
				{
					help_clear(n->left);
					n->left = 0;
				}
				if (n->right)
				{
					help_clear(n->right);
					n->right = 0;	
				}
				node_alloc.destroy(n);
				node_alloc.deallocate(n, 1);
			}

			void clear() {
				if (root->left)
					help_clear(root->left);
				root->left = 0;
				_size = 0;
			}

			iterator begin() {
				if (_size == 0)
					return iterator(root);
				return iterator(root->left->leftmost());
			}

			iterator end() {
				return iterator(root);
			}

			const_iterator begin() const {
				if (_size == 0)
					return const_iterator(root);
				return const_iterator(root->left->leftmost());
			}

			const_iterator end() const {
				return const_iterator(root);
			}
			
			ft::pair<iterator,bool> insert(const value_type& val) {
				ft::pair<iterator,bool>		ret;
				node_type					new_node(val);
				node_pointer				cur = root->left;
				node_pointer				prev = root;
				bool						side = false;	// side == false -> left / side == true -> right
				
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
						return ft::make_pair<iterator, bool> (iterator(cur), false);
				}

				cur = node_alloc.allocate(1);
				new_node.parent = prev;
				node_alloc.construct(cur, new_node);
				if (side)
					prev->right = cur;
				else
					prev->left = cur;
				_size++;
				ret = ft::make_pair<iterator, bool> (iterator(cur), true);

				bool balanced = false;
				node_pointer	uncle;
				while (!balanced)
				{
					if (cur == root->left)
					{
						cur->color = 0;
						balanced = true;
					}
					else
					{
						if (cur->parent->color == 1)
						{
							if (cur->parent == cur->parent->parent->left)
								uncle = cur->parent->parent->right;
							else
								uncle = cur->parent->parent->left;
							
							if (uncle && uncle->color == 1)
							{
								uncle->color = 0;
								cur->parent->color = 0;
								cur->parent->parent->color = 1;
								cur = cur->parent->parent;
							}
							else
							{
								node_pointer G = cur->parent->parent;
								node_pointer GG = G->parent;
								side = false;
								if (G == G->parent->right)
									side = true;
								if (cur->parent == cur->parent->parent->left)
								{
									if (cur == cur->parent->left)
									{
										G = G->rotateRight();
										G->color = 0;
										G->right->color = 1;
									}
									else
									{
										G->left = G->left->rotateLeft();
										G->left->parent = G;
										G = G->rotateRight();
										G->color = 0;
										G->right->color = 1;
									}
								}
								else
								{
									if (cur == cur->parent->right)
									{
										G = G->rotateLeft();
										G->color = 0;
										G->left->color = 1;
									}
									else
									{
										G->right = G->right->rotateRight();
										G->right->parent = G;
										G = G->rotateLeft();
										G->color = 0;
										G->left->color = 1;
									}
								}
								G->parent = GG;
								if (side)
									GG->right = G;
								else
									GG->left = G;

								balanced = 1;
							}
						}
						else
							balanced = 1;
					}
				}

				if (root->right)
					std::cout << "Hello\n";
				return ret;
			}
			
			//detache le noeud pos
			//attache son enfant si existe
			//retourne l'enfant
			//position est un noeud mono enfant
			node_pointer help_erase(node_pointer position) {
				node_pointer	child;
				if (!position->right && !position->left)
				{
					if (position == position->parent->left)
						position->parent->left = 0;
					else
						position->parent->right = 0;
					return 0;
				}
				else
				{
					if (position->left)
						child = position->left;
					else
						child = position->right;
					if (position == position->parent->left)
						position->parent->left = child;
					else
						position->parent->right = child;
					child->parent = position->parent;
					return child;
				}
			}

			size_type erase(value_type val) {
				iterator ite = end();
				iterator itk = find(val);
				if (itk == ite)
					return 0;
				erase(itk.as_node());
				return 1;
			}

			void erase(node_pointer v) {
				node_pointer	u;
				bool			v_color = v->color;
				node_pointer	p;
				node_pointer	s;

				//Si v est une feuille ou un noeud mono enfant
				if (!v->right || !v->left)
				{
					u = help_erase(v);
					p = v->parent;
					s = get_sibling(u, p);
					node_alloc.destroy(v);
					node_alloc.deallocate(v, 1);
				}
				else
				{
					//Si 2 enfants, remplacer v par son successeur puis erase le successeur
					iterator it(v);
					node_pointer successor = (++it).as_node();
					u = help_erase(successor);
					if (v == v->parent->left)
						v->parent->left = successor;
					else
						v->parent->right = successor;
					if (successor->parent == v)
					{
						p = successor;
					}
					else
					{
						p = successor->parent;
					}
					successor->left = v->left;
					successor->right = v->right;
					successor->color = v->color;
					successor->parent = v->parent;
					if (v->left)
						v->left->parent = successor;
					if (v->right)
						v->right->parent = successor;
					s = get_sibling(u, p);
					node_alloc.destroy(v);
					node_alloc.deallocate(v, 1);
				}

				if (v_color || (u && u->color))
				{
					if (u)
						u->color = 0;
				}
				else
				{
					handleDoubleBlack(u,p,s);
				}

				_size--;
				if (root->right)
					std::cout << "Hello\n";
			}

			iterator find(value_type val) {
				iterator ite = end();
				if (_size == 0)
					return ite;
				bool not_found = true;
				node_pointer cur = root->left;
				while(not_found && cur)
				{
					if (comp(val, cur->content))
						cur = cur->left;
					else if (comp(cur->content, val))
						cur = cur->right;
					else
						not_found = false;
				}
				if (cur)
					return iterator(cur);
				return ite;
			}

			const_iterator find(value_type val) const {
				const_iterator ite = end();
				if (_size == 0)
					return ite;
				bool not_found = true;
				node_pointer cur = root->left;
				while(not_found && cur)
				{
					if (comp(val, cur->content))
						cur = cur->left;
					else if (comp(cur->content, val))
						cur = cur->right;
					else
						not_found = false;
				}
				if (cur)
					return const_iterator(cur);
				return ite;
			}

			size_type size() const { return _size; }

			iterator lower_bound(const value_type& val) {
				iterator it_cur = begin();
				iterator ite = end();
				while (comp(it_cur.as_node()->content, val) && it_cur != ite)
					it_cur++;
				return it_cur;
			}

			const_iterator lower_bound(const value_type& val) const {
				const_iterator it_cur = begin();
				const_iterator ite = end();
				while (comp(it_cur.as_node()->content, val) && it_cur != ite)
					it_cur++;
				return it_cur;
			}

			iterator upper_bound(const value_type& val) {
				iterator it_cur = begin();
				iterator ite = end();
				while (!comp(val, it_cur.as_node()->content) && it_cur != ite)
					it_cur++;
				return it_cur;
			}

			const_iterator upper_bound(const value_type& val) const {
				const_iterator it_cur = begin();
				const_iterator ite = end();
				while (!comp(val, it_cur.as_node()->content) && it_cur != ite)
					it_cur++;
				return it_cur;
			}

			void swap(RBbst & x) {
				size_type size_tmp = _size;
				node_pointer root_tmp = root;
				_size = x._size;
				root = x.root;
				x._size = size_tmp;
				x.root = root_tmp;
			}

			size_type max_size() const {
				return (node_alloc.max_size());
			}

		private:
			node_pointer	root;
			Comp			comp;
			node_alloc_type	node_alloc;
			size_type		_size;

			int	get_color(node_pointer n) {
				if (!n)
					return 0;
				return n->color;
			}

			node_pointer get_sibling(node_pointer child, node_pointer parent) {
				if (child == parent->left)
					return parent->right;
				return parent->left;
			}

			void move_down(node_pointer p, node_pointer s)
			{
				if (p == p->parent->left)
					p->parent->left = s;
				else
					p->parent->right = s;
				s->parent = p->parent;
				p->parent = s;
			}

			void lRotate_d(node_pointer p)
			{
				node_pointer p2 = p->right;

				// if (p == root->left)
				// 	root->left = p2;
				
				move_down(p, p2);

				p->right = p2->left;

				if (p2->left != NULL)
					p2->left->parent = p;
				
				p2->left = p;
			}

			void rRotate_d(node_pointer p)
			{
				node_pointer p2 = p->left;

				// if (p == root->left)
				// 	root->left = p2;
				
				move_down(p, p2);

				p->left = p2->right;

				if (p2->right != NULL)
					p2->right->parent = p;
				
				p2->right = p;
			}

			void handleDoubleBlack(node_pointer u, node_pointer p, node_pointer s) {
				//node is root
				if (u == root->left)
					return;
				//no sibling
				if (s == 0)
				{
					if (p->color)
					{
						p->color = 0;
						return;
					}
					node_pointer u2 = p;
					node_pointer p2 = p->parent;
					node_pointer s2 = get_sibling(p, p2);
					handleDoubleBlack(u2, p2, s2);
				}
				else if (s->color == 0 && (get_color(s->left) || get_color(s->right)))
				{
					//sibling is black and at least one child is red
					node_pointer r;
					if (get_color(s->left))
						r = s->left;
					else
						r = s->right;
					if (s == p->left)
					{
						if (r == s->left)
						{
							s->left->color = s->color;
							s->color = p->color;
							rRotate_d(p);
						}
						else
						{
							s->right->color = p->color;
							lRotate_d(s);
							rRotate_d(p);
						}
					}
					else
					{
						if (r == s->right)
						{
							s->right->color = s->color;
							s->color = p->color;
							lRotate_d(p);
						}
						else
						{
							s->left->color = p->color;
							rRotate_d(s);
							lRotate_d(p);
						}
					}
					p->color = 0;
				} // sibling and both its children are black
				else if (s->color == 0 && get_color(s->left) == 0 && get_color(s->right) == 0)
				{
					s->color = 1;
					if (p->color)
						p->color = 0;
					else
					{
						node_pointer u2 = p;
						node_pointer p2 = p->parent;
						node_pointer s2 = get_sibling(p, p2);
						handleDoubleBlack(u2, p2, s2);
					}
				} // sibling is red
				else
				{
					p->color = 1;
					s->color = 0;
					if (s == p->right)
						lRotate_d(p);
					else
						rRotate_d(p);
					s = get_sibling(u, p);
					handleDoubleBlack(u, p, s);
				}
			}

			void ft_print(node_pointer n) {
				if (n->left)
					ft_print(n->left);
				if (n->right)
					ft_print(n->right);
				std::cout << n->content.first << " | " << n->content.second << " : " << n->color << "\n";
			}

			
	};
}
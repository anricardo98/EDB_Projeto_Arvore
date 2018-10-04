#ifndef CA_UWATERLOO_ALUMNI_DWHARDER_GENERAL_TREE
#define CA_UWATERLOO_ALUMNI_DWHARDER_GENERAL_TREE

#include <cassert>
#include <iostream>

// Author:  Douglas Wilhelm Harder
// Copyright (c) 2009 by Douglas Wilhelm Harder.  All rights reserved.
// Under construction....

namespace Data_structures {
	/****************************************************
	 * ************************************************ *
	 * *                 General Tree                 * *
	 * ************************************************ *
	 ****************************************************/

	/****************************************************
	 * General Tree Class
	 *   class General_tree<Type>
	 *
	 * Author: Douglas Wilhelm Harder
	 * 2009-10-10
	 *
	 * A general tree class which attempts to generalize
	 * the philosophy of the weak ordering used in the
	 * STL to a hierarchical ordering.  The ordering
	 * is explicit:  the programmer dictates which
	 * objects are placed as children to a specific
	 * object.
	 *
	 * There are very few functions which work on	
	 * general trees:
	 *  - a constructor and destructor
	 *  - empty, height, size, and clear
	 *
	 * All other functionality is moved to the
	 * iterators, of which there are three sorts:
	 *    - an explicit iterator where the programmer
	 *      can traverse either up or down the edges
	 *      of a tree
	 *
	 *    - a depth-first traversal iterator which
	 *      begins at the root node and steps through
	 *      the nodes in a depth-first traversal	
	 *      order visiting each node once
	 *
	 *    - a breadth-first traversal iterator which
	 *      begins at the root node and steps through
	 *      the nodes in a breadth-first traversal
	 *      order visiting each node once
	 *
	 * In order to perform a pre-, post-, or mixed-order 
	 * traversal, the programmer use the explicit iterator
	 * together with a stack or queue.
	 ****************************************************/

	template <typename Type>
	class General_tree {
		public:
			class iterator;
			class depth_iterator;
			class breadth_iterator;

			General_tree( Type const &obj = Type() );
			~General_tree();
			bool empty() const;
			int size() const;
			int height() const;

			void clear();

			iterator begin();
			iterator end();

			depth_iterator begin_depth();
			depth_iterator end_depth();

			breadth_iterator begin_breadth();
			breadth_iterator end_breadth();

		private:
			class tree_node;
			tree_node *root_node;

		friend class iterator;
		friend class depth_iterator;
		friend class breadth_iterator;
		friend class tree_node;
	};

	/****************************************************
	 * ************************************************ *
	 * *                  Tree Node                   * *
	 * ************************************************ *
	 ****************************************************/

	/****************************************************
	 * Tree Node Class
	 *   class General_tree<Type> :: Tree_node
	 *
	 * Author: Douglas Wilhelm Harder
	 * 2009-10-10
	 *
	 * A tree node class for representing node stored
	 * in this general tree.  These nodes contain:
	 *
	 * Pointers to:
	 *   The parent tree node,
	 *   The next and previous sibling tree nodes, and
	 *   The head and tail pointers for a doubly linked
	 *   list of children nodes.
	 *
	 * Other information stored includes:
	 *   The degree, depth, height, and size of the
	 *   node and the asssociated subtree defined by
	 *   this node and all its descendants.
	 ****************************************************/

	template <typename Type>
	class General_tree<Type>::tree_node {
		public:
			Type element;
			tree_node *parent;
			tree_node *previous_sibling;
			tree_node *next_sibling;
			tree_node *children_head;
			tree_node *children_tail;

			int node_degree;
			int node_depth;
			int node_height;
			int node_size;

			tree_node( Type const &, tree_node *, tree_node *, tree_node *, int );
			void clear();
			// iterator find( Type const & );
	};

	/****************************************************
	 * ************************************************ *
	 * *                   Iterator                   * *
	 * ************************************************ *
	 ****************************************************/

	/****************************************************
	 * Iterator Class
	 *   class General_tree<Type> :: iterator
	 *
	 * Author: Douglas Wilhelm Harder
	 * 2009-10-10
	 *
	 * The object stored in the tree node referenced
	 * by the iterator may be accessed with operator*
	 *
	 * The depth and degree of the referenced tree node
	 * may be retrieved, and
	 * The status of the tree node as a leaf node may
	 * also be queried.
	 *
	 * The height and size of the subtree defined by
	 * the referenced tree node and all its descendants
	 * may be accessed.
	 *
	 * An iterator starting at the first child may
	 * be accessed and an iterator pointing to the
	 * parent may also be accessed.
	 ****************************************************/

	template <typename Type>
	class General_tree<Type>::iterator {
		public:
			iterator();

			int degree() const;
			int depth() const;
			int height() const;
			int size() const;
			bool leaf() const;
			bool root() const;

			void insert( Type const &obj );
			int search (Type const &obj, iterator itr);
			int search_ ( Type const &obj, iterator itr);
			void remove( Type const &obj, iterator itr);
			//int remove_( Type const &obj, iterator itr);


			iterator &operator++();
			iterator operator++( int );
			Type &operator*();
			bool operator==( iterator const &rhs ) const;
			bool operator!=( iterator const &rhs ) const;

			iterator parent();
			iterator begin();
			iterator end();

		private:
			tree_node *current_node;
			tree_node *parent_node;
			iterator( tree_node *, tree_node * );

		friend class General_tree;
	};

	/****************************************************
	 * ************************************************ *
	 * *        Depth-first Traversal Iterator        * *
	 * ************************************************ *
	 ****************************************************/

	/****************************************************
	 * Iterator Class
	 *   class General_tree<Type> :: iterator
	 *
	 * Author: Douglas Wilhelm Harder
	 * 2009-10-10
	 *
	 * ...
	 ****************************************************/

	template <typename Type>
	class General_tree<Type>::depth_iterator {
		public:
			depth_iterator();
			~depth_iterator();
			depth_iterator( depth_iterator const & );
			depth_iterator &operator=( depth_iterator const & );

			int degree() const;
			int depth() const;
			int height() const;
			int size() const;
			bool leaf() const;
			bool root() const;

			depth_iterator &operator++();
			depth_iterator operator++( int );
			Type &operator*();
			bool operator==( depth_iterator const &rhs ) const;
			bool operator!=( depth_iterator const &rhs ) const;

		private:
			class stack_node;
			stack_node *stack_top;
			depth_iterator( tree_node * );

		friend class General_tree;
	};

	/****************************************************
	 * Stack Node Class
	 *   class General_tree<Type>::depth_iterator :: stack_node
	 *
	 * Author: Douglas Wilhelm Harder
	 * 2009-10-10
	 *
	 * A node used to create a stack where each entry
	 * of the stack stores:
	 *   - A pointer to a tree node, and
	 *   - A pointer to the next stack node.
	 *
	 * This stack is used for implementing a depth-
	 * first traversal of the tree.
	 ****************************************************/

	template <typename Type>
	class General_tree<Type>::depth_iterator::stack_node {
		public:
			tree_node *pointer;
			stack_node *next;
			stack_node( tree_node *, stack_node * );
			stack_node( stack_node const & );

		friend class General_tree<Type>::depth_iterator;
	};

	/****************************************************
	 * ************************************************ *
	 * *       Breadth-first Traversal Iterator       * *
	 * ************************************************ *
	 ****************************************************/

	/****************************************************
	 * Iterator Class
	 *   class General_tree<Type> :: iterator
	 *
	 * Author: Douglas Wilhelm Harder
	 * 2009-10-10
	 *
	 * ...
	 ****************************************************/

	template <typename Type>
	class General_tree<Type>::breadth_iterator {
		public:
			breadth_iterator();
			~breadth_iterator();
			breadth_iterator( breadth_iterator const & );
			breadth_iterator &operator=( breadth_iterator const & );

			int degree() const;
			int depth() const;
			int height() const;
			int size() const;
			bool leaf() const;
			bool root() const;

			breadth_iterator &operator++();
			breadth_iterator operator++( int );
			Type &operator*();
			bool operator==( breadth_iterator const &rhs ) const;
			bool operator!=( breadth_iterator const &rhs ) const;

		private:
			class queue_node;
			queue_node *queue_front;
			queue_node *queue_back;
			breadth_iterator( tree_node * );

		friend class General_tree;
	};

	/****************************************************
	 * Queue Node Class
	 *   class General_tree<Type>::breadth_iterator :: queue_node
	 *
	 * Author: Douglas Wilhelm Harder
	 * 2009-10-10
	 *
	 * A node used to create a queue where each entry
	 * of the queue stores:
	 *   - A pointer to a tree node, and
	 *   - A pointer to the next stack node.
	 *
	 * This queue is used for implementing a breadth-
	 * first traversal of the tree.
	 ****************************************************/

	template <typename Type>
	class General_tree<Type>::breadth_iterator::queue_node {
		public:
			tree_node *pointer;
			queue_node *next;
			queue_node( tree_node *, queue_node * );
			queue_node( queue_node const & );

		friend class General_tree<Type>::breadth_iterator;
	};

	/****************************************************
	 * ************************************************ *
	 * *           General Tree Definitions           * *
	 * ************************************************ *
	 ****************************************************/

	/*
	 * Destructor
	 *   General_tree<Type> :: ~General_tree()
	 *
	 * Create a new tree node storing the object.
	 *
	 * O(1)
	 */

	template <typename Type>
	General_tree<Type>::General_tree( Type const &obj ):
	root_node( new tree_node( obj, 0, 0, 0, 0 ) ) {
		// Empty constructor
	}

	/*
	 * Destructor
	 *   General_tree<Type> :: ~General_tree()
	 *
	 * Must recursively clear all objects within
	 * the tree.
	 *
	 * O(n)
	 */

	template <typename Type>
	General_tree<Type>::~General_tree() {
		root_node->clear();
	}

	/*
	 * Empty
	 *   bool General_tree<Type> :: empty() const
	 *
	 * Returns 'false':  there is always a root
	 * node in the general tree.
	 *
	 * O(1)
	 */

	template <typename Type>
	bool General_tree<Type>::empty() const {
		return false;
	}

	/*
	 * Size
	 *   int General_tree<Type> :: size() const
	 *
	 * Returns the number of nodes within the
	 * general tree.
	 *
	 * O(1)
	 */

	template <typename Type>
	int General_tree<Type>::size() const {
		return root_node->node_size;
	}

	/*
	 * Height
	 *   int General_tree<Type> :: height() const
	 *
	 * Returns the height of the general tree:
	 * the lenght of the longest path from
	 * the root node to a node within the tree.
	 *
	 * O(1)
	 */

	template <typename Type>
	int General_tree<Type>::height() const {
		return root_node->node_height;
	}

	/*
	 * Clear
	 *   void General_tree<Type> :: clear()
	 *
	 * Removes all nodes except for the root node.
	 *
	 * O(n)
	 */

	template <typename Type>
	void General_tree<Type>::clear() {
		for ( tree_node *child = root_node->children_head; child != 0; child = child->next_sibling ) {
			child->clear();
		}
	}

	/*
	 * Explicit Iterator
	 *   iterator General_tree<Type> :: begin()
	 *
	 * Returns a explicit (programmer-directored) traversing
	 * iterator which initially refers to the root node.
	 *
	 * O(1)
	 */

	template <typename Type>
	typename General_tree<Type>::iterator General_tree<Type>::begin() {
		return iterator( root_node, 0 );
	}

	template <typename Type>
	typename General_tree<Type>::iterator General_tree<Type>::end() {
		return iterator( 0, 0 );
	}

	/*
	 * Depth-first Traversing Iterator
	 *   iterator General_tree<Type> :: begin_depth()
	 *
	 * Returns a depth-first traversing
	 * iterator which initially refers to the root node.
	 *
	 * O(1)
	 */

	template <typename Type>
	typename General_tree<Type>::breadth_iterator General_tree<Type>::begin_breadth() {
		return breadth_iterator( root_node );
	}

	template <typename Type>
	typename General_tree<Type>::breadth_iterator General_tree<Type>::end_breadth() {
		return breadth_iterator();
	}

	/*
	 * Breadth-first Traversing Iterator
	 *   iterator General_tree<Type> :: begin_breadth()
	 *
	 * Returns a breadth-first traversing
	 * iterator which initially refers to the root node.
	 *
	 * O(1)
	 */

	template <typename Type>
	typename General_tree<Type>::depth_iterator General_tree<Type>::begin_depth() {
		return depth_iterator( root_node );
	}

	template <typename Type>
	typename General_tree<Type>::depth_iterator General_tree<Type>::end_depth() {
		return depth_iterator();
	}

	/****************************************************
	 * ************************************************ *
	 * *             Tree Node Definitions            * *
	 * ************************************************ *
	 ****************************************************/

	/*
	 * Constructor
	 *   iterator General_tree<Type>::tree_node :: tree_node( ... )
	 *
	 * Constructs a new tree node where:
	 *   The object stored is specified.
	 *   Pointers to the nodes containing the parent, previous
	 *   sibling, and next sibling are specified.
	 *   The list of children is initially empty
	 *     - Children head and tail and the degree are set to 0
	 *  The depth is specified.
	 *  The height is 0 and the size is 1.
	 *
	 * O(1)
	 */

	template <typename Type>
	General_tree<Type>::tree_node::tree_node( Type const &obj, tree_node *par, tree_node *p, tree_node *n, int d ):
	element( obj ),
	parent( par ),
	previous_sibling( p ),
	next_sibling( n ),
	children_head( 0 ),
	children_tail( 0 ),
	node_degree( 0 ),
	node_depth( d ),
	node_height( 0 ),
	node_size( 1 ) {
		// Empty constructor
	}

	template <typename Type>
	void General_tree<Type>::tree_node::clear() {
		for ( tree_node *child = children_head; child != 0; child = child->next_sibling ) {
			child->clear();
		}

		delete this;
	}

/*
	template <typename Type>
	typename General_tree<Type>::iterator General_tree<Type>::tree_node::find( Type const &obj ) {
		return iterator();
	}
 */

	/****************************************************
	 * ************************************************ *
	 * *             Iterator Definitions             * *
	 * ************************************************ *
	 ****************************************************/

	template <typename Type>
	General_tree<Type>::iterator::iterator():
	current_node( 0 ),
	parent_node( 0 ) {
		// Empty constructor
	}

	template <typename Type>
	General_tree<Type>::iterator::iterator( tree_node *c, tree_node *p ):
	current_node( c ),
	parent_node( p ) {
		// Empty constructor
	}

	template <typename Type>
	typename General_tree<Type>::iterator General_tree<Type>::iterator::parent() {
		if ( current_node->parent_node == 0 ) {
			assert( false );
		}

		return iterator( current_node->parent_node, current_node->parent_node->parent );
	}

	/*
	 * Degree of a Tree Node
	 *   int General_tree<Type>::iterator :: degree() const
	 *
	 * Returns the degree (number of children) of the currently
	 * referred to node.
	 *
	 * O(1)
	 */

	template <typename Type>
	int General_tree<Type>::iterator::degree() const {
		return current_node->node_degree;
	}

	/*
	 * Depth of a Tree Node
	 *   int General_tree<Type>::iterator :: depth() const
	 *
	 * Returns the depth of the currently referred to
	 * node (the length of the path from the root
	 * node to the current node).
	 *
	 * O(1)
	 */

	template <typename Type>
	int General_tree<Type>::iterator::depth() const {
		return current_node->node_depth;
	}

	/*
	 * Height of a Tree Node
	 *   int General_tree<Type>::iterator :: height() const
	 *
	 * Returns the height of the tree defined by the
	 * currently referred to node and its descendants.
	 *
	 * O(1)
	 */

	template <typename Type>
	int General_tree<Type>::iterator::height() const {
		return current_node->node_height;
	}

	/*
	 * Size of a Tree Node
	 *   int General_tree<Type>::iterator :: size() const
	 *
	 * Returns the size of (number of nodes within) the tree defined
	 * by the currently referred to node and its descendants.
	 *
	 * O(1)
	 */

	template <typename Type>
	int General_tree<Type>::iterator::size() const {
		return current_node->node_size;
	}

	/*
	 * Leaf Query
	 *   bool General_tree<Type>::iterator :: leaf() const
	 *
	 * Returns true if the currently referred to tree node is
	 * leaf node (no children), and false otherwise.
	 *
	 * O(1)
	 */

	template <typename Type>
	bool General_tree<Type>::iterator::leaf() const {
		return current_node->children_head == 0;
	}

	/*
	 * Root Query
	 *   bool General_tree<Type>::iterator :: root() const
	 *
	 * Returns true if the currently referred to tree node is
	 * root node, and false otherwise.
	 *
	 * O(1)
	 */

	template <typename Type>
	bool General_tree<Type>::iterator::root() const {
		return current_node->parent == 0;
	}

	template <typename Type>
	typename General_tree<Type>::iterator General_tree<Type>::iterator::begin() {
		return iterator( current_node->children_head, current_node );
	}

	template <typename Type>
	typename General_tree<Type>::iterator General_tree<Type>::iterator::end() {
		return iterator( 0, current_node );
	}

	template <typename Type>
	typename General_tree<Type>::iterator &General_tree<Type>::iterator::operator++() {
		if ( current_node != 0 ) {
			current_node = current_node->next_sibling;
		}

		return *this;
	}

	/*
	 * Postincrement Step
	 *   bool General_tree<Type>::iterator :: operator++( int )
	 *
	 * This function is similar to the Preincrement Step function;
	 * however, an iterator referring to the original tree node
	 * is returned.
	 *
	 * O(1)
	 */

	template <typename Type>
	typename General_tree<Type>::iterator General_tree<Type>::iterator::operator++( int ) {
		iterator copy = *this;

		if ( current_node != 0 ) {
			current_node = current_node->next_sibling;
		}

		return copy;
	}

	/*
	 * Dereference Operator
	 *   bool General_tree<Type>::iterator :: operator*()
	 *
	 * Return a reference to the object stored in the node
	 * currently referred to by this iterator.
	 *
	 * O(1)
	 */

	template <typename Type>
	Type &General_tree<Type>::iterator::operator*() {
		return current_node->element;
	}

	template <typename Type>
	bool General_tree<Type>::iterator::operator==( iterator const &rhs ) const {
		return ( current_node == rhs.current_node );
	}

	template <typename Type>
	bool General_tree<Type>::iterator::operator!=( iterator const &rhs ) const {
		return ( current_node != rhs.current_node );
	}

	/*
	 * Insert a New Type as a Child of the Currently Referrred To Node
	 *   void General_tree<Type>::iterator :: insert( Type const &obj ) const
	 *
	 * For an object to be inserted into a node, a number of operations
	 * must be performed:
	 *   The object must be appended to the doubly linked list
	 *   of children of the current node.
	 *     - This new node is a leaf node with depth one greater
	 *       than the depth of the current node.
	 *   The degree of the referred to node must be incremented.
	 *   If the current node was previously a leaf node, its height
	 *   and the height of all of its ancestors must be updated.
	 *   The size of this node and all of its ancestors must
	 *   be incremented.
	 *
	 */

	template <typename Type>
	void General_tree<Type>::iterator::insert( Type const &obj ) {
		if ( current_node->node_degree == 0 ) {
			// If the current node is a leaf node, then
			// a new node must be placed into the empty list
			// of children.

			current_node->children_head = new tree_node(
				obj, current_node, 0, 0, current_node->node_depth + 1
			);

			current_node->children_tail = current_node->children_head;
			current_node->node_degree = 1;

			// Set the height to 1 and update all strict ancestors
			// recursing back to the root node (the parent of which is 0).

			current_node->node_height = 1;

			for (
				tree_node *current = current_node, *regress = current_node->parent;
				regress != 0;
				current = regress, regress = regress->parent
			) {
				regress->node_height = std::max( current->node_height + 1, regress->node_height );
			}

			// The size must now be 2:  the current node and its 
			current_node->node_size = 2;

		} else {
			// If the current node is not a leaf node, then
			// append the new tree node to the currently existing
			// list of children.
			tree_node *tmp = new tree_node(
				obj, current_node, current_node->children_tail, 0, current_node->node_depth + 1
			);

			current_node->children_tail->next_sibling = tmp;
			current_node->children_tail = tmp;
			++( current_node->node_degree );

			// Increment the size of the current node
			++( current_node->node_size );
		}

		// Increment the size of all strict ancestors
		// recursing back to the root node.

		for ( tree_node *regress = current_node->parent; regress != 0; regress = regress->parent ) {
			++( regress->node_size );
		}
	}

	template <typename Type>
	int General_tree<Type>::iterator::search( Type const &obj, iterator itr) {
			
		int aux = search_(obj, itr);

		if (aux == 0){
			cout << "Nao esta presente na lista" << endl;
		}
	
		return aux;

	}

	template <typename Type>
	int General_tree<Type>::iterator::search_( Type const &obj, iterator itr) {

		int aux = 0;
		
		for (General_tree<int>::iterator child = itr.begin(); child != itr.end(); ++child) {
			aux = search_(obj, child);

			if (aux == 1){
				child = itr.end();
			}
		}

		if (aux == 0){
			if (*itr == obj){
				cout << "Esta presente na lista" << endl;
				std::cout << *itr <<
				"  (depth " << itr.depth() <<
				", size " << itr.size() <<
				", height " << itr.height() <<
				", degree " << itr.degree() <<
				", is root " << itr.root() <<
				", is leaf " << itr.leaf() <<
				")" << std::endl;
				aux = 1;
			} 

		} 

		return aux;

	}


	template <typename Type>
	void General_tree<Type>::iterator::remove( Type const &obj, iterator itr) {

		for (General_tree<int>::iterator child = itr.begin(); child != itr.end(); ++child) {
			remove(obj, child);

		}

		if (*itr == obj){

			int altura;
			int tamanho = itr.current_node->node_size;


			tree_node *temp = itr.current_node->next_sibling;
			tree_node *temp2 = itr.current_node->previous_sibling;
			tree_node *pai = itr.parent_node;

			if (temp != NULL){
					temp->previous_sibling = temp2;
					cout << "Um" << endl;
			}

			if (temp2 != NULL){
				temp2->next_sibling = temp;
			}

			if (pai->children_tail == itr.current_node){
				pai->children_tail = temp2;
			}

			if (pai->children_head == itr.current_node){
				pai->children_head = temp;
			}

			pai->node_degree = itr.parent_node->node_degree - 1;

			for (tree_node * regress = pai; regress != 0; regress = regress->parent){
	
				regress->node_size = regress->node_size - tamanho;
			}

			if (pai->node_degree == 0){

				pai->node_height = 0;

				for (tree_node * regress = pai->parent; regress != 0; regress = regress->parent) {

					altura = 0;

					for (tree_node *i = regress->children_head; i != regress->children_tail; i = i->next_sibling){
						altura = std::max(altura, i->node_height);
					}

					regress->node_height = altura + 1;
				}
			}

			itr.current_node->clear();
			cout << "No removido" << endl;
			return;
		}

	}

	/****************************************************
	 * ************************************************ *
	 * *  Depth-first Traversal Iterator Definitions  * *
	 * ************************************************ *
	 ****************************************************/

	template <typename Type>
	General_tree<Type>::depth_iterator::depth_iterator():
	stack_top( 0 ) {
		// Empty constructor
	}

	template <typename Type>
	General_tree<Type>::depth_iterator::depth_iterator( tree_node *rt ):
	stack_top( new stack_node( rt, 0 ) ) {
		// Empty constructor
	}

	template <typename Type>
	General_tree<Type>::depth_iterator::~depth_iterator() {
		while ( stack_top != 0 ) {
			stack_node *tmp = stack_top;
			stack_top = stack_top->next;
			delete tmp;
		}
	}

	template <typename Type>
	General_tree<Type>::depth_iterator::depth_iterator( depth_iterator const &itr ):
	stack_top( 0 ) {
		*this = itr;
	}

	template <typename Type>
	typename General_tree<Type>::depth_iterator &General_tree<Type>::depth_iterator::operator=( depth_iterator const &rhs ) {
		if ( this == &rhs ) {
			return *this;
		}

		while ( stack_top != 0 ) {
			stack_node *tmp = stack_top;
			stack_top = stack_top->next;
			delete tmp;
		}

		if ( rhs.stack_top == 0 ) {
			stack_top = 0;
			return *this;
		}

		stack_top = new stack_node( *rhs.stack_top );
		stack_node *lptr = stack_top;

		for ( stack_node *rptr = rhs.stack_top->next; rptr != 0; rptr = rptr->next ) {
			lptr->next = new stack_node( *rptr );
			lptr = lptr->next;
		}
	}

	template <typename Type>
	int General_tree<Type>::depth_iterator::degree() const {
		return stack_top->pointer->node_degree;
	}

	/*
	 * Depth of a Tree Node
	 *   int General_tree<Type>::depth_iterator :: depth() const
	 *
	 * Returns the depth of the currently referred to
	 * node (the length of the path from the root
	 * node to the current node).
	 *
	 * O(1)
	 */

	template <typename Type>
	int General_tree<Type>::depth_iterator::depth() const {
		return stack_top->pointer->node_depth;
	}

	/*
	 * Height of a Tree Node
	 *   int General_tree<Type>::depth_iterator :: height() const
	 *
	 * Returns the height of the tree defined by the
	 * currently referred to node and its descendants.
	 *
	 * O(1)
	 */

	template <typename Type>
	int General_tree<Type>::depth_iterator::height() const {
		return stack_top->pointer->node_height;
	}

	/*
	 * Size of a Tree Node
	 *   int General_tree<Type>::depth_iterator :: size() const
	 *
	 * Returns the size of (number of nodes within) the tree defined
	 * by the currently referred to node and its descendants.
	 *
	 * O(1)
	 */

	template <typename Type>
	int General_tree<Type>::depth_iterator::size() const {
		return stack_top->pointer->node_size;
	}

	/*
	 * Leaf Query
	 *   bool General_tree<Type>::depth_iterator :: leaf() const
	 *
	 * Returns true if the currently referred to tree node is
	 * leaf node (no children), and false otherwise.
	 *
	 * O(1)
	 */

	template <typename Type>
	bool General_tree<Type>::depth_iterator::leaf() const {
		return stack_top->pointer->children_head == 0;
	}

	/*
	 * Root Query
	 *   bool General_tree<Type>::depth_iterator :: root() const
	 *
	 * Returns true if the currently referred to tree node is
	 * root node, and false otherwise.
	 *
	 * O(1)
	 */

	template <typename Type>
	bool General_tree<Type>::depth_iterator::root() const {
		return stack_top->pointer->parent == 0;
	}

	/*
	 * Preincrement Step
	 *   bool General_tree<Type>::depth_iterator :: operator++()
	 *
	 * A stack is used to facilitate a depth-first traversal.
	 * The root node is pushed onto a stack and then we iterate:
	 *   While the stack is not empty:
	 *    - Pop the top of the stack, and
	 *      Push all children onto the stack in reverse order.
	 *
	 * This function performs the pop operation together with
	 * any necessary push operations,
	 * Updates the iterator to refer to the tree node popped
	 * off the stack, and
	 * Returns a reference to this iterator.
	 *
	 * O(1)
	 */

	template <typename Type>
	typename General_tree<Type>::depth_iterator &General_tree<Type>::depth_iterator::operator++() {
		// We can only increment an interator which
		// has not yet already completed.
		if ( stack_top == 0 ) {
			return *this;
		}

		// Pop the top stack_node off of the stack
		stack_node *tmp = stack_top;
		stack_top = stack_top->next;

		if ( tmp->pointer->children_head == 0 ) {
			delete tmp;
			return *this;
		}

		// Push the children of the top stack_node onto the stack in reverse order
		stack_node *new_stack_top = new stack_node( tmp->pointer->children_head, stack_top );
		stack_node *ptr = new_stack_top;

		for ( tree_node *child = tmp->pointer->children_head->next_sibling; child != 0; child = child->next_sibling ) {
			ptr->next = new stack_node( child, stack_top );
			ptr = ptr->next;
		}

		stack_top = new_stack_top;
		delete tmp;

		return *this;
	}

	/*
	 * Postincrement Step
	 *   bool General_tree<Type>::depth_iterator :: operator++( int )
	 *
	 * This function is similar to the Preincrement Step function;
	 * however, an iterator referring to the original tree node
	 * is returned.
	 *
	 * O(1)
	 */

	template <typename Type>
	typename General_tree<Type>::depth_iterator General_tree<Type>::depth_iterator::operator++( int ) {
		depth_iterator copy = *this;

		++(*this);

		return copy;
	}

	/*
	 * Dereference Operator
	 *   bool General_tree<Type>::depth_iterator :: operator*()
	 *
	 * Return a reference to the object stored in the node
	 * currently referred to by this iterator.
	 *
	 * O(1)
	 */

	template <typename Type>
	Type &General_tree<Type>::depth_iterator::operator*() {
		return stack_top->pointer->element;
	}

	template <typename Type>
	bool General_tree<Type>::depth_iterator::operator==( depth_iterator const &rhs ) const {
		if ( stack_top == 0 || rhs.stack_top == 0 ) {
			return stack_top == rhs.stack_top;
		} else {
			return stack_top->pointer == rhs.stack_top->pointer;
		}
	}

	template <typename Type>
	bool General_tree<Type>::depth_iterator::operator!=( depth_iterator const &rhs ) const {
		if ( stack_top == 0 || rhs.stack_top == 0 ) {
			return stack_top != rhs.stack_top;
		} else {
			return stack_top->pointer != rhs.stack_top->pointer;
		}
	}

	template <typename Type>
	General_tree<Type>::depth_iterator::stack_node::stack_node( tree_node *p, stack_node *n ):
	pointer( p ),
	next( n ) {

	}

	template <typename Type>
	General_tree<Type>::depth_iterator::stack_node::stack_node( stack_node const &node ):
	pointer( node.pointer ),
	next( node.next ) {

	}

	/****************************************************
	 * ************************************************ *
	 * * Breadth-first Traversal Iterator Definitions * *
	 * ************************************************ *
	 ****************************************************/

	template <typename Type>
	General_tree<Type>::breadth_iterator::breadth_iterator():
	queue_front( 0 ),
	queue_back( 0 ) {
		// Empty constructor
	}

	template <typename Type>
	General_tree<Type>::breadth_iterator::breadth_iterator( tree_node *rt ):
	queue_front( new queue_node( rt, 0 ) ),
	queue_back( queue_front ) {
		// Empty constructor
	}

	template <typename Type>
	General_tree<Type>::breadth_iterator::~breadth_iterator() {
		while ( queue_front != 0 ) {
			queue_node *tmp = queue_front;
			queue_front = queue_front->next;
			delete tmp;
		}
	}

	template <typename Type>
	General_tree<Type>::breadth_iterator::breadth_iterator( breadth_iterator const &itr ):
	queue_front( 0 ),
	queue_back( 0 ) {
		*this = itr;
	}

	template <typename Type>
	typename General_tree<Type>::breadth_iterator &General_tree<Type>::breadth_iterator::operator=( breadth_iterator const &rhs ) {
		if ( this == &rhs ) {
			return *this;
		}

		while ( queue_front != 0 ) {
			queue_node *tmp = queue_front;
			queue_front = queue_front->next;
			delete tmp;
		}

		if ( rhs.queue_front == 0 ) {
			queue_front = 0;
			queue_back = 0;
			return *this;
		}

		queue_front = new queue_node( *rhs.queue_front );
		queue_node *lptr = queue_front;

		for ( queue_node *rptr = rhs.queue_front->next; rptr != 0; rptr = rptr->next ) {
			lptr->next = new queue_node( *rptr );
			lptr = lptr->next;
		}

		queue_back = lptr;
	}

	template <typename Type>
	int General_tree<Type>::breadth_iterator::degree() const {
		return queue_front->pointer->node_degree;
	}

	/*
	 * Depth of a Tree Node
	 *   int General_tree<Type>::breadth_iterator :: depth() const
	 *
	 * Returns the depth of the currently referred to
	 * node (the length of the path from the root
	 * node to the current node).
	 *
	 * O(1)
	 */

	template <typename Type>
	int General_tree<Type>::breadth_iterator::depth() const {
		return queue_front->pointer->node_depth;
	}

	/*
	 * Height of a Tree Node
	 *   int General_tree<Type>::breadth_iterator :: height() const
	 *
	 * Returns the height of the tree defined by the
	 * currently referred to node and its descendants.
	 *
	 * O(1)
	 */

	template <typename Type>
	int General_tree<Type>::breadth_iterator::height() const {
		return queue_front->pointer->node_height;
	}

	/*
	 * Size of a Tree Node
	 *   int General_tree<Type>::breadth_iterator :: size() const
	 *
	 * Returns the size of (number of nodes within) the tree defined
	 * by the currently referred to node and its descendants.
	 *
	 * O(1)
	 */

	template <typename Type>
	int General_tree<Type>::breadth_iterator::size() const {
		return queue_front->pointer->node_size;
	}

	/*
	 * Leaf Query
	 *   bool General_tree<Type>::breadth_iterator :: leaf() const
	 *
	 * Returns true if the currently referred to tree node is
	 * leaf node (no children), and false otherwise.
	 *
	 * O(1)
	 */

	template <typename Type>
	bool General_tree<Type>::breadth_iterator::leaf() const {
		return queue_front->pointer->children_head == 0;
	}

	/*
	 * Root Query
	 *   bool General_tree<Type>::breadth_iterator :: root() const
	 *
	 * Returns true if the currently referred to tree node is
	 * root node, and false otherwise.
	 *
	 * O(1)
	 */

	template <typename Type>
	bool General_tree<Type>::breadth_iterator::root() const {
		return queue_front->pointer->parent == 0;
	}

	/*
	 * Preincrement Step
	 *   bool General_tree<Type>::breadth_iterator :: operator++()
	 *
	 * A queue is used to facilitate a breadth-first traversal.
	 * The root node is pushed onto a queue and then we iterate:
	 *   While the queue is not empty:
	 *     - Pop the front of the queue and
	 *     - Push all children onto the queue.
	 *
	 * This function performs the pop operation together with
	 * any necessary push operations,
	 * Updates the iterator to refer to the tree node popped
	 * off the queue, and
	 * Returns a reference to this iterator.
	 *
	 * O(1)
	 */

	template <typename Type>
	typename General_tree<Type>::breadth_iterator &General_tree<Type>::breadth_iterator::operator++() {
		if ( queue_front == 0 ) {
			return *this;
		}

		// Push the children of the front tree queue_node onto the queue
		for ( tree_node *child = queue_front->pointer->children_head; child != 0; child = child->next_sibling ) {
			queue_back->next = new queue_node( child, 0 );
			queue_back = queue_back->next;
		}

		// Pop the front queue_node off the queue
		queue_node *tmp = queue_front;
		queue_front = queue_front->next;
		delete tmp;

		return *this;
	}

	/*
	 * Postincrement Step
	 *   bool General_tree<Type>::breadth_iterator :: operator++( int )
	 *
	 * This function is similar to the Preincrement Step function;
	 * however, an iterator referring to the original tree node
	 * is returned.
	 *
	 * O(1)
	 */

	template <typename Type>
	typename General_tree<Type>::breadth_iterator General_tree<Type>::breadth_iterator::operator++( int ) {
		breadth_iterator copy = *this;

		++(*this);

		return copy;
	}

	/*
	 * Dereference Operator
	 *   bool General_tree<Type>::breadth_iterator :: operator*()
	 *
	 * Return a reference to the object stored in the node
	 * currently referred to by this iterator.
	 *
	 * O(1)
	 */

	template <typename Type>
	Type &General_tree<Type>::breadth_iterator::operator*() {
		return queue_front->pointer->element;
	}

	template <typename Type>
	bool General_tree<Type>::breadth_iterator::operator==( breadth_iterator const &rhs ) const {
		if ( queue_front == 0 || rhs.queue_front == 0 ) {
			return queue_front == rhs.queue_front;
		} else {
			return queue_front->pointer == rhs.queue_front->pointer;
		}
	}

	template <typename Type>
	bool General_tree<Type>::breadth_iterator::operator!=( breadth_iterator const &rhs ) const {
		if ( queue_front == 0 || rhs.queue_front == 0 ) {
			return queue_front != rhs.queue_front;
		} else {
			return queue_front->pointer != rhs.queue_front->pointer;
		}
	}

	template <typename Type>
	General_tree<Type>::breadth_iterator::queue_node::queue_node( tree_node *p, queue_node *n ):
	pointer( p ),
	next( n ) { 
	}


	template <typename Type>
	General_tree<Type>::breadth_iterator::queue_node::queue_node( queue_node const &node ):
	pointer( node.pointer ),
	next( node.next ) {

	}
}

#endif
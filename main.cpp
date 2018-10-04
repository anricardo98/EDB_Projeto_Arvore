#include <iostream>
#include <stack>
using namespace std;

/******************************************************
 * This function generates a simple general tree:
 * 
 *                                                  1
 *                11                                21                                31
 *        111              211              121              221              131              231
 *  1111 2111 3111   1211 2211 3211   1121 2121 3121   1221 2221 3221   1131 2131 3131   1231 2231 3231 
 *
 * Numerous traversals are performed including a
 * user-defined depth-first traversal of the nodes.
 ******************************************************/

#include "arvores-gerais.hpp"
using namespace Data_structures;

// A pre-order printer

void print( General_tree<int>::iterator itr, int n ) {
	for ( int i = 0; i < n; ++i ) {
		std::cout << "  ";
	}

	std::cout << *itr <<
		"  (depth " << itr.depth() <<
		", size " << itr.size() <<
		", height " << itr.height() <<
		", degree " << itr.degree() <<
		", is root " << itr.root() <<
		", is leaf " << itr.leaf() <<
		")" << std::endl;

	for ( General_tree<int>::iterator child = itr.begin(); child != itr.end(); ++child ) {
		print( child, n + 1 );
	}
}

// A post-order printer

int sum( General_tree<int>::iterator itr, int n ) {
	int s = 0;

	for ( General_tree<int>::iterator child = itr.begin(); child != itr.end(); ++child ) {
		s += sum( child, n + 1 );
	}

	for ( int i = 0; i < n; ++i ) {
		std::cout << "  ";
	}

	s += *itr;

	std::cout << *itr << "    " << s << std::endl;

	return s;
}

int main() {
	General_tree<int> tree( 1 );

	int saida;
	General_tree<int>::iterator itr = tree.begin();

	itr.insert( 11 );
	itr.insert( 21 );
	itr.insert( 31 );

	for ( General_tree<int>::iterator i = itr.begin(); i != itr.end(); ++i ) {
		i.insert( *i + 100 );
		i.insert( *i + 200 );
	}

	for ( General_tree<int>::iterator i = itr.begin(); i != itr.end(); ++i ) {
		for ( General_tree<int>::iterator j = i.begin(); j != i.end(); ++j ) {
			j.insert( *j + 1000 );
			j.insert( *j + 2000 );
			j.insert( *j + 3000 );
		}
	}

	itr = tree.begin();
	cout << "Size: " << tree.size() << endl;
	cout << "Height: " << tree.height() << endl;
	print( tree.begin(), 0 );
	cout << endl;
	saida = itr.search(11, itr);
	cout << saida << endl;
	/*saida = itr.search(2, itr);
	cout << saida << endl;*/
	itr.remove(1111, itr);
	saida = itr.search(1111, itr);
	cout << saida << endl;

	print (tree.begin(), 0);


	//sum( tree.begin(), 0 );
	//cout << endl;
/*
	for (
		General_tree<int>::breadth_iterator i = tree.begin_breadth();
		i != tree.end_breadth();
		++i
	) {
		cout << *i << " ";
	}

	cout << endl;

	for (
		General_tree<int>::breadth_iterator i = tree.begin_breadth();
		i != tree.end_breadth();
		i++
	) {
		cout << *i << " ";
	}

	cout << endl;

	for (
		General_tree<int>::depth_iterator i = tree.begin_depth();
		i != tree.end_depth();
		++i
	) {
		cout << *i << " ";
	}

	cout << endl;

	for (
		General_tree<int>::depth_iterator i = tree.begin_depth();
		i != tree.end_depth();
		i++
	) {
		cout << *i << " ";
	}

	cout << endl;
*/
	return 0;
}
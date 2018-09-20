#include <iostream>
#include <stack>
using namespace std;

/******************************************************
 * This function generates a randome tree and prints
 * the result using depth-first and breadth-first
 * traversals together with a user-defined pre-order
 * depth-first traversal.
 ******************************************************/

#include "arvores-gerais.hpp"
using namespace Data_structures;

void print( General_tree<long>::iterator itr, int n ) {
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

	for ( General_tree<long>::iterator child = itr.begin(); child != itr.end(); ++child ) {
		print( child, n + 1 );
	}
}

void generate( General_tree<long>::iterator itr, long m, long n ) {
	for ( long i = 0; i < (rand() % (m/2)); ++i ) {
		itr.insert( *itr + (i + 1)*n );
	}

	for ( General_tree<long>::iterator child = itr.begin(); child != itr.end(); ++child ) {
		generate( child, std::max<long>( 3, m - 1 ), 10*n );
	}
}

int main() {
	General_tree<long> random_tree( 1 );
	General_tree<long>::iterator itr;

	itr = random_tree.begin();

	generate( itr, 16, 10 );

	cout << "Size: " << random_tree.size() << endl;
	cout << "Height: " << random_tree.height() << endl;
	print( random_tree.begin(), 0 );

	for (
		General_tree<long>::breadth_iterator i = random_tree.begin_breadth();
		i != random_tree.end_breadth();
		++i
	) {
		cout << *i << " ";
	}

	cout << endl;

	for (
		General_tree<long>::breadth_iterator i = random_tree.begin_breadth();
		i != random_tree.end_breadth();
		i++
	) {
		cout << *i << " ";
	}

	cout << endl;

	for (
		General_tree<long>::depth_iterator i = random_tree.begin_depth();
		i != random_tree.end_depth();
		++i
	) {
		cout << *i << " ";
	}

	cout << endl;

	for (
		General_tree<long>::depth_iterator i = random_tree.begin_depth();
		i != random_tree.end_depth();
		i++
	) {
		cout << *i << " ";
	}

	cout << endl;

	return 0;
}
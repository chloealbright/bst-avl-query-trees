#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream> //additional for void print function
#include "dsexceptions.h"
#include <algorithm>
#include <cmath> //additional for log2N
#include <string> //additional for compare() string
using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
public:
	BinarySearchTree( ) : root{ nullptr }
	{
	}

	/**
	 * Copy constructor
	 */
	BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
	{
		root = clone( rhs.root );
	}

	/**
	 * Move constructor
	 */
	BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
	{
		rhs.root = nullptr;
	}

	/**
	 * Destructor for the tree
	 */
	~BinarySearchTree( )
	{
		makeEmpty( );
	}

	/**
	 * Copy assignment
	 */
	BinarySearchTree & operator=( const BinarySearchTree & rhs )
	{
		BinarySearchTree copy = rhs;
		std::swap( *this, copy );
		return *this;
	}

	/**
	 * Move assignment
	 */
	BinarySearchTree & operator=( BinarySearchTree && rhs )
	{
		std::swap( root, rhs.root );
		return *this;
	}


	/**
	 * Find the smallest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	const Comparable & findMin( ) const
	{
		if( isEmpty( ) )
			throw UnderflowException{ };
		return findMin( root )->element;
	}

	/**
	 * Find the largest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	const Comparable & findMax( ) const
	{
		if( isEmpty( ) )
			throw UnderflowException{ };
		return findMax( root )->element;
	}

	/**
	 * Returns true if x is found in the tree.
	 */
	bool contains( const Comparable & x ) const
	{
		return contains( x, root );
	}

	/**
	 * Test if the tree is logically empty.
	 * Return true if empty, false otherwise.
	 */
	bool isEmpty( ) const
	{
		return root == nullptr;
	}

	/**
	 * Print the tree contents in sorted order.
	 */
	void printTree( ostream & out = cout ) const
	{
		if( isEmpty( ) )
			out << "Empty tree" << endl;
		else
			printTree( root, out );
	}

	/**
	 * Make the tree logically empty.
	 */
	void makeEmpty( )
	{
		makeEmpty( root );
	}

	/**
	 * Insert x into the tree; duplicates are ignored.
	 */
	void insert( const Comparable & x )
	{
		insert( x, root );
	}

	/**
	 * Insert x into the tree; duplicates are ignored.
	 */
	void insert( Comparable && x )
	{
		insert( std::move( x ), root );
	}

	/**
	 * Remove x from the tree. Nothing is done if x is not found.
	 */
	void remove( const Comparable & x )
	{
		remove( x, root );
	}

	//MY FUNCTIONS: PUBLIC
	/** 
	*/

	/** Part 2A: FindNode
		If the value is found in the tree 
		@post prints the value, else return "Not Found"
	*/
	void FindNode( const Comparable & x ) const
	{
		FindNode( x, root );
	}//end FindNode

	/** Part 2A and 2B: Size
	 @returns total number of nodes in the tree.
	*/
	int Size() const{		
      return Size(root);
    }//end Size


	/** Part 2B: Find 
		Helper function for Part 4A: strings found in tree
		@returns true if sting is found. 
	*/
	bool Find( const string & x ) const
	{
		Find( x, root );
	}//end Find

	

	/** Part 2B: Depth
		Helper function for AvgDepth()
		Depth is the total height-rank value of nodes from the root node.
		(example: root height-rank is 0, parent = 1, leaf = 2)
		@returns Depth length
	*/
	int Depth(){
		int x = 0;
		return Depth(x, root);
	}//end Depth

	/** Part 2B: RemoveThirdSeq()
		Similar to remove function.
		Removes every 3rd sequence in sequences.txt from the tree 
		@post true if successfully removed 
	*/
	void RemoveThirdSeq( const Comparable & x ) const{
		RemoveThirdSeq( x, root);
	}//end RemoveThirdSeq

	//END MY FUNCTIONS: PUBLIC


private:
	struct BinaryNode
	{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;

		BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
			: element{ theElement }, left{ lt }, right{ rt } { }

		BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
			: element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
	};

	BinaryNode *root;


	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert( const Comparable & x, BinaryNode * & t ) //for l value: pointer value
	{
		if( t == nullptr )
			t = new BinaryNode{ x, nullptr, nullptr };
		else if( x < t->element )
			insert( x, t->left );
		else if( t->element < x )
			insert( x, t->right );
		else  //ADDITIONAL CASE FOR MERGE 
			t->element.Merge(x);
	}//end insert

	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert( Comparable && x, BinaryNode * & t ) //for rvalue: literal expressions
	{
		if( t == nullptr )
			t = new BinaryNode{ std::move( x ), nullptr, nullptr };
		else if( x < t->element )
			insert( std::move( x ), t->left );
		else if( t->element < x )
			insert( std::move( x ), t->right );
		else  //ADDITIONAL CASE FOR MERGE 
			t->element.Merge(x);
	}//end insert

	/**
	 * Internal method to remove from a subtree.
	 * x is the item to remove.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void remove( const Comparable & x, BinaryNode * & t )
	{
		if( t == nullptr )
			return;   // Item not found; do nothing
		if( x < t->element )
			remove( x, t->left );
		else if( t->element < x )
			remove( x, t->right );
		else if( t->left != nullptr && t->right != nullptr ) // Two children
		{
			t->element = findMin( t->right )->element;
			remove( t->element, t->right );
		}
		else
		{
			BinaryNode *oldNode = t;
			t = ( t->left != nullptr ) ? t->left : t->right;
			delete oldNode;
		}
	}

	/**
	 * Internal method to find the smallest item in a subtree t.
	 * Return node containing the smallest item.
	 */
	BinaryNode * findMin( BinaryNode *t ) const
	{
		if( t == nullptr )
			return nullptr;
		if( t->left == nullptr )
			return t;
		return findMin( t->left );
	}

	/**
	 * Internal method to find the largest item in a subtree t.
	 * Return node containing the largest item.
	 */
	BinaryNode * findMax( BinaryNode *t ) const
	{
		if( t != nullptr )
			while( t->right != nullptr )
				t = t->right;
		return t;
	}


	/**
	 * Internal method to test if an item is in a subtree.
	 * x is item to search for.
	 * t is the node that roots the subtree.
	 */
	bool contains( const Comparable & x, BinaryNode *t ) const
	{
		if( t == nullptr )
			return false;
		else if( x < t->element )
			return contains( x, t->left );
		else if( t->element < x )
			return contains( x, t->right );
		else
			return true;    // Match
	}
	/****** NONRECURSIVE VERSION*************************
	    bool contains( const Comparable & x, BinaryNode *t ) const
	    {
	        while( t != nullptr )
	            if( x < t->element )
	                t = t->left;
	            else if( t->element < x )
	                t = t->right;
	            else
	                return true;    // Match

	        return false;   // No match
	    }
	*****************************************************/

	/**
	 * Internal method to make subtree empty.
	 */
	void makeEmpty( BinaryNode * & t )
	{
		if( t != nullptr )
		{
			makeEmpty( t->left );
			makeEmpty( t->right );
			delete t;
		}
		t = nullptr;
	}

	/**
	 * Internal method to print a subtree rooted at t in sorted order.
	 */
	void printTree( BinaryNode *t, ostream & out ) const
	{
		if( t != nullptr )
		{
			printTree( t->left, out );
			out << t->element << endl;
			printTree( t->right, out );
		}
	}

	/**
	 * Internal method to clone subtree.
	 */
	BinaryNode * clone( BinaryNode *t ) const
	{
		if( t == nullptr )
			return nullptr;
		else
			return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
	}

	//MY FUNCTIONS: PRIVATE
	/** 
	*/

	/** Part 2A and 2B: Size
	 @post: returns total number of nodes in the tree.
	 Node count starts from node 0, i.e the root.
	 To include the root in node count return +1.
	*/
	int Size(BinaryNode* t) const{
		if(t == nullptr)
			return 0;
		return Size(t->left) + Size(t->right) + 1;
	}//end Size

	/** Part 2A: FindNode
		(Similar to Contains function except Contains just returns true or false)
		* Internal method to test if an item is in a subtree.
		* x is item to search for.
		* t is the node that roots the tree.
		If the value is found in the tree @post prints the value, else return "Not Found"
	 */
	void FindNode( const Comparable & x, BinaryNode* t ) const
	{
		if( t == nullptr )
			std::cout<< "Not Found" <<std::endl;
		else if( x < t->element ) //keeps traversing left and right until x value is found in tree
			FindNode( x, t->left ); //traverses left
		else if( t->element < x )
			FindNode( x, t->right ); //traverses right
		else
			std::cout<< t->element <<std::endl;    // Match
	}//end FindNode



	/** Part 2B: Find 
		Helper function for Part 4A: strings found in tree
		(Similar to Contains function)
		@returns true if sting is found. 
		*/
	bool Find( const string & x, BinaryNode* t ) const{
		if( t == nullptr )
			return false;
		else if( x.compare(t->element.ReturnString()) == 1 && t->left != nullptr) //if string x doesn't match root string && we can search left
			return Find( x, t->left );
		else if(x.compare(t->element.ReturnString()) == 1 && t->right != nullptr) //if string x doesn't match left string && we can search right
			return Find( x, t->right );
		else if( x.compare(t->element.ReturnString()) == 0)
			return true;
			
	}//end Find


	/** Part 2B: Depth
		Helper function for AvgDepth()
		Depth is the total height-rank value of nodes from the root node.
		(example: root height-rank is 0, parent = 1, leaf = 2)
		@returns Depth length
	*/
	int Depth(int x, BinaryNode* t){ //citing from source: pg 142 Data Structures txtbook
		if( t == nullptr )
			return 0;
		else
			return x + Depth(Size(t->left), t->left) + Depth((Size(t->left)), t->right) + 1;
			
    }//end Depth


	/** Part 2B: RemoveThirdSeq()
		Similar to remove function.
		Finds if @param x string is contained in tree.

		Removes every 3rd sequence in sequences.txt from the tree 
		@post true if successfully removed 
		 
	*/
	void RemoveThirdSeq( const Comparable & x, BinaryNode* & t ) const{
		/*if( !contains(x, t) )//DELETE MAYBE 
			std::cout<< "Not Found" <<std::endl;*/
		if( contains(x, t) )
			remove(x, t);

	}//end RemoveThirdSeq

	//END MY FUNCTIONS: PRIVATE
};

#endif
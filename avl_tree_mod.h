#ifndef AVL_TREE_MOD_H
#define AVL_TREE_MOD_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream> //additional for void print function

#include <string> //additional for compare() string
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
public:
	AvlTree( ) : root{ nullptr }
	{ }

	AvlTree( const AvlTree & rhs ) : root{ nullptr }
	{
		root = clone( rhs.root );
	}

	AvlTree( AvlTree && rhs ) : root{ rhs.root }
	{
		rhs.root = nullptr;
	}

	~AvlTree( )
	{
		makeEmpty( );
	}

	/**
		* Deep copy.
		*/
	AvlTree & operator=( const AvlTree & rhs )
	{
		AvlTree copy = rhs;
		std::swap( *this, copy );
		return *this;
	}

	/**
		* Move.
		*/
	AvlTree & operator=( AvlTree && rhs )
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
	void printTree( ) const
	{
		if( isEmpty( ) )
			cout << "Empty tree" << endl;
		else
			printTree( root );
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

	/** Part 2A and 2B: Size
		@returns total number of nodes in the tree.
	*/
	int Size() const{		
		return Size(root);
	}//end Size

	/** Part 2A: FindNode
		If the value is found in the tree 
		@post prints the value, else return "Not Found"
	*/
	void FindNode( const Comparable & x ) const
	{
		FindNode( x, root );
	}//end FindNode

	

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

	/** Part 2B: RemoveThirdSeq
		Similar to remove function.
		Removes every 3rd sequence in sequences.txt from the tree 
		@post true if successfully removed 
	*/
	void RemoveThirdSeq( const Comparable & x ){
		RemoveThirdSeq( x, root );
	}//end RemoveThirdSeq

	//END MY FUNCTIONS: PUBLIC

private:
	struct AvlNode
	{
		Comparable element;
		AvlNode   *left;
		AvlNode   *right;
		int       height;

		AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
			: element{ ele }, left{ lt }, right{ rt }, height{ h } { }

		AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
			: element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
	};

	AvlNode *root;

    

	


	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert( const Comparable & x, AvlNode * & t ) //*& pass by type: can take pointer, reference, or double object ptr
	{
		if( t == nullptr )
			t = new AvlNode{ x, nullptr, nullptr };
		else if( x < t->element )
			insert( x, t->left );
		else if( t->element < x )
			insert( x, t->right );
		else
			t->element.Merge(x);

		balance( t );
	}//end insert

	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert( Comparable && x, AvlNode * & t )//&& pass by Rvalue: literal expression
	{
		if( t == nullptr )
			t = new AvlNode{ std::move( x ), nullptr, nullptr };
		else if( x < t->element )
			insert( std::move( x ), t->left );
		else if( t->element < x )
			insert( std::move( x ), t->right );
		else  //ADDITIONAL CASE FOR MERGE 
			t->element.Merge(x);
		balance( t );
	}//end insert

	/**
	 * Internal method to remove from a subtree.
	 * x is the item to remove.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void remove( const Comparable & x, AvlNode * & t )
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
			AvlNode *oldNode = t;
			t = ( t->left != nullptr ) ? t->left : t->right;
			delete oldNode;
		}

		balance( t );
	}

	static const int ALLOWED_IMBALANCE = 1;

	// Assume t is balanced or within one of being balanced
	void balance( AvlNode * & t )
	{
		if( t == nullptr )
			return;

		if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ) {
			if( height( t->left->left ) >= height( t->left->right ) )
				rotateWithLeftChild( t );
			else
				doubleWithLeftChild( t );
		} else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ) {
			if( height( t->right->right ) >= height( t->right->left ) )
				rotateWithRightChild( t );
			else
				doubleWithRightChild( t );
		}
		t->height = max( height( t->left ), height( t->right ) ) + 1;
	}

	/**
	 * Internal method to find the smallest item in a subtree t.
	 * Return node containing the smallest item.
	 */
	AvlNode * findMin( AvlNode *t ) const
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
	AvlNode * findMax( AvlNode *t ) const
	{
		if( t != nullptr )
			while( t->right != nullptr )
				t = t->right;
		return t;
	}

	/**
	 * Internal method to test if an item is in a subtree.
	 * x is item to search for.
	 * t is the node that roots the tree.
	 */
	bool contains( const Comparable & x, AvlNode *t ) const
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
	    bool contains( const Comparable & x, AvlNode *t ) const
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
	void makeEmpty( AvlNode * & t )
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
	void printTree( AvlNode *t ) const
	{
		if( t != nullptr )
		{
			printTree( t->left );
			cout << t->element << endl;
			printTree( t->right );
		}
	}

	

	/**
	 * Internal method to clone subtree.
	 */
	AvlNode * clone( AvlNode *t ) const
	{
		if( t == nullptr )
			return nullptr;
		else
			return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
	}
	// Avl manipulations
	/**
	 * Return the height of node t or -1 if nullptr.
	 */
	int height( AvlNode *t ) const
	{
		return t == nullptr ? -1 : t->height;
	}

	int max( int lhs, int rhs ) const
	{
		return lhs > rhs ? lhs : rhs;
	}

	/**
	 * Rotate binary tree node with left child.
	 * For AVL trees, this is a single rotation for case 1.
	 * Update heights, then set new root.
	 */
	void rotateWithLeftChild( AvlNode * & k2 )
	{
		AvlNode *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
		k1->height = max( height( k1->left ), k2->height ) + 1;
		k2 = k1;
	}

	/**
	 * Rotate binary tree node with right child.
	 * For AVL trees, this is a single rotation for case 4.
	 * Update heights, then set new root.
	 */
	void rotateWithRightChild( AvlNode * & k1 )
	{
		AvlNode *k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
		k2->height = max( height( k2->right ), k1->height ) + 1;
		k1 = k2;
	}

    /*PART 2C rotate directly 
     alter doubleWithLeftChild so that instead of calling 2 single rotations
     it implements the rotations directly. 

    How to use Part 2C:
    Run the exact same code as in Part 2(b) but with your modified AVL implementation. 
    The executable should be named test_tree_mod. The results should be the same as in Part 2(b).
    */

	/**
	 * Double rotate binary tree node: first left child.
	 * with its right child; then node k3 with new left child.
	 * For AVL trees, this is a double rotation for case 2.
	 * Update heights, then set new root.
	 */
	void doubleWithLeftChild( AvlNode * & k3 )
	{ //LEFT->RIGHT->LEFT 

        /* PSEUDOCODE FOR rotateWithRightChild( k3->left );
        make new node ptr == param ->right to save value
        param ->right =  new node ptr->left
        new node ptr->left = param
        param->height = max(height(param->left),  height(param->right)) +1;
        //NOTE CHANGES IN SECOND LINE 
        new node ptr->height = max(height(new node ptr->right),  param->height) +1; 
        //LASTLY COMMIT CHANGE BY SETTING EQUAL
        param = new node ptr; 

        */
        

        AvlNode *k4 = new AvlNode{ " ", nullptr, nullptr };
        //where x is const Comparable &x
        
        k4 = &k3; //preserve value for 2nd rotation: rotateWithLeftChild

        AvlNode *k2 = k3->right;
		k3->right = k2->left;
		k2->left = k3;
		k3->height = max( height( k3->left ), height( k3->right ) ) + 1;
		k2->height = max( height( k2->right ), k3->height ) + 1;
		k3 = k2;
        
        //left child param = k2 ,change to k4
		//rotateWithLeftChild( k3 );
        AvlNode *k6 = k4->left;
		k4->left = k6->right;
		k6->right = k4;
		k4->height = max( height( k4->left ), height( k4->right ) ) + 1;
		k6->height = max( height( k6->left ), k4->height ) + 1;
		k4 = k6;
        
	}

	/**
	 * Double rotate binary tree node: first right child.
	 * with its left child; then node k1 with new right child.
	 * For AVL trees, this is a double rotation for case 3.
	 * Update heights, then set new root.
	 */
	void doubleWithRightChild( AvlNode * & k1 )
	{ //RIGHT->LEFT->RIGHT

        //left child param = k2 
		//rotateWithLeftChild( k1->right );
        
        AvlNode *k4 = new <AvlNode>();
        k4 = &k1; //preserve value for 2nd rotation: rotateWithLeftChild
        
        //change k1 to k 5
        //change k2 to k1
        AvlNode *k5 = k1->left;
		k1->left = k5->right;
		k5->right = k1;
		k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
		k5->height = max( height( k5->left ), k1->height ) + 1;
		k1 = k5;

        //right child param = k1, change k1 to k4
		//rotateWithRightChild( k1 );
        AvlNode *k2 = k4->right; //change k1 to k4
		k4->right = k2->left;
		k2->left = k4;
		k4->height = max( height( k4->left ), height( k4->right ) ) + 1;
		k2->height = max( height( k2->right ), k4->height ) + 1;
		k4 = k2;

        
	}

	//MY FUNCTIONS: PRIVATE
	/** 
	*/

	/** Part 2A and 2B: Size
	 @post: returns total number of nodes in the tree.
	 Node count starts from node 0, i.e the root.
	 To include the root in node count return +1.
	*/
	int Size(AvlNode* t) const{
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
	void FindNode( const Comparable & x, AvlNode *t ) const
	{
		if( t == nullptr )
			std::cout<< "Not Found" <<std::endl;
		else if( x < t->element ) //keeps traversing left and right until x value is found in tree
			FindNode( x, t->left ); //traverses left
		else if( t->element < x )
			FindNode( x, t->right ); //traverses right
		else
			std::cout<< t->element<<std::endl;    // Match
	}//end FindNode


	/** Part 2B: Find 
		Helper function for Part 4A: strings found in tree
		(Similar to Contains function)
		@returns true if sting is found. 
		*/
	bool Find( const string & x, AvlNode *t ) const{
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
	int Depth(int x, AvlNode* t){ //citing from source: pg 142 Data Structures txtbook
		if( t == nullptr )
			return 0;
		else
			return x + Depth(Size(t->left), t->left) + Depth((Size(t->left)), t->right) + 1;
			
    }//end Depth

	/** Part 2B: RemoveThirdSeq
		Similar to remove function.
		Finds if @param x string is contained in tree.

		Removes every 3rd sequence in sequences.txt from the tree 
		@post true if successfully removed 
		 
	*/
	void RemoveThirdSeq( const Comparable & x, AvlNode * & t ) const{
		/*if( !contains(x, t) )//DELETE MAYBE 
			std::cout<< "Not Found" <<std::endl;*/

		if( contains(x, t) )
			remove(x, t);

	}//end RemoveThirdSeq
	

	//END MY FUNCTIONS: PRIVATE
};

#endif

// Chloe Albright
// Main file for Part2(a) for Project 2.
// Code will compile and run after you have completed sequence_map.h.

#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <sstream> //ADDITIONAL
#include <fstream> //ADDITIONAL
#include <string>
using namespace std;

namespace {

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
	// Code for running Part2(a)
	// Parse input file @db_filename and feel tree @a_tree
	// Then prompt the user for exactly three strings (do a loop) and
	// provide the results of find() as described in the assignment.
	string input; //take in input line
	ifstream filename; //object to open db_filename
	filename.open(db_filename, ios::in); 
	//initiate filename to db_filename & start input operation

	
	/*
	AanI TTA'TAA
	AarI CACCTGCNNNN'NNNN
	AasI GACNNNN'NNGTC
	Line 1 should be:
	enzyme acro: AanI
	recogn seq: TTA'TAA
	 For each acronym and corresponding recognition sequence, 
	 you will create a SequenceMap containing the recognition sequence 
	 as its recognition_sequence_ and the enzyme acronym as the only string 
	 of its enzyme_acronyms_, and you will insert it into the tree.

	*/
	//if file is open read through it
	if(filename.is_open()){
		while(std::getline(filename, input)){
			string a_rec_seq; //fill sequence
			string an_enz_acro; //fill acronym
			std::stringstream sequence(input); //read string line
			std::getline(sequence, an_enz_acro, ' ');
			// std::cout<<an_enz_acro<<" "<<std::endl;//FOR TESTING
			while(std::getline(sequence, a_rec_seq, '\n')){
				SequenceMap new_node(a_rec_seq, an_enz_acro);
				a_tree.insert(new_node); //make tree node
				//FOR TESTING only prints out acro: a_tree.printNode(new_node);
			}
		}
	}

	string string1, string2, string3;
	std::cout<< "Enter THREE strings: " <<std::endl; 
	std::cin>>string1>>string2>>string3;
	SequenceMap node1(string1, " ");
	SequenceMap node2(string2, " ");
	SequenceMap node3(string3, " ");
	a_tree.FindNode(node1);
	a_tree.FindNode(node2);
	a_tree.FindNode(node3);

	//SequenceMap(const string &a_rec_seq, const string &an_enz_acro)
	//void FindNode( const Comparable & x, AvlNode *t ) const
}

}// end namespace

int
main(int argc, char **argv){
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
		return 0;
	}
	const string db_filename(argv[1]);
	const string param_tree(argv[2]);
	cout << "Input filename is " << db_filename << endl;
	cout << "Type of tree is " << param_tree << endl;
	if (param_tree == "BST") {
		BinarySearchTree<SequenceMap> a_tree;
		QueryTree(db_filename, a_tree);
	} else if (param_tree == "AVL") {
		AvlTree<SequenceMap> a_tree;
		QueryTree(db_filename, a_tree);
	} else {
		cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
	}
	return 0;
}

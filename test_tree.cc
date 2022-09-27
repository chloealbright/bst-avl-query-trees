// Chloe Albright
// Main file for Part2(a) for Project 2.
// Code will compile and run after you have completed sequence_map.h.

#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <fstream> //ADDITIONAL 
#include <sstream> //ADDITIONAL
#include <cmath> //additional for log2N
#include <string>
using namespace std;

namespace{

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree){
	// Code for running Part2(b)
	string input; //take in input line
	ifstream filename; //object to open db_filename
	//before filename.open(db_filename);
	filename.open(db_filename, ios::in); //Open rebase210.txt
	
	//initiate filename to db_filename & start input operation
	//if file is open read through it

	/*
	Part 2A & 2B: parses database and constructs a search tree
	prints num nodes in tree n, the enzyme acro
	*/

	if(filename.is_open()){ 
		while(std::getline(filename, input)){ 
			string a_rec_seq; //fill sequence
			string an_enz_acro; //fill acronym
			std::stringstream sequence(input); //read string line
			std::getline(sequence, an_enz_acro, ' ');
			//std::cout<<an_enz_acro<<" "<<std::endl;//FOR TESTING
			while(std::getline(sequence, a_rec_seq, '\n')){
				SequenceMap new_node(a_rec_seq, an_enz_acro);
				a_tree.insert(new_node); 
			}
		}
	}

	int size1 = a_tree.Size();
	int depth1 = a_tree.Depth();

	float avgDepth1 =  depth1 / size1;
	float depthRatio1 = avgDepth1 / log2(size1);
	//std::cout<< "test tree depth: "<< depth1 <<std::endl;
	std::cout<< "2: "<< size1 <<std::endl; //num of nodes
	//Note: passing int argument through float param should automatically convert to float
	//since I declared float infront of my function: float AvgDepth(float x) const
	std::cout<< "3a: "<< avgDepth1 <<std::endl; //avg depth
	std::cout<< "3b: "<< depthRatio1 <<std::endl; //avg depth ratio
	
	

	//Part 2B:

	//Part 4: total recursive calls for strings found and avg 
	string input2;
	ifstream filename2;
	filename2.open(seq_filename, ios::in); //Open sequences.txt
	//query = total num of strings found, i.e successful removes.
	//call = total recursive calls.
	//avg = avg recursive calls = call/query
	int query=0, string_count= 0, call=0;
	float avg;
	
	//compare each string in sequence txt with tree 
	if(filename2.is_open()){

		while(std::getline(filename2, input2)){
			string a_rec_seq2; //fill sequence
			std::stringstream sequence2(input2); //read string line
			while(std::getline(sequence2, a_rec_seq2, '\n')){
				string_count++;
				if(a_tree.Find(a_rec_seq2) == 0)
					query++;
				

			}
			
		}
	}
	avg = string_count / query; //total calls / strings matched
	int size2 = a_tree.Size();
	int depth2 = a_tree.Depth();

	//std::cout<< "test tree depth2: "<< depth2 <<std::endl;
	//std::cout<< "test string count: "<< string_count <<std::endl;
	std::cout<< "4a: "<< query <<std::endl; //total recurs calls for strings found
	std::cout<< "4b: "<< avg <<std::endl; //avg recurs calls for strings found
	


	//Part 5: total recursive calls for remove 3rd seq and avg
	//seq = total num of 3rd sequences removed.
	//call2 or newLine = total recursive calls.
	//avg2 = avg recursive calls = call2/seq
	int seq_removes = 0, seq_count= 0;
	float avg2;
	string input3;
	ifstream filename3;
	filename3.open(seq_filename, ios::in); //Open sequences.txt

	if(filename3.is_open()){ 
		while(std::getline(filename3, input3)){ 
			string a_rec_seq3; //fill sequence
			std::stringstream sequence3(input3); //read string line
			
			while(std::getline(sequence3, a_rec_seq3, '\n')){
				seq_count++;
				SequenceMap new_node3(a_rec_seq3, " ");
				if(seq_count%3==0){
					a_tree.remove(new_node3);
					seq_removes ++;

				}
						
			}

		}
	}
	avg2 = seq_count / seq_removes;
	int size3 = a_tree.Size();
	int depth3 = a_tree.Depth();

	float avgDepth2 = depth3 / size3;
	float depthRatio2 = avgDepth2 / log2(a_tree.Size());

	//std::cout<< "test tree depth3: "<< depth3 <<std::endl;
	//std::cout<< "test sequences removed: "<< seq_removes <<std::endl;
	std::cout<< "5a: "<< seq_count <<std::endl; //total recurs calls for remove 3rd seq
	std::cout<< "5b: "<< avg2<<std::endl; //avg recurs calls for remove 3rd seq
	std::cout<< "6a: "<< size3 <<std::endl; //repeat steps 2&3: num of nodes
	std::cout<< "6b: "<< avgDepth2 <<std::endl; //avg depth
	std::cout<< "6c: "<< depthRatio2  <<std::endl; //avg depth ratio




/*

 reference *output type*
	std::cout<< "2: "<< <integer> <<std::endl; //num of nodes
	std::cout<< "3a: "<< <float> <<std::endl; //avg depth
	std::cout<< "3b: "<< <float> <<std::endl; //avg depth ratio
	std::cout<< "4a: "<< <integer> <<std::endl; //total recurs calls for strings found
	std::cout<< "4b: "<< <float> <<std::endl; //avg recurs calls for strings found
	std::cout<< "5a: "<< <integer> <<std::endl; //total recurs calls for remove 3rd seq
	std::cout<< "5b: "<< <float> <<std::endl; //avg recurs calls for remove 3rd seq
	std::cout<< "6a: "<< <integer> <<std::endl; //repeat steps 2&3: num of nodes
	std::cout<< "6b: "<< <float> <<std::endl; //avg depth
	std::cout<< "6c: "<< <float> <<std::endl; //avg depth ratio
*/
}
    
}    // namespace

int 
main(int argc, char **argv){
	if (argc != 4) {
		cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
		return 0;
	}
	const string db_filename(argv[1]);
	const string seq_filename(argv[2]);
	const string param_tree(argv[3]);
	cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
	cout << "Type of tree is " << param_tree << endl;
	if (param_tree == "BST") {
		BinarySearchTree<SequenceMap> a_tree;
		TestTree(db_filename, seq_filename, a_tree);
	} else if (param_tree == "AVL") {
		AvlTree<SequenceMap> a_tree;
		TestTree(db_filename, seq_filename, a_tree);
	} else{
		cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
	} 
   return 0;
}


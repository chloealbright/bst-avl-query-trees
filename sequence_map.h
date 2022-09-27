/*
Name: Chloe Zambrano 
Professor Katchadourian
CSCi 335-01
Assign 2, Description: 
The class SequenceMap is used to compare the performance and implementation of 
self-balancing (height) AVL trees and Binary search trees (BST).
*/

#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SequenceMap
{
public:
     
    //Start Big 5 

    //Default constructor 
    SequenceMap() = default;
    
    //Destructor 
    ~SequenceMap() = default;

    //Copy constructor
    SequenceMap(const SequenceMap &rhs) = default;

    //Copy assignment
    SequenceMap& operator= (const SequenceMap &rhs) = default;

    //Move constructor 
    SequenceMap(SequenceMap &&rhs) = default;

    //Move assignment 
    SequenceMap& operator=(SequenceMap &&rhs) = default;

    //End Big Five 


    /** Constructor 
        Creates a SequenceMap from 2 strings such that 
        @private string recognition_sequence_ is set to @param a_rec_seq 
      & @private vector enzyme_acronyms_ contains the element @param an_enz_acro  
    */
    SequenceMap(const string &a_rec_seq, const string &an_enz_acro){
        recognition_sequence_ = a_rec_seq;
        enzyme_acronyms_.push_back(an_enz_acro);
    }//end Constructor

    /** operator<
        String comparison @returns true if recognition_sequence_ < @param rhs 
    */
    bool operator<(const SequenceMap &rhs) const{
        return (recognition_sequence_ < rhs.recognition_sequence_);

    }//end operator<

    /** operator>
        String comparison @returns true if recognition_sequence_ > @param rhs
    */
    bool operator>(const SequenceMap &rhs) const{
        return (recognition_sequence_ > rhs.recognition_sequence_);

    }//end operator>

    /** Output overload operator<< 
        @post prints enzyme acronyms  
    */
    friend std::ostream &operator<<(std::ostream &out, SequenceMap &other_sequence){
        if(other_sequence.enzyme_acronyms_.size()==0){
            out<<"empty"<<std::endl;
            return out;
        }
        for(size_t i = 0; i < other_sequence.enzyme_acronyms_.size(); i++){
            out<<other_sequence.enzyme_acronyms_[i]<<" ";
        }
        //out<<std::endl;
        return out;

    }//end operator<<

    /** Input overload operator>>
        @post reads a vector sequence from an input stream
    */
    /*friend std::istream &operator>>(std::istream &in, SequenceMap &other_sequence){

        string input;

        while(in >> input){
            enzyme_acronyms_.pushback(other_sequence.enzyme_acronyms_[i]);
        }

        return in;
    

        
        //referenced from class lecture & assign 1; 
       int size = other_sequence.enzyme_acronyms_.size();
       if(size > 0){
           other_sequence.enzyme_acronyms_.clear(); //make vector size 0
       }

       in>>other_sequence.enzyme_acronyms_.size;

       for(size_t i = 0; other_sequence.enzyme_acronyms_.size() > i; i++){
           in>> enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]); 
       } 
       std::cout<<std::endl;
       return in;
    } */
    //end operator>>

    //MY FUNCTIONS: PUBLIC

    /** Merge
        Case for handling duplicate sequences, i.e the sequences are equal:
        @post Merges the @param other_sequence.enzyme_acronym_ with the object’s enzyme_acronym_. 
        The other_sequence object isn't affected.
    */
    void Merge(const SequenceMap &other_sequence){
        for(size_t i = 0; i < other_sequence.enzyme_acronyms_.size(); i++){
            enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
        }
    }//end Merge

    
    /** ReturnString
        Helper function for Part2B: 4A total matched strings from sequence.txt
        @returns recognition_sequence
    */
    string ReturnString() const{
        return recognition_sequence_;
    }

    

    //END MY FUNCTIONS: PUBLIC
    


private:
    string recognition_sequence_;
    vector<string> enzyme_acronyms_;
};

#endif
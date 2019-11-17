//
//  main.cpp
//  Project_Three
//
//  Created by Srishti Dhawan on 7/26/19.
//  Copyright © 2019 Srishti Dhawan. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in


int loadWords(istream &dictfile, string dict[]);
bool findWord (string word, const string dict[], int top, int bot);
void swapme (char & a, char & b) ;
void permute(string a, int front, int end, const string dict[], int dict_total, int &matched, string results[]);
void Loop (string &a, int i, int front, int end, const string dict[], int dict_total, int &matched, string results[]);
int recBlends(string word, const string dict[], int size, string results[]) ;
void showResults(const string results[], int size);
bool checkWord (int i, int max, string b ,string results[] );


//Adds all the words from dictfile into an array of strings called dict
int loadWords(istream &dictfile, string dict[]) {
    string data;

    if (dictfile.eof()) { // end of dictfile
        return 0;
    }

    dictfile >> data;
    // uses recursion to loop to the end of dictfile (dict starts with Z)
    int x = loadWords(dictfile, dict);
    if (x < MAXDICTWORDS) {
        dict[x] = data;
        x++;
        return x;
    }
    else
        return MAXDICTWORDS; //reached max capacity of array
}

//Checks if a word is in the array dict[]
bool findWord (string word, const string dict[], int top, int bot) {
    if (top>bot) {
        return false;// string not found
    }
    else {
        int mid = (top + bot)/2;
        string check = dict[mid];
        check[0] = tolower(check[0]); // makes all words lowecase
        if (word.compare(check)==0)  {
            return true;
        }
        else if (word.compare(check) >0) {
            return findWord (word, dict, top, mid-1);
        }
        else if (word.compare(check) < 0) {
            return findWord (word, dict, mid+1, bot);
        }
    }
    return true;
}

//Swaps 2 characters in a word
void swapme (char & a, char & b)  {
    char temp = a;
    a = b;
    b = temp;
}

// Finds all the permutations of a word
void permute(string a, int front, int end, const string dict[], int dict_total, int &matched, string results[])
{
    if (front == end) // found a possible permutation
    {
        if (findWord(a, dict ,0, dict_total)) // check if word exists
        {
            if (!(checkWord(0, matched, a, results))) // check if word is already in results
            {
                results[matched] = a;
                matched++;
            }
        }
    }
    else
    {
        Loop (a, front, front, end, dict, dict_total, matched, results);
    }
}

void Loop(string &a, int i, int front, int end, const string dict[], int dict_total, int &matched, string results[]) {
    if (i > end)
        return;
    // for all remaining letters (i) this loop continues and permutes all possible anagrams
    swapme(a[front], a[i]);
    permute(a, front+1, end, dict, dict_total, matched, results);
    // returns back the switch so that the next loop can swap 2 different characters
    swapme(a[front], a[i]);
    //replaces the for loop by incrementing i in every call until it reaches "max" or end
    Loop(a, (i+1), front, end, dict, dict_total, matched, results);

}

// main function used to find the number of anagrams formed from a given string
// puts the anagrams in an array called results
int recBlends(string word, const string dict[], int size, string results[]) {
    int back = word.size()- 1;
    int matched = 0;
    permute (word, 0, back, dict, size, matched, results );
    
    return matched;
}

// Prints all the strings in results
void showResults(const string results[], int size) {
    if (size-1 <0)
        return;
    cout << "Matching word " << results[size-1] << endl;
    showResults(results, size-1);
    
}
// checks if a word exists in results already (avoids doubling ex: kool gives look twice
bool checkWord (int i, int max, string b ,string results[] ) {
    if (i == max)
        return false;
    if (b.compare(results[i]) == 0 )
        return true;
    checkWord (i+1, max, b, results);
    return false;
}

int main()
{
    
    
//    string results[MAXRESULTS];
//    string dict[MAXDICTWORDS];
//    ifstream dictfile;         // file containing the list of words
//    int nwords;                // number of words read from dictionary
//    string word;
//
//    dictfile.open("words.txt");
//    if (!dictfile) {
//        cout << "File not found!" << endl;
//        return (1);
//    }
//
//    nwords = loadWords(dictfile, dict);
//
//
//    cout << "Please enter a string for an anagram: ";
//    cin >> word;
//
//    int numMatches = recBlends(word, dict, nwords, results);
//    if (!numMatches)
//        cout << "No matches found" << endl;
//    else
//        showResults(results, numMatches);
    
    
    string results3[5];
    string exampleDict[] = { "moe", "kool", "dee"};
    int numResults = recBlends("kloo", exampleDict, 3, results3);
    cout << numResults << endl;
    assert(numResults == 1 && results3[0] == "kool");
    cout << "woot" << endl;
    return 0;
}


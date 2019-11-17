//
//  main.cpp
//  Project_Two
//
//  Created by Srishti Dhawan on 7/15/19.
//  Copyright © 2019 Srishti Dhawan. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include "BballRoster.h"
using namespace std;


int main() {
//    cout << "hi " << endl;
//    BballRoster lakers;
//    lakers.signPlayer ("LeBron", "James", "6");
//    lakers.signPlayer ("Anthony", "Davis", "23");
//    lakers.signPlayer ("Kyle", "Kuzma", "0");
//    lakers.signPlayer ("Boogie", "Cousins", "15");
//    lakers.signPlayer ("Rajon", "Rondo", "8");
//
//    BballRoster const lakers1 = lakers;
//
//    BballRoster lakerstwo;
//    lakerstwo.signPlayer ("LeBron", "James", "10");
//    lakerstwo.signPlayer ("Josh", "Jones", "23");
//    lakerstwo.signPlayer ("Ryan", "Kids", "0");
//    lakerstwo.signPlayer ("Boogie", "Cousins", "15");
//    lakerstwo.signPlayer ("Rajon", "Rondo", "8");
//
//    BballRoster const lakers2 = lakerstwo;
//
//    BballRoster team;
//
//    joinRosters( lakers1, lakers2, team);
//
//    BballRoster teamtwo;
//    team.signPlayer("s", "d", "5");
//
//
//
//    cout << "bye" << endl;

    
    // default constructor
    BballRoster lal;
    // For an empty list:
    assert(lal.rosterEmpty()); // test empty
    assert(lal.howManyPlayers() == 0); // test size
    assert(!lal.resignPlayer("LeBron", "James", "23")); // no player
    assert(!lal.renouncePlayer("LeBron", "James")); // nothing to erase
    string firstone;
    string lastone;
    SomeType valone;
    assert(!lal.choosePlayer(5, firstone, lastone , valone));
    
    

    //Lists with players
    BballRoster lakers; // constructor
    //adds players to lakers in alphabetical order
    lakers.signPlayer ("LeBron", "James", "6");
    lakers.signPlayer ("Anthony", "Davis", "23");
    lakers.signPlayer ("Kyle", "Kuzma", "0");
    lakers.signPlayer ("Boogie", "Cousins", "15");
    lakers.signPlayer ("Rajon", "Rondo", "8");
    BballRoster const lakers1 = lakers;

    assert(lakers.resignPlayer("LeBron", "James", "10")); //checks for an existent player
    assert(!lakers.resignPlayer("Bob", "Smith", "10")); //checks for a nonexistent player
    
    lakers.signOrResign("Anthony", "Davis", "10"); //checks for an existent player
    lakers.signOrResign("Bob", "Smith", "10"); //adds a nonexistent player
    
    assert(lakers.renouncePlayer("Kyle", "Kuzma")); //checks for an existent player
    assert( !(lakers.renouncePlayer("Bobby", "Smith"))); //checks for a nonexistent player
    
    //checks the choose player function for a list
    for (int n = 0; n < lakers.howManyPlayers(); n++)
    {
        string first;
        string last;
        SomeType val;
        lakers.choosePlayer (n, first, last, val);
        cout << first << " " << last << " " << val << endl;
    }
    
    BballRoster raptors;
    assert(raptors.signPlayer("Pascal", "Siakam", "43"));
    assert(raptors.signPlayer("Kyle", "Lowry", "7"));
    assert(raptors.howManyPlayers() == 2); //confirms size of a not empty list
    
    
    BballRoster lakerstwo; //constructor
    //adds players to lakerstwo in alphabetical order
    lakerstwo.signPlayer ("LeBron", "James", "10");
    lakerstwo.signPlayer ("Josh", "Jones", "23");
    lakerstwo.signPlayer ("Ryan", "Kids", "0");
    lakerstwo.signPlayer ("Boogie", "Cousins", "15");
    lakerstwo.signPlayer ("Rajon", "Rondo", "8");
    
    assert(lakerstwo.playerOnRoster("Josh", "Jones"));// checks for an existent player
    assert(!lakerstwo.playerOnRoster("bob", "saget")); // checks for a nonexistent player
    string first, last;
    SomeType a;
    assert(raptors.choosePlayer(0, first, last, a) && a == "7"); // changes value of a
    assert(raptors.choosePlayer(1, first, last, a) && (first == "Pascal" && a == "43")); //checks value of first and a
    
    BballRoster const lakers2 = lakerstwo;
    
    
    BballRoster team;     //constructor
    
    assert (!joinRosters( lakers1, lakers2, team)); // checks if joinRosters works with 2 lists
    
    
    BballRoster swapcheck;
    swapcheck.signPlayer ("LeBron", "James", "6");
    swapcheck.signPlayer ("Anthony", "Davis", "23");
    
    BballRoster checkswap;
    checkswap.signPlayer ("Kyle", "Kuzma", "0");
    checkswap.signPlayer ("Boogie", "Cousins", "15");
    
    swapcheck.swapRoster(checkswap);
    
    //confirm that swapRoster swaps the two lists
    for (int n = 0; n < checkswap.howManyPlayers(); n++)
    {
        string first;
        string last;
        SomeType val;
        checkswap.choosePlayer (n, first, last, val);
        cout << first << " " << last << " " << val << endl;
    }
    cout <<"woot" <<endl;

    return 0;
}



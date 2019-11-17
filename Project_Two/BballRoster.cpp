//
//  BballRoster.cpp
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

//constructor
BballRoster ::  BballRoster() {
    head.next = &tail;
    tail.prev = &head;
}

//destructor
BballRoster :: ~BballRoster() {
    Node *temp = &head;
    Node *h = &head;
    h= h->next;
    while (h != nullptr && h != &tail && h->next != nullptr){
        temp = h;
        h = h->next;
        if (temp == nullptr) {
            return;
        }
        delete temp;
    }
}


//copy constructor
BballRoster :: BballRoster (const BballRoster & org) {
    
    if (org.head.next == nullptr) {
        head.m_value = nullptr;
    }
    if (this == &org) {
        return;
    }
    
    
    Node const* p = &(org.head);
    head.m_value = "";
    tail.m_value = "";
    head.next = &tail;
    tail.prev = &head;
    Node *top = &head;
    while (p != &(org.tail)) {
        Node *added = new Node;
        added->m_first = p->m_first;
        added->m_last = p->m_last;
        added->m_value = p->m_value;
        added->next = &tail;
        tail.prev = added;
        added->prev = top;
        top->next = added;
        top = top->next;
        p = p->next;
    }
    
    
}

//assignment operator
const BballRoster& BballRoster ::operator=(const BballRoster& org) {
   
    
    if (this == &org) {
        return *this;
    }
    
    Node * h = &head;
    Node * temp = &head;
    
    while ( h != &tail) {
        h = h->next;
        delete temp;
        temp = h;
    }
    delete h;
    
    BballRoster tempo(org);
    swapRoster(tempo);
    
    return *this;
}


//done
bool BballRoster ::rosterEmpty() const {
    if (head.next == &tail) {
        return true;
    }
    return false;
}

//done
int BballRoster ::howManyPlayers() const{
    if (head.next == &tail) {
        return 0;
    }
    int team_size = 0;
    Node *p = head.next;
    while (p != &tail) {
        team_size++;
        p = p->next;
    }
    return team_size;
}

//add a new player
bool BballRoster ::signPlayer(const std::string& firstName, const std::string&
                              lastName, const SomeType& value){
    //create a new node to carry the player's info
    Node *add = new Node;
    add->m_first = firstName;
    add->m_last = lastName;
    add->m_value = value;
    
    if (head.next == &tail) {
        addNode(&head, add);
        return true;
    }
    Node *p = &head;
 
    //go to the right point in the current LinkedList (either last or
    // right when lastName > than the lastName on that linked list)
    while (p->next!= &tail && p->next != nullptr && lastName > p->next->m_last) {
        p= p->next;
    }
    if (p->next == &tail || p->next == nullptr) {
        addNode(p,add);
        return true;
    }
    if (p->next != &tail && p->next != nullptr && lastName < p->next->m_last) {
        addNode(p,add);
        return true;
    }
    //Same last names --> find out where the first name is
    if (p->next != &tail && p->next != nullptr && lastName == p->next->m_last) {
        while (firstName > p->next->m_first) {
            p = p->next;
        }
        if (firstName < p->next->m_first) {
            addNode(p,add);
            return true;
        }
        //if both first and last name match, dont add and return false
        if (firstName == p->next->m_first) {
            delete add;
            return false;
        }
    }
    return false;
}
//change player's value if he is present in the roster
bool BballRoster ::resignPlayer(const std::string& firstName, const std::string&
                                lastName, const SomeType& value){
    Node * p = head.next;
    while (p != &tail) {
        if (p->m_first == firstName && p->m_last == lastName) {
            p->m_value = value;
            return true;
        }
        p = p->next;
    }
    return false;
}

//if the player is not present, add him
//if the player is present, change his value
bool BballRoster ::signOrResign(const std::string& firstName, const std::string&
                                lastName, const SomeType& value){
    if (!resignPlayer(firstName, lastName, value)) {
        signPlayer(firstName, lastName, value);
    }
    return true;
}

//remove player if present
bool BballRoster ::renouncePlayer(const std::string& firstName, const
                                  std::string& lastName){
    
    Node* bye = head.next;
    // search for player
    while (bye != &tail) {
        if (bye->m_first == firstName && bye->m_last == lastName) {
            //skip over player
            bye->prev->next = bye->next;
            bye->next->prev = bye->prev;
            delete bye;
            return true;
        }
        bye = bye->next;
    }
    return false;
}

//look for player in the list
bool BballRoster ::playerOnRoster(const std::string& firstName, const
                                  std::string& lastName) const{
    Node * p = head.next;
    while (p != &tail) {
        if (p->m_first == firstName && p->m_last == lastName) {
            return true;
        }
        p = p->next;
    }
    return false;
}

//if player is present, change value to the players m_value
bool BballRoster ::lookupPlayer(const std::string& firstName, const std::string&
                                lastName, SomeType& value) const{
    Node * p = head.next;
    while (p != &tail) {
        if (p->m_first == firstName && p->m_last == lastName) {
            value = p->m_value;
            return true;
        }
        p = p->next;
    }
    return false;
}

//find the player @ node i and give its firstName, lastName, and value
bool BballRoster ::choosePlayer(int i, std::string& firstName, std::string&
                                lastName, SomeType& value) const{
    if (i< 0 || i>= howManyPlayers())
        return false;
    
    Node* p = head.next;
    int x = 0;
    while (x != i) {
        p = p->next;
        x++;
    }
    firstName = p->m_first;
    lastName = p->m_last;
    value = p->m_value;
    
    return true;
}

// swaps two rosters
void BballRoster ::swapRoster(BballRoster& other){
    Node *temp = head.next;
    head.next = other.head.next;
    other.head.next = temp;
}

//done
void BballRoster:: dump() const {
    Node* p = head.next;
    while (p != nullptr || p!= &tail  ) {
        cerr << p->m_last << " " << p->m_first << " " << p->m_value << endl;
        if (p->next == nullptr)
            break;
        p = p->next;
    }
    cerr << "reached the end" << endl;
}

// combines two rosters without duplicates
bool joinRosters(const BballRoster & bbOne,
                 const BballRoster & bbTwo,
                 BballRoster & bbJoined) {
    
    BballRoster *temporary = new BballRoster;
    
    int pplbbOne = bbOne.howManyPlayers();
    int pplbbTwo = bbTwo.howManyPlayers();
    string fName;
    string lName;
    SomeType valOne;
    SomeType valTwo;
    int boolnum = 0;
    
    //loop through bbOne
    for (int i = 0; i < pplbbOne; i++) {
        bbOne.choosePlayer(i, fName, lName, valOne);
        if (bbTwo.lookupPlayer(fName, lName, valTwo)) {
            if (valOne == valTwo) {
                temporary->signPlayer(fName, lName, valOne);
            }
            else {
                boolnum++;
            }
        }
        else {
            temporary->signPlayer(fName, lName, valOne);
        }
    }
    
    //loop through bbTwo
    for (int i = 0; i < pplbbTwo; i++) {
        bbTwo.choosePlayer(i, fName, lName, valTwo);
        if (bbOne.lookupPlayer(fName, lName, valOne)) {
            if (valTwo != valOne) {
                boolnum++;
            }
            continue;
        }
        temporary->signPlayer(fName, lName, valTwo);
    }
    
    
    //swap temp with bbRoster & delete temp
    bbJoined.swapRoster(*temporary);
    delete temporary;
    
    //check for same name but diff values 
    if (boolnum > 0) {
        return false;
    }
    return true;
}

// looks for players of a given first and/or last name given
void checkRoster (const std::string& fsearch,
                  const std::string& lsearch,
                  const BballRoster& bbOne,
                  BballRoster& bbResult) {
    
    
    string fName;
    string lName;
    SomeType val;
    
    BballRoster* temp = new BballRoster;
    
    //first name and last name are given
    if (fsearch != "*" && lsearch != "*"){
        for (int i =0; i <bbOne.howManyPlayers(); i++){
            bbOne.choosePlayer(i, fName, lName, val);
            if (fName == fsearch && lName == lsearch) {
                temp->signPlayer(fName, lName, val);
            }
        }
    }
    //only last name is given
    else if (fsearch == "*" && lsearch != "*"){
        for (int i =0; i <bbOne.howManyPlayers(); i++){
            bbOne.choosePlayer(i, fName, lName, val);
            if (lName == lsearch) {
                temp->signPlayer(fName, lName, val);
            }
        }
    }
    //only first name is given
    else if (fsearch != "*" && lsearch == "*"){
        for (int i =0; i <bbOne.howManyPlayers(); i++){
            bbOne.choosePlayer(i, fName, lName, val);
            if (fName == fsearch) {
                temp->signPlayer(fName, lName, val);
            }
        }
    }
    //neither names are given
    else if (fsearch == "*" && lsearch == "*" ){
        // if its an alias, just return
        if (&bbOne == &bbResult) {
            return;
        }
        for (int i =0; i <bbOne.howManyPlayers(); i++){
            bbOne.choosePlayer(i, fName, lName, val);
            temp->signPlayer(fName, lName, val);
        }
    }
    //swaps the temp with the actual roster and deletes temp
    bbResult.swapRoster(*temp);
    delete temp;
}

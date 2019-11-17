//
//  BballRoster.h
//  Project_Two
//
//  Created by Srishti Dhawan on 7/15/19.
//  Copyright © 2019 Srishti Dhawan. All rights reserved.
//

#ifndef BballRoster_h
#define BballRoster_h

#include <string>


typedef std::string SomeType;

struct Node {
    std::string m_first;
    std::string m_last;
    SomeType m_value;
    Node* next;
    Node* prev;
};

class BballRoster
{
private:
    
    Node head;
    Node tail;
    
    //adds a Node after p
    void addNode (Node *p, Node* add){
        add->next = p->next;
        add->prev = p;
        if(p->next != nullptr)
            p->next->prev = add;
        p->next = add;
    }
    
public:
    BballRoster();// Create an empty BballRoster list
    //destructor
    ~BballRoster();
    //copy constructor
    BballRoster (const BballRoster & org);
    
    //assignment operator
    const BballRoster& operator=(const BballRoster& org);
    
    bool rosterEmpty() const; // Return true if the BballRoster list
    // is empty, otherwise false.
    int howManyPlayers() const; // Return the number of players in
    // the BballRoster list.
    bool signPlayer(const std::string& firstName, const std::string&
                    lastName, const SomeType& value);
    // If the full name (both the first and last name) is not equal
    // to any full name currently in the list then add it and return
    // true. Elements should be added according to their last name.
    // Elements with the same last name should be added according to
    // their first names. Otherwise, make no change to the list and
    // return false (indicating that the name is already in the
    // list).
//    The signPlayer function primarily places elements so that
//    they are sorted in the list based on last name. If there are
//    multiple entries with the same last name then those
//    elements, with the same last name, are added so that they
//    are sorted by their first name.
    
    bool resignPlayer(const std::string& firstName, const std::string&
                      lastName, const SomeType& value);
    // If the full name is equal to a full name currently in the
    // list, then make that full name no longer map to the value it
    // currently maps to, but instead map to the value of the third
    // parameter; return true in this case. Otherwise, make no
    // change to the list and return false.
    bool signOrResign(const std::string& firstName, const std::string&
                      lastName, const SomeType& value);
    // If full name is equal to a name currently in the list, then
    // make that full name no longer map to the value it currently
    // maps to, but instead map to the value of the third parameter;
    // return true in this case. If the full name is not equal to
    // any full name currently in the list then add it and return
    // true. In fact, this function always returns true.
    bool renouncePlayer(const std::string& firstName, const
                        std::string& lastName);
    // If the full name is equal to a full name currently in the
    // list, remove the full name and value from the list and return
    // true. Otherwise, make no change to the list and return
    // false.
    bool playerOnRoster(const std::string& firstName, const
                        std::string& lastName) const;
    // Return true if the full name is equal to a full name
    // currently in the list, otherwise false.
    bool lookupPlayer(const std::string& firstName, const std::string&
                      lastName, SomeType& value) const;
    // If the full name is equal to a full name currently in the
    // list, set value to the value in the list that that full name
    // maps to, and return true. Otherwise, make no change to the
    // value parameter of this function and return false.
    bool choosePlayer(int i, std::string& firstName, std::string&
                      lastName, SomeType& value) const;
    // If 0 <= i < size(), copy into firstName, lastName and value
    // parameters the corresponding information of the element at
    // position i in the list and return true. Otherwise, leave the
    // parameters unchanged and return false. (See below for details
    // about this function.)
    
    void swapRoster(BballRoster& other);
    // Exchange the contents of this list with the other one.
    
    void dump () const;
};

bool joinRosters(const BballRoster & bbOne,
                 const BballRoster & bbTwo,
                 BballRoster & bbJoined);

void checkRoster (const std::string& fsearch,
                  const std::string& lsearch,
                  const BballRoster& bbOne,
                  BballRoster& bbResult);

#endif /* BballRoster_h */

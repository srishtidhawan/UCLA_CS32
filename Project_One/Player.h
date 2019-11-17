//
//  Player.h
//  Project_One
//
//  Created by Srishti Dhawan on 7/5/19.
//  Copyright © 2019 Srishti Dhawan. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <string>

class Arena;

class Player
{
public:
    // Constructor
    Player(Arena *ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;
    
    // Mutators
    std::string takeComputerChosenTurn();
    void   stand();
    void   move(int dir);
    bool   shoot(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_age;
    bool   m_dead;
    
    int    computeDanger(int r, int c) const;
};


#endif /* Player_h */

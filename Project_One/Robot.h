//
//  Robot.h
//  Project_One
//
//  Created by Srishti Dhawan on 7/5/19.
//  Copyright © 2019 Srishti Dhawan. All rights reserved.
//

#ifndef Robot_h
#define Robot_h

class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Robot declaration.

class Robot
{
public:
    // Constructor
    Robot(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool takeDamageAndLive();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
};


#endif /* Robot_h */

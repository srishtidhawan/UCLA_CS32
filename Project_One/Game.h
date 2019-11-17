//
//  Game.h
//  Project_One
//
//  Created by Srishti Dhawan on 7/5/19.
//  Copyright © 2019 Srishti Dhawan. All rights reserved.
//

#ifndef Game_h
#define Game_h

class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};


#endif /* Game_h */

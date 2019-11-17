#ifndef ACTOR_H_
#define ACTOR_H_

#include "GameConstants.h"
#include "GraphObject.h"
#include "StudentWorld.h"


// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor: public GraphObject {
public:
    Actor (StudentWorld *world, int startingX, int startingY, int imageID, Direction dir, double size, unsigned int depth);
    virtual ~Actor();
    
    bool isAlive();
    void moveTo(int x, int y);
    void dead();
    StudentWorld* returnWorld();
    
    virtual void incAnnoyed(int hitPoints);
    virtual void doSomething() = 0;
    
private:
    bool m_alive;
    StudentWorld* m_world;
};


class Human: public Actor {
public:
    Human (StudentWorld * world, int imageID, int startingX, int startingY, Direction dir, int hitPoints);
    int getHitPoints();
    void decHitPoints(int points);
    
    virtual void incAnnoyed(int hitPoints) = 0;
    virtual void moveDirection(Direction direction) = 0;
private:
    int m_hitPoints;
};


class TunnelMan: public Human {
public:
    TunnelMan(StudentWorld*world);
    int getWater();
    int getSonar();
    int getGold();
    
    void squirt();
    void addActor(int imageID);
    
    virtual void doSomething ();
    virtual void incAnnoyed (int hitPoints);
    virtual void moveDirection( Direction direction);
    
private:
    int m_water;
    int m_sonar;
    int m_gold;
};

class Earth: public Actor {
public:
    Earth(StudentWorld* world, int startingX, int startingY);
    virtual void doSomething();
};

class Boulder: public Actor {
public:
    Boulder(StudentWorld*world, int startingX, int startingY);
    
    virtual void doSomething();
private:
    bool m_stable;
    bool m_Falling;
    int m_ticks;
};

class Squirt: public Actor {
public:
    Squirt(StudentWorld*world, int startingX, int startingY, Direction dir);
    bool annoyProt();
    virtual void doSomething();
private:
    int m_distance;
};


class PickMeUp: public Actor {
public:
    PickMeUp(StudentWorld * world, int imageID, int startingX, int startingY);
    virtual void doSomething()=0;
    virtual void tickLifeTime(int ticks);
private:
    int m_ticks;
};

class Barrel : public PickMeUp {
public:
    Barrel(StudentWorld* world, int startingX, int startingY);
    virtual void doSomething();
};

class Gold: public PickMeUp {
public:
    Gold (StudentWorld * world, int startingX, int startingY, bool visible, bool tunnelPickUp);
    virtual void doSomething();
private:
    bool m_picker;
};

class Goodie: public PickMeUp {
public:
    Goodie(StudentWorld* world, int imageID, int startingX, int startingY);
    virtual void doSomething();
};

class Sonar: public Goodie {
public:
    Sonar (StudentWorld* world, int startingX, int startingY);
};

class WaterPool: public Goodie {
public:
    WaterPool ( StudentWorld * world, int startingX, int startingY);
};

class Protester: public Human {
public:
    Protester (StudentWorld *world, int imageID, int hitPoints);
    virtual void doSomething();
    void decTicksToWait();
    void beBribed();
    void moveTowardExit();
    void decTicksSinceYell();
    int ret_ticksSinceYell();
    bool confirmDirection();
    bool inALine(Direction direction);
    void moveOneStep(Direction direction);
    Direction randomDirection();
    bool canIMoveInDirection(int c, int r, Direction direction);
    bool atIntersection();
    virtual void incAnnoyed(int hitPoints) ;
    virtual void moveDirection(Direction direction);



private:
    bool m_leaveField;
    int m_numSquaresMove;
    int m_ticksToWait;
    int m_ticksSincePerpTurn;
    int m_ticksSinceYell;
    
};

class RegProtester: public Protester {
public:
    RegProtester(StudentWorld* world);
};

class HardcoreProtester: public Protester {
public:
    HardcoreProtester(StudentWorld *world);
    
};

#endif // ACTOR_H_

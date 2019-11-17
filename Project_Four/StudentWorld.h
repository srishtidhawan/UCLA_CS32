#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include "Actor.h"
#include "GraphObject.h"
#include <queue>

class GraphObject;
class Earth;
class TunnelMan;
class Protester;
class Actor;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    ~StudentWorld();
    
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    bool aroundEarth(int c, int r);
    void addProtesters();
    void addGoodies();
    void cleanActors();
    std::string formatDisplay(int level, int lives, int health, int squirts, int gold, int barrelsLeft, int sonar, int score);
    void updateStatusText();
    bool actorsInRad(int c, int r, int radius);
    void showActors(int c, int r, int radius);
    void addActor(Actor* newActor);
    bool checkRadius(int c1, int r1, int c2, int r2, int radius );
    bool nearbyBoulder(int c, int r, int radius=3);
    bool clearEarth (int c, int r);
    bool earthBelow (int c, int r);
    bool playerInRad(Actor *actor, int radius);
    TunnelMan* getPlayer();
    bool protinRad(Actor* actor, int radius);
    bool nearbyEarth(int c, int r);
    Protester* protesterInRad(Actor* actor, int radius);
    void foundBarrel();
    void decProtester();
    void addNewActor(Actor* actor);
    void addBoulder(int num);
    void addGold(int num);
    void addBarrel(int num);
    int numBarrel();
    void decBarrel();

    
private:
    TunnelMan* m_player;
    std::vector<Actor*> m_actors;
    Earth* m_earth[64][64];
    int m_maze[64][64];
    bool m_firstTick;
    int m_ticksSoFar;
    int m_numProtesters;
    int m_numBarrels;
    
    struct Grid {
        int c;
        int r;
        Grid(int x, int y): c(x), r(y) {}
    };
};

#endif // STUDENTWORLD_H_

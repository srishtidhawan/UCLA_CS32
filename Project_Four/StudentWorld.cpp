#include "StudentWorld.h"
#include <string>
using namespace std;



#include "Actor.h"
#include "GraphObject.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>


GameWorld* createStudentWorld(string assetDir) {
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(std::string assetDir): GameWorld(assetDir), m_firstTick(true), m_ticksSoFar(0), m_numProtesters(0), m_player(nullptr), m_numBarrels(0) { }

StudentWorld:: ~StudentWorld(){
    cleanUp();
}

int StudentWorld::init() {
    m_firstTick = true;
    m_ticksSoFar = 0;
    m_numProtesters = 0;
    m_numBarrels = 0;
    m_player = new TunnelMan(this);
    
    int c = 0;
    int r = 0;
    while (c <64) {
        while (r<60) {
            if (c <30 || c >33 || r<4) {
                m_earth[c][r] = new Earth(this, c, r);
            }
            r++;
        }
        c++;
    }
    
    //game objects in field
    int B = min((int)getLevel() / 2 + 2, 9);
    int G = max(5-(int)getLevel() / 2, 2);
    int L = min(2 + (int)getLevel(), 21);
    
    addBoulder(B);
    addGold(G);
    addBarrel(L);
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld:: move() {
    updateStatusText();

    vector<Actor*>:: iterator ptr;
    for (ptr = m_actors.begin(); ptr!= m_actors.end(); ptr++) {
        if ((*ptr) -> isAlive()) {
            (*ptr)->doSomething();
        }
        if(!m_player->isAlive()) {
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
        if (m_numBarrels == 0) {
            playSound(SOUND_FINISHED_LEVEL);
            return GWSTATUS_FINISHED_LEVEL;
        }
    }
    m_player->doSomething();
    

    addProtesters();
    addGoodies();
    
    cleanActors();
    
    return GWSTATUS_CONTINUE_GAME;

}

void StudentWorld:: cleanUp() {
    vector<Actor*> :: iterator ptr = m_actors.begin();
    while (ptr != m_actors.end()) {
        delete *ptr;
        ptr++;
    }
    m_actors.clear();
    int c;
    int r;
    for (c=0; c<64; c++) {
        for (r = 0; r<60 ; r++ )
            delete m_earth[c][r];
    }
    delete m_player;
}

void StudentWorld:: addProtesters() {
    int T = max(25, 200 - (int)getLevel());
    int P = fmin(15, 2 + (int)getLevel() * 1.5);
    int probabilityOfHardcore = min(90, (int)getLevel() * 10 + 30);
    
    if (m_firstTick || ((m_ticksSoFar>=T) && m_numProtesters < P)) {
        int chance = rand() %101;
        if (chance < probabilityOfHardcore) {
            addActor(new HardcoreProtester(this));
        }
        else
            addActor(new RegProtester(this));
        m_firstTick = false;
        m_ticksSoFar = 0;
        m_numProtesters++;
    }
    m_ticksSoFar++;
    
}

void StudentWorld:: addGoodies() {
    int G = (int)getLevel() * 25 + 300;
    int c = rand() % 61;
    int r = rand() % 61;
    int current = rand() % G;
    if (current == 1) {
        int chance = rand() % 5;
        if (chance == 1) {
            addActor(new Sonar(this, 0, 60));
        }
        else  {
            while (!aroundEarth(c, r)) {
                c = rand() % 61;
                r = rand() % 61;
            }
            addActor(new WaterPool(this, c, r));
        }
    }
}

bool StudentWorld:: aroundEarth(int c, int r) {
    int x= c;
    int y = r;
    while (x< x+4) {
        while (y < y+4) {
            if (m_earth[x][y] != nullptr)
                return true;
            y++;
        }
        x++;
    }
    return false;
}

void StudentWorld:: cleanActors() {
    vector <Actor*>:: iterator ptr = m_actors.begin();
    while (ptr != m_actors.end()) {
        if (!(*ptr) -> isAlive()) {
            delete *ptr;
            ptr = m_actors.erase(ptr);
        }
        else
            ptr++;
    }
}

void StudentWorld:: updateStatusText() {
    
    int level = getLevel();
    int lives = getLives();
    int health = m_player->getHitPoints();
    int squirts = m_player->getWater();
    int gold = m_player->getGold();
    int barrelsLeft = numBarrel();
    int sonar = m_player->getSonar();
    int score = getScore();
    
    string s = formatDisplay(level, lives, health, squirts, gold, barrelsLeft, sonar, score);
    setGameStatText(s);
}

string StudentWorld:: formatDisplay(int level, int lives, int health, int squirts, int gold, int barrelsLeft, int sonar, int score) {
    stringstream s;
    s.fill(' ');
    s << "Lvl: ";
    s << setw(2) << level;
    s.fill(' ');
    s << "  Lives: ";
    s << setw(1) << lives;
    s.fill(' ');
    s << "  Hlth: ";
    s << setw(3) << health*10;
    s << '%';
    s.fill(' ');
    s << "  Wtr: ";
    s << setw(2) << squirts;
    s.fill(' ');
    s << "  Gld: ";
    s << setw(2) << gold;
    s.fill(' ');
    s << "  Oil Left: ";
    s << setw(2) << barrelsLeft;
    s.fill(' ');
    s << "  Sonar: ";
    s << setw(2) << sonar;
    s.fill('0');
    s << "  Scr: ";
    s << setw(6) << score;
    
    return s.str();
}

void StudentWorld:: addNewActor(Actor* actor) {
    m_actors.push_back(actor);
}

void StudentWorld::addBoulder(int num) {
    int c =0;
    int r=0;
    int i = 0;
    while (i < num) {
        do {
            c = rand() %61;
            r = rand() %37 + 20;
        }
        while (actorsInRad(c, r, 6) || (c>=30 && c<=33 && r > 4));
    }
    addActor(new Boulder(this, c, r));
}

void StudentWorld::addGold(int num) {
    int c =0;
    int r=0;
    int i = 0;
    while (i < num) {
        do {
            c = rand() %61;
            r = rand() %57;
        }
        while (actorsInRad(c, r, 6) || (c>=30 && c<=33 && r > 4));
    }
    addActor(new Gold(this, c, r, false, true));
}

void StudentWorld::addBarrel(int num) {
    int c =0;
    int r=0;
    int i = 0;
    while (i < num) {
        do {
            c = rand() %61;
            r = rand() %57;
        }
        while (actorsInRad(c, r, 6) || (c>=30 && c<=33 && r > 4));
    }
    addActor(new Barrel(this, c, r));
}

bool StudentWorld:: actorsInRad(int c, int r, int radius) {
    vector<Actor*>::iterator ptr = m_actors.begin();
    while (ptr != m_actors.end()) {
        int x = (*ptr)->getX();
        int y = (*ptr)->getY();
        if (checkRadius(c, r, x, y, radius))
            return true;
        ptr++;
    }
    return false;
}

void StudentWorld::showActors(int c, int r, int radius) {
    int x, y;
    vector <Actor*>:: iterator ptr = m_actors.begin();
    while (ptr != m_actors.end()) {
        if ((*ptr)->getID() == TID_GOLD || (*ptr)->getID() == TID_BARREL) {
            x = (*ptr)->getX();
            y = (*ptr)->getY();
            int distance = (c-x)*(c-x) + (r-y)*(r-y);
            if (distance <= radius*radius)
                (*ptr)->setVisible(true);
        }
    }
}

void StudentWorld::addActor (Actor *newActor) {
    m_actors.push_back(newActor);
}

bool StudentWorld:: checkRadius (int c1, int r1, int c2, int r2, int radius) {
    int current = (c1-c2)*(c1-c2) - (r1-r2)*(r1-r2);
    int rad = radius*radius;
    if (current <= rad)
        return true;
    return false;
}

bool StudentWorld:: nearbyBoulder(int c, int r, int radius) {
    vector<Actor*>:: iterator ptr = m_actors.begin();
    while(ptr != m_actors.end()) {
        if (checkRadius(c, r, (*ptr)->getX(), (*ptr)->getY(), radius) && (*ptr)->getID() == TID_BOULDER)
            return true;
        ptr++;
    }
    return false;
}

bool StudentWorld:: clearEarth(int c, int r) {
    bool sound = false;
    int a = c;
    int b = r;
    while (a < (a+4)) {
        while (b < (b+4)) {
            if (m_earth[a][b] != nullptr)  {
                delete m_earth[a][b];
                m_earth[a][b] = nullptr;
                sound = true;
            }
            b++;
        }
        a++;
    }
    return sound;
}

bool StudentWorld:: earthBelow(int c, int r) {
    int a = c;
    while (a != a+4) {
        if (m_earth[a][r-1] !=nullptr)
            return true;
        a++;
    }
    return false;
}

bool StudentWorld:: playerInRad(Actor *actor, int radius) {
    return checkRadius(actor->getX(), actor->getY(), m_player->getX(), m_player->getY(), radius);
}

TunnelMan* StudentWorld:: getPlayer() {
    return m_player;
}

bool StudentWorld:: protinRad(Actor* actor, int radius) {
    vector<Actor*>:: iterator ptr = m_actors.begin();
    while (ptr != m_actors.end()) {
        if ((*ptr)->getID() == TID_PROTESTER || (*ptr)->getID() == TID_HARD_CORE_PROTESTER) {
            if (checkRadius(actor->getX(), actor->getY(), (*ptr)->getX(), (*ptr)->getY(), radius))
                return dynamic_cast<Protester*>(*ptr);
        }
        ptr++;
    }
    return nullptr;
}

bool StudentWorld:: nearbyEarth(int c, int r) {
    if (m_earth[c][r] != nullptr)
        return true;
    return false;
}

Protester* StudentWorld:: protesterInRad(Actor* actor, int radius) {
    vector<Actor*>::iterator ptr = m_actors.begin();
    while(ptr != m_actors.end()) {
        if ((*ptr) -> getID() == TID_HARD_CORE_PROTESTER || (*ptr) ->getID()== TID_PROTESTER) {
            bool inRad = checkRadius(actor->getX(), actor->getY(), (*ptr)->getX(), (*ptr)->getY(), radius);
            if (inRad)
                return dynamic_cast< Protester*>(*ptr);
        }
        ptr++;
    }
    return nullptr;
}

void StudentWorld:: foundBarrel() {
    m_numBarrels--;
}

void StudentWorld:: decProtester() {
    m_numProtesters--;
}

int StudentWorld:: numBarrel() {
    return m_numBarrels;
}

void StudentWorld:: decBarrel() {
    m_numBarrels--;
}

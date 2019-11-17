#include "Actor.h"
#include "StudentWorld.h"
#include "GraphObject.h"
#include <algorithm>
using namespace std;

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp


// ACTOR ------

Actor:: Actor (StudentWorld *world, int startingX, int startingY, int imageID, Direction dir, double size, unsigned int depth): GraphObject(imageID, startingX, startingY, dir, size, depth), m_world(world), m_alive(true) {
    setVisible(true);
}

Actor:: ~Actor() {
    setVisible(false);
}

bool Actor:: isAlive() {
    return m_alive;
}

void Actor:: moveTo(int x, int y) {
    if (x < 0)
        x = 0;
    if (x > 60)
        x = 60;
    if (y < 0)
        y = 0;
    if (y > 60)
        y = 60;
    GraphObject::moveTo(x, y);
}

void Actor::dead() {
    m_alive = false;
}

StudentWorld* Actor::returnWorld() {
    return m_world;
}


//MAN ------
Human:: Human (StudentWorld * world, int imageID, int startingX, int startingY,
               Direction dir, int hitPoints): Actor(world, imageID, startingX, startingY, dir, 1.0, 0), m_hitPoints(hitPoints) {}
int Human:: getHitPoints() {
    return m_hitPoints;
}
void Human:: decHitPoints(int points){
    m_hitPoints -= points;
}

//TUNNELMAN -----

TunnelMan:: TunnelMan(StudentWorld * world): Human(world, TID_PLAYER, 30, 60, right, 10), m_water(5), m_sonar(1), m_gold(0) {}

int TunnelMan::getWater() {
    return m_water;
}
int TunnelMan::getSonar() {
    return m_sonar;
}
int TunnelMan::getGold() {
    return m_gold;
}

void TunnelMan:: doSomething () {
    if (!isAlive()) return;
    if (returnWorld()->clearEarth(getX(), getY()))
        returnWorld()->playSound(SOUND_DIG);
    
    int userInput;
    
    if (returnWorld()->getKey(userInput) == true) {
        switch (userInput) {
            case KEY_PRESS_ESCAPE: dead();
                break;
            case KEY_PRESS_SPACE:
                if (m_water >0) {
                    squirt();
                    m_water--;
                }
                break;
            case KEY_PRESS_LEFT:
                moveDirection(left);
                break;
            case KEY_PRESS_RIGHT:
                moveDirection(right);
                break;
            case KEY_PRESS_UP:
                moveDirection(up);
                break;
            case KEY_PRESS_DOWN:
                moveDirection(down);
                break;
            case 'Z': //sonar
            case 'z':
                if (m_sonar > 0) {
                    m_sonar--;
                    returnWorld()->showActors(getX(), getY(), 12);
                    returnWorld()->playSound(SOUND_SONAR);
                }
                break;
            case KEY_PRESS_TAB: //Gold
                if (m_gold >0) {
                    m_gold = m_gold-1;
                    returnWorld()->addActor(new Gold(returnWorld(), getX(), getY(), true, true));
                }
                break;
                
        }
    }
}


void TunnelMan:: squirt() {
//    switch (getDirection()) {
//        case up:
//            <#code#>
//            break;
//        case down:
//            <#code#>
//            break;
//        case left:
//
//        case right:
//            <#code#>
//            break;
//        case none:
//            return;
//    }
    returnWorld()-> playSound(SOUND_PLAYER_SQUIRT);
}

void TunnelMan:: addActor(int imageID) {
    switch (imageID) {
        case TID_WATER_POOL: m_water+=5;
            break;
        case TID_SONAR: m_sonar+=2;
            break;
        case TID_GOLD: m_gold++;
            break;
    }
}

void TunnelMan:: incAnnoyed(int hitPoints){
    decHitPoints(hitPoints);
    if (getHitPoints() <= 0) {
        dead();
        returnWorld()->playSound(SOUND_PLAYER_GIVE_UP);
    }
}

void TunnelMan:: moveDirection( Direction direction) {
    if (direction == left) {
        if (getDirection()== left) {
            if (!(returnWorld()->nearbyBoulder(getX()-1, getY())))
                moveTo(getX()-1, getY());
        }
        else
            setDirection(left);
    }
    if (direction == right) {
        if (getDirection()== right) {
            if (!(returnWorld()->nearbyBoulder(getX()+1, getY())))
                moveTo(getX()+1, getY());
        }
        else
            setDirection(right);
    }
    if (direction == up) {
        if (getDirection()== up) {
            if (!(returnWorld()->nearbyBoulder(getX(), getY()-1)))
                moveTo(getX(), getY()-1);
        }
        else
            setDirection(up);
    }
    if (direction == down) {
        if (getDirection()== down) {
            if (!(returnWorld()->nearbyBoulder(getX(), getY()+1)))
                moveTo(getX(), getY()+1);
        }
        else
            setDirection(down);
    }
}



// EARTH ------
Earth:: Earth(StudentWorld* world, int startingX, int startingY): Actor(world, TID_EARTH, startingX, startingY, right, .25, 3) {}
void Earth::doSomething() {} 

//BOULDER
Boulder:: Boulder(StudentWorld * world, int startingX, int startingY) : Actor(world, TID_BOULDER, startingX, startingY, down, 1.0, 1) {}

void Boulder:: doSomething () {
    if (!isAlive())
        return;
    if (m_stable) {
        if (returnWorld()->earthBelow(getX(), getY()))
            return;
        else
            m_stable = false;
    }
    if (m_ticks == 30) {
        m_Falling = true;
        returnWorld()->playSound(SOUND_FALLING_ROCK);
    }
    m_ticks++;
    if (m_Falling) {
        if (getY()==0 || returnWorld()->nearbyBoulder(getX(), getY()-1, 0) || returnWorld()->earthBelow(getX(), getY()-1))
            dead();
    }
    if (returnWorld()->playerInRad(this, 3))
        returnWorld()->getPlayer()->incAnnoyed(100);
    //annoy protesters
}


//SQUIRT ------

Squirt:: Squirt (StudentWorld*world, int startingX, int startingY, Direction dir): Actor(world, TID_WATER_SPURT, startingX, startingY, dir , 1.0, 1), m_distance(0) { }

bool Squirt:: annoyProt(){
    Protester* prot = returnWorld()->protesterInRad(this, 3);
    if (prot!= nullptr) {
        prot->incAnnoyed(2);
        return true;
    }
    return false;
}

void Squirt:: doSomething() {
    if (!isAlive()) return;
    if (annoyProt() || m_distance==4) {
        dead();
        return;
    }
    int x = getX();
    int y = getY();
    if (getDirection() == left) {
        if (returnWorld()->nearbyBoulder(x-1, y, 0) || returnWorld()->nearbyEarth(x-1,y) ){
            dead();
            return;
        }
        else
            moveTo(x-1, y);
    }
    if (getDirection() == right) {
        if (returnWorld()->nearbyBoulder(x+1, y, 0) || returnWorld()->nearbyEarth(x+1,y) ){
            dead();
            return;
        }
        else
            moveTo(x+1, y);
    }
    if (getDirection() == up) {
        if (returnWorld()->nearbyBoulder(x, y-1, 0) || returnWorld()->nearbyEarth(x,y-1) ){
            dead();
            return;
        }
        else
            moveTo(x, y-1);
    }
    if (getDirection() == down) {
        if (returnWorld()->nearbyBoulder(x, y-1, 0) || returnWorld()->nearbyEarth(x,y-1) ){
            dead();
            return;
        }
        else
            moveTo(x, y-1);
    }
    m_distance++;
}

// PICKMEUP -----
PickMeUp:: PickMeUp(StudentWorld * world, int imageID, int startingX, int startingY): Actor(world, imageID, startingX, startingY, right, 1.0, 2) {}

void PickMeUp:: tickLifeTime (int ticks) {
    if (m_ticks == ticks)
        dead();
    else
        m_ticks++;
}

//BARREL -----
Barrel::Barrel(StudentWorld* world, int startingX, int startingY) : PickMeUp(world, TID_BARREL, startingX, startingY) {
    setVisible(false);
}
void Barrel:: doSomething() {
    if (!isAlive())
        return;
    if (!isVisible() && returnWorld()->playerInRad(this,4)) {
        setVisible(true);
        return;
    }
    if (returnWorld()-> playerInRad(this, 3)) {
        dead();
        returnWorld()->playSound(SOUND_FOUND_OIL);
        returnWorld()->increaseScore(1000);
        returnWorld()->decBarrel();
    }
}

//GOLD -----
Gold:: Gold (StudentWorld * world, int startingX, int startingY, bool visible, bool tunnelPickUp) : PickMeUp(world, TID_GOLD, startingX, startingY), m_picker(tunnelPickUp) {
    setVisible(visible);
}
void Gold:: doSomething() {
    if (!isAlive()) {
        return;
    }
    if(!isVisible() && returnWorld()->playerInRad(this, 4)) {
        setVisible(true);
        return;
    }
    if (m_picker) {
        if (returnWorld()->playerInRad(this, 3)) {
            dead();
            returnWorld()->playSound(SOUND_GOT_GOODIE);
            returnWorld()->increaseScore(10);
            returnWorld()->getPlayer()->addActor(TID_GOLD);
        }
    }
    if (!m_picker) {
        Protester* cur = (returnWorld()-> protesterInRad(this, 3)) ;
        if (cur != nullptr) {
            dead();
            returnWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
            cur->beBribed();
        }
    }
    tickLifeTime(50);
    
}

//GOODIE -----
Goodie:: Goodie(StudentWorld* world, int imageID, int startingX, int startingY) : PickMeUp(world, imageID, startingX, startingY) {}
void Goodie:: doSomething() {
    if (!isAlive())
        return;
    if (returnWorld()->playerInRad(this, 3) ) {
        dead();
        returnWorld()->playSound(SOUND_GOT_GOODIE);
        if (getID() == TID_SONAR) {
            returnWorld()->getPlayer()->addActor(TID_SONAR);
            returnWorld()->increaseScore(75);
        }
        if (getID()== TID_WATER_POOL) {
            returnWorld()->getPlayer()->addActor(TID_WATER_POOL);
            returnWorld()->increaseScore(100);
        }
    }
    int T = max(100, 300 - 10*(int)returnWorld()->getLevel() );
    tickLifeTime(T);
}

//SONAR -----
Sonar :: Sonar (StudentWorld* world, int startingX, int startingY): Goodie(world, TID_SONAR, startingX, startingY) {}


// WATER POOL -----
WaterPool :: WaterPool ( StudentWorld * world, int startingX, int startingY) : Goodie(world, TID_WATER_POOL, startingX, startingY) {}



// PROTESTER -----
Protester::Protester (StudentWorld *world, int imageID, int hitPoints): Human(world, imageID, 60, 60, left, hitPoints), m_leaveField(false){
    m_numSquaresMove = rand() % 53 + 8;
    m_ticksToWait = max(0, (3 - (int)returnWorld()->getLevel()/4));
}

void Protester:: decTicksToWait() {
    m_ticksToWait--;
}

void Protester:: doSomething() {
    if (!isAlive())
        return;
    if (m_ticksToWait != 0) {
        decTicksToWait();
        return;
    }
    else {
        m_ticksToWait = max(0, (3 - (int)returnWorld()->getLevel()/4));
        m_ticksSincePerpTurn++;
    }
    if(m_leaveField) {
        if (getX()==60 && getY()==60) {
            dead();
            returnWorld()->decProtester();
            return;
        }
        moveTowardExit();
        return;
    }
    
    if (returnWorld()->playerInRad(this, 4) && confirmDirection()) {
        if (ret_ticksSinceYell()>15){
            returnWorld()->playSound(SOUND_PROTESTER_YELL);
            returnWorld()->getPlayer()->incAnnoyed(2);
            m_ticksSinceYell = 0;
            return;
        }
        return;
    }
    Direction direction = none;
    int playerX = returnWorld()->getPlayer()->getX();
    int playerY = returnWorld()->getPlayer()->getY();
    int deltaX = playerX-getX();
    int deltaY = playerY-getY();
    
    if (deltaX ==0 && deltaY ==0)
        direction = getDirection();
    else if (deltaX == 0 && deltaY <0)
        direction = up;
    else if (deltaX == 0 && deltaY > 0)
        direction = down;
    else if (deltaX <0 && deltaY==0)
        direction = left;
    else if (deltaX>0 && deltaY==0)
        direction = right;
    
    if (direction!= none && !returnWorld()->playerInRad(this, 4) && inALine(direction)) {
        setDirection(direction);
        moveOneStep(direction);
        m_numSquaresMove= 0;
        return;
    }
    m_numSquaresMove--;
    
    if (m_numSquaresMove <= 0){
        Direction changeDir = randomDirection();
        while (!canIMoveInDirection(getX(), getY(), changeDir)) {
            changeDir = randomDirection();
        }
        setDirection(changeDir);
        m_numSquaresMove = rand() % 53 + 8;
    }
    else if (atIntersection() && m_ticksSincePerpTurn > 200) {
        if (getDirection() == left || getDirection() == right) {
            if (!canIMoveInDirection(getX(), getY(), up)) {
                setDirection(down);
            }
            else if (!canIMoveInDirection(getX(), getY(), down)) {
                setDirection(up);
            }
            else {
                int rando = rand() %2;
                switch(rando) {
                    case 0:
                        setDirection(up);
                    case 1:
                        setDirection(down);
                }
            }
        }
        if (getDirection() == up || getDirection() == down) {
            if (!canIMoveInDirection(getX(), getY(), left)) {
                setDirection(right);
            }
            else if (!canIMoveInDirection(getX(), getY(), right)) {
                setDirection(left);
            }
            else {
                int rando = rand() %2;
                switch(rando) {
                    case 0:
                        setDirection(left);
                    case 1:
                        setDirection(right);
                }
            }
        }
        m_ticksSincePerpTurn = 0;
        m_numSquaresMove=rand() % 53 + 8;
    }
    moveOneStep(getDirection());
    if (!canIMoveInDirection(getX(), getY(), getDirection())) {
        m_numSquaresMove = 0;
    }
    
}

bool Protester:: atIntersection() {
    Direction curDir = getDirection();
    
    if (curDir == left || curDir == right) {
        if (canIMoveInDirection(getX(), getY(), up) || canIMoveInDirection(getX(), getY(), down))
            return true;
    }
    else
        if (canIMoveInDirection(getX(), getY(), up) || canIMoveInDirection(getX(), getY(), down))
            return true;
    return false;
}

bool Protester:: canIMoveInDirection(int c, int r, Direction direction) {
    switch (direction) {
        case left:
            if(c!= 0 && !returnWorld()->nearbyBoulder(c-1, r) && !returnWorld()->nearbyEarth(c-1, r)) {
                return true;
            }
        case right:
            if(c!= 60 && !returnWorld()->nearbyBoulder(c+1, r) && !returnWorld()->nearbyEarth(c+1, r)) {
                return true;
            }
        case up:
            if(r!= 0 && !returnWorld()->nearbyBoulder(c, r-1) && !returnWorld()->nearbyEarth(c, r-1)) {
                return true;
            }
        case down:
            if(r!= 60 && !returnWorld()->nearbyBoulder(c, r+1) && !returnWorld()->nearbyEarth(c, r+1)) {
                return true;
            }
        case none:
            return false;
    }
}


GraphObject:: Direction Protester:: randomDirection() {
    int rando = rand() %4;
    switch (rando) {
        case 0: return left;
        case 1: return right;
        case 2: return up;
        case 3: return down;
    }
    return none;
}
    

void Protester:: moveTowardExit() {
    //add code
}

bool Protester:: inALine(Direction direction) {
    int playerX = returnWorld()->getPlayer()->getX();
    int playerY = returnWorld()->getPlayer()->getY();
    int protX = getX();
    int protY = getY();
    if (direction == left) {
        int a = getX();
        while (a >= playerX) {
            if (returnWorld()->nearbyEarth(a-1, protY) && returnWorld()->nearbyBoulder(a-1, protY)) {
                return false;
            }
            a--;
        }
        return true;
    }
    if (direction == right) {
        int a = getX();
        while (a <= playerX) {
            if (returnWorld()->nearbyEarth(a+1, protY) && returnWorld()->nearbyBoulder(a+1, protY)) {
                return false;
            }
            a++;
        }
        return true;
    }
    if (direction == up) {
        int b = getY();
        while (b >= playerY) {
            if (returnWorld()->nearbyEarth(protX, b-1) && returnWorld()->nearbyBoulder(protX, b-1)) {
                return false;
            }
            b--;
        }
        return true;
    }
    if (direction == down) {
        int b = getY();
        while (b <= playerY) {
            if (returnWorld()->nearbyEarth(protX, b+1) && returnWorld()->nearbyBoulder(protX, b+1)) {
                return false;
            }
            b++;
        }
        return true;
    }
    return false;
}

void Protester:: moveOneStep(Direction direction) {
    int protX = getX();
    int protY = getY();
    switch (direction) {
        case left:
            setDirection(left);
            if (protX != 0) {
                moveTo(protX-1, protY);
            }
            break;
        case right:
            setDirection(right);
            if (protX != 60) {
                moveTo(protX+1, protY);
            }
            break;
        case up:
            setDirection(up);
            if (protY != 0)
                moveTo(protX, protY-1);
            break;
        case down:
            setDirection(down);
            if(protY !=60) {
                moveTo(protX, protY+1);
            }
        case none:
            return;
    }
}

bool Protester:: confirmDirection() {
    if (getDirection()==left) {
        int playerX = returnWorld()->getPlayer()->getX();
        return (playerX <= getX());
    }
    if (getDirection() == right) {
        int playerX = returnWorld()->getPlayer()->getX();
        return (playerX >= getX());
    }
    if (getDirection() == up) {
        int playerY = returnWorld()->getPlayer()->getY();
        return (playerY <= getY());
    }
    if (getDirection() == down) {
        int playerY = returnWorld()->getPlayer()->getY();
        return (playerY >= getY());
    }
    return false;
}

void Protester:: beBribed() {
    if (getID()== TID_PROTESTER) {
        returnWorld()->increaseScore(25);
        m_leaveField = true;
    }
    if (getID() == TID_HARD_CORE_PROTESTER) {
        returnWorld()->increaseScore(50);
        m_ticksToWait = max(50, 100 - ((int)(returnWorld()->getLevel()) * 10));
    }
}

void Protester:: decTicksSinceYell() {
    m_ticksSinceYell++;
}

int Protester:: ret_ticksSinceYell() {
    return m_ticksSinceYell;
}

void Protester:: incAnnoyed(int hitPoints)  {
    if (m_leaveField)
        return;
    decHitPoints(hitPoints);
    if (getHitPoints() >0) {
        returnWorld()->playSound(SOUND_PROTESTER_ANNOYED);
        m_ticksToWait = max(50, 100 - (int)returnWorld()->getLevel() * 10);
    }
    if (getHitPoints()<= 0) {
        m_leaveField = true;
        returnWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
        m_ticksToWait = 0;
        if (hitPoints == 100) {
            returnWorld()->increaseScore(500);
        }
        if (getID() == TID_PROTESTER) {
            returnWorld()->increaseScore(100);
        }
        if (getID() == TID_HARD_CORE_PROTESTER) {
            returnWorld()->increaseScore(250);
        }
    }
}



//REG -----
RegProtester:: RegProtester(StudentWorld* world) : Protester(world, TID_PROTESTER, 5) {}

//HARDCORE -----
HardcoreProtester:: HardcoreProtester(StudentWorld* world) : Protester(world, TID_HARD_CORE_PROTESTER, 20) {}




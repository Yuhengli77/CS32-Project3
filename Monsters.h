//
//  Monster.hpp
//  Project3
//
//  Created by Yuheng Li on 5/20/24.
//

#ifndef Monster_h
#define Monster_h

#include <iostream>
#include "Actors.h"
#include <string>
#include <set>
#include <utility>
#include <map>
class Temple;
using namespace std;

class Monsters : public Actors{
    
    
 public:
    Monsters(Temple *tp, int r, int c);
    virtual ~Monsters();
    virtual bool attack();
    
    
 private:
    
    
};



class Bogeymen : public Monsters{
 public:
    Bogeymen(Temple* tp, int r, int c);
    virtual bool move();
    
    
};


class Snakewomen : public Monsters{
public:
    Snakewomen(Temple* tp, int r, int c);
    virtual bool move();
};

class Dragons : public Monsters{
    
public:
    Dragons(Temple* tp, int r, int c);
    void gain_hitPoints();
    virtual bool move();
    
private:
    int maximumHitpoints;
};


class Goblins : public Monsters{
    
public:
    Goblins(Temple* tp, int r, int c, int distance);
    virtual bool move();
    int Goblin_Recursion(int steps, int r, int c, int &bestDir, std::set<std::pair<int,int>> &visited, std::map<std::pair<int,int>,int> &m_map);
    void setSmile_dist(int d);
private:
    int smile_dist = 15;
    
};

#endif /* Monster_h*/

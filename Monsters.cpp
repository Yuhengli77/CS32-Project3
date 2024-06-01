//
//  Monster.cpp
//  Project3
//
//  Created by Yuheng Li on 5/20/24.
//

#include "Monsters.h"
#include "Weapons.h"
#include "utilities.h"
#include "Temple.h"
#include "Player.h"
#include<cmath>
#include<set>
#include<map>
#include<utility>
using namespace std;

Monsters::Monsters(Temple *tp, int r, int c)
: Actors(tp, r, c){}

Monsters::~Monsters()
{
    delete m_wp;
}

bool Monsters::attack()
{
    
    // get a player's pointer
    Player* player = Actors::temple()->player();
    
    int damagePoints = randInt(0, strengthPoints() + this->m_wp->damage() - 1);
    
    int attackerPoints = dexterityPoints()+ this->m_wp->dexterityPoints();
    int defenderPoints = player->dexterityPoints() + player->armorPoints();
    if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)){
        player->setHitPoints(player->hitPoints() - damagePoints);
        m_wp->setString(name() + " " + m_wp->actionMethod() + m_wp->name() + " at " + player->name() + " and hits.");
        
        // when hits the defender
        // if the currenr weapon is magic fangs
        // there is a 1 in 5 chance to put the defender sleep
        Fangs* rp = dynamic_cast<Fangs*>(m_wp);
        if(rp!= nullptr){
            if(trueWithProbability(0.2)){
                rp->putSleep(player);
                m_wp->setString(name() + " " + m_wp->actionMethod() + m_wp->name() + " at " + player->name() + " and hits, putting "+player->name() + " to sleep");
                
            }
        }
        
        
        display_message = m_wp->getString();
    }else{
        m_wp->setString(name() + " " + m_wp->actionMethod() + m_wp->name() + " at " + player->name() + " and misses.");
        display_message = m_wp->getString();
    }
    
    //determine if the player dies
    if(player->hitPoints() <=0){
        m_wp->setString(name() + " " + m_wp->actionMethod() + m_wp->name() + " at " + player->name() + " dealing a final blow.");
        display_message = m_wp->getString();
        
        player->setHitPoints(0);
    }
    
    return true;

    
}



Bogeymen::Bogeymen(Temple* tp, int r, int c):Monsters(tp, r, c){
    m_wp = new ShortSwords("short sword", tp, this, r, c);
    Actors::setHitPoints(randInt(5, 10));
    Actors::setStrengthPoints(randInt(2, 3));
    Actors::setArmorPoints(2);
    Actors::setName("Bogeyman");
    
    
}

bool Bogeymen::move()
{
    // we want to calculate the Manhattan distance to determine if the
    // bogeyman can reach the player in five steps
    Temple* tp = Actors::temple();
    int distance = abs(row() - tp->player()->row()) + abs(col() - tp->player()->col());
    if(distance <= 5){
        // it has a 50 50 chance to move closer to the row or column
        // but it won't move farther
        if(col() < tp->player()->col() && tp->moveAble(row(), col() +1)){
            tp->setEmpty(row(), col());
            setCol(col() + 1);
            return true;
        }
        else if(col()> tp->player()->col() && tp->moveAble(row(), col()-1)){
            tp->setEmpty(row(), col());
            setCol(col() - 1);
            return true;
        }
        else if(row() > tp->player()->row() && tp->moveAble(row() - 1, col())){
            tp->setEmpty(row(), col());
            setRow(row() - 1);
            return true;
        }
        else if(row() < tp->player()->row() && tp->moveAble(row()+1, col())){
            tp->setEmpty(row(), col());
            setRow(row() + 1);
            return true;
        }
        // if can't move
        return false;
        
    }
    // if it is too far, won't move
    return false;
}


Snakewomen::Snakewomen(Temple* tp, int r, int c):Monsters(tp, r, c)
{
    m_wp = new Fangs("magic fangs", tp, this, r, c);
    Actors::setHitPoints(randInt(3, 6));
    Actors::setStrengthPoints(2);
    Actors::setDexterityPoints(3);
    Actors::setArmorPoints(3);
    Actors::setName("Snakewoman");
    
    
}
bool Snakewomen::move()
{
    
    // we want to calculate the Manhattan distance to determine if the
    // bogeyman can reach the player in five steps
    Temple* tp = Actors::temple();
    int distance = abs(row() - tp->player()->row()) + abs(col() - tp->player()->col());
    if(distance <= 3){
        // it has a 50 50 chance to move closer to the row or column
        // but it won't move farther
        if(col() < tp->player()->col() && tp->moveAble(row(), col() +1)){
            tp->setEmpty(row(), col());
            setCol(col() + 1);
            return true;
        }
        else if(col()> tp->player()->col() && tp->moveAble(row(), col()-1)){
            tp->setEmpty(row(), col());
            setCol(col() - 1);
            return true;
        }
        else if(row() > tp->player()->row() && tp->moveAble(row() - 1, col())){
            tp->setEmpty(row(), col());
            setRow(row() - 1);
            return true;
        }
        else if(row() < tp->player()->row() && tp->moveAble(row()+1, col())){
            tp->setEmpty(row(), col());
            setRow(row() + 1);
            return true;
        }
        // if can't move
        return false;
        
    }
    // if it is too far, won't move
    return false;
}


Dragons::Dragons(Temple* tp, int r, int c):Monsters(tp, r, c)
{
    m_wp = new LongSwords("long sword", tp, this, r, c);
    Actors::setHitPoints(randInt(20, 25));
    Actors::setStrengthPoints(4);
    Actors::setDexterityPoints(4);
    Actors::setArmorPoints(4);
    Actors::setName("Dragon");
    
    // maximumhitpoints is euqal to initial hitpoints
    maximumHitpoints = Actors::hitPoints();
    
    
}
bool Dragons::move()
{
    // I can't move
    return false;
}

Goblins::Goblins(Temple* tp, int r, int c, int distance):Monsters(tp, r, c){
    m_wp = new ShortSwords("short sword", tp, this, r, c);
    Actors::setHitPoints(randInt(15, 20));
    Actors::setStrengthPoints(3);
    Actors::setDexterityPoints(1);
    Actors::setArmorPoints(1);
    Actors::setName("Goblin");
    smile_dist = distance;
    
}

bool Goblins::move()
{
    int steps = 0;
    int bestDir = -1;
    // initialize a set to keep track of the place we visited like hw3
    // where we used a notation to mark we visited a place
    
    // use a map to record how many step we need to access one given position
    set<pair<int,int>> visited;
    map<pair<int, int>, int> m_map;
    
    // minimum distance that needs for goblin to reach the player
    int minimum = Goblin_Recursion(steps, row(), col(), bestDir, visited, m_map);
    
    // if can'r reach in the dist, return false;
    if(minimum > smile_dist)
        return false;
    
    Temple* tp = Actors::temple();
    // now we have the steps
    // move right, left, down, up
    //        0     1    2     3
    //temple()->setEmpty(row(), col());
    if(bestDir == 0){
        if(tp->moveAble(row(), col() +1)){
            temple()->setEmpty(row(), col());
            setCol(col() + 1);
        }
    }
    else if(bestDir == 1){
        if(tp->moveAble(row(), col()-1)){
            temple()->setEmpty(row(), col());
            setCol(col() - 1);
        }
    }
    else if(bestDir == 2){
        if(tp->moveAble(row()+1, col())){
            temple()->setEmpty(row(), col());
            setRow(row() + 1);
        }
    }
    else if (bestDir == 3){
        if(tp->moveAble(row()-1, col())){
            temple()->setEmpty(row(), col());
            setRow(row() -1);
        }
    }
    
    return true;
}

int Goblins::Goblin_Recursion(int steps, int r, int c, int &bestDir, std::set<std::pair<int, int>> &visited, std::map<std::pair<int, int>, int> &m_map)
{
    // base case
    // if the step we took to find the player is greater than goblin's smile distance
    // return a useless number
    if(steps > smile_dist)
        return 666;
    
    // if we reached the player
    // return the best step we need to reach the player
    if(r == Actors::temple()->player()->row() && c == Actors::temple()->player()->col())
        return steps;
    
    // we want to insert the current position into the visited set, as we did in hw 3
    visited.insert({r,c});
    
    // use the map to record how many steps we need to reach the specific position
    m_map[{r,c}] = steps;
    
    // move right, left, down, up
    int row_arr[4] = {0,0,1,-1};
    int col_arr[4] = {1,-1,0,0};
    
    
    int minimum = 666;
    
    for(int i = 0; i<4; i++)
    {
        // if the right || left ||  down || up is not moveable
        // or the place is already visited
        // continue to the next step
        if(!Actors::temple()->moveAble(row_arr[i] + r, col_arr[i] + c) || visited.count({r + row_arr[i],c + col_arr[i]})!=0)
            continue;
        
        
        // if the place is a new place or we found a better path
        // call the recursion to next step
        // then we can set the result to the minimum step
        // so check if it does not contain the position
        if(m_map[{r + row_arr[i],c + col_arr[i]}] == 0 || steps + 1 < m_map[{r + row_arr[i],c + col_arr[i]}]){
            int result = Goblin_Recursion(steps+1, r + row_arr[i], c + col_arr[i], bestDir, visited, m_map);
            if(result < minimum){
                minimum = result;
                
                // we want to determine next best direction
                // so if this is the first call, set the best dir to the i
                if(steps == 0)
                    bestDir = i;
            }
            
        }
        
    }
    
    // we have to unmark the set
    visited.erase({r,c});
    return minimum;
}




void Dragons::gain_hitPoints()
{
    if (hitPoints() < maximumHitpoints)
        setHitPoints(hitPoints()+1);
    
    
    if(hitPoints() > maximumHitpoints)
        setHitPoints(maximumHitpoints);
}

void Goblins::setSmile_dist(int d)
{
    smile_dist = d;
}

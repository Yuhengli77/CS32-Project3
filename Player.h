//
//  Player.hpp
//  Project3
//
//  Created by Yuheng Li on 5/18/24.
//


#ifndef Player_h
#define Player_h

#include "Actors.h"
#include "GameObjects.h"
class ShortSwords;
class GameObjects;
#include <iostream>
#include <vector>
#include <string>
class Player : public Actors{
    
 public:
    Player(Temple* tp, int r, int c);
    virtual ~Player();
    
    bool Move(char dir);
    
    void open_inventory() const;
    
    bool pickup();
    
    // methods in the inventory page
    void read_scroll(char choice);
    void switch_weapon(char choice);
    
    bool is_weapon(char choice);
    
    bool attack(char dir);
    
    bool isdied();
    bool hasGoldenIdol();
    
    void gain_hitPoints();
    void setMaxHitpoints();

    
    
    
    
    
 private:
    std::vector<GameObjects*> m_inventory;
    int maximumHitPoints = 20;
    bool hasIdol = false;

};





#endif /* Player_h */

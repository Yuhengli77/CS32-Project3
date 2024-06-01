//
//  Player.cpp
//  Project3
//
//  Created by Yuheng Li on 5/18/24.
//
#include "Player.h"
#include "Weapons.h"
#include "GameObjects.h"
#include "utilities.h"
#include <iostream>
#include <cctype>
#include "Monsters.h"
using namespace std;

Player::Player(Temple* tp, int r, int c):Actors(tp, r, c){
    Actors::setName("Player");
    Actors::setHitPoints(20);
    Actors::setArmorPoints(2);
    setStrengthPoints(2);
    setDexterityPoints(2);
    // set current weapon to shortsword
    m_wp = new ShortSwords("short sword", tp, this, r, c);
    m_inventory.push_back(m_wp);
    
    
}
Player::~Player()
{
    for (GameObjects* ptr : m_inventory) {
            delete ptr;
        }
}

bool Player::Move(char dir){
    if(Actors::move(dir))
    return true;
    
    return false;
}


void Player::open_inventory()const{
    clearScreen();
    char abc[1] = {'a'};
    cout<<"Inventory: "<<endl;
    for (int i = 0; i <m_inventory.size() ; i++){
        // for weapons and scrolls, we need different display
        Weapons* rp = dynamic_cast<Weapons*>(m_inventory[i]);
        if (rp!= nullptr)
            cout <<" "<<abc[0]<<". "<<m_inventory[i]->name()<<endl;
        else
            cout<<" "<<abc[0]<<". A scroll called "<<m_inventory[i]->name()<<endl;
        
        
        abc[0]++;
    }
    
    
    
    
}


bool Player::pickup(){
    display_message = "";
    if (Actors::temple()->getObjectChar(row(), col()) == '&'){
        hasIdol = true;
        return true;
    }
    
    if (Actors::temple()->getObjectChar(row(), col()) == ' ' ||Actors::temple()->getObjectChar(row(), col()) == '>' )
        return false;
    
    if (Actors::temple()->getObjectChar(row(), col()) == '?' || Actors::temple()->getObjectChar(row(), col()) == '(' ){
        // first get the object
        // if size is less than 26
        // put it into the inventory
        if(m_inventory.size() >= 26)
        {
            display_message = "Your knapsack is full; you can't pick that up.";
            return false;
        }
        if (m_inventory.size() < 26){
            m_inventory.push_back( Actors::temple()->GameObjectsAt(Actors::row(), Actors::col()));
            Actors::temple()->deleteObjects(Actors::row(), Actors::col());
            
            
            // use dynamic casteing to know if it is scroll or weapon
            Weapons* rp = dynamic_cast<Weapons*>(m_inventory.back());
            if (rp!= nullptr)
                display_message = "You pick up " + m_inventory.back()->name()+".";
            else
                display_message = "You pick up a scroll called " + m_inventory.back()->name()+".";
            return true;
        }
        
    }
    return false;
}

void Player::read_scroll(char choice){
    display_message = "";
    char abc = 'a';
    for (int i = 0; i <m_inventory.size() ; i++){
        if (abc == choice){
            if(is_weapon(choice)){
                display_message = "You can't read a " + m_inventory[i]->name() +".";
                return;
            }
            if (m_inventory[i]->name() == "scroll of teleportation"){
                // randomly move it to another place
                char new_place;
                int new_r;
                int new_c;
                do{
                    new_r = randInt(2, 17);
                    new_c = randInt(2, 69);
                    new_place = Actors::temple()->getMapChar(new_r, new_c);
                }while (new_place == 'B' || new_place == 'S'||new_place == 'D' || new_place ==  'G' || new_place ==  '#');
                
                // move player to that place
                Actors::setRow(new_r);
                Actors::setCol(new_c);
                display_message = "You read the scroll called teleportation.\nYou feel your body wrenched in space and time.";
            }else if (m_inventory[i]->name() == "scroll of improve armor"){
                Actors::setArmorPoints(Actors::armorPoints() + randInt(1, 3));
                // make sure it is not greater than 99
                if (Actors::armorPoints() > 99){
                    Actors::setArmorPoints(99);
                }
                display_message = "You read the scroll called enhance armor.\nYour armor glows blue.";
                
            }else if (m_inventory[i]->name() == "scroll of raise strength"){
                Actors::setStrengthPoints(Actors::strengthPoints() + randInt(1, 3));
                // make sure it is not greater than 99
                if (Actors::strengthPoints() > 99){
                    Actors::setStrengthPoints(99);
                }
                display_message = "You read the scroll called raise strength.\nYour muscles bulge.";
                
            }else if (m_inventory[i]->name() == "scroll of enhance health"){
                maximumHitPoints += randInt(3, 8);
                display_message = "You read the scroll called enhance health.\nYou feel your heart beating stronger.";
            }else if (m_inventory[i]->name() == "scroll of enhance dexterity"){
                Actors::setDexterityPoints(Actors::dexterityPoints()+1);
                if (Actors::dexterityPoints()>99)
                    Actors::setDexterityPoints(99);
                display_message = "You read the scroll called enhance dexterity.\nYou feel like less of a klutz.";
            }
            
            delete m_inventory[i];
            m_inventory.erase(m_inventory.begin()+i);
            
            
        }
        abc++;
        // if don't match choice and inventory's menu, do nothing
    }
}

void Player::switch_weapon(char choice){
    // check if it is a weapon first
    // first use the same code from read_scroll to get the obeject
    char abc = 'a';
    for (int i = 0; i <m_inventory.size() ; i++){
        // if we have the weapon
        // switch it to the current weapon
        if (abc == choice){
            // convert it to a weapon pointer
            //Weapons* rp = dynamic_cast<Weapons*>(m_inventory[i]);
            //std::swap(m_inventory[0], m_inventory[i]);
            if(!is_weapon(choice)){
                display_message = "You can't wield " + m_inventory[i]->name() + ".";
                return;
            }
            Weapons* rp = dynamic_cast<Weapons*>(m_inventory[i]);
            m_wp = rp;
            display_message = "You are wielding " + m_inventory[i]->name()+ ".";
        }
        abc++;
    }
    
    // if don't match choice and inventory's menu, do nothing
    
}

bool Player::is_weapon(char choice){
    char abc = 'a';
    for (int i = 0; i <m_inventory.size() ; i++){
        if (abc == choice){
            // convert it to a weapon pointer
            Weapons* rp = dynamic_cast<Weapons*>(m_inventory[i]);
            if (rp != nullptr)
                return true;
            
            return false;
            
        }
        abc++;
    }
    
    // defaultly return false;
    return false;
}



bool Player::attack(char dir)
{
    Temple * tp = Actors::temple();
    // if no target, return false
    if(!tp->monsterNearMe())
        return false;
    
    int mon_r;
    int mon_c;
    
    
    switch (dir)
        {
          case ARROW_UP:
                mon_r = Actors::row()-1;
                mon_c = Actors::col();
                break;
          case ARROW_DOWN:
                mon_r = Actors::row()+1;
                mon_c = Actors::col();
                break;
                
          case ARROW_LEFT:
                mon_r = Actors::row();
                mon_c = Actors::col()-1;
                break;
                
          case ARROW_RIGHT:
                mon_r = Actors::row();
                mon_c = Actors::col()+1;
                break;
                
          default:
                return false;
        }
    
    // we can't attack a wall
    if (tp->getMapChar(mon_r, mon_c) == '#')
        return false;
    // now we have the location of the monster
    // get the monster's pointer
    Monsters* mon = tp->MonstersAt(mon_r, mon_c);
    
    // now we can perform the attack
    // first get the damage points
    int damagePoints = randInt(0, strengthPoints() + this->m_wp->damage() - 1);
    
    int attackerPoints = dexterityPoints()+ this->m_wp->dexterityPoints();
    int defenderPoints = mon->dexterityPoints() + mon->armorPoints();
    if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)){

        // hits the defender
        mon->setHitPoints(mon->hitPoints() - damagePoints);
        m_wp->setString("Player " +m_wp->actionMethod() + m_wp->name() + " at " + mon->name() + " and hits.");
        
        // when hits the defender
        // if the currenr weapon is magic fangs
        // there is a 1 in 5 chance to put the defender sleep
        Fangs* rp = dynamic_cast<Fangs*>(m_wp);
        if(rp!= nullptr){
            if(trueWithProbability(0.2)){
                rp->putSleep(mon);
                m_wp->setString("Player strikes " + m_wp->name() + " at " + mon->name() + " and hits, putting "+mon->name() + " to sleep");
                
            }
        }
        
        
        display_message = m_wp->getString();
    }else{
        m_wp->setString("Player " + m_wp->actionMethod() + m_wp->name() + " at " + mon->name() + " and misses.");
        display_message = m_wp->getString();
    }
    
    
    //determine if the monster dies
    if (mon->hitPoints() <= 0)
    {
        m_wp->setString("Player " +m_wp->actionMethod() + m_wp->name() + " at " + mon->name() + " dealing a final blow.");
        display_message = m_wp->getString();
        // possibilly drop an item
        // check what kind of monster it is
        
        // dragon has a 1.0 possibility to drop a scroll of some kind
        Dragons* rp = dynamic_cast<Dragons*>(mon);
        if(rp != nullptr){
            // check if there is an object already
            if (tp->GameObjectsAt(mon_r, mon_c) == nullptr){
                if (trueWithProbability(0.2))
                    tp->addTeleporation(mon_r, mon_c);
                else
                    tp->addScroll(mon_r, mon_c);
            }
        }
        // bogeyman has a 0.1 possiblity to drop a magic axe
        Bogeymen* bg = dynamic_cast<Bogeymen*>(mon);
        if (bg != nullptr)
            if(trueWithProbability(0.1))
                if (tp->GameObjectsAt(mon_r, mon_c) == nullptr)
                    tp->addAxe(mon_r, mon_c);
        
        // snakewoman has a 1/3 chance drop a magic fangs of sleep
        Snakewomen* sn = dynamic_cast<Snakewomen*>(mon);
        if(sn != nullptr)
            if(trueWithProbability(0.33))
                if (tp->GameObjectsAt(mon_r, mon_c) == nullptr)
                    tp->addFang(mon_r, mon_c);
                
        //goblin has a 1/3 chance drop either a axe or fangs
        
        Goblins* gb = dynamic_cast<Goblins*>(mon);
        if(gb != nullptr)
            if(trueWithProbability(0.33)){
                if (trueWithProbability(0.5)) {
                    if (tp->GameObjectsAt(mon_r, mon_c) == nullptr)
                        tp->addAxe(mon_r, mon_c);
                    
                }else{
                    if (tp->GameObjectsAt(mon_r, mon_c) == nullptr)
                        tp->addFang(mon_r, mon_c);
                }
            }
        
        //delete the monster
        tp->deleteMonster(mon_r, mon_c);
        
        
        
    }
    
    
    return true;
}

bool Player::isdied()
{
    if(hitPoints() <= 0)
        return true;
    
    return false;
}


void Player::gain_hitPoints()
{
    if (hitPoints() < maximumHitPoints)
        setHitPoints(hitPoints()+1);
    
    
    if(hitPoints() > maximumHitPoints)
        setHitPoints(maximumHitPoints);
    
}

bool Player::hasGoldenIdol()
{
    return hasIdol;
}

void Player::setMaxHitpoints()
{
    maximumHitPoints = 50;
}

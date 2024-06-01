//
//  Weapons.h
//  Project3
//
//  Created by Yuheng Li on 5/20/24.
//

#ifndef Weapons_h
#define Weapons_h
#include "GameObjects.h"
#include "Temple.h"
#include "Actors.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <string>
using namespace std;


class Weapons : public GameObjects{
 public:
    Weapons(string name, Temple* tp, Actors* ac, int r, int c);
    
    void displayString();
    
    int damage();
    int dexterityPoints();
    void setString(string s);
    string getString();
    virtual string actionMethod();
    
    
    
 protected:
    int m_dexterityBonus;
    int m_damageAmount;
    
private:
    string action_string;
    
};


class Maces : public Weapons{
public:
    Maces(string name, Temple* tp, Actors* ac, int r, int c);
    virtual string actionMethod();
private:
    string action_method = "swings ";
    
};


class ShortSwords : public Weapons{
public:
    
    ShortSwords(string name, Temple* tp, Actors* ac, int r, int c);
    virtual string actionMethod();
private:
    string action_method = "slashes ";
};

class LongSwords : public Weapons{
public:
    LongSwords(string name, Temple* tp, Actors* ac, int r, int c);
    virtual string actionMethod();
private:
    string action_method = "swing ";
    
};

class MagicAxes : public Weapons{
    
public:
    MagicAxes(string name, Temple* tp, Actors* ac, int r, int c);
    virtual string actionMethod();
private:
    string action_method = "chops ";
};


class Fangs : public Weapons{
public:
    
    Fangs(string name, Temple* tp, Actors* ac, int r, int c);
    void putSleep(Actors* ac);
    virtual string actionMethod();
private:
    string action_method = "strikes ";
};








#endif /* Weapons_h */

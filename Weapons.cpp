//
//  Weapons.cpp
//  Project3
//
//  Created by Yuheng Li on 5/20/24.
//
#include <iostream>
#include "Weapons.h"
#include "GameObjects.h"
#include "Actors.h"
#include "Temple.h"
#include "utilities.h"
using namespace std;


Weapons::Weapons(string name, Temple* tp, Actors* ac, int r, int c): GameObjects(name, tp, ac, r, c){
    
    
}
string Weapons::actionMethod()
{
    return " swings";
}
int Weapons::damage()
{
    return m_damageAmount;
}

int Weapons::dexterityPoints()
{
    return m_dexterityBonus;
}

void  Weapons::displayString()
{
    cout<<action_string<<endl;
    action_string="";
}

void Weapons::setString(string s)
{
    action_string = s;
}

string Weapons::getString()
{
    return action_string;
}

ShortSwords::ShortSwords(string name, Temple* tp, Actors* ac, int r, int c):Weapons(name, tp, ac, r, c){
    m_dexterityBonus = 0;
    m_damageAmount = 2;
}

string ShortSwords::actionMethod()
{
    return action_method;
}

Fangs::Fangs(string name, Temple* tp, Actors* ac, int r, int c):Weapons(name, tp, ac, r, c){
    
    m_dexterityBonus = 3;
    m_damageAmount = 2;
    
    
}
string Fangs::actionMethod()
{
    return action_method;
}

LongSwords::LongSwords(string name, Temple* tp, Actors* ac, int r, int c):Weapons(name, tp, ac, r, c){
    m_dexterityBonus = 2;
    m_damageAmount = 4;
    
}
string LongSwords::actionMethod()
{
    return action_method;
}

Maces::Maces(string name, Temple* tp, Actors* ac, int r, int c):Weapons(name, tp, ac, r, c){
    m_dexterityBonus = 0;
    m_damageAmount = 2;
    
}
string Maces::actionMethod()
{
    return action_method;
}

MagicAxes::MagicAxes(string name, Temple* tp, Actors* ac, int r, int c):Weapons(name, tp, ac, r, c){
    m_dexterityBonus = 5;
    m_damageAmount = 5;
    
}
string MagicAxes::actionMethod()
{
    return action_method;
}

void Fangs::putSleep(Actors* ac)
{
    if(!ac->isSleeping()){
        ac->setSleepTime(randInt(2,6));
    }else
    {
        int y = ac->sleepTime();
        int x = randInt(2,6);
        ac->setSleepTime(max(x,y));
        
    }
    
}

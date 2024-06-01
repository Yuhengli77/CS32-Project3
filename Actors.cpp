//
//  Actors.cpp
//  Project3
//
//  Created by Yuheng Li on 5/18/24.
//

#include <iostream>
#include "Actors.h"
#include "utilities.h"
#include "Weapons.h"


Actors::Actors(Temple* tp, int r, int c)
: m_tp(tp), m_row(r), m_col(c), m_hitPoints(99), m_armorPoints((0)), m_name("")
{}

Actors::~Actors()
{
    
}

int Actors::row() const
{
    return m_row;
}

void Actors::setRow(int r)
{
    m_row = r;
}

int Actors::col() const
{
    return m_col;
}

void Actors::setCol(int c)
{
    m_col = c;
}


int Actors::hitPoints()const
{
    return m_hitPoints;
}

void Actors::setHitPoints(int points)
{
    
    m_hitPoints = points;
}


int Actors::armorPoints()const
{
    return m_armorPoints;
}


void Actors::setArmorPoints(int points)
{
    m_armorPoints = points;
}

int Actors::dexterityPoints()const
{
    return m_dexterityPoints;
}

void Actors::setDexterityPoints(int points)
{
    m_dexterityPoints = points;
}

int Actors::sleepTime() const
{
    return m_sleepTime;
}

void Actors::setSleepTime(int points)
{
    m_sleepTime = points;
}

int Actors::strengthPoints() const
{
    return m_strengthPoints;
}


void Actors::setStrengthPoints(int points)
{
    m_strengthPoints = points;
}


bool Actors::move(char dir){
    
    switch (dir)
        {
          case ARROW_UP:     if (row() <= 1)      return false; else m_row--; break;
          case ARROW_DOWN:   if (row() >= 17) return false; else m_row++; break;
          case ARROW_LEFT:   if (col() <= 1)      return false; else m_col--; break;
          case ARROW_RIGHT:  if (col() >= 69) return false; else m_col++; break;
          default:     return false;
        }
        return true;
}


bool Actors::move()
{
    return false;
}
Weapons* Actors::weapon() const{
    
    return m_wp;
}

string Actors::name() const{
    return m_name;
}


void Actors::setName(string name){
    m_name = name;
}


Temple* Actors::temple()const{
    return m_tp;
}

void Actors::displayMessage()
{
    cout<<display_message<<endl;
    display_message="";
}


string Actors::message()
{
    return display_message;
}

bool Actors::isSleeping()
{
    if(m_sleepTime > 0)
        return true;
    
    return false;
}


void Actors::try_to_wakeup()
{
    m_sleepTime -= 1;
}


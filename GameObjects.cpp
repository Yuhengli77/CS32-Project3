//
//  GameObjects.cpp
//  Project3
//
//  Created by Yuheng Li on 5/20/24.
//
#include <iostream>
#include "GameObjects.h"
#include <string>

using namespace std;

GameObjects::GameObjects(string name, Temple* tp, Actors* ac, int r, int c)
:m_tp(tp), m_ac(ac)
{
    m_name = name;
    m_row = r;
    m_col = c;
}

GameObjects::~GameObjects(){}


string GameObjects::name() const
{
    return m_name;
}

int GameObjects::cols() const
{
    return m_col;
}

int GameObjects::rows() const
{
    return m_row;
}

Staricase::Staricase(string name, Temple* tp, Actors* ac, int r, int c):GameObjects(name, tp, ac, r, c)
{
    
}

GoldenIdol::GoldenIdol(string name, Temple* tp, Actors* ac, int r, int c):GameObjects(name, tp, ac, r, c)
{
    
}

//
//  GameObjects.hpp
//  Project3
//
//  Created by Yuheng Li on 5/20/24.
//

#ifndef GameObjects_h
#define GameObjects_h

#include <iostream>
#include <string>
#include "Actors.h"
#include "Player.h"
#include<vector>
class Temple;

using namespace std;

class GameObjects{
 public:
    
    GameObjects(string name, Temple* tp, Actors* ac, int r, int c);
    virtual ~GameObjects();
    int cols() const;
    int rows() const;
    string name()const;
    
    
    
    
 private:
    string m_name;
    int m_row;
    int m_col;
    Temple* m_tp;
    Actors* m_ac;
    
};


class Staricase : public GameObjects
{
 public:
    
    Staricase(string name, Temple* tp, Actors* ac, int r, int c);
    
    
};

class GoldenIdol : public GameObjects
{
 public:
    GoldenIdol(string name, Temple* tp, Actors* ac, int r, int c);
};
#endif /* GameObjects_h */



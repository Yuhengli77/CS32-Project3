//
//  Actors.h
//  Project3
//
//  Created by Yuheng Li on 5/18/24.
//
#include "Temple.h"

#ifndef Actors_h
#define Actors_h
#include <vector>
#include <string>
using namespace std;
class Weapons;

class Actors{
 public:
    Actors(Temple* tp, int r, int c);
    virtual ~Actors();
    // some properties
    int  row() const;
    void setRow(int r);
    int  col() const;
    void setCol(int c);
    int  hitPoints() const;
    void setHitPoints(int points);
    int armorPoints() const;
    void setArmorPoints(int points);
    int dexterityPoints() const;
    void setDexterityPoints(int points);
    int sleepTime() const;
    void setSleepTime(int points);
    
    int strengthPoints() const;
    void setStrengthPoints(int points);
    
    void try_to_wakeup();
    
    Weapons* weapon() const;
    
    virtual bool move(char dir);
    virtual bool move();
    
    string name() const;
    void setName(string name);
    
    Temple* temple() const;
    
    void displayMessage();
    
    string message();
    
    bool isSleeping();

    
    

private:
    
    Temple* m_tp;
    int   m_row;
    int   m_col;
    int   m_hitPoints;
    int   m_armorPoints;
    int   m_strengthPoints;
    int   m_dexterityPoints;
    int   m_sleepTime;
    string m_name;
    
    
    
protected:
    Weapons* m_wp;
    string display_message;
};


#endif /* Actors_h */

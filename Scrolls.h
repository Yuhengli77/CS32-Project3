//
//  Scrolls.hpp
//  Project3
//
//  Created by Yuheng Li on 5/20/24.
//

#ifndef Scrolls_h
#define Scrolls_h
#include "GameObjects.h"
#include <iostream>
class Scrolls : public GameObjects{
 public:
    Scrolls(string name, Temple* tp, Actors* ac, int r, int c);
    
    virtual ~Scrolls();
    
    
};


class Teleporation : public Scrolls{
public:
    Teleporation(Temple* tp, Actors* ac, int r, int c);
    
    
};

class ImproveArmor : public Scrolls{
public:
    ImproveArmor(Temple* tp, Actors* ac, int r, int c);
};

class RaiseStrength : public Scrolls{
public:
    RaiseStrength(Temple* tp, Actors* ac, int r, int c);

};

class EnhanceHealth : public Scrolls{
public:
    EnhanceHealth(Temple* tp, Actors* ac, int r, int c);
};

class EnhanceDexterity : public Scrolls{
public:
    EnhanceDexterity(Temple* tp, Actors* ac, int r, int c);
};



#endif /* Scrolls_h */

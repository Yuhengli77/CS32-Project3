//
//  Scrolls.cpp
//  Project3
//
//  Created by Yuheng Li on 5/20/24.
//

#include "Scrolls.h"

Scrolls::Scrolls(string name, Temple* tp, Actors* ac, int r, int c):GameObjects(name, tp, ac, r, c){}

Scrolls::~Scrolls(){}

Teleporation::Teleporation(Temple* tp, Actors* ac, int r, int c)
:Scrolls("scroll of teleportation", tp, ac, r, c){}


ImproveArmor::ImproveArmor(Temple* tp, Actors* ac, int r, int c)
:Scrolls("scroll of improve armor", tp, ac, r, c){}


RaiseStrength::RaiseStrength(Temple* tp, Actors* ac, int r, int c)
:Scrolls("scroll of raise strength", tp, ac, r, c){}


EnhanceHealth::EnhanceHealth(Temple* tp, Actors* ac, int r, int c)
:Scrolls("scroll of enhance health", tp, ac, r, c){}


EnhanceDexterity::EnhanceDexterity(Temple* tp, Actors* ac, int r, int c)
:Scrolls("scroll of enhance dexterity", tp, ac, r, c){}



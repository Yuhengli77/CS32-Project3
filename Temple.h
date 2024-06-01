//
//  Map.hpp
//  Project3
//
//  Created by Yuheng Li on 5/17/24.
//
#ifndef Temple_h
#define Temple_h
class Monsters;
class Scrolls;
class GameObjects;

class Player;
#include <iostream>
#include <vector>

class Temple{
    
 public:
    Temple(int nRows, int nCols);
    ~Temple();
    int     rows() const;
    int     cols() const;
    void display();
    Player* player() const;
    void addPlayer();
    
    bool movePlayer(char dir);
    
    bool moveAble(char dir);
    bool moveAble(int r, int c);
    
    void addMonster();
    
    bool addScroll();
    bool addScroll(int r, int c);
    bool addTeleporation(int r, int c);
    
    bool addWeapon();
    
    char getMapChar(int r, int c);
    
    GameObjects* GameObjectsAt(int r, int c);
    Monsters* MonstersAt(int r, int c);
    
    void addObjects();
    void deleteObjects(int r, int c);
    
    bool isMonster(char c);
    
    bool monsterNearMe();
    bool playerNearMe(int r, int c);
    
    void deleteMonster(int r, int c);
    
    
    char getObjectChar(int r, int c);
    
    void addAxe(int r, int c);
    void addFang(int r, int c);
    
    void monster_turn();
    
    bool isOverlapping(char grid[18][70], int x1, int y1, int x2, int y2);
    void insertRoom(char grid[18][70], int x1, int y1, int x2, int y2);
    void connectRoom(char grid[18][70], int row1, int col1, int row2, int col2);
    void generateTemple();
    void clean();
    
    void addDragon();
    void addGoblin();
    void addSnakeWoman();
    void addBogeyman();
    void addStaircase();
    void addGolenIdol();
    void setEmpty(int r, int c);
    
    void goDown();
    void setGoblindist(int dist);
 private:
    int m_rows;
    int m_cols;
    
    Player* m_player;
    
    std::vector<Monsters*> m_monsters;
    
    std::vector<GameObjects*> m_objects;
    
    char grid[18][70];
    
    int m_level = 0;
    int goblin_dist;
    
};




#endif /* Temple_h */

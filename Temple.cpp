//
//  Map.cpp
//  Project3
//
//  Created by Yuheng Li on 5/17/24.
//

#include "Temple.h"
#include "utilities.h"
#include "Player.h"
#include "Monsters.h"
#include "Scrolls.h"
#include "Weapons.h"
#include "GameObjects.h"
#include <stack>

using namespace std;

Temple::Temple(int nRows, int nCols){
    m_rows = nRows;
    m_cols = nCols;
}

Temple::~Temple(){
    
    // delete the player
    if (m_player != nullptr)
        delete m_player;
    
    // delete the monster
    for (Monsters* ptr : m_monsters) {
            delete ptr;
        }
    
    // delete the objects on the map
    for (GameObjects* ptr : m_objects) {
            delete ptr;
        }
}

int Temple::rows() const
{
    return m_rows;
}

int Temple::cols() const
{
    return m_cols;
}

Player* Temple::player() const
{
    return m_player;
}

void Temple::addPlayer()
{
    bool placed = false;
    
    while(!placed)
    {
        int rPlayer = randInt(2, 17);
        int cPlayer = randInt(2, 69);
        // check if current position is valid
        if(grid[rPlayer][cPlayer] != '#'){
            // Dynamically allocate new Player and add it to the temple
            m_player = new Player(this, rPlayer, cPlayer);
            placed = true;
        }
        
    }
}


bool Temple::movePlayer(char dir){
    if(m_player!= nullptr){
        m_player->move(dir);
        return true;
    }
    return false;
    
}

void Temple::display() {
    // draw player
    if (m_player != nullptr)
    {
        // Set the char to '@', unless there's also a Tooter there
        // (which should never happen), in which case set it to '*'.
        char& gridChar = grid[m_player->row()][m_player->col()];
        gridChar = '@';
        
    }
    
    // draw monsters
    for(int i =0; i < m_monsters.size(); i++){
        char& gridChar = grid[m_monsters[i]->row()][m_monsters[i]->col()];
        if (gridChar == ' ' || gridChar == '?' || gridChar == '(' || gridChar == '&' || gridChar == '>'){
            if (m_monsters[i]->name() == "Bogeyman"){
                gridChar = 'B';
            }else if (m_monsters[i]->name() == "Snakewoman"){
                gridChar = 'S';
            }else if (m_monsters[i]->name() == "Dragon"){
                gridChar = 'D';
            }else if (m_monsters[i]->name() == "Goblin"){
                gridChar = 'G';
            }
            
            
        }
    }
    
    // draw game objetcs
    for(int i =0; i < m_objects.size(); i++){
        char& gridChar = grid[m_objects[i]->rows()][m_objects[i]->cols()];
        
        Weapons* rp = dynamic_cast<Weapons*>(m_objects[i]);
        if (rp != nullptr){
            if(gridChar == ' ')
                gridChar = '(';
        }else{
            if(m_objects[i]->name() == "Stairs"){
                if(gridChar == ' ')
                    gridChar = '>';}
            else if (m_objects[i]->name() == "the golden idol"){
                if(gridChar == ' ')
                    gridChar = '&';
            }else{
                if(gridChar == ' ')
                    gridChar = '?';
            }
        }
        
    }
    
    
    // Draw the grid
    clearScreen();
    for (int r = 0; r < rows(); r++)
    {
        for (int c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    
    
    // there is a 1 in 10 chance for player to regain 1 hit point
    if(trueWithProbability(0.1))
        player()->gain_hitPoints();
    
    // display the information:
    cout <<"Level: " <<m_level<<", Hit points: "<<player()->hitPoints()<<", Armor: "<<player()->armorPoints()<<", Strength: "<<
    player()->strengthPoints()<<", Dexterity: "<<player()->dexterityPoints()<<endl;
    
    //cout<<endl;
    
    // print game messages
    player()->displayMessage();
    for (int i =0; i < m_monsters.size(); i++){
        if (m_monsters[i]->message() != "")
            m_monsters[i]->displayMessage();
    }
    
    
}


bool Temple::moveAble(char dir){
    
    int r = m_player->row();
    int c = m_player->col();
    
    switch (dir)
        {
          case ARROW_UP:
                if (grid[r-1][c] == 'B' || grid[r-1][c]== 'S' || grid[r-1][c] == 'D' || grid[r-1][c] ==  'G'|| grid[r-1][c] ==  '#' )
                    return false;
                return true;
                
          case ARROW_DOWN:
                if (grid[r+1][c] == 'B' || grid[r+1][c]== 'S' || grid[r+1][c] == 'D' || grid[r+1][c] ==  'G'|| grid[r+1][c] ==  '#')
                    return false;
                return true;
          case ARROW_LEFT:
                if (grid[r][c-1] == 'B' || grid[r][c-1]== 'S' || grid[r][c-1] == 'D' || grid[r][c-1] ==  'G' || grid[r][c-1] ==  '#')
                    return false;
                return true;
          case ARROW_RIGHT:
                if (grid[r][c+1] == 'B' || grid[r][c+1]== 'S' || grid[r][c+1] == 'D' || grid[r][c+1] ==  'G'|| grid[r][c+1] ==  '#')
                    return false;
                return true;
          default:     return false;
        }
}

void Temple::addMonster(){
    int num_monsters = randInt(2, 5*(m_level+1)+1);
    
    // level 0 only has goblins and snakewomen
    if(m_level == 0 || m_level == 1){
        for(int i = 0; i <num_monsters; i++)
        {
            if(trueWithProbability(0.5)){
                addGoblin();
            }else{
                addSnakeWoman();
            }
        }
    }
    
    // level 2 has goblins snakewomen and bogeyman
    
    if(m_level == 2)
    {
        for(int i = 0; i <num_monsters; i++)
        {
            int type = randInt(1, 3);
            if(type == 1)
                addGoblin();
            else if(type ==2)
                addSnakeWoman();
            else if(type ==3)
                addBogeyman();
        }

    }
    
    if(m_level == 3 || m_level == 4)
    {
        for(int i = 0; i <num_monsters; i++)
        {
            int type = randInt(1, 4);
            if(type == 1)
                addGoblin();
            else if(type ==2)
                addSnakeWoman();
            else if(type ==3)
                addBogeyman();
            else if(type == 4)
                addDragon();
        }

    }



}

bool Temple::addScroll(){
    // randomly add a scroll on the map
    bool placed = false;
    while(!placed){
        int r = randInt(2, 17);
        int c = randInt(2, 69);
        
        //int ran = randInt(1, 5);
        if( grid[r][c] != '#'){
            addScroll(r, c);
            placed = true;
        }
    }
    return true;
}

bool Temple::addScroll(int r, int c)
{
    //addTeleporation(r, c);

    int ran = randInt(2, 5);
    
    if (ran == 2){
        Scrolls *scr = new ImproveArmor(this, m_player, r, c);
        m_objects.push_back(scr);
    }else if (ran == 3){
        Scrolls *scr = new RaiseStrength(this, m_player, r, c);
        m_objects.push_back(scr);
    }else if (ran == 4){
        Scrolls *scr = new EnhanceHealth(this, m_player, r, c);
        m_objects.push_back(scr);
        
    }else if (ran == 5){
        Scrolls *scr = new EnhanceDexterity(this, m_player, r, c);
        m_objects.push_back(scr);
    }
    return true;

}
bool Temple::addTeleporation(int r, int c)
{
    Scrolls *scr = new Teleporation(this, m_player, r, c);
    m_objects.push_back(scr);
    return true;
}


char Temple::getMapChar(int r, int c){
    return grid[r][c];
}


GameObjects* Temple::GameObjectsAt(int r, int c){
    for (int i =0; i < m_objects.size(); i++){
        if (m_objects[i]->cols() == c && m_objects[i]->rows() == r)
            return m_objects[i];
    }
    return nullptr;
}

Monsters* Temple::MonstersAt(int r, int c)
{
    for (int i =0; i < m_monsters.size(); i++){
        if (m_monsters[i]->col() == c && m_monsters[i]->row() == r)
            return m_monsters[i];
    }
    return nullptr;
}


void Temple::deleteObjects(int r, int c){
    for (int i =0; i < m_objects.size(); i++){
        if (m_objects[i]->cols() == c && m_objects[i]->rows() == r)
            m_objects.erase(m_objects.begin()+i);
            
            }
    
}


bool Temple::addWeapon(){
    
    bool added = false;
    while(!added){
        int r = randInt(2, 17);
        int c = randInt(2, 69);
        if(grid[r][c] != '#' && grid[r][c] != '?' && grid[r][c] != '('){
            int ran = randInt(1, 3);
            
            if (ran == 1){
                Weapons *wp = new ShortSwords("short sword", this, m_player, r, c);
                m_objects.push_back(wp);
                
            }else if (ran == 2){
                Weapons *wp = new Maces("mace", this, m_player, r, c);
                m_objects.push_back(wp);
            }else if (ran == 3){
                Weapons *wp = new LongSwords("long sword", this, m_player, r, c);
                m_objects.push_back(wp);
            }
            added = true;
        }
            
        
    }
    return true;
    
    
}

void Temple::addAxe(int r, int c)
{
    Weapons *wp = new MagicAxes("magic axe", this, m_player, r, c);
    m_objects.push_back(wp);
}

void Temple::addFang(int r, int c)
{
    Weapons* wp = new Fangs("magic fangs", this, m_player, r, c);
    m_objects.push_back(wp);
}


bool Temple::isMonster(char c)
{
    if(c == 'G' || c == 'B' || c == 'D' || c == 'S')
        return true;
    
    return false;
}

bool Temple::monsterNearMe()
{
    for (int i =0; i < m_monsters.size(); i++)
    {
        if(playerNearMe(m_monsters[i]->row(), m_monsters[i]->col()))
            return true;
    }
    
    return false;
    
}

bool Temple::playerNearMe(int r, int c)
{
    if(r-1 == player()->row() && c == player()->col())
        return true;
    if(r == player()->row() && c-1 == player()->col())
        return true;
    if(r+1 == player()->row() && c == player()->col())
        return true;
    if(r == player()->row() && c+1 == player()->col())
        return true;
    
    return false;
}

void Temple::deleteMonster(int r, int c)
{
    grid[r][c] = ' ';
    
    for (int i =0; i < m_monsters.size(); i++){
        if (m_monsters[i]->col() == c && m_monsters[i]->row() == r){
            delete m_monsters[i];
            m_monsters.erase(m_monsters.begin()+i);
        }
            }

}


char Temple::getObjectChar(int r, int c)
{
    for (int i = 0; i < m_objects.size(); i++){
        if(m_objects[i]->cols() == c && m_objects[i]->rows() == r){
            // dynamic casting to know what class it is
            Weapons* rp = dynamic_cast<Weapons*>(m_objects[i]);
            if (rp != nullptr)
                return '(';
                
            Scrolls* sc = dynamic_cast<Scrolls*>(m_objects[i]);
            if (sc != nullptr)
                return '?';
            
            GoldenIdol* gi = dynamic_cast<GoldenIdol*>(m_objects[i]);
            if (gi != nullptr)
                return '&';
            
            Staricase* st = dynamic_cast<Staricase*>(m_objects[i]);
            if (st != nullptr)
                return '>';
           
        }
            
    }
    
    // if not found return space
    return ' ';
}


void Temple::monster_turn()
{
    
    // loop for every monster
    // if the player is near the monster
    // attack the plater
    for (int i =0; i < m_monsters.size(); i++){
        // if the monster is a dragon
        // there is a 1 in 10 chance
        Dragons* rp = dynamic_cast<Dragons*>(m_monsters[i]);
        if(rp != nullptr)
        {
            if(trueWithProbability(0.1))
                rp->gain_hitPoints();
        }
        
        if(m_monsters[i]->isSleeping())
        {
            m_monsters[i]->try_to_wakeup();
            continue;
        }
        
        if(playerNearMe(m_monsters[i]->row(), m_monsters[i]->col())){
            if (m_monsters[i]->attack())
                continue;
        }
        // if don't attack, move
        m_monsters[i]->move();
        
    }
    
}

bool Temple::isOverlapping(char grid[18][70], int x1, int y1, int x2, int y2)
{
    // check if two rooms are overlapping
    // x1,y1 is the top left conner of the room
    // x2,y2 is the bottom right conner of the room
    // then for the whole room, if some place is already ' '
    // there is an overlap
    for(int i = x1; i<= x2; i++){
        for (int j = y1; j <= y2; j++){
            if(grid[j][i] == ' ')
                return true;
        }
    }
    
    return false;
}

void Temple::insertRoom(char grid[18][70], int x1, int y1, int x2, int y2)
{
    // x1,y1 is the top left conner of the room
    // x2,y2 is the bottom right conner of the room
    // set the whole area to ' ' so we insert a room
    for(int i = x1; i<= x2; i++){
        for (int j = y1; j <= y2; j++){
            grid[j][i] = ' ';
        }
    }
    
    
}

void Temple::connectRoom(char grid[18][70], int row1, int col1, int row2, int col2)
{
    // row1 and col1 is the center of the first room
    // row2 and col2 is the center of the second room
    // we want to connect the center of the two rooms
    // thus we should 'go' from the first room's center and second room's center
    // then
    while(row1 != row2 || col1 != col2){
        // for each step we set the current place to a ' '
        grid[row1][col1] = ' ';
        
        // if the 1st room is lower than 2nd room
        // go up one step
        // vice versa
        if(row1 < row2) row1++;
        else if(row1 > row2) row1--;
        
        // if the 1st room is on the righter of the 2nd room
        // go right one step
        // vice versa
        else if(col1 < col2) col1++;
        else if(col1 > col2) col1--;
        
        // this loop will ends when we reach the 2nd room's center
    }
    
    
}

void Temple::generateTemple()
{
    // fill the map with '#' first
    for(int i = 0; i < rows(); i++){
        for(int j = 0; j < cols(); j ++){
            grid[i][j] = '#';
        }
    }
    
    
    // create two stacks to hold the col_centers and row_centers
    stack<int> col_centers;
    stack<int> row_centers;
    
    // we will have 4- 6 rooms
    int num_room = randInt(4, 6);
    for(int i = 0; i < num_room; i++){
        // to insert a room, we need the top left and the bottom right's place
        // first randomly generate the top left conner
        // want the room's size to be 3-6 * 3-6
        // and we don't want x to be too right and too low
        // since that will make room to be very small
        bool placed = false;
    
        
        while(!placed)
        {
            int y1 = randInt(2, 8);
            int x1 = randInt(2, 60);
            
            int y2 = y1 + randInt(4, 8);
            int x2 = x1 + randInt(4, 8);
            
            if(!isOverlapping(grid, x1, y1, x2, y2)){
                insertRoom(grid, x1, y1, x2, y2);
                col_centers.push((x1+x2)/2);
                row_centers.push((y1+y2)/2);
                placed = true;
            }
            
        }
        
        
    }
    
    // after inserted all rooms, connect them together
    for(int j = 0; j < num_room-1; j++){
        
        int row1 = row_centers.top();
        int col1 = col_centers.top();
        
        // pop the first one out to get the 2nd room's center
        if(!row_centers.empty())
            row_centers.pop();
        if(!col_centers.empty())
            col_centers.pop();
        
        
        int row2 = row_centers.top();
        int col2 = col_centers.top();
        
        // connect them
        connectRoom(grid, row1,  col1, row2, col2);
    }
    
    // if level = 0, initialize the room
    if(m_level == 0){
        addPlayer();
        addMonster();
        addObjects();
        // place staircase
        addStaircase();
        
    }
}

void Temple::clean()
{
    grid[player()->row()][player()->col()] = ' ';
}

void Temple::addDragon()
{
    bool added = false;
    while(!added){
        int r = randInt(2, 17);
        int c = randInt(2, 69);
        // check if current position is valid
        if(grid[r][c] != '#'){
            Monsters *mst = new Dragons(this, r, c);
            m_monsters.push_back(mst);
            added = true;
        }
    }
}

void Temple::addBogeyman()
{
    bool added = false;
    while(!added){
        int r = randInt(2, 17);
        int c = randInt(2, 69);
        // check if current position is valid
        if(grid[r][c] != '#'){
            Monsters *mst = new Bogeymen(this, r, c);
            m_monsters.push_back(mst);
            added = true;
        }
    }
}

void Temple::addGoblin()
{
    bool added = false;
    while(!added){
        int r = randInt(2, 17);
        int c = randInt(2, 69);
        // check if current position is valid
        if(grid[r][c] != '#'){
            Monsters *mst = new Goblins(this, r, c, goblin_dist);
            m_monsters.push_back(mst);
            added = true;
        }
    }
}

void Temple::addSnakeWoman()
{
    bool added = false;
    while(!added){
        int r = randInt(2, 17);
        int c = randInt(2, 69);
        // check if current position is valid
        if(grid[r][c] != '#'){
            Monsters *mst = new Snakewomen(this, r, c);
            m_monsters.push_back(mst);
            added = true;
        }
    }
}


void Temple::addStaircase()
{
    bool added = false;
    while(!added){
        int r = randInt(2, 17);
        int c = randInt(2, 69);
        
        if(grid[r][c] != '#' && grid[r][c] != '?' && grid[r][c] != '('){
            GameObjects* obj = new Staricase("Stairs", this, m_player, r, c);
            m_objects.push_back(obj);
            added = true;
        }
    }
        
}

void Temple::goDown()
{
    m_level++;
    if (m_level <= 4){
        // delete all monsters and objects in this temple
        
        for (Monsters* ptr : m_monsters) {
                delete ptr;
            }
        m_monsters.clear();
        
        // delete the objects on the map
        for (GameObjects* ptr : m_objects) {
                delete ptr;
            }
        m_objects.clear();
        
        
        // regenerate the temple
        generateTemple();
        
        // replace the player
        bool placed = false;
        while(!placed){
            int r = randInt(2, 17);
            int c = randInt(2, 69);
            
            if(grid[r][c] != '#'){
                m_player->setRow(r);
                m_player->setCol(c);
                placed = true;
            }
            
        }
        
        
        
        // according to the level, place the monsters
        addMonster();
        
        // add gameobjs
        addObjects();
        
        // if level < 4 add stair
        
        if(m_level < 4)
            addStaircase();
        
        if(m_level == 4)
            addGolenIdol();
        
    }
}


void Temple::addObjects()
{
    int num_objs = randInt(2, 3);
    
    // place gameobjs
    for(int i = 0; i < num_objs; i++){
        if(trueWithProbability(0.5)){
            addScroll();
        }else{
            addWeapon();
        }
    }
}

void Temple::addGolenIdol()
{
    bool added = false;
    while(!added){
        int r = randInt(2, 17);
        int c = randInt(2, 69);
        
        if(grid[r][c] != '#' && grid[r][c] != '?' && grid[r][c] != '('){
            GameObjects* obj = new GoldenIdol("the golden idol", this, m_player, r, c);
            m_objects.push_back(obj);
            added = true;
        }
    }
}

bool Temple::moveAble(int r, int c)
{
    if (grid[r][c] == '@' || grid[r][c] == '#' || grid[r][c] == 'B' || grid[r][c] == 'D' || grid[r][c] == 'S' || grid[r][c] == 'G')
        return false;
    
    // also check there is no monster here
    for(Monsters* p : m_monsters)
    {
        if (p->row() == r && p-> col() == c)
            return false;
    }
    
    return true;
}

void Temple::setEmpty(int r, int c)
{
    grid[r][c] = ' ';
}

void Temple::setGoblindist(int dist)
{
    goblin_dist = dist;
}

// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

// You may add data members and other member functions to this class.

class Game
{
public:
    Game(int goblinSmellDistance);
    void play();
private:
    int goblin_distance;
};

#endif // GAME_INCLUDED

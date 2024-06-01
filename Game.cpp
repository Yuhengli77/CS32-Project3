// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>
#include "Temple.h"
#include "Player.h"
using namespace std;

// Implement these and other Game member functions you may have added.




Game::Game(int goblinSmellDistance)
{
    goblin_distance = goblinSmellDistance;
}


void Game::play()
{
    //    cout << "The game hasn't been implemented yet." << endl;
    
    Temple* tp = new Temple(18,70);
    tp->setGoblindist(goblin_distance);
    tp->generateTemple();
    
    tp->display();
    string action = "";
    string choice = "";
    
    while(action[0] != 'q'){
        tp->clean();
        action = getCharacter();

        // if the player is died
        // force the plaer to quit the game
        if(tp->player()->isdied() && action[0] != 'q')
            continue;
        
        // if the player has the idol game over
        if(tp->player()->hasGoldenIdol() && action[0] != 'q')
            continue;
        
        
        // if player is sleeping
        // player try to wake up and monster do their turn
        if(tp->player()->isSleeping())
        {
            tp->player()->try_to_wakeup();
        }else{
            
            switch (action[0])
            {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    break;
//                case 'q':
//                    delete tp;
//                    cout<<"Saving session...\n...copying shared history...\n...saving history...truncating history files...\n...completed.\n";
//                    return;
                case 'h':
                case 'l':
                case 'k':
                case 'j':
                    if(tp->moveAble(action[0])){
                        tp->movePlayer(action[0]);
                    }else{
                        tp->player()->attack(action[0]);
                    }
                    break;
                    
                case 'w':
                    tp->player()->open_inventory();
                    choice = getCharacter();
                    tp->player()->switch_weapon(choice[0]);
                    
                    break;
                case 'i':
                    tp->player()->open_inventory();
                    getCharacter();
                    break;
                case 'r':
                    tp->player()->open_inventory();
                    choice = getCharacter();
                    tp->player()->read_scroll(choice[0]);
                    
                    break;
                    
                case 'g':
                        tp->player()->pickup();
                    break;
                    
                case '>':
                        if (tp->GameObjectsAt(tp->player()->row(), tp->player()->col()) != nullptr && tp->GameObjectsAt(tp->player()->row(), tp->player()->col())->name() == "Stairs")
                            tp->goDown();
                    break;
                    
                case 'c':
                    tp->player()->setMaxHitpoints();
                    tp->player()->setHitPoints(50);
                    tp->player()->setStrengthPoints(9);
                    break;
            }
        }
        // player will have a chance to gain hit points
        tp->monster_turn();
        tp->display();
        
        if(tp->player()->isdied())
        {
            cout<<"You are died, game over.\nPress q to quit the game:"<<endl;
        }
        
        if(tp->player()->hasGoldenIdol()){
            cout<<"Congratulations, you won!\nPress q to quit the game:"<<endl;
        }
        
    }
    
    delete tp;
    return;
}


// You will presumably add to this project other .h/.cpp files for the various
// classes of objects you need to play the game:  player, monsters, weapons, 
// etc.  You might have a separate .h/.cpp pair for each class (e.g., Player.h,
// Bogeyman.h, etc.), or you might put the class declarations for all actors in
// Actor.h, all game objects in GameObject.h, etc.

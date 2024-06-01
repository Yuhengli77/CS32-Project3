# CS32-Project3

Upon starting a new game, you the player are placed on the top level of the temple. From here, you must work your way through the rooms on that level, battling monsters, finding treasures, and using staircases to descend ever deeper into the temple's depths. When you reach the bottom level of the temple, you must reach the golden idol in order to win the game.


<img width="585" alt="Screenshot 2024-06-01 at 3 57 38 PM" src="https://github.com/Yuhengli77/CS32-Project3/assets/171456235/e8fa5aed-ae75-4c31-9aa4-8336372b2832">

To control the player in the game, you issue commands from the keyboard. Use the getCharacter function we will supply you to read characters from the keyboard in a way that does not require the user to hit Enter after each command. (Also, getCharacter does not echo the character onto the screen.) Doom is not a "real-time" game; the game progresses only when the player issues a command. After each player command, the monsters each make a move and then the screen is updated to reflect the current state of the game.

The player commands are:
Move one space using the arrow keys or alternative movement letters:
h to move left
l to move right
k to move up
j to move down
Our getCharacter function translates movement commands into character constants named ARROW_LEFT, etc.
Attack a monster next to you by moving in its direction.
Pick up an object by standing on it and typing g.
Wield a weapon by typing w and then selecting a weapon from your inventory.
Read a scroll by typing r and then selecting a scroll from your inventory.
See an inventory of your items by typing i.
When standing on a stairway, descend deeper into the temple by typing >.
Quit the game by typing q.
Cheat by typing c. This command sets the player's characteristics to make defeating monsters easy, and exists solely to let us test some aspects of your program without our having to slog through a regular game.
If you type something not on this list, you do nothing for this turn, but the monsters take their turn.


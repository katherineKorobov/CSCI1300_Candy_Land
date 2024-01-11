#include "Board.h" //include all files
#include "CandylandPlayer.h"
#include "Game.h" 
#include "candystore.h"
#include <iostream> //include libraries
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

int main()
{

    srand((unsigned) time (NULL)); //passes the current time in seconds to the radnom number seed function. should only ever be executed once for all random generations.

    Game game; //defines an object using the default constructor of the the Game class. This will run the full game.
    
    
}
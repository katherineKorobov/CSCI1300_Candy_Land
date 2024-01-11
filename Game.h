#ifndef GAME_H
#define GAME_H

#include "CandylandPlayer.h"
#include "Board.h"
#include "candystore.h"

#include <iostream>
#include <vector>

using namespace std;

struct Card
{
    string card_color = "";
    bool if_double = false;
    string display_card = "";
};

struct Calamity
{
    string type = "";
    string message = "";
};


class Game
{
private:
    // vector<Candy> all_candies;
    // vector<CandylandPlayer> all_characters;
    // vector<CandylandPlayer> all_players;
    // Board game_board;

public:
    int const NUM_OF_PLAYERS= 2 ;

    Card single_magenta {MAGENTA, false, "You drew a Mystic Magenta card. Your game piece advances to Magenta tile. Here is the updated trail: "};
    Card single_blue {BLUE, false, "You drew a Bubblegum Blue card. Your game piece advances to Blue tile. Here is the updated trail: "};
    Card single_green {GREEN, false, "You drew a Groovy Green card. Your game piece advances to Green tile. Here is the updated trail: "};
    Card two_magenta{MAGENTA, true, "You drew a double Mystic Magenta card. Your game piece advances to Magenta tile. Here is the updated trail: "};
    Card two_blue {BLUE, true, "You drew a double Bubblegum Blue card. Your game piece advances to Blue tile. Here is the updated trail: "};
    Card two_green {GREEN, true, "You drew a double Groovy Green card. Your game piece advances to Green tile. Here is the updated trail: "};
    Card cards_to_draw[9] = {single_magenta, single_blue, single_green, single_magenta, single_blue, single_green, two_magenta, two_blue, two_green};
    
    Card drawCard(); //rand between 0 and 8 which will correspond to index of card to draw array and that will be the card they pickup

    Calamity candy_bandit = {"Candy Bandits", "Candy Bandits! Oh no! Candy Bandits have swiped your gold coins"};
    Calamity lollipop_labryinth = {"Lost in a Lollipop Labyrinth", "Oh dear! You got lost in the lollipop labyrinth!"};
    Calamity candy_avalanche = {"Candy Avalanche", "Candy Avalanche! Watch out! A candy avalanche has struck!"};
    Calamity taffy_trap = {"Sticky Taffy Trap","Oops! You are stuck in a sticky taffy trap!"};

    Game(); //calls all other functions (setups, and play and end)
    
    //bool initializeCandyStores(); //initialize candy store arrays first
    
    bool initializeTreasure(); //make array of hidden treasure structs from manually made structs
    vector <Riddle> initializeRiddles(); //read in file and put all in array of riddle type
    bool initializedRiddles;

    bool setupBoard(); //use the initializers of candystore, treasure, and riddle to build board
    vector <CandylandPlayer> setupGame(vector <Candy>, vector <Character>&); //this will get player characters and number, put all players into an array. use initializer for candies and characters 
    void playGame(vector<CandylandPlayer>&, Board, vector <Riddle>&, vector <Candy>&); //tursn, player moves, for loops through plaeyrs for turns
    bool onCastle(vector<CandylandPlayer>&); //checks if the current player position is last tile
    void endGame(vector <CandylandPlayer>&); //output stats of palyers, and ofstream the final stats too

    void calamityOccurs(CandylandPlayer&);
    void specialTile(Board, CandylandPlayer&, vector<CandylandPlayer>&);

    void samePlayerTile (CandylandPlayer&, vector<CandylandPlayer>&, Board);

    vector <Candy> initializeCandies();
    bool initializedCandies = false;
    
    vector <Character> initializeCharacters();
    bool initializedCharacters = false;

    Board initializeBoardTiles();
    bool initializedBoard = false;

    void displayCharacters(vector <Character>& );
    
    //void playCalamity (Player); //if tile has calmity then rand through all possibilites and play one

    bool doesCalamityOccur(Tile); //checks if a calamity occurs. once on a tile(after a turn), will generate ranodm number to tell if a calmity occurs
    //true if it does, false if no calmity

    bool askTreasureRiddle(vector <Riddle>&); //if true then the user has inputed in the right stuff, false if they havent
    void playHiddenTreasures(CandylandPlayer&);

};



#endif
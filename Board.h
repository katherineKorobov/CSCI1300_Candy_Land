#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "CandylandPlayer.h"

#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"

using namespace std;

struct Tile
{
    string color;
    string type;
    bool hasHiddenTreasure;
    bool hasCandyStore;
    bool hasCandylandPlayer;
    bool isSpeical;
};

struct Riddle
{
    string riddle_question = "";
    string riddle_answer = "";
};


struct HiddenTreasure
{
    Riddle treasure_riddle;
    string treasure_type = "";
};


class Board //the board
{
private:
    const static int _BOARD_SIZE = 83; //size of board
    Tile _tiles[_BOARD_SIZE]; //array of every tile on the board that stores structs of tile type
    const static int _MAX_CANDY_STORE = 3; // will only ever be 3 candy stores
    int _candy_store_position[_MAX_CANDY_STORE];//an arrray of the positions of the candy stores in the game
    int _candy_store_count = 0; //??
    int _player_position; //players position on the board?? 

public:
    Board();

    void resetBoard(); //resets the board. use it to start the game, and from there add in special tiles
    void displayTile(int, vector <CandylandPlayer>&); //displays the tile at the positon
    void displayBoard(vector <CandylandPlayer>&);

    //draw card function??

    Tile getTile (int player_position);
    void setTileColor(string, int);
    void setTileType(string, int);
    void setHasHiddenTreasure(bool, int);
    void setHasCandyStore (bool, int);
    void setHasCandylandPlayer(bool, int);
    void setIsSpecial(bool, int);

    int getBoardSize() const;
    int getPlayerPosition() const;

    int getCandyStoreCount() const;
    bool addCandyStore(int);
    bool isPositionCandyStore(int); 

    bool movePlayer(CandylandPlayer current); //will return the tile the player is on
    
};

#endif
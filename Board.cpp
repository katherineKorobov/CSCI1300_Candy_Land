#include "Board.h"
#include "CandylandPlayer.h"
#include <cstdlib> //include package to use rand
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Construct a new Board:: Board object. 
 * Defualt constructor just resets the board
 * 
 */
Board::Board() //default constructor
{
    resetBoard();
}

/**
 * @brief Resets the board object, to its initial state of an empty display
 * 
 */
void Board::resetBoard() //resets to 0 candy stores, 0 player position, etc
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        new_tile = {current_color, "regular tile"};
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular tile"};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;
    }

    _player_position = 0;
}

/**
 * @brief Displays a single tile. 
 * 
 * @param position is the position of the tile(?)
 * @param all_players is a vector of all the players in the game. I pass it by reference(no copy of data made). 
 */
void Board::displayTile(int position, vector <CandylandPlayer>& all_players) //displays 1 tile. 
{

    int player_position_1 = all_players.at(0).getCurrentPlayerPosition();
    int player_position_2 = all_players.at(1).getCurrentPlayerPosition();

    Tile target = _tiles[position]; //the target tile is the tile at the index in the tile array
    cout << target.color << " "; //print the color

    if (position == player_position_1) //if the inputed position of the player is equal to position of the player on the board
    {
        cout << all_players.at(0).getPlayerID(); 
    }
    else if(position == player_position_2)
    {
        cout<<all_players.at(1).getPlayerID();
    }
    else
    {
        cout << " "; //else nothing?
    }

    cout << " " << RESET; //what
}

/**
 * @brief Displays the whole board using the display tile function. 
 * 
 * @param all_players is the vector of all the players in the game.(pass by reference)
 */
void Board::displayBoard(vector <CandylandPlayer> &all_players) //displays board, do i have to look at this? would rather leave it alone
{
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i, all_players);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i, all_players);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i, all_players);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i, all_players);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i, all_players);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}

/**
 * @brief an accessor function to get the board size (const 83)
 * 
 * @return int returns the integer values of the board size
 */
int Board::getBoardSize() const 
{
    return _BOARD_SIZE;
}

/**
 * @brief an accessor function to get the constant candy store count (3)
 * 
 * @return int is the integer values of how many candystores on teh board
 */
int Board::getCandyStoreCount() const //accessor function to get the constant candy store count
{
    return _candy_store_count;
}

/**
 * @brief Get the Tile object from teh array of tiles, a private data member
 * 
 * @param position 
 * @return Tile 
 */
Tile Board:: getTile(int position)
{
    return _tiles[position];
}

/**
 * @brief Adds a candy store to the inputed psoiton on the baord
 * 
 * @param position 
 * @return true 
 * @return false 
 */
bool Board::addCandyStore(int position) //position is already randomized when inputed in. here it just makes store on tile
{
    if (_candy_store_count >= _MAX_CANDY_STORE) //if the 
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = position;
    _candy_store_count++;
    return true;
}

/**
 * @brief a boolean check to see if the tile a player has landed on, or that tile has a candy store on it
 * 
 * @param board_position 
 * @return true 
 * @return false 
 */
bool Board::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if(_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief a mutator function that sets the color of a tile to the input
 * 
 * @param color 
 * @param tile_index 
 */
void Board::setTileColor(string color, int tile_index)
{
    _tiles[tile_index].color = color;
}

/**
 * @brief a mutator that sets a specific tile to a type at and inputed index
 * 
 * @param type 
 * @param tile_index 
 */
void Board::setTileType(string type, int tile_index)
{ 
    _tiles[tile_index].type = type;
}

/**
 * @brief mutator that sets a tile to have a hidden treasure
 * 
 * @param hasHiddenTreasure 
 * @param tile_index 
 */
void Board::setHasHiddenTreasure(bool hasHiddenTreasure, int tile_index)
{
    _tiles[tile_index].hasHiddenTreasure = hasHiddenTreasure;
}

void Board:: setHasCandyStore (bool hasCandyStore, int tile_index)
{
    _tiles[tile_index].hasCandyStore = hasCandyStore;

    if(hasCandyStore == false)
    {
        return;
    }
    
    for(int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        if(_candy_store_position[i] == -1) //if index is empty add in a candy store position
        {
            _candy_store_position[i] = tile_index;
            _candy_store_count++;
            break;
        }
    }
}

void Board::setHasCandylandPlayer(bool hasCandyLandPlayer, int tile_index)
{
    _tiles[tile_index].hasCandylandPlayer = hasCandyLandPlayer;
}

void Board::setIsSpecial(bool isSpecial, int tile_index)
{
    _tiles[tile_index].isSpeical = isSpecial;
}

/**
 * @brief moves the player on the board. for display.
 * 
 * @param current 
 * @return true 
 * @return false 
 */
bool Board::movePlayer(CandylandPlayer current) 
{
   // int new_player_position = current.getCurrentPlayerPosition(); //current. getplayer postion
    if(current.getCurrentPlayerPosition() < 0 || current.getCurrentPlayerPosition() >= _BOARD_SIZE)
    {
        return false;
    }
    _player_position = current.getCurrentPlayerPosition();
    //call current.setplayer postion(newplayer positon) isntead of above line
    //find (using getTile) tile in total tile array using players new posiiton and then return true
    return true;
    
}

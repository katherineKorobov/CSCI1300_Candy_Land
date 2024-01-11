#ifndef CANDYLANDPLAYER_H
#define CANDYLANDPLAYER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Candy
{
    string name; //candy name
    string description; //candy description
    double price; //candy price
    string effect_type; //what part of player the candy affects
    int effect_value; //the amount it affects the player
    string candy_type; //candy type
};

struct Character
{
    string name;
    int stamina;
    double gold;
    Candy character_candies[9];
    int const CHARACTER_CANDY_MAX = 9;
    void printCandies()
    {
        // for loop that prints the _inventory (name)
        Candy empty; //empty struct 
        for(int i = 0; i< CHARACTER_CANDY_MAX; i++)
        {
            if(i % 3 == 0 && i !=0) //for each even index, start on new line && can't start new line in the beginning
            {
                cout<<"|";
                cout<<endl;
            } 
        
            if(character_candies[i].name == empty.name) //if the _inventory struct has an empty name, then don't display name 
            {
                cout<<"|[Empty]";
                continue; //if it couts then there is no need to keep going with the code, and move to the next array index
            }   

            cout<<"|["<<character_candies[i].name<<"]"; //happy case where you can just print out the name
        }
        cout<<"|";
        cout<<endl;
        //NOT TESTED SINCE CHANGING THE I % TO I%3
    }
};

class CandylandPlayer
{
private:
    const static int _MAX_CANDY_AMOUNT = 9; //max number of candies the player can have in their inventory (4)
    int _stamina; // current energy
    double _gold; //value of the players current money
    string _effect; //name of current effect
    Candy _inventory[_MAX_CANDY_AMOUNT]; //array to store the candy
    int _candy_amount; //amount of intitialized candy structs in the inventory array
    string _real_name = "";//name of the person who is playing 
    string _character_name= "";
    int _player_id; //how the player is represented on teh board
    int _current_player_position; //-> the board tells if valid position, but each player should keep their own position, add getters and seters
    int _past_player_position;
    bool _skip_turn;

public:
    CandylandPlayer(); //creates new instance of Player with all null values
    CandylandPlayer(int, double, string, string, string, int, int, int); //creates new instance of Player and sets data
    
    int getCandyAmount() const; // returns the _amount_candy in _inventory 

    void setStamina(int); //sets _stamina to user's input
    int getStamina() const; //returns private variable _stamina 

    void setGold(double); //sets gold to user's input
    double getGold() const; //returns private variable _gold

    void setEffect(string); //sets effeect to user's input
    string getEffect() const; //returns the _effect

    void setRealName(string);
    string getRealName() const;

    void setPlayerID(int); //player ID is how the player is represented on teh board
    int getPlayerID () const;

    void setCurrentPlayerPosition(int);
    int getCurrentPlayerPosition() const;

    void setPastPlayerPosition(int);
    int getPastPlayerPosition() const;

    void setCharacterName(string);
    string getCharacterName();

    void setSkipTurn(bool);
    bool getSkipTurn();

    void printInventory(); //prints inventory to terminal
    string getInventory();
    // void printCharacter(); //print all character stats and invetory //NEW!!!!ADDDDDDDDDDD
    
    Candy findCandy(string); //returns the Candy struct that we tried to find
    bool addCandy(Candy); //will add a struct to the inventory given enough space
    bool removeCandy(string); //will remove a struct from the inventory given that it is there

    vector <Candy> initializeCandies();
    bool initializedCandies;
    
    vector <Character> initializeCharacters();
    bool initializedCharacters;

    void setPlayer(string, int, vector <Character>& all_characters);

    void displayPlayer();

    void useCandy(string, vector <CandylandPlayer>&);

    void magicalCandy(Candy);

    void poisionCandy(Candy, vector<CandylandPlayer>&);

    void gummyCandy(Candy, vector<CandylandPlayer>&);

    void treasureCandy(Candy);
    
    
};

#endif
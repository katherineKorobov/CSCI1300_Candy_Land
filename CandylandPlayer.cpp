#include "CandylandPlayer.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/***
 * @brief toLowerCase is a function which takes in a string that needs to be changed to all lowercase. This function is useful for comparing strings without dealing with capital letters
 * @param ConvertToLower which is a string that needs to be changed to all lowercase
 * @return the lower case string. same string, but fully lowercase
 * 
*/
string toLowerCase(string ConvertToLower) //makes sure that it checks case INSENSITIVE (ie. changes any string inputed to lowercase)
{
    int string_length = ConvertToLower.length();
    for(int i =0; i < string_length; i++) //iterate through the string 
    {
        if(ConvertToLower[i] >= 65 && ConvertToLower[i] <=90) //use ASCII table for when the character is uppercase
        {
            ConvertToLower[i] += 32; //then add 32 to go to lowercase ASCII
        }
    }
    return ConvertToLower; //return lowercase string
}

/**
 * @brief This function will generate a random int between the provided min and max. It is a global function.
 *
 * @param min is the smallest value the random number it can be
 * @param max is the largest value the random number can be
 * @return int is a random number
 */
int generateRandom(int min, int max) // will generate a random number between the min input and maxinput
{
    return (rand() % (max - min + 1) + min);
}

/**
 * @brief default constructor. Sets all private variables of the player to null or zero.
 * 
 */
CandylandPlayer ::CandylandPlayer() 
{
    _stamina = 0; 
    _gold = 0.00;
    _effect = "";

    Candy empty;
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        _inventory[i] = empty; // for loop sets all elements of the array _inventory equal to an empty struct
    }

    _candy_amount = 0;
    string _real_name = "";
    string _character_name = "";
    //int _player_id = 0;
    //int _current_player_position = 0;
    //int _past_player_position = 0;
}

/**
 * @brief Construct a new Candyland Player:: Candyland Player object. parameterized constructor. private variables change, inventory is set to empty structs.
 * 
 * @param stamina is the stamina of the player
 * @param gold is the gold of the player
 * @param effect is the  effect of the player??
 * @param real_name is the real name of the player
 * @param character_name is the character name the player chooses
 * @param player_id is how the player is represented on the board
 * @param current_posiiton is the current position of the player on the board
 * @param past_position is the past position of the player on the board
 */
CandylandPlayer::CandylandPlayer(int stamina, double gold, string effect, string real_name, string character_name, int player_id, int current_posiiton, int past_position) //parameterized constructor - sets everything exept the _inventory 
{
    _stamina = stamina;
    _gold = gold;
    _effect = effect;
    _real_name = real_name;
    _character_name = character_name;
    _player_id = player_id;
    _current_player_position = current_posiiton;
    _past_player_position = past_position;
    _candy_amount = 0;

    Candy empty_candy= {"", "", 0, "", 0, ""};
    for(int i = 0; i < 8; i++)
    {
        _inventory[i] = empty_candy;
    }

    //NOT TESTED YET, do i need this??

}

int CandylandPlayer::getCandyAmount() const
{
    return _candy_amount;
}

void CandylandPlayer::setStamina(int stamina) 
{
    _stamina = stamina;
}

int CandylandPlayer:: getStamina() const
{
    return _stamina;
}

void CandylandPlayer::setGold(double gold)
{
    _gold = gold;
}

double CandylandPlayer::getGold() const
{
    return _gold;
}

void CandylandPlayer::setEffect(string effect)
{
    _effect = effect;
}

string CandylandPlayer::getEffect() const
{
    return _effect;
}

void CandylandPlayer::setRealName(string player_name)
{
    _real_name = player_name;
}

string CandylandPlayer::getRealName() const
{
    return _real_name;
}

void CandylandPlayer::setPlayerID(int player_id)
{
    _player_id = player_id;
}

int CandylandPlayer::getPlayerID () const
{
    return _player_id;
}

void CandylandPlayer:: setCurrentPlayerPosition(int player_current_position)
{
    _current_player_position = player_current_position;
}

int CandylandPlayer:: getCurrentPlayerPosition() const
{
    return _current_player_position;
}

void CandylandPlayer::setPastPlayerPosition(int player_past_position)
{
    _past_player_position = player_past_position;
}

int CandylandPlayer:: getPastPlayerPosition() const
{
    return _past_player_position;
}   

void CandylandPlayer:: setCharacterName(string name)
{
    _character_name = name;
}

string CandylandPlayer:: getCharacterName()
{
    return _character_name;
}

void CandylandPlayer::setSkipTurn(bool skip_turn)
{
    _skip_turn = skip_turn;
}

bool CandylandPlayer::getSkipTurn()
{
    return _skip_turn;
}

/**
 * @brief pritnts the inventory of the player. if the player has empty slots in their inveontory, it will print empty
 * 
 */
void CandylandPlayer::printInventory()
{
    // for loop that prints the _inventory (name)
    Candy empty; //empty struct 
    for(int i = 0; i< _MAX_CANDY_AMOUNT; i++)
    {
        if(i % 3 == 0 && i !=0) //for each even index, start on new line && can't start new line in the beginning
        {
            cout<<"|";
            cout<<endl;
        } 
        
        if(_inventory[i].name == empty.name) //if the _inventory struct has an empty name, then don't display name 
        {
            cout<<"|[Empty]";
            continue; //if it couts then there is no need to keep going with the code, and move to the next array index
        } 

        cout<<"|["<<_inventory[i].name<<"]"; //happy case where you can just print out the name
    }
    cout<<"|";
    cout<<endl;
}

/**
 * @brief this function will find a candy in the players inventory. will find the candy regardless of capitalization. 
 * 
 * @param candy_to_find is the name of the candy that the function will try to find in the players inventory
 * @return Candy is the Candy struct that is returned when the candy is found. if it does not find the candy in the inventory it will return an empty struct and if it finds the correct candy it will be the candy with the same string name
 */
Candy CandylandPlayer::findCandy(string candy_to_find)
{
    Candy empty; //empty struct

    for(int i = 0; i < _MAX_CANDY_AMOUNT; i++) //cycle through full array
    {
        if(toLowerCase(candy_to_find) == toLowerCase(_inventory[i].name)) //if the lowercase names of the index and string inputed, then it is a match
        {
            return _inventory[i]; //we return the candy struct 
        }
    }
    return empty; //else we will return an empty struct
    
}

/**
 * @brief The function adds candy to the players inventory if there is space in it. 
 * 
 * @param add_candy is the candy struct that is trying to be added into the inventory of the player
 * @return true if the candy is added to the players inventory and the candyamount is +1
 * @return false if no space is found in the inventory for an candy to be added too
 */
bool CandylandPlayer::addCandy(Candy add_candy) //will add a Candy of the user's choice to the inventory if there is space in the _inventory
{
    Candy empty;
    for(int i = 0; i < _MAX_CANDY_AMOUNT; i++)//running through array
    {
        if(_inventory[i].name == empty.name) //if there is an empty index within the array, then add Candy to array at that index and return true
        {
            _inventory[i]= add_candy;
            _candy_amount++; //add one to the _candy_amount becauase a Candy was just addd
            return true;
        }
    }
    return false; //false if it never finds an empty spot in the array
}

/**
 * @brief The function removes a candy struct from the players inventory. wil find the candy needed to remove and replace it with an empty strut
 * 
 * @param remove_candy is the string of the name of the candy struct that is going to be removed
 * @return true if the candy is removed and the index is set to an empty struct
 * @return false if the candy struct cannot be found 
 */
bool CandylandPlayer::removeCandy(string remove_candy) //will remove a candy of the user's choice (user will input the name of the candy they want to rid and we find it and delete it)
{
    Candy empty;//empty struct
    string removeInLower = toLowerCase(remove_candy); //take inputed string and change it into lowercase
    for(int i = 0; i < _candy_amount; i++) //the array should be compact, so only need to go until _candy_amount
    {
        string elementInLower = toLowerCase(_inventory[i].name); //change each element.name in array to lowercase and check if they match.

        if(removeInLower == elementInLower)//if the lowercase are equal
        {
            
            if (_candy_amount - 1 == i) //this is checking if the element we want to delete is at the end of the array. if it is, then all we need to do is make the end = to an empty struct
            {
                _inventory[i] = empty;
                _candy_amount --; //subtract one from _candy_amount because there is one less candy in the array
                return true;
            }
            else //when we may want to delete an element in the middle of the array
            {
                for(int j = i; j < _candy_amount - 1; j++) //will go until the end of the candy_amount - 1 because we don't wanna go off our bounds during the shift
                {
                    _inventory[j] = _inventory[j + 1]; //then shift the array elements over 

                }
                _inventory[_candy_amount - 1] = empty; //set the last element that was previously a vlaue before shift equal to empty
                _candy_amount--; //subtract one from teh candy amount
                return true;
            }
        }
    }
    return false; //if it cannot find a name that matches, return false because it was not found.
}

/**
 * @brief removes a candy of choice from teh players inventory using teh name of the candy they wish to remove
 * 
 * @param character_choice_name 
 * @param all_characters 
 * @return true if the candy struct was found and removed from teh inventory
 * @return false if the candy struct could not be found or removed 
 */
bool removeCharacter(string character_choice_name, vector <Character>& all_characters)
{
    string remove_in_lower = toLowerCase(character_choice_name); //take inputed string and change it into lowercase
    for(int i = 0; i < int(all_characters.size()) ; i++) //should go through full vector of characters 
    {
        string element_in_lower = toLowerCase(all_characters.at(i).name); //change each element.name in array to lowercase and check if they match.

        if(remove_in_lower == element_in_lower)//if the lowercase are equal
        {
            if (int(all_characters.size()) - 1 == i) //this is checking if the element we want to delete is at the end of the array. if it is, then all we need to do is make the end = to an empty struct
            {
                all_characters.pop_back();
                return true;//this section is working
            }
            else //when we may want to delete an element in the middle of the vector
            {
                for(int j = i; j < int(all_characters.size()) - 1; j++) //will go until the end of the candy_amount - 1 because we don't wanna go off our bounds during the shift
                {
                    all_characters.at(j).name = all_characters.at(j + 1).name;//then shift the array elements over
                    all_characters.at(j).gold = all_characters.at(j + 1).gold;
                    all_characters.at(j).stamina = all_characters.at(j + 1).stamina;
                    
                    for(int k = 0; k < all_characters.at(i).CHARACTER_CANDY_MAX; k++) //sets candies
                    {
                        all_characters.at(i).character_candies[k] = all_characters.at(i+1).character_candies[k];
                    }


                }
                //all_characters.at(int(all_characters.size()) - 1) = empty; //set the last element that was previously a vlaue before shift equal to empty
                all_characters.pop_back();
                return true;
            }
        }
    }
    return false; //if it cannot find a name that matches, return false because it was not found.  
}

/**
 * @brief Set the Player object to a specific character of their choice and sets their name.
 * 
 * @param character_choice_name is the name of the character the player wants to set themselves too
 * @param player_id is how th player wants to see themselves on the board
 * @param all_characters is the vector of all the characters. pass by reference so changes can be made
 */
void CandylandPlayer:: setPlayer (string character_choice_name, int player_id, vector <Character>& all_characters)
{
    _player_id = player_id;
    _candy_amount = 0;

    Candy empty_candy= {"", "", 0, "", 0, ""}; //all of this may work but havent tested *crosses fingers*
    bool character_name_found = false;
    int index_to_delete;

    for(int i = 0; i < int(all_characters.size()); i++) //run through vector of all characters
    {
        if(character_choice_name == all_characters.at(i).name) //find if the names equal, then set 
        {
            character_name_found = true;
            index_to_delete = i;
            break;
        
        }
        character_name_found = false;
            
    }

    if(character_name_found == true)
    {
        _character_name = all_characters.at(index_to_delete).name;
        _stamina = all_characters.at(index_to_delete).stamina;
        _gold = all_characters.at(index_to_delete).gold;


        for(int k = 0; k < 9; k++)
        {
            _inventory[k] = all_characters.at(index_to_delete).character_candies[k];
            if(all_characters.at(index_to_delete).character_candies[k].name != empty_candy.name) //if there is not an empty part of the inventory, then add 
            {
                _candy_amount++;
            }
        }
        cout<<getRealName()<<" has successfully set their player with "<<all_characters.at(index_to_delete).name<<"!"<<endl;

        //after setting the player to the character, we need to remove that character from the vector of all_characters
        removeCharacter(all_characters.at(index_to_delete).name, all_characters); //should delete element of vector

    }
    else
    {
        cout<<"No character was found!"<<endl;

    }
    _current_player_position = 0;
    _past_player_position = 0;
}

/**
 * @brief will display a players stats.
 * 
 */
void CandylandPlayer::displayPlayer() //displays all stats of the player
{
    cout<<"Here are your stats:"<<endl;
    cout<<"Player Name: "<<getRealName()<<endl;
    cout<<"Character Name: "<<getCharacterName()<<endl;
    cout<<"Amount of Gold: "<<getGold()<<endl;
    cout<<"Amount of Stamina: "<<getStamina()<<endl;
    cout<<"Inventory: ";
    printInventory();
}

/**
 * @brief goes through specific cases of using all magical candies
 * part of the use candy function.
 * 
 * @param candy_to_use 
 */
void CandylandPlayer::magicalCandy(Candy candy_to_use)
{   
    //could use private variables or getters and setters
    if(candy_to_use.name == "Frosty Fizz")
    {
        if(getStamina() >= 90) //can't go over the max stamina. 100 - 10 = 90
        {
            setStamina(100);
        }
        else
        {
            setStamina(getStamina() + 10); //add ten to stamina
        }
        removeCandy(candy_to_use.name);
        cout<<"You have used Frosty Fizz. This has increased your stamina by 10 points."<<endl;
        return;
    }
    else if (candy_to_use.name == "Crimson Crystal")
    {
        if(getStamina() >= 85) //can't go over the max stamina 100 - 15 = 85
        {
            setStamina(100);
        }
        else
        {
            setStamina(getStamina() + 15); //add ten to stamina
        }
        removeCandy(candy_to_use.name);
        cout<<"You have used Crimson Crystal. This has increased your stamina by 15 points."<<endl;
        return;
    
    }
    else if (candy_to_use.name == "Mystic Marshmallow")
    {
        if(getStamina() >= 80) //can't go over the max stamina 100 - 20 = 80
        {
            setStamina(100);
        }
        else
        {
            setStamina(getStamina() + 20); //add ten to stamina
        }
        removeCandy(candy_to_use.name);
        cout<<"You have used Mystic Marshmallow. This has increased your stamina by 20 points."<<endl;
        return;
    }
    
}

/**
 * @brief goes through specific cases of using all poision candies
 * part of the use candy function.
 * 
 * @param candy_to_use 
 * @param all_players 
 */
void CandylandPlayer::poisionCandy(Candy candy_to_use, vector <CandylandPlayer>& all_players)
{
    int temp_index = 0;
    for(int i = 0; i < int (all_players.size()); i++)
    {
        if(getPlayerID() != all_players.at(i).getPlayerID())
        {
            temp_index = i;
            break;
        }
    }
    CandylandPlayer& affected_player = all_players.at(temp_index);

    //creating three booleans that tell if the affected player has any of the immunity candies
    bool hasCarmelComet = false;
    bool hasSparklingSapphire = false;
    bool hasBubbleGumBlast = false;

    if(affected_player.findCandy("Bubblegum Blast").name == "Bubblegum Blast")
    {
        hasBubbleGumBlast = true;
    }
    if(affected_player.findCandy("Sparkling Sapphire").name == "Sparkling Sappire")
    {
        hasSparklingSapphire = true;
    }
    if(affected_player.findCandy("Caramel Comet").name == "Caramel Comet")
    {
        hasCarmelComet = true;
    }

    if(hasCarmelComet == true)
    {
        cout<<"Uh oh! You're poisoning attempt has been thwarted because the other player had an immunity candy!"<<endl;
        affected_player.removeCandy("Caramel Comet");
        removeCandy(candy_to_use.name);
        return;

    }

    if(candy_to_use.name == "Toxic Taffy")
    {
        if(affected_player.getStamina() <= 20)
        {
            affected_player.setStamina(0);
        }
        else
        {
            affected_player.setStamina(getStamina() - 20);
        }
        removeCandy(candy_to_use.name);
        return;
    }
    else if(candy_to_use.name == "Venomous Vortex")
    {
        if(hasSparklingSapphire == true)
        {
            cout<<"Uh oh! You're poisoning attempt has been thwarted because the other player had an immunity candy!"<<endl;
            return;
        }
        
        if(affected_player.getStamina() <= 15)
        {
            affected_player.setStamina(0);
        }
        else
        {
            affected_player.setStamina(getStamina() - 15);
        }
        affected_player.removeCandy("Sparkling Sapphire");
        removeCandy(candy_to_use.name);
        return;
        
    }
    else if(candy_to_use.name == "Lucky Licorice")
    {
        if(hasSparklingSapphire== true || hasBubbleGumBlast == true)
        {
            cout<<"Uh oh! You're poisoning attempt has been thwarted because the other player had an immunity candy!"<<endl;
            return;
        }

        if(affected_player.getStamina() <= 10)
        {
            affected_player.setStamina(0);
        }
        else
        {
            affected_player.setStamina(getStamina() - 10);
        }
        
        if(affected_player.removeCandy("Sparkling Sapphire") == false) //executes the remove and moves on unless it fails
        {
            affected_player.removeCandy("Bubblegum Blast");
        }

    }
}

/**
 * @brief goes through specific cases of using all gummy candies
 * part of the use candy function.
 * 
 * @param candy_to_use 
 * @param all_players 
 */
void CandylandPlayer::gummyCandy(Candy candy_to_use, vector <CandylandPlayer>& all_players)
{
    int temp_index = 0;
    for(int i = 0; i < int (all_players.size()); i++)
    {
        if(getPlayerID() != all_players.at(i).getPlayerID())
        {
            temp_index = i;
            break;
        }
    }
    CandylandPlayer& affected_player = all_players.at(temp_index);

    if(candy_to_use.name == "Ruby Rupture")
    {
        affected_player.setSkipTurn(true);
        removeCandy(candy_to_use.name);
        cout<<"You have used Ruby Rupture on your opponent!"<<endl;
        return;
    }
    else if(candy_to_use.name == "Fearsome Fudge")
    {
        affected_player.setSkipTurn(true);
        removeCandy(candy_to_use.name);
        cout<<"You have used Fearsome Fudge on your opponent!"<<endl;
        return;
    }
}

/**
 * @brief goes through specific cases of using all treasure candies. ie candies from the hidden treasures
 * part of the use candy function.
 * 
 * @param candy_to_use 
 */
void CandylandPlayer::treasureCandy(Candy candy_to_use)
{
    if(candy_to_use.name == "Jellybean of Vigor")
    {
        if(getStamina() >= 50)
        {
            setStamina(100);
        }
        else
        {
            setStamina(getStamina() + 50); 
        }
        removeCandy(candy_to_use.name);
        cout<<"You have used Jellybean of Vigor. This has increased your stamina by 50 points."<<endl;
        return;
    }
}

/**
 * @brief this is the use candy which is called when teh user selects 2 in the game. if the user has inputed a correct input, then it will sort the candy by type and call it respective function
 * 
 * @param usable_candy 
 * @param all_players 
 */
void CandylandPlayer::useCandy(string usable_candy, vector <CandylandPlayer>& all_players)
{
    if (findCandy(usable_candy).name == "") // if didn't return an empty struct, meaning it didn't find it
    {
        cout << "The candy was not found in your inventory." << endl;
        return;
    }

    Candy candy_to_use = findCandy(usable_candy);
    if(candy_to_use.candy_type == "magical")
    {
        magicalCandy(candy_to_use);
    }
    else if(candy_to_use.candy_type == "poison")
    {
        poisionCandy(candy_to_use, all_players);
    }
    else if(candy_to_use.candy_type == "gummy")
    {
        gummyCandy(candy_to_use, all_players);
    }
    else if (candy_to_use.candy_type == "Treasure")
    {
        treasureCandy(candy_to_use);
    }
}

/**
 * @brief gets inventory of player
 * 
 * @return string 
 */
string CandylandPlayer::getInventory()
{
    string all_candies_in_inventory = "";
    string temp_to_add = "";

    for(int i = 0; i < _candy_amount; i++)
    {
        temp_to_add = _inventory[i].name;
        all_candies_in_inventory += " | "+ temp_to_add;
    }

    return all_candies_in_inventory;

}
#include "candystore.h"

#include <iostream>
#include <vector>

using namespace std;

int generateRandom(int min, int max);

string toLowerCase(string ConvertToLower);
//no default constructor, so one is automatically generated in compilation

/**
 * @brief a function that calls all the functions for when a player is in the candy store
 * 
 * @param current_player 
 * @param all_candies 
 */
void CandyStore::inCandyStore(CandylandPlayer& current_player, vector <Candy> all_candies)
{
    setCandystoreInventory(all_candies);
    displayCandyStore();
    buyFromCandyStore(current_player);
}

int CandyStore::getMaxInventory()
{
    return _MAX_INVENTORY_CANDYSTORE;
}
int CandyStore::getNumOfCandystore()
{
    return _MAX_NUM_OF_CANDYSTORE;
}

/**
 * @brief intitialzises and array of cnady strutcts. randomly selects one of each candy type (besides immunity) to offer.
 * 
 * @param all_candies 
 */
void CandyStore::setCandystoreInventory(vector <Candy> all_candies)
{
    for(int i = 0; i < int(all_candies.size()); i++)
    {
        if(all_candies.at(i).candy_type == "magical")
        {
            _available_magical.push_back(all_candies.at(i));
        }
        else if(all_candies.at(i).candy_type == "poison")
        {
            _available_poision.push_back(all_candies.at(i));
        }
        else if(all_candies.at(i).candy_type == "gummy")
        {
           _available_gummy.push_back(all_candies.at(i));
        }
    }

    int rand_candy_index;

    for(int i = 0; i < _MAX_INVENTORY_CANDYSTORE; i++)
    {
        if(i ==0)
        {
            int vec_size_m = _available_magical.size();
            rand_candy_index = generateRandom(0,vec_size_m - 1);
            _candystore_inventory[0] = _available_magical.at(rand_candy_index);

        }
        else if(i ==1)
        {
            int vec_size_p = _available_poision.size();
            rand_candy_index = generateRandom(0,vec_size_p - 1);
            _candystore_inventory[1] = _available_poision.at(rand_candy_index); 
        }
        else if (i == 2)
        {
            int vec_size_g = _available_gummy.size();
            rand_candy_index = generateRandom(0, vec_size_g - 1);
            _candystore_inventory[2] = _available_gummy.at(rand_candy_index);
        }
    }

}
/**
 * @brief displays the candy store inventory
 * 
 */
void CandyStore::displayCandyStore()
{
    cout << "Here is a list of candies in the candy store: " << endl;
    for(int i = 0; i < 3; i++)
    {
        cout << "Name:" << _candystore_inventory[i].name<< endl;
        cout << "Description: " << _candystore_inventory[i].description << endl;
        cout << "Effect: " << _candystore_inventory[i].effect_value << endl;
        cout << "Effect value: " << _candystore_inventory[i].effect_type<< endl;
        cout << "Candy type: "<<  _candystore_inventory[i].candy_type<< endl;
        cout << "Price: " << _candystore_inventory[i].price << endl;
        cout <<"---------------------------------------------------------------"<<endl;
    }

}

/**
 * @brief called when the user wants to buy a candy. 
 * 
 * @param current_player 
 */
void CandyStore::buyFromCandyStore(CandylandPlayer& current_player)
{
    string user_candy_choice;
    Candy candy_choice;
    char user_Y_N;
    cout << "Which candy would you like to buy? " << endl;
    cin.clear();
    cin.ignore(1000, '\n');
    getline(cin, user_candy_choice);

    if(current_player.getCandyAmount() == 9)
    {
        cout << "You do not have sufficient place in the candy inventory. Would you like to substitute your candy with existing candy? (y/n)" << endl;
        cin>>user_Y_N;

        while((user_Y_N != 'y' && user_Y_N != 'n' ) || cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cin>>user_Y_N;
        }
        if(user_Y_N == 'n')
        {
            cout<<"Thank you for visiting the CandyStore! Safe travels!"<<endl;
            return;
        }
        else
        {
            string player_inventory_candy;
            cout<<"What candy would you like to substitute?"<<endl;

            cout<<"Here are your current candies:"<<endl;
            current_player.printInventory();

            cin.clear();
            cin.ignore(1000, '\n');
            getline(cin, player_inventory_candy);

            if(current_player.removeCandy(player_inventory_candy) == false)
            {
                cout<<"Candy could not be subsituted."<<endl;
                while(current_player.removeCandy(player_inventory_candy) == false)
                {
                    cout<<"Try again."<<endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cin>>player_inventory_candy;
                }
                
            }
            //if it gets down to here, teh candy has been removed
        }
    }
    
    int index_of_candy_choice = -1; //unvlaid index

    while(index_of_candy_choice == -1)
    {
        for(int i = 0; i < _MAX_INVENTORY_CANDYSTORE; i++) //go through candies and search for the name of teh candy teh player wants
        {
            if(toLowerCase(user_candy_choice) == toLowerCase(_candystore_inventory[i].name))
            {
                index_of_candy_choice = i; //get index of the candy in the inventory if it is in there
                break;
            }
        }
    }

    candy_choice = _candystore_inventory[index_of_candy_choice];

    if(candy_choice.price > current_player.getGold())
    {
        cout<<"You are unable to buy this candy because you don't have enough gold."<<endl;
        return;
    }
    else
    {
        current_player.setGold(current_player.getGold() - candy_choice.price);
        current_player.addCandy(candy_choice);
        cout<<"Candy added!"<<endl;
        cout<<"Thank you for visiting the CandyStore! Safe travels!"<<endl;

    }

}


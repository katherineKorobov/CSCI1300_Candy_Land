#include "Game.h"
#include "Board.h"
#include "CandylandPlayer.h"
#include "candystore.h"

#include <cstdlib> //needed for pseudo - random function
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int generateRandom(int min, int max); //calls to functions in CandylandPlayer.cpp

string toLowerCase(string ConvertToLower);


/**
 * @brief Construct a new Game:: Game object. the default constrution. Acts as the "main" of the class. It calls setup, play 
 *
 */
Game::Game()
{
    vector<Candy> all_candies = initializeCandies();
    vector<Character> all_characters = initializeCharacters();
    Board game_board = initializeBoardTiles();
    vector <Riddle> all_riddles = initializeRiddles();
    vector<CandylandPlayer> all_players = setupGame(all_candies, all_characters);

    playGame(all_players, game_board, all_riddles, all_candies);
}

/**
 * @brief Will draw a random card from a public array, cards_to_draw, and returns the Card struct
 * uses a randomizer function, input the range of indices possible in the array and assingn that number to an index variable
 *
 * @return a random card struct
 */
Card Game::drawCard()
{
    int index_of_card;
    Card random_card;

    index_of_card = generateRandom(0, 8);

    random_card = cards_to_draw[index_of_card];

    return random_card;
}

/**
 * @brief Get the Valid Input Of rock, paper, scissors game.
 * 
 * @param Player_Choice 
 * @return true if the user inputed a correct character
 * @return false if teh user did not input a correct character
 */
bool GetValidInputOfRPS(char Player_Choice) // makes sure that the user inputs a valid input
{
    if (Player_Choice != 'r' && Player_Choice != 's' && Player_Choice != 'p') // if the user-inputs something that is not a wanted value, return false so that they will be asked again
    {
        return false;
    }
    else
    {
        return true; // if it is something we want, then we return true and in playRockPaperScissors we can set that to an index in the array
    }
}

/**
 * @brief figures out the winner of rock paper scissors. either computer or player.
 * 
 * @param choices 
 * @return int 
 */
int DetermineWinnerOfRPS(char choices[2]) // returning index of the player in players[2] who has one the rock,paper,scissors battle
{
    char Player_Choice; // same name :( but it does the same thing (a variable that takes in the player's r,p,s choice)

    while (choices[0] == choices[1]) // player_choices are equal -> tie, ask again
    {
        cout << "Tie! Play again" << endl;

        cout << "Player, enter r, p, or s" << endl;
        cin >> Player_Choice;

        while (GetValidInputOfRPS(Player_Choice) == false) // if the user-inputs something not so good
        {
            cout << "Invalid selection!" << endl;
            cin.clear();
            cin.ignore(1000, '\n'); // clear buffer
            cin >> Player_Choice;   // ask again and replace
        }

        if (GetValidInputOfRPS(Player_Choice) == true) // if it is a correct value (r,s,p) then can set that input to an array index
        {
            choices[0] = Player_Choice; // this assigns the value inputed to their respective index (player 1 = 0, player 2 = 1)
            cin.clear();
            cin.ignore(1000, '\n'); // clear and ingnore so no funny buffer business
        }

        int computer_choice;
        int computer_rand = generateRandom(1, 3);
        if (computer_rand == 1)
        {
            computer_choice = 'r';
        }
        else if (computer_rand == 2)
        {
            computer_choice = 'p';
        }
        else
        {
            computer_choice = 's';
        }
        choices[1] = computer_choice;
    }
    if (choices[0] == 'r' && choices[1] == 's') // player 1 is r and player 2 is s -> player 1
    {
        return 0;
    }
    if (choices[0] == 'r' && choices[1] == 'p') // player 1 is r and player 2 is p -> player 2
    {
        return 1;
    }
    if (choices[0] == 's' && choices[1] == 'r') // player 1 is s and player 2 is r -> player 2
    {
        return 1;
    }
    if (choices[0] == 's' && choices[1] == 'p') // player 1 is s and player 2 is p -> player 1
    {
        return 0;
    }
    if (choices[0] == 'p' && choices[1] == 'r') // player 1 is p and player 2 is r -> player 1
    {
        return 0;
    }
    if (choices[0] == 'p' && choices[1] == 's') // player 1 is p and player 2 is s -> player 2
    {
        return 1;
    }
    return -1; // if non, then return -1, something went crazy wrong
}

/**
 * @brief "main" function of rock paper scissors game. 
 * 
 * @param current_player 
 * @return true 
 * @return false 
 */
bool playRockPaperScissors(CandylandPlayer &current_player) // function that allows user to play rock, paper, scissors
{
    char choices[2];    // array of the players r,p,s choice if valid (player 1 = index 0, player 2 = index 1)
    char player_choice; // variable to collect user input
    char computer_choice;

    cout << "Player " << current_player.getPlayerID() << ": Enter r, p, or s" << endl; // i +1 to shift display from "player 0" and "player 1" to "player 1" and "player 2"
    cin >> player_choice;                                                              // player enters a char so only need cin

    while (GetValidInputOfRPS(player_choice) == false) // if the user-inputs something not so good, chekc using helper function!
    {
        cout << "Invalid selection!" << endl;
        cin.clear();
        cin.ignore(1000, '\n'); // clear buffer
        cin >> player_choice;   // ask again and replace
    }

    if (GetValidInputOfRPS(player_choice) == true) // if it is a correct value (r,s,p) then can set that input to an array index
    {
        choices[0] = player_choice;
    }
    cin.clear();
    cin.ignore(1000, '\n'); // no funny buffer business

    int computer_rand = generateRandom(1, 3);
    if (computer_rand == 1)
    {
        computer_choice = 'r';
    }
    else if (computer_rand == 2)
    {
        computer_choice = 'p';
    }
    else
    {
        computer_choice = 's';
    }
    choices[1] = computer_choice;

    if (DetermineWinnerOfRPS(choices) == 0) // if player wins
    {
        cout << "Player has won! " << endl;
        return true;
    }

    if (DetermineWinnerOfRPS(choices) == 1) // if computer wins
    {
        cout << "The computer has won! " << endl;
        return false;
    }
    return false;
}

/**
 * @brief Will read in a specific file and split into two components of the riddles and put all parts into an vector of riddle structs
 *
 * @return vector <Riddle> is the vector of all possible riddles
 */
vector<Riddle> Game::initializeRiddles() // if file read was unable to happen or another error, then it will return false, and the game cannot continue, else it will return true
{
    // Riddle riddle_empty;
    vector<Riddle> all_riddles;
    string line;
    ifstream fin("riddles.txt");

    if (fin.fail()) // if file fails to open
    {
        cout << "Unable to initialize riddles." << endl; // return false and cannot initialize
        initializedRiddles = false;
        return all_riddles;
    }

    while (!fin.eof()) // if it does open, then read in all the riddles until the end of the file
    {
        Riddle riddle_temp;

        getline(fin, line);

        stringstream ss(line);

        getline(ss, riddle_temp.riddle_question, '|');

        getline(ss, riddle_temp.riddle_answer);

        all_riddles.push_back(riddle_temp);
    }
    initializedRiddles = true;
    return all_riddles;
}

/**
 * @brief intializes a board object. sets color tiles on the board. sets special tiles, candystores, and hidden treasures
 * 
 * @return Board 
 */
Board Game::initializeBoardTiles()
{
    Board game_board;
    game_board.resetBoard();

    for (int i = 0; i < int(game_board.getBoardSize()); i++) // initialze whole board. indices -1 but also don't want to include castle tile
    {                                                        // tile 0 to tile 82
        if (i % 3 == 0)
        {
            game_board.setTileColor(MAGENTA, i);
        }
        else if (i % 3 == 1)
        {
            game_board.setTileColor(GREEN, i);
        }
        else if (i % 3 == 2)
        {
            game_board.setTileColor(BLUE, i);
        }

        if (i == 17 || i == 26 || i == 40 || i == 80) // initiazle special tile
        {
            game_board.setIsSpecial(true, i);
            if (i == 17)
            {
                game_board.setTileType("Gingerbread House", i);
            }
            else if (i == 26)
            {
                game_board.setTileType("Ice Cream", i);
            }
            else if (i == 40)
            {
                game_board.setTileType("Shortcut", i);
            }
            else if (i == 80)
            {
                game_board.setTileType("Gumdrop", i);
            }
        }
        else
        {
            game_board.setTileType("Regular", i);
        }

        game_board.setHasCandyStore(false, i); // set candy stores

        game_board.setHasCandylandPlayer(false, i); // set all to false for now

        if (i == 82) // last tile, castle tile
        {
            game_board.setTileColor(ORANGE, i);
            game_board.setTileType("End", i);
            game_board.setIsSpecial(false, i);
        }
    }

    int rand_temp;

    do
    {
        rand_temp = generateRandom(1, 27);
        if (game_board.getTile(rand_temp).color == MAGENTA)
        {
            break;
        }
    } while (game_board.getTile(rand_temp).color == GREEN || game_board.getTile(rand_temp).color == BLUE);
    game_board.setHasCandyStore(true, rand_temp);

    do
    {
        rand_temp = generateRandom(28, 53);
        if (game_board.getTile(rand_temp).color == GREEN)
        {
            break;
        }
    } while (game_board.getTile(rand_temp).color == MAGENTA || game_board.getTile(rand_temp).color == BLUE);
    game_board.setHasCandyStore(true, rand_temp);

    do
    {
        rand_temp = generateRandom(54, 82);
        if (game_board.getTile(rand_temp).color == BLUE)
        {
            break;
        }
    } while (game_board.getTile(rand_temp).color == MAGENTA || game_board.getTile(rand_temp).color == GREEN);
    game_board.setHasCandyStore(true, rand_temp);

    
    int rand_hidden_treasure;
    for (int j = 0; j < 3; j++) // make three hidden treasures
    {
        rand_hidden_treasure = generateRandom(1, 82);
        game_board.setHasHiddenTreasure(true, rand_hidden_treasure);
    }

    return game_board;
}

/**
 * @brief Will read in all the regular (not hidden treasure/special candies) candies that are included in the game. those candies beocme initialized in a vector.
 *
 * @return vector <Candy> holds all the regular candies in the game.
 */
vector<Candy> Game::initializeCandies()
{
    vector<Candy> all_candies; // a vector that will store all candies from file
    Candy candy;               // an empty struct of type Candy which will hold eahc and every candy information as it goes into vector
    string line;               // a string of the whole line, that fin inputed and ss is reading
    string price;              // a storer of the price of the candy from using getline. used as a temporary storage in order to switch the value to an int
    string effectvalue;

    ifstream fin("candies.txt"); // open file and use fin to read

    if (fin.fail())
    {
        cout << "Unable to initialize candy." << endl;
        initializedCandies = false; // will tell if it was unable to fully initialize
        return all_candies;
    }

    while (!fin.eof())

    {
        getline(fin, line);

        stringstream ss(line);

        getline(ss, candy.name, '|');
        getline(ss, candy.description, '|');
        getline(ss, candy.effect_type, '|');
        getline(ss, effectvalue, '|');
        candy.effect_value = stoi(effectvalue);
        getline(ss, candy.candy_type, '|');
        getline(ss, price);
        candy.price = stoi(price);

        all_candies.push_back(candy); // make big candy vector!
    }
    initializedCandies = true; // once initialied then can tell
    return all_candies;        // once everything is initialized, return true
}

/**
 * @brief Will read in all the characters from a file and inititalize it into a vector of Characters.
 *
 * @return vector <Character> holds all the characters the players can choose from
 */
vector<Character> Game::initializeCharacters()
{
    vector<Character> all_characters; // a vector that will store all characters from file
    Character character;              // empty character struct for temp use
    // Candy character_inventory; //an empty struct of type Candy which will hold eahc and every candy information as it goes into vector
    string line;              // a string of the whole line, that fin inputed and ss is reading
    string character_stamina; // a storer of the price of the candy from using getline. used as a temporary storage in order to switch the value to an int
    string character_gold;
    Candy candy;
    vector<Candy> all_candies1 = initializeCandies();

    if (initializedCandies == false)
    {
        cout << "Please inialize game candies before intialzing characters" << endl;
        initializedCharacters = false;
        return all_characters;
    }

    ifstream fin("characters.txt"); // open file and use fin to read

    if (fin.fail())
    {
        cout << "Unable to initialize characters." << endl;
        // initializedCharacters = false;
        return all_characters;
    }

    while (!fin.eof())
    {

        getline(fin, line);

        stringstream ss(line);

        getline(ss, character.name, '|');
        getline(ss, character_stamina, '|');
        character.stamina = stoi(character_stamina);
        getline(ss, character_gold, '|');
        character.gold = stod(character_gold);

        string candy_in_line; // empty string
        vector<Candy> candys;

        getline(ss, candy_in_line);

        stringstream sss(candy_in_line);

        while (getline(sss, candy.name, ',')) // have chec if its blank?
        {
            if (candy.name == "") // for empty string at end of line??
            {
                break;
            }

            int len = all_candies1.size();

            for (int i = 0; i < len; i++) // cycle through vector of possible candies. initializeCandies().size()
            {

                if (candy.name == all_candies1.at(i).name) // if the names are equal
                {
                    candy = all_candies1.at(i); // set structs of candy equal to each other
                    candys.push_back(candy);
                }
            }
            int number_candy = 0;
            for (int i = 0; i < int(candys.size()); i++)
            {
                character.character_candies[i] = candys.at(i);
                if (character.character_candies[i].name != "") // this may not be worth
                {
                    number_candy++; // adds one if the index is a candy
                }
            }

            Candy empty_candy = {"", "", 0, "", 0, ""}; // all of this may work but havent tested *crosses fingers*
            for (int i = number_candy + 1; i < 9; i++)  // this is for all the empty parts. set it to empty jsut in case.
            {
                if (character.character_candies[i].name == "")
                {
                    character.character_candies[i] = empty_candy;
                }
            }
        }
        all_characters.push_back(character);
    }
    initializedCharacters = true;
    return all_characters; // once everything is initialized, return true
}

/**
 * @brief will display all the characters availaible. should actually pass in a a vector.
 *
 */
void Game::displayCharacters(vector<Character> &all_characters)
{
    if (initializedCharacters == false)
    {
        cout << "Cannot display characters if characters are not initialzed." << endl;
        return;
    }

    cout << "Awesome! Here is a list of characters a player can select from:" << endl;

    for (int i = 0; i < int(all_characters.size()); i++)
    {
        cout << "Name: " << all_characters.at(i).name << endl;
        cout<< "Gold: " << all_characters.at(i).gold <<endl;
        cout << "Stamina:" << all_characters.at(i).stamina << endl;
        cout << "Candies: " << endl;
        ;
        all_characters.at(i).printCandies();
        cout << "-----------------------------------------------------------------" << endl;
    }
}

/**
 * @brief This function initializes players and lets players choose their characters and asks if they want to use teh candystore before starting the game.
 *
 * @return CandylandPlayer
 */
vector<CandylandPlayer> Game::setupGame(vector<Candy> all_candies, vector<Character> &all_characters)
{
    vector<CandylandPlayer> all_players1;

    if (initializedCandies == true && initializedCharacters == true)
    {
        cout << "Welcome to the game of candyland. Please enter the two participants." << endl;

        vector<CandylandPlayer> all_players;
        string temp_player_name;
        string temp_character_name;
        CandylandPlayer temp_player;

        for (int i = 0; i < NUM_OF_PLAYERS; i++)
        {
            cout << "Enter player name:" << endl;
            cin >> temp_player_name;

            for (int j = 0; j < int(all_players.size()); j++) // cycles through player array to check if duplicates
            {
                while (temp_player_name == all_players.at(j).getRealName())
                {
                    cout << "Two Players cannot have the same name. Please choose another." << endl;
                    cin >> temp_player_name;
                }
            }
            all_players.push_back(temp_player);
            all_players.at(i).setRealName(temp_player_name);

            bool character_found = false;
            do
            {
                displayCharacters(all_characters);

                cout << "The selected character is: " << endl;
                cin >> temp_character_name;

                for (int j = 0; j < int(all_characters.size()); j++) // find if there is a name taht matches
                {
                    if (temp_character_name != all_characters.at(j).name)
                    {
                        character_found = false;
                        continue;
                    }
                    else
                    {
                        character_found = true;
                        break;
                    }
                }
                if (character_found == false)
                {
                    cout << "Invalid input. Please try again!" << endl;
                }
            } while (character_found == false); // if the person cannot input correctly (multiple times!!)

            all_players.at(i).setPlayer(temp_character_name, i, all_characters); // outside while. must be true that the character was found.

            char user_y_n;
            cout<<"Do you want to visit the candy store? (y/n)"<<endl;
            cin>>user_y_n;

            if((user_y_n != 'y' && user_y_n != 'n') || cin.fail())
            {
                while((user_y_n != 'y' && user_y_n !='n') || cin.fail())
                {
                    cin>>user_y_n;
                }
            }
            if(user_y_n == 'y')
            {
                CandyStore store;
                store.inCandyStore(all_players.at(i), all_candies); 
            }  

        }
        return all_players;
    }
    else
    {
        cout << "Please initialize characters and candies before setting players." << endl;
        return all_players1;
    }
}

/**
 * @brief if either player is on teh castle, it will call the endGame
 * 
 * @param all_players 
 * @return true 
 * @return false 
 */
bool Game::onCastle(vector<CandylandPlayer> &all_players)
{
    for (int i = 0; i < int(all_players.size()); i++)
    {
        if (all_players.at(i).getCurrentPlayerPosition() >= 82) // 82 is index of last tile
        {
            return true;
        }
    }
    return false;

    // this will check the players current posiiton and return true or false based on if they are on the last candy tile or not
    // this can check at the end of each turn of the player
}

/**
 * @brief prints out the stats and reads all teh data of the players into a new file
 * 
 * @param all_players 
 */
void Game::endGame(vector<CandylandPlayer> &all_players)
{
    int index_of_winning_player;
    for (int i = 0; i < int(all_players.size()); i++)
    {
        if (all_players.at(i).getCurrentPlayerPosition() >= 82)
        {
            index_of_winning_player = i;
        }
    }
    cout << "Congratualtions " << all_players.at(index_of_winning_player).getRealName() << "! You have won the game of Candyland." << endl;
    for (int i = 0; i < int(all_players.size()); i++)
    {
        all_players.at(i).displayPlayer();
    }

    ofstream ofs("all_candyland_player_stats.txt");
    if (ofs.is_open())
    {
        ofs << "Player Name: "<< all_players.at(0).getRealName()<<endl;;
        ofs << "Character Name: "<<all_players.at(0).getCharacterName()<<endl;
        ofs << "Gold: "<<all_players.at(0).getGold()<<endl;
        ofs << "Stamina: "<<all_players.at(0).getStamina()<<endl;
        ofs << "Candies: "<<all_players.at(0).getInventory() << endl;

        ofs <<"--------------------------------------------------------------"<<endl;

        ofs << "Real Name: "<<all_players.at(1).getRealName() << endl;
        ofs << "Character Name: "<< all_players.at(1).getCharacterName() << endl;
        ofs << "Gold: "<<all_players.at(1).getGold()<<endl;;
        ofs << "Stamina: "<<all_players.at(1).getStamina() << endl;
        ofs << "Candies: "<<all_players.at(1).getInventory() << endl;

        ofs <<"--------------------------------------------------------------"<<endl;
    }
    // this will end the game. return and then output the final stats of the players and send them to a file
    // based on the onCastle function
    // figure out which player has won and is on 82 or is more than 82
}

/**
 * @brief does a randomizer and checks if teh calamity occurs on the tile
 * 
 * @param tile 
 * @return true 
 * @return false 
 */
bool Game::doesCalamityOccur(Tile tile)
{
    if (tile.isSpeical)
    {
        return false;
    }
    else
    {
        int percent_num = generateRandom(0, 100);
        if (percent_num >= 0 && percent_num <= 40)
        {
            return true;
        }
    }
    return false;

    // this checks if a calamity occurs. once a tile is landed on, then we can check if a calmity occurs using  a random number generator
    // will turn true if it does, and false if there is no calamity
    // may need to move this to the game class, as it is more of a turn attribute rather than a tile attribute
}

/**
 * @brief if teh above function returns true, then the calmity has occured and it will go through a random generator to select teh calmity that happens to the player
 * 
 * @param current_player 
 */
void Game::calamityOccurs(CandylandPlayer &current_player)
{
    int calamity_type = generateRandom(1, 100);

    if (calamity_type > 0 && calamity_type <= 15) // 15% chance?
    {
        cout << candy_avalanche.message << endl;

        if (playRockPaperScissors(current_player) == false)
        {
            int rand_stamina = generateRandom(5, 10);

            if (current_player.getStamina() <= rand_stamina)
            {
                current_player.setStamina(0);
            }
            else
            {
                current_player.setStamina(current_player.getStamina() - rand_stamina);
            }
            current_player.setSkipTurn(true);
        }
    }
    else if (calamity_type > 15 && calamity_type <= 50) // 35%
    {
        cout << lollipop_labryinth.message << endl;

        if (playRockPaperScissors(current_player) == false)
        {
            current_player.setSkipTurn(true);
        }
    }
    else if (calamity_type > 50 && calamity_type <= 80) // 30%
    {
        cout << candy_bandit.message << endl;
        int rand_gold = generateRandom(1, 10);
        
        if(current_player.getGold() <= rand_gold) //if current player has less than gold being taken away, then set to 0
        {
            current_player.setGold(0);
        }
        else
        {
                current_player.setGold(current_player.getGold() - rand_gold); 
        }
    }
    else if (calamity_type > 80 && calamity_type <= 100) // 20%
    {
        cout << taffy_trap.message << endl;

        if (current_player.findCandy("Crimson Crystal").name != "Crimson Crystal" ||
            current_player.findCandy("Frosty Fizz").name != "Frosty Fizz" ||
            current_player.findCandy("Mystic Marshmallow").name != "Mystic Marshmallow")
        {
            current_player.setSkipTurn(true);
        }
    }
}

/**
 * @brief asks teh hidden treasure riddles if the player lands on a hidden treasure
 * 
 * @param all_riddles 
 * @return true 
 * @return false 
 */
bool Game:: askTreasureRiddle(vector <Riddle>& all_riddles)
{
    cout<<"You have landed on a hidden treasure. To access the treasure, solve this riddle!"<<endl;

    string player_answer;
    int max_riddle_count = all_riddles.size();

    int rand_riddle_index = generateRandom(0, max_riddle_count -1); //doing index so -1

    cout<<all_riddles.at(rand_riddle_index).riddle_question<<endl;
    cin>>player_answer;

    if(cin.fail() || player_answer != all_riddles.at(rand_riddle_index).riddle_answer) //if input weird or not correct
    {
        cout<<"You have lost the hidden treasure."<<endl;
        return false;
    }
    else if(player_answer == all_riddles.at(rand_riddle_index).riddle_answer)
    {
        return true;
    }
    return false;
}
 
/**
  * @brief if teh user answeres teh riddle corrently it will give out a reward to the player of one of the hidden treasures
  * 
  * @param current_player 
  */
void Game::playHiddenTreasures(CandylandPlayer& current_player)
{
    int hidden_treasure_type = generateRandom(1,100); 

    if(hidden_treasure_type > 0 && hidden_treasure_type <= 30) //30%
    {
        cout<<"You have landed on the Stamina Refill Hidden Treasure!"<<endl;
        int stamina_replinish = generateRandom(10,30);
        if(100 - current_player.getStamina() >= stamina_replinish)
        {
            current_player.setStamina(100);
        }
        else
        {
            current_player.setStamina(current_player.getStamina() + stamina_replinish);
        }
        cout<<"Added "<<stamina_replinish<<" to your stamina!"<<endl;
        return;
    }
    else if(hidden_treasure_type > 30 && hidden_treasure_type <= 40) //10%
    {
        cout<<"You have landed on the Gold Windfall Hidden Treasure!"<<endl;
        int gold_to_add = generateRandom(20,40);
        if(current_player.getGold() >= 80) //100-20
        {
            current_player.setGold(100);
        }
        else
        {
            current_player.setGold(current_player.getGold() + gold_to_add);
        }
        cout<<"Added "<<gold_to_add<<" to your gold!"<<endl;
        return;
    }
    else if(hidden_treasure_type > 40 && hidden_treasure_type <= 70) //30%
    {
        cout<<"You have landed on the Robber's Repel Hidden Treasure!"<<endl;
        
        Candy Robbers_Repel = {"Robber's Repel", "Safeguards player's gold from potential theft", -1 , "Anti-Robbery", -1, "Treasure"};

        if(current_player.addCandy(Robbers_Repel) == false)
        {
            cout<<"There is no space in your inventory to add Robber's Repel."<<endl;
            return;
        }
        else
        {
            cout<<"Added "<<Robbers_Repel.name<<" to your inventory!"<<endl;
            return;
        }
    }
    else if(hidden_treasure_type >70 && hidden_treasure_type<=100)//30%
    {
        cout<<"You have landed on the Candy Acquisition Hidden Treasure!"<<endl;

        int rand_treasure_acquisition = generateRandom(1,100);

        if(rand_treasure_acquisition > 0 && rand_treasure_acquisition <= 70)
        {
            Candy jellybean = {"Jellybean of Vigor", "Boost to player energy levels", -1, "stamina", 50, "Treasure"};

            if(current_player.addCandy(jellybean) == false)
            {
                cout<<"There is no space in your inventory to add Jellybean of Vigor."<<endl;
                return;
            }
            else
            {
                cout<<"Added "<<jellybean.name<<" to your inventory!"<<endl;
                return;
            }
        }
        else if(rand_treasure_acquisition > 70 && rand_treasure_acquisition <= 100)
        {
            Candy truffle = {"Treasure Hunter's Truffle", "Unlocks hidden treasure", -1, "Treasure", -1, "Treasure"};
            
            if(current_player.addCandy(truffle) == false)
            {
                cout<<"There is no space in your inventory to add Treasure Hunter's Truffle."<<endl;
                return;
            }
            else
            {
                cout<<"Added "<<truffle.name<<" to your inventory!"<<endl;
                return;
            }
        }
    }

}

/**
 * @brief for special tiles. given teh name, it will run through and affect the player who lands on it
 * 
 * @param game_board 
 * @param current_player 
 * @param all_players 
 */
void Game::specialTile(Board game_board, CandylandPlayer& current_player, vector <CandylandPlayer>& all_players)
{
    if(game_board.getTile(current_player.getCurrentPlayerPosition()).type == "Gingerbread House")
    {
       cout<<"You have landed on the Special Tile: Gingerbread House"<<endl;
       int temp_player_position = current_player.getCurrentPlayerPosition(); //sets a temp to the previous current positoin
       current_player.setCurrentPlayerPosition(current_player.getPastPlayerPosition());
       current_player.setPastPlayerPosition(temp_player_position);

        if(current_player.findCandy("Bubblegum Blast").name == "Bubblegum Blast")
        {
            current_player.removeCandy("Bubblegum Blast");
        }
        else if(current_player.findCandy("Sparkling Sapphire").name == "Sparkling Sapphire")
        {
            current_player.removeCandy("Sparkling Sapphire");
        }
        else if(current_player.findCandy("Caramel Comet").name == "Caramel Comet")
        {
           current_player.removeCandy("Caramel Comet"); 
        }
        else
        {
            cout<<"No Immunity Candy in the Player's inventory to delete."<<endl;
        }
        cout<<"It's a bittersweet return to your previous location, accompanied by the forfeiture of one immunity candy"<<endl;
        return;
    }
    else if(game_board.getTile(current_player.getCurrentPlayerPosition()).type == "Ice Cream")
    {
        //draw card again?
        //change boolean of the other player to true
        cout<<"You have landed on the Special Tile: Ice Cream"<<endl;

        int index_of_other_player;
        for(int i = 0; i < int(all_players.size()); i++)
        {
            if(current_player.getPlayerID() != all_players.at(i).getPlayerID())
            {
                index_of_other_player = i;
            }
        }
        CandylandPlayer& affected_player = all_players.at(index_of_other_player);

        affected_player.setSkipTurn(true); //skips the turn of the other player, granting the current player an "extra" trun

        cout<<"Congrats! You get a chance to draw a card again."<<endl;
    }
    else if(game_board.getTile(current_player.getCurrentPlayerPosition()).type == "Shortcut")
    {
        //set curren tplayers to position +4 if curren tpositoin is 79 then move to castle
        cout<<"You have landed on the Special Tile: Shortcut"<<endl;
        if(current_player.getCurrentPlayerPosition() >= 79)
        {
            current_player.setCurrentPlayerPosition(82);//last tile, castle
        }
        else
        {
            current_player.setCurrentPlayerPosition(current_player.getCurrentPlayerPosition() + 4);
        }
        cout<<"Your spirits soar as you're propelled four tiles ahead, closing in on the Candy Castle."<<endl;
        return;
    }
    else if(game_board.getTile(current_player.getCurrentPlayerPosition()).type == "Gumdrop")
    {
       //go back 4 itles if curren tposition is less than or equal to 4, then set to 0. rand gold lost, if less than that number, then set to 0.
        cout<<"You have landed on the Special Tile: Gumdrop"<<endl;
        if(current_player.getCurrentPlayerPosition() <= 4)
        {
            current_player.setCurrentPlayerPosition(0);
        }
        else
        {
            current_player.setCurrentPlayerPosition(current_player.getCurrentPlayerPosition() -4);
        }

        int gold_lost = generateRandom(5,10);

        if(current_player.getGold() <= gold_lost)
        {
            current_player.setGold(0);
        }
        else
        {
            current_player.setGold(current_player.getGold() - gold_lost);
        }

        cout<<"Oops, you head back 4 tiles and lose"<< gold_lost <<"gold."<<endl;
        return;
    }
}

/**
 * @brief function for if the players land on the same tile.
 * 
 * @param current_player 
 * @param all_players 
 * @param game_board 
 */
void Game::samePlayerTile(CandylandPlayer& current_player, vector<CandylandPlayer>& all_players, Board game_board)
{
    //if curren tplayer lands on this type of tile, then it is the SECOND to be there. 
    CandylandPlayer& second_player = current_player;
    int other_player;
    for(int i = 0; i < int(all_players.size()); i++)
    {
        if(second_player.getPlayerID() != all_players.at(i).getPlayerID())
        {
            other_player = i;
            break;
        }
    }
    CandylandPlayer& first_player = all_players.at(other_player);
    if(second_player.findCandy("Robber's Repel").name != "Robber's Repel") //f the second player does not have robbres repel in inventory, then the first player takes gold from second
    {
        int gold_steal = generateRandom(5,30);

        if(second_player.getGold() < gold_steal) //for scoend player 
        {
            gold_steal = second_player.getGold();
            second_player.setGold(0);

        }
        else //when second player has gold to spare
        {
            second_player.setGold(second_player.getGold() - gold_steal);
        }

        if(first_player.getGold() + gold_steal >= 100)//for ifrst player
        {
            first_player.setGold(100);
        }
        else
        {
            first_player.setGold(first_player.getGold() + gold_steal);
        }

    }

    int temp_position = first_player.getCurrentPlayerPosition(); //sets a temp to teh "current" which is now going to be the past
    first_player.setPastPlayerPosition(temp_position); //set to past
    first_player.setCurrentPlayerPosition(temp_position - 1); //sets teh new position of the player to what it was previously when they were on the tile together -1

    game_board.setHasCandylandPlayer(true, first_player.getCurrentPlayerPosition());

    game_board.movePlayer(first_player);
    
}

/**
 * @brief full play game function. controls everything from teh menu, end game, all teh tile types.
 * 
 * @param all_players 
 * @param game_board 
 * @param all_riddles 
 * @param all_candies 
 */
void Game::playGame(vector<CandylandPlayer> &all_players, Board game_board, vector<Riddle>& all_riddles, vector <Candy>& all_candies)
{
while (!onCastle(all_players))
    {
        for (int i = 0; i < int(all_players.size()); i++) // player size should be 2
        {
            CandylandPlayer &current_player = all_players.at(i); // the local variable needs to be a refernce, in order
            //.at returns refence, but if local variable is also not reference then it will return value which is a copy
            int user_select;
            
            if (current_player.getSkipTurn() == true)
            {
                cout << "You have lost your turn." << endl;
                current_player.setStamina(current_player.getStamina() +1);
                current_player.setSkipTurn(false);
                continue;
            }
            do
            {
                cout << "It's " << current_player.getRealName() << " turn." << endl;
                cout << "Please select a menu option:" << endl;
                cout << "1. Draw Card" << endl;
                cout << "2. Use Candy" << endl;
                cout << "3. Show Stats" << endl;

                cin >> user_select;

                while (cin.fail() || (user_select < 1 || user_select > 3))
                {
                    cout << "Invalid selection. Select again." << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cin >> user_select;
                }

                if (user_select == 1)
                {
                    cout << "Drawing a card from deck." << endl;
                    Card card_drawn = drawCard(); // draw card
                    cout << card_drawn.display_card << endl;

                    int targetPos;
                    for (int i = current_player.getCurrentPlayerPosition(); i < game_board.getBoardSize(); i++)
                    {
                        if (card_drawn.card_color == game_board.getTile(current_player.getCurrentPlayerPosition()).color) // if the card drawn color is teh same as the color taht the playe ris on
                        {
                            if (card_drawn.if_double == false)
                            {
                                int temp_position = current_player.getCurrentPlayerPosition();
                                current_player.setPastPlayerPosition(temp_position);
                                game_board.setHasCandylandPlayer(false, current_player.getPastPlayerPosition());
                                targetPos = i + 3; // move to the next tile of the same color
                                break;
                            }
                            else // when it IS a double card
                            {
                                int temp_position = current_player.getCurrentPlayerPosition();
                                current_player.setPastPlayerPosition(temp_position);
                                game_board.setHasCandylandPlayer(false, current_player.getPastPlayerPosition());
                                targetPos = i + 6; // have to move to the next tile of the same color and then also move to teh next tile of the same color
                                break;
                            }
                        }
                        else if (card_drawn.card_color == game_board.getTile(i).color || game_board.getTile(i).color == ORANGE)
                        {
                            if (card_drawn.if_double == false)
                            {
                                int temp_position = current_player.getCurrentPlayerPosition();
                                current_player.setPastPlayerPosition(temp_position);
                                game_board.setHasCandylandPlayer(false, current_player.getPastPlayerPosition());
                                targetPos = i;
                                break;
                            }
                            else // when it IS a double card
                            {
                                int temp_position = current_player.getCurrentPlayerPosition();
                                current_player.setPastPlayerPosition(temp_position);
                                game_board.setHasCandylandPlayer(false, current_player.getPastPlayerPosition());
                                targetPos = i + 3;
                                break;
                            }
                        }
                    }
                    if(targetPos >= 82)
                    {
                        current_player.setCurrentPlayerPosition(82);
                    }
                    else
                    {
                        current_player.setCurrentPlayerPosition(targetPos);
                    }
                    game_board.movePlayer(current_player);

                    if (game_board.getTile(current_player.getCurrentPlayerPosition()).hasCandylandPlayer)
                    {
                        samePlayerTile(current_player, all_players, game_board);
                    }
                    else
                    {
                        game_board.setHasCandylandPlayer(true, current_player.getCurrentPlayerPosition());
                    }

                    if (onCastle(all_players) || targetPos >= 82) // last tile
                    {
                        endGame(all_players);
                        return;
                    }

                    current_player.setStamina(current_player.getStamina() - 1); // move player means taht theyre stamina goes down
                    if(current_player.getStamina() == 0)
                    {
                        cout<<"Your stamina has reached 0 points. You will lose a turn."<<endl;
                        current_player.setSkipTurn(true);
                        current_player.setStamina(20);
                    } //reset stamina 

                    game_board.displayBoard(all_players);

                    if (doesCalamityOccur(game_board.getTile(current_player.getCurrentPlayerPosition())) == true) // tile at players position
                    {
                        calamityOccurs(current_player);
                    }

                    if (game_board.getTile(current_player.getCurrentPlayerPosition()).isSpeical) // if tile is special
                    {
                        specialTile(game_board, current_player, all_players);
                    }

                    if (game_board.getTile(current_player.getCurrentPlayerPosition()).hasCandyStore)
                    {
                        char user_y_n;
                        cout<<"You have landed on a tile which has a candystore."<<endl;

                        cout<<"Do you want to visit the candy store? (y/n)"<<endl;
                        cin>>user_y_n;

                        if((user_y_n != 'y' && user_y_n != 'n') || cin.fail())
                        {
                            while((user_y_n != 'y' && user_y_n != 'n') || cin.fail())
                            {
                                cin.clear();
                                cin.ignore(1000, '\n');
                                cin>>user_y_n;
                            }
                        }

                        if(user_y_n == 'y')
                        {
                           CandyStore store;
                            store.inCandyStore(current_player, all_candies); 
                        }
                    }

                    if (game_board.getTile(current_player.getCurrentPlayerPosition()).hasHiddenTreasure)
                    {
                        if(askTreasureRiddle(all_riddles) == true)
                        {
                            playHiddenTreasures(current_player);
                        }

                    }

                    cout << "Ending " << current_player.getRealName() << "'s turn. Here is the updated board:" << endl;
                    game_board.displayBoard(all_players);
                }
                else if (user_select == 2)
                {
                    string player_candy_choice;
                    cout << "Here is a list of your candies: " << endl;
                    current_player.printInventory();

                    cout << "Enter a candy you wish to use: " << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    getline(cin, player_candy_choice); // need validation to make sure they dont enter numbers or someth??

                    if(current_player.findCandy(player_candy_choice).name == "Treasure Hunter's Truffle") //sepcial case so i can call the hiddne treasure function again
                    {
                        playHiddenTreasures(current_player);
                    }
                    else
                    {
                       current_player.useCandy(player_candy_choice, all_players);  
                    }
                }
                else if (user_select == 3)
                {
                    current_player.displayPlayer();
                }
            } while (user_select == 2 || user_select == 3);
        }
    }
    endGame(all_players);
}

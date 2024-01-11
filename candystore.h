#ifndef CANDYSTORE_H
#define CANDYSTORE_H

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

#include "CandylandPlayer.h"
//#include "Board.h"

using namespace std;

class CandyStore
{
    private:

        const static int _MAX_INVENTORY_CANDYSTORE= 3;//fix size
        const static int _MAX_NUM_OF_CANDYSTORE = 3;
        Candy _candystore_inventory[3];
        vector <Candy> _available_magical;
        vector <Candy> _available_poision;
        vector <Candy> _available_gummy;
    

    public:
        //CandyStore();
        
        void inCandyStore(CandylandPlayer&, vector <Candy>);
        void displayCandyStore();
        void buyFromCandyStore(CandylandPlayer&);

        int getMaxInventory ();
        int getNumOfCandystore();

        void setCandystoreInventory(vector <Candy>);
};

#endif 
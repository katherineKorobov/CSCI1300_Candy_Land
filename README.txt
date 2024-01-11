---------------------------------------------------------
HOW TO COMPILE AND RUN
---------------------------------------------------------
Compile: g++ -Werror -Wpedantic -Wall -std=c++17 CandylandPlayer.cpp 
boardDriver.cpp Game.cpp Board.cpp CandyStore.cpp
Run: ./a.exe

----------------------------------------------------------
DEPENDENCIES
----------------------------------------------------------
CandylandPlayer.h, Game.h, Board.h, candstore.h, riddles.txt, 
characters.txt, candies.txt must be in the same directory as the
cpp files in order to compile.

-----------------------------------------------------------
SUBMISSION INFORMATION
------------------------------------------------------------
CSCI 1300 Fall 2023 Project 2
Author: Katherine Korobov
Recitation 201 - Nolan Bonnie
Date: Dec 7,2023

------------------------------------------------------------
ABOUT THIS PROJECT 
------------------------------------------------------------
This is an implementation of the well known board game, Candyland.
Two players compete by drawing cards to move to new tiles, using
candies, and showing stats. Numerous actoins can happen, both good 
and bad, to the player such as Calamities, Special Tiles, and Hidden
Treasures. The player who gets to the Candyland Castle at the end
of the board wins the game. 
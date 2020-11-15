#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;

//Global constant definition
const int PLAYER_NUM = 5;
const int SIZE = 5;
const int MAX_NAME_LENGTH = 10;
const int MAX_NUMBER = SIZE * SIZE;

// User-defined data type
struct Player
{ 
    char name[MAX_NAME_LENGTH];  
    int bingo_card[SIZE][SIZE];             
    bool card_status[SIZE][SIZE];     // 0 for empty, 1 for occupied
    bool bingo;               
};

// external funciton declarations
// Your code here
void init_player(Player &, char *);
void display_info(Player *, int);
void change_status(Player &, int);
bool check_bingo(Player);
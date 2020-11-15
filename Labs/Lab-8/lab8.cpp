#include "lab8.h"

/*
Task 1
Initialize the players:
Assign the name
Randomly generate a bingo card
Initialize card_status to all zeros and bingo to false
Hint: you can use "std::random_shuffle()" function to generate 1d array with size 25, and resize it to 5x5 2d array
*/

// function name: init_player
// Your code here
int myrandom (int i) { return std::rand()%i;}

void init_player(Player &player, char name[]){
    //init name
    for (int i = 0; i < MAX_NAME_LENGTH; i++) {
        player.name[i] = name[i];
    }

    //init bingo_card
    int numbers[MAX_NUMBER];

    for (int i = 1; i <= 25; i++) {
        numbers[i-1] = i;
    }

    std::random_shuffle(&numbers[0], &numbers[MAX_NUMBER], myrandom);

    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            player.bingo_card[i][j] = numbers[i*SIZE + j];
        }
    }

    //init card_status 
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            player.card_status[i][j] = false;
        }
    }

    player.bingo = false;
}
 
/*
Task 2:
Display five players' information:
If the number has been picked, add '*' after it. 
The output for each player looks like this:
___________________________________________________
Name: Peter
Bingo card ('*' means the number has been picked)
20      4       15      16      11
3       23      25      9*      5
21      8       6       12      2
10      1       22      14      19
13      24      7       17      18
*/
// function name: display_info
// Your code here
void display_info(Player players[], int playerNum) {
    for (int i=0; i < playerNum; i++) {
        cout<< "___________________________________________________" <<endl;
        cout<< "Name: " << players[i].name << endl;
        cout<< "Bingo card ('*' means the number has been picked)"<< endl;

        for (int j = 0; j < SIZE; j++){
            for (int k = 0; k < SIZE; k++) {
                if (players[i].card_status[j][k] == false) {
                    cout << players[i].bingo_card[j][k] << '\t';
                }
                else{
                    cout << players[i].bingo_card[j][k] << "* \t";
                }
            }
            cout << endl;
        }
    }
}



/*
Task 3:
Change the status for picked number:
You should find the position of the number you picked in bingo card and update the status.
*/

// function name: change_status
// Your code here
void change_status(Player &player, int number) {
    for (int j = 0; j < SIZE; j++){
        for (int k = 0; k < SIZE; k++) {
            if (player.bingo_card[j][k] == number){
                player.card_status[j][k] = true;
            }
        }
    }
}

/*
Task 4:
Check bingo:
You should check the status for all rows, columns and two diagonals. 
Return true if there is an entire occupied line, otherwise, return false.
*/

// function name: check_bingo
// Your code here
bool check_bingo(Player player) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (player.card_status[i][j] == true){
                if (j == SIZE-1){
                    return true;
                }
            }
            else {
                break;
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (player.card_status[j][i] == true){
                if (j == SIZE-1){
                    return true;
                }
            }
            else {
                break;
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        if (player.card_status[i][i] == true){
            if (i == SIZE-1){
                return true;
            }
        }
        else {
            break;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        if (player.card_status[i][SIZE - 1 - i] == true){
            if (i == SIZE-1){
                return true;
            }
        }
        else {
            break;
        }
    }
    return false;
}
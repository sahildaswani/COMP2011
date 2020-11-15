#include "lab8.h"

int main()
{
    srand(time(0));
    bool END = false;
    struct Player plys[PLAYER_NUM];
  	
    // input information for each player
	for(int i = 0; i < PLAYER_NUM; i++){
        char name[MAX_NAME_LENGTH];
		cout << "Player " << i + 1 << endl;
		cout << "Enter name (shorter than 10 characters)" << endl;
		cin >> name;
		cout << "Generating bingo card for player " << i + 1 << "..." << endl;
        init_player(plys[i], name);
	}
    cout << "Initialization done." << endl;
    display_info(plys, PLAYER_NUM);

    // Start game
    cout << endl;
    cout << "=================Welcome to Bingo Game=================" << endl;

    int round = 0;
    while(!END){

        cout << "-----------Round " << ++ round << "-----------" << endl;
        cout << "Please select a number between 1 to 25: ";
        int selected_number;
        cin >> selected_number;

        for(int i = 0; i < 5; i ++){
            change_status(plys[i], selected_number);
            bool ret = check_bingo(plys[i]);
            if (ret){
                END = true;
            }
        }
        display_info(plys, PLAYER_NUM);
    }

    // print the winner(s)
    for(int i = 0; i < 5; i ++){
        if (plys[i].bingo)
            cout << plys[i].name << " is the winner!" << endl;
    }
    cout << "=================Game over==================" << endl;
    return 0;
}

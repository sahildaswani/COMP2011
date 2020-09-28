#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

bool player1;

string displayPlayer() {
    if (player1) {
        return "Player 1. ";
    } 
    else {
        return "Player 2. ";
    }
}

void togglePlayer() {
    player1 ? player1 = false : player1 = true;
}

int main() {
    srand(time(0));
    int input;
    int randomNumber = rand() % 100 + 1;
    player1 = true;

    while (true) {
        cout << displayPlayer() << "Please guess the number between 1-100: ";
        cin >> input;

        if (input > randomNumber){
            cout << "The random number is smaller than " << input << endl;
            togglePlayer();
        }
        else if (input < randomNumber){
            cout << "The random number is greater than " << input << endl;
            togglePlayer();
        }
        else {
            cout << "Congratulations! You guessed the right number. The winner is " << displayPlayer() << endl;
            break;
        }
    }

    return 0;
}

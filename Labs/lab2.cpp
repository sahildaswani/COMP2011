#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    srand(time(0));
    int round = 1;
    int heapA = rand() % 4 + 3;
    int heapB = rand() % 4 + 3;
    int heapC = rand() % 4 + 3;
    int player = 1;
    bool game = true;

    cout << "Welcome to the Nim game!" << endl; 
    while (game) {
        char removeHeap;
        int availableCoins;
        int removeCoins;

        //Print number of coins in each heap during the round
        cout << "Round " << round << ". A:" << heapA << " B:" << heapB << " C:" << heapC << endl; 

        //Let player choose which heap to remove coins from
        cout << "Player " << player << ", please select a heap (A, B or C): ";
        cin >> removeHeap;
        //Input validation
        while (removeHeap != 'A' && removeHeap != 'B' && removeHeap != 'C' ){
            cout << "Invalid Input" << endl;
            cout << "Player " << player << ", please select a heap (A, B or C): ";
            cin >> removeHeap;
        }

        if (removeHeap == 'A'){
            availableCoins = heapA;
        } 
        else if (removeHeap == 'B'){
            availableCoins = heapB;
        }
        else if (removeHeap == 'C'){
            availableCoins = heapC;
        }

        while (availableCoins <= 0) {
            cout << "Invalid Input" << endl;
            cout << "Player " << player << ", please select a heap (A, B or C): ";
            cin >> removeHeap;

            if (removeHeap == 'A'){
                availableCoins = heapA;
            } 
            else if (removeHeap == 'B'){
                availableCoins = heapB;
            }
            else if (removeHeap == 'C'){
                availableCoins = heapC;
            }
        }
        

        //Let player choose how many coins to remove
        cout << "Player " << player << ", please select the number of coins to remove (1, 2 or 3): ";
        cin >> removeCoins;
        //Input validation
        while (removeCoins <= 0 || removeCoins > 3 || removeCoins > availableCoins) {
            cout << "Invalid Input" << endl;
            cout << "Player " << player << ", please select the number of coins to remove (1, 2 or 3): ";
            cin >> removeCoins;
        }

        if (removeHeap == 'A'){
            heapA -= removeCoins;
            cout << "Player " << player << " removes " << removeCoins << " coin(s) from heap A." << endl;
        } 
        else if (removeHeap == 'B'){
            heapB -= removeCoins;
            cout << "Player " << player << " removes " << removeCoins << " coin(s) from heap B." << endl;
        }
        else if (removeHeap == 'C'){
            heapC -= removeCoins;
            cout << "Player " << player << " removes " << removeCoins << " coin(s) from heap C." << endl;
        }
        
        cout << "" << endl;

        if (heapA == 0 && heapB == 0 && heapC == 0){
            cout << "Player " << player << " wins!" << endl;
            game = false;
        }

        player = player % 2 + 1;
        round += 1;
    }

    return 0;
}
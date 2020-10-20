#include <iostream>
using namespace std;

int main()
{
    /*
        There are 4 errors in total. Can you catch them all? :)
 
        See the expected output section on the lab page to see what is expected from the corrected program.
    */

    //Declare number variable
    int number;

    cout << "Welcome to the exciting, fun, and awesome programming world! "
         << "Enter a positive integer, and I can tell something about you! " << endl;
    cin >> number;

    //Change =< to <=
    if (number <= 0)
        cout << "You must be fun at parties... XD" << endl;
    else
    {
        //Added &&
        if (10 < number && number < 100)
            cout << "You are an awesome person!" << endl;
        else
            cout << "You must be very excited! Me too!" << endl;
    }

    //Added semicolon ';'
    return 0;
}
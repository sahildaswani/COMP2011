#include <iostream>
using namespace std;

int main() 
{
    int j = 10;
    int k = 4;
   
    while (k > 0)
    {
        cout << "first j: " << --j << endl;
        
        int j = 6;
        cout << "second j: " << --j << endl << endl;
        --k;
    }

    return 0;
}

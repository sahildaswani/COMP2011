#include <iostream>
using namespace std;

int power(int x, int y) {
	int power = x;
	if (y == 0) {
		return 1;
	} else {
		for (int i=1; i<y; i++){
            if (i != 30){
                power *= x;
            }
            else {
                return 2147483647;
            }
		}
		return power;
	}
}

int get_min_bits_length(int x)
{
	if (x==0){
		return 2;
	} 
    else if (x == 2147483647) {
        return 32;
    }
	else if (x > 0){
		int i = 0; 
		while (true) {
			if (x < power(2, i)) {
				i += 1;
				break;
			} 
			else {
				i += 1;
			}
		}
		return i;
	}
	else {
		int y = x*(-1) - 1;
		int i = 0; 
		while (true) {
			if (y < power(2, i)) {
				i += 1;
				break;
			} 
			else {
				i += 1;
			}
		}
		return i;
	}
	
}

int main(){
    int x = get_min_bits_length(2147483647);

    cout << x << endl;
}
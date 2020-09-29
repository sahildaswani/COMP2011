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

// Task 1
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

// Task 2
int get_bit_positive(int x, int n)
{
	if (x < 0 || n < 0){
		return -1;
	}
	else {
		int i = get_min_bits_length(x) - 2;
		int number = x;
		if (n <= i){
			for (i; i > -1; i--){
				if (power(2,i) <= number){
					number -= power(2,i);
					if (i==n){
						return 1;
					}
				} else {
					if (i==n){
						return 0;
					}
				}
			}
		} 
		return 0;
	}
}

// Task 3
int get_bit_negative(int x, int n)
{
	if (x >= 0 || n < 0){
		return -1;
	} 
	else if (n >= get_min_bits_length(x)){
		return 1;
	}
	else {
		int carrier = 0;
		for (int i=0; i < get_min_bits_length(x); i++){
			int bit = (get_bit_positive(x*-1, i) + 1) % 2;
			if (i == 0 && bit == 0) {
				bit = 1;
				if (n == i){
					return bit;
				}
			}
			else if (i == 0 && bit == 1) {
				bit = 0;
				carrier = 1;
				if (n == i){
					return bit;
				}
			}
			else {
				if (bit == 1 && carrier == 1){
					bit = 0;
					carrier = 1;
					if (n == i){
						return bit;
					}
				}
				else if (bit == 1 && carrier == 0 || bit == 0 && carrier == 1) {
					bit = 1;
					carrier = 0;
					if (n == i){
						return bit;
					}
				}
			}
		}
	}
	return 0;
}


// Task 4
void print_2s_complement_representation(int x)
{	
	if (x >= 0) {
		for (int i = get_min_bits_length(x) - 1; i > -1; i--) {
			cout << get_bit_positive(x, i);
		}
	} 
	else if (x < 0) {
		for (int i = get_min_bits_length(x) - 1; i > -1; i--) {
			cout << get_bit_negative(x, i);
		}
	}
	cout<<endl;
}

int get_bit(int x, int n) {
	if (x >= 0) {
		return get_bit_positive(x, n);
	}
	else {
		return get_bit_negative(x, n);
	}
}

int getCarryBitLength(int a, int b) {
	int bitLength = (get_min_bits_length(a) > get_min_bits_length(b)) ? 
	get_min_bits_length(a) : 
	get_min_bits_length(b);

	return bitLength;
}

int getCarryBit(int a, int b, int n) {
	int carrier = 0;

	int bitLength = getCarryBitLength(a, b);

	for (int i=0; i < bitLength; i++){
		int bitA = get_bit(a, i);
		int bitB = get_bit(b, i);

		if (bitA + bitB + carrier == 3) {
			carrier = 1;
			if (n == i){
				return 0;
			}
		} 
		else if (bitA + bitB + carrier == 2)  {
			carrier = 1;
			if (n == i){
				return 1;
			}
		} 
		else if (bitA + bitB + carrier == 1) {
			carrier = 0;
			if (n == i){
				return 0;
			}
		}
		else if (bitA + bitB + carrier == 0) {
			carrier = 0;
			if (n == i){
				return 1;
			}
		}
	}
    return 404;
}

// Task 5
void print_addition_carry_out(int a, int b)
{
	int bitLength = getCarryBitLength(a, b);

	for (int i = bitLength - 1 ; i > -1; i--) {
		cout << getCarryBit(a, b, i);
	}

    cout << endl;
}

int main() {
    cout << "get bitA: " << get_bit(-10, 4) << endl;
    cout << "get bitB: " << get_bit(11, 0) << endl;
    cout << "get carry bit: " << getCarryBit(3, 11, 5) << endl;
    print_addition_carry_out(3, -10);
}
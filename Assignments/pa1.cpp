/*
 * COMP2011 (Fall 2020) Assignment 1: Binary Numbers
 *
 * Student name: Daswani, Sahil Bharat
 * Student ID: 20630681
 * Student email: sbdaswani@connect.ust.hk
 *
 * Note:
 * 1. You CANNOT define and use any arrays.
 * 2. You CANNOT define and use any global variables.
 * 3. You CANNOT use the static keyword.
 * 4. You CANNOT include any extra libraries other than iostream.
 * 5. You CANNOT use any bitwise operators: ~, ^, |, & (since they are not taught in this course).
 * 6. You CANNOT change the function headers of the functions given in the tasks.
 * 7. You CANNOT use any string operations.
 * 8. You can add helper functions.
 */

#include <iostream>
using namespace std;

// Task 1
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

// Task 5
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
				return carrier;
			}
		} 
		else if (bitA + bitB + carrier == 2)  {
			carrier = 1;
			if (n == i){
				return carrier;
			}
		} 
		else if (bitA + bitB + carrier == 1) {
			carrier = 0;
			if (n == i){
				return carrier;
			}
		}
		else if (bitA + bitB + carrier == 0) {
			carrier = 0;
			if (n == i){
				return carrier;
			}
		}
	}
    return 404;
}

void print_addition_carry_out(int a, int b)
{
	int bitLength = getCarryBitLength(a, b);

	for (int i = bitLength - 1 ; i > -1; i--) {
		cout << getCarryBit(a, b, i);
	}

    cout << endl;
}

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE REPLACED

int main()
{
	while (true) {
		int option = 0;

		do {
			cout << "1. Task 1" << endl;
			cout << "2. Task 2" << endl;
			cout << "3. Task 3" << endl;
			cout << "4. Task 4" << endl;
			cout << "5. Task 5" << endl;
			cout << "0. Exit" << endl;
			cout << "Enter an option (0-5): ";
			cin >> option;
		} while (option < 0 || option > 5);
		
		if (option == 0)
			break;
		else if (option == 1) {
			int number;
			cout << "Enter a number: ";
			cin >> number;
			cout << number << " needs " << get_min_bits_length(number) << " bits." << endl;
		}
		else if (option == 2) {
			int number;
			int bit;

			cout << "Enter a number: ";
			cin >> number;

			cout << "Which bit? ";
			cin >> bit;
			
			cout << "The number " << bit << " bit of " << number << " is " << get_bit_positive(number, bit) << endl;
		}
		else if (option == 3) {
			int number;
			int bit;

			cout << "Enter a number: ";
			cin >> number;

			cout << "Which bit? ";
			cin >> bit;
			
			cout << "The number " << bit << " bit of " << number << " is " << get_bit_negative(number, bit) << endl;
		}
		else if (option == 4) {
			int number;
			cout << "Enter a number: ";
			cin >> number;
			cout << "The 2's complement representation of " << number << " is:" << endl;
			print_2s_complement_representation(number);
		}
		else if (option == 5) {
			int a, b;
			cout << "Enter number A: ";
			cin >> a;
			cout << "Enter number B: ";
			cin >> b;
			cout << "The sum of " << a << " and " << b << " is " << a + b << ". The carry bits are:" << endl;
			print_addition_carry_out(a, b);
		}

		cout << endl;
	}

	return 0;
}
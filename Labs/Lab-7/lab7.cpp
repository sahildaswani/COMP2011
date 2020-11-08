#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/* Global constant */

const int STR_LEN = 30;

const int NUM_PEN_TYPES = 3; // Number of pen types

enum PEN_TYPE { FOUNTAIN, BALLPOINT, GEL };

const char pen_type_names[NUM_PEN_TYPES][STR_LEN] = {"Fountain pen", "Ballpoint pen", "Gel pen"};

const int STORE_COUNT = 2; // Number of stores

/* Structure Definitions */
struct Pen {
    PEN_TYPE pen_type;
    int price;
    int amount;
};

struct Store 
{
    int store_ID;
    Pen pen[NUM_PEN_TYPES];
};

/* Utility functions for struct Pen */
// Given
void print_pen(const Pen &pen) 
{
    cout.width(15);
    cout << pen_type_names[pen.pen_type] << ", price: " << pen.price << ", amount: " << pen.amount << endl;
}

/* Utility functions for struct Store*/
// Given
void print_store(const Store &store, int num_pen_types) 
{
    cout << "Store ID: " << store.store_ID << endl;

    for (int i = 0; i < num_pen_types; i++)
        print_pen(store.pen[i]);

}

// FUNCTION 1 
/**
   TODO: Initialize a pen, i.e. the type, price and amount.
      The price and amount are generated randomly.
   The range of amount: [20, 30); The range of price: [10, 20).
 **/
void init_pen(Pen &pen, PEN_TYPE type)
{
    pen.pen_type = type;
    pen.amount = rand()%10 + 20;
    pen.price = rand()%10 + 10;
}



// FUNCTION 2 
/**
   TODO: Initialize a store, i.e. the ID of each store, and the information of all the pens that the store sells by using the function "init_pen".
   store_id: the id of the store to be initialized;
   type: the number of pen types
 **/
void init_store(Store &store, int store_id, int type){
    Pen pens[NUM_PEN_TYPES];

    store.store_ID = store_id;

    for (int i=0; i < NUM_PEN_TYPES; i++) {
        init_pen(pens[i], static_cast<PEN_TYPE>(i));
    }
    for (int i=0; i<NUM_PEN_TYPES; i++) {
        store.pen[i] = pens[i];
    }
    
}

/* Functions for purchase strategy */
// Given
void print_decision(int store_ID, PEN_TYPE pen_type, int amount, int remain_money)
{
    cout << "Buy " << amount 
         << " " << pen_type_names[pen_type]
         << " from Store " << store_ID 
         << ", money remaining: " << remain_money << endl;
}

// FUNCTION 3 
/**
   TODO: Find the strategy of buying pens as many as possible.
   Hint: it's a greedy strategy. 
   In each round, you should find the kind of pens with minimum price
   (Note that if several kinds of pens have the same minimum price, you could pick anyone)
    and then buy this kind of pens using your remaing money as many as possible.
   After each round, you should print the information about this purchase by using the function "print_decision".
   If your remaining money can not buy even a single pen or you have bought all pens, return false.
 **/
bool decision_for_each_round(Store stores[], int store_count, int num_pen_types, int &money)
{
    int minimumPrice = 30;
    int store = 0;
    int penType = 0; 

    for (int i=0; i<store_count; i++){
        for (int j=0; j<num_pen_types; j++){
            if (stores[i].pen[j].price < minimumPrice && stores[i].pen[j].amount != 0){
                minimumPrice = stores[i].pen[j].price;
                store = i;
                penType = j;
            }
        }
    }

    if (minimumPrice <= money) {
        int total = minimumPrice*stores[store].pen[penType].amount;

        if (total <= money){
            money -= total;
            cout << "Buy " << stores[store].pen[penType].amount << " " << pen_type_names[penType] << " from Store " <<
            store + 1 << ", money remaining: " << money << endl;
            stores[store].pen[penType].amount = 0;
        } 
        else {
            int quantity = money/minimumPrice;
            money -= minimumPrice * quantity;
            cout << "Buy " << quantity << " " << pen_type_names[penType] << " from Store " <<
            store + 1 << ", money remaining: " << money << endl;
            stores[store].pen[penType].amount -= quantity;
        }
        return true;
    }
    return false;
}


int main() 
{
    // set the random seed
    srand(time(0));

    int money;

    cout << "How much money do you have? ";
    cin >> money;

    Store stores[STORE_COUNT];

    for (int i = 0; i < STORE_COUNT; i++)
        init_store(stores[i], i+1, NUM_PEN_TYPES);

    cout << "==========================" << endl;
    cout << " Pen prices of each store " << endl;
    cout << "==========================" << endl;
    for (int i = 0; i < STORE_COUNT; i++)
    {
        print_store(stores[i], NUM_PEN_TYPES);
        cout << "-------------------------" << endl;
    }

    cout << "*******************" << endl;
    cout << " Purchase Strategy " << endl;
    cout << "*******************" << endl;

    int round = 1;
    do
    {
        cout << "Round " << round++ << ": ";
    }
    while (decision_for_each_round(stores, STORE_COUNT, NUM_PEN_TYPES, money));

    cout << "No more purchase!" << endl;

    return 0;
}
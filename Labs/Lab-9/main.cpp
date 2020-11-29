// COMP2011 Fall 2020
// main.cpp -- lab 9

#include <iostream>
#include "lab9.h"
using namespace std;

// This function will load several given contacts' information.
Telephone_Directory* load_existing_telephone_directory(){

    Telephone_Directory* d = new_telephone_directory();

    add_contact_to_telephone_directory(d, "Eric", "28783368");
    add_contact_to_telephone_directory(d, "Shirley", "28783388");
    add_contact_to_telephone_directory(d,"Paul", "28102589");
    add_contact_to_telephone_directory(d, "Teresa", "39184111");
    add_contact_to_telephone_directory(d, "Katy", "39184112");
    add_contact_to_telephone_directory(d, "Hinz", "39184117");
    add_contact_to_telephone_directory(d, "Mackenzie", "39184128");
    add_contact_to_telephone_directory(d, "Olivia", "39184130");
    add_contact_to_telephone_directory(d, "Mark", "39184555");
    add_contact_to_telephone_directory(d, "Sarah", "39184123");
    return d;
}

int main() {

    Telephone_Directory* td;
    
    int reply;
    char contact_name[MAX_NAME_LENGTH+1];
    char phone_number[MAX_PHONE_NUMBER_LENGTH+1];
    char contact_name_partial[MAX_NAME_LENGTH+1];
    char phone_number_partial[MAX_PHONE_NUMBER_LENGTH+1];
    
    int matched_contacts[MAX_CONTACT_NUMBER];
    int matched_count;

    td = load_existing_telephone_directory();
    do {
        cout << "Choose what to do next:" << endl;
        cout << "1: Add a contact" << endl;
        cout << "2: Look up by contact name" << endl;
        cout << "3: Look up by phone number" << endl;
        cout << "4: Update phone number" << endl;
        cout << "5: View all contacts sorted by names" << endl;
        cout << "6: View all contacts sorted by phone numbers" << endl;
        cout << "7: Quit" << endl;
        cin >> reply;

        switch(reply) {
        case 1:
            cout << "Please enter the name of the contact:" ;
            cin >> contact_name;
            cout << "Please enter a phone number:";
            cin >> phone_number;
            add_contact_to_telephone_directory(td, contact_name, phone_number);
            break;
        case 2:
            cout << "Please enter the name of the contact:";
            cin >> contact_name_partial;
            matched_count = lookup_by_contact_name(td, contact_name_partial, matched_contacts);
            show_contacts(td, matched_contacts, matched_count, true);
            break;
        case 3:
            cout << "Please enter the phone number of the contact:";
            cin >> phone_number_partial;            
            matched_count = lookup_by_phone_number(td, phone_number_partial, matched_contacts);
            show_contacts(td, matched_contacts, matched_count, false);
            break;
        case 4:
            cout << "Please enter the name of the contact whose phone number you want to update:";
            cin >> contact_name;
            cout << "Please enter the new phone number:";
            cin >> phone_number;
            update_phone_number(td, contact_name, phone_number);
            break;
        case 5:
            cout << "Here are all contacts in your telephone directory:" << endl;
            show_contacts(td);
            break;
        case 6:
            cout << "Here are all contacts in your telephone directory:" << endl;
            show_contacts(td, false);
            break;
        default:
            break;
        }

    } while (reply != 7);

    delete_telephone_directory(td);
    td = nullptr;

    return 0;
}




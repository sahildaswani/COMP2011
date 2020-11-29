// COMP2011 Fall 2020
// lab9.h -- header file

#ifndef CONTACT_H_
#define CONTACT_H_

const int MAX_NAME_LENGTH = 20;
const int MAX_PHONE_NUMBER_LENGTH = 8;
const int MAX_CONTACT_NUMBER = 20;

struct Contact {
    char contact_name[MAX_NAME_LENGTH + 1];
    char phone_number[MAX_PHONE_NUMBER_LENGTH + 1];
};

struct Telephone_Directory {
    Contact* contacts_by_name[MAX_CONTACT_NUMBER]; // in sorted order of contact_name
    Contact* contacts_by_phone_number[MAX_CONTACT_NUMBER]; // in sorted order of phone_number
    int num_of_contacts; // number of contacts
};

void print_contact(const Contact*);
// This function prints one contact's information.

Contact* new_contact(const char [], const char []);
// This function will create (new) a Contact object.

Telephone_Directory* new_telephone_directory();
// This function will create (new) a Telephone_Directory object.

void show_contacts(const Telephone_Directory* , const int [], int , bool );
// This function will print queried contacts' infomation either sorted by their names (when by_name=true) or sorted by their phone numbers (when by_name=false).

void show_contacts(const Telephone_Directory*, bool = true);
// This function will print all contacts' infomation sorted by their names 

void delete_telephone_directory(Telephone_Directory* );
// This function will delete the whole telephone directory. 

void add_contact_to_telephone_directory(Telephone_Directory *, const char [], const char []);
// This function will use new_contact() to create object and add the pointer (address) to the array of pointers appropriately in the Telephone_Directory object.

int lookup_by_contact_name(const Telephone_Directory* , const char [], int []);
// This function will return num of matched contacts and the indices of the matched contacts in the contacts_by_name array of Telephone_Directory are stored in the integer array.

int lookup_by_phone_number(const Telephone_Directory* , const char [], int []);
// This function will return num of matched contacts and the indicses of the matched contacts in the contacts_by_phone_number array of Telephone_Directory are stored in the integer array.

void update_phone_number(Telephone_Directory* d, const char [], const char []);
// This function will update a contact's phone number given the contact_name.

#endif

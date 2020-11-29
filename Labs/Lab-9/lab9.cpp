// COMP2011 Fall 2020
// lab9.cpp -- source file

#include <iostream>
#include <cstring>
#include "lab9.h"
using namespace std;

// This function prints one contact's information.
void print_contact(const Contact *contact)
{
        cout << contact->contact_name << ":" << contact->phone_number << endl;
}

// This function will create (new) a Contact object with the given contact_name & phone_number,
// and return its address (pointer).
Contact *new_contact(const char contact_name[], const char phone_number[])
{
        Contact *contact = new Contact;

        strcpy(contact->contact_name, contact_name);
        strcpy(contact->phone_number, phone_number);

        return contact;
}

// This function will create (new) a Telephone_Directory object,
// initialize num_of_contact to 0, initialize all array elements to nullptr,
// and return the Telephone_Directory pointer (address).
Telephone_Directory *new_telephone_directory()
{
        Telephone_Directory *directory = new Telephone_Directory;

        directory->num_of_contacts = 0;

        for (int i = 0; i < MAX_CONTACT_NUMBER; i++)
        {
                directory->contacts_by_phone_number[i] = nullptr;
                directory->contacts_by_name[i] = nullptr;
        }

        return directory;
}

// This function will print queried contacts' infomation (indices stored in matched_contacts[]) either sorted by their names (when by_name=true) 
//or sorted by their phone numbers (when by_name=false)
void show_contacts(const Telephone_Directory* d, const int matched_contacts[], int matched_contacts_count,  bool by_name)
{
        for (int i = 0 ; i < matched_contacts_count ; i++)
        {
                int j = matched_contacts[i];

                if (by_name)
                {
                        cout << d -> contacts_by_name[j] -> contact_name << ":" << d -> contacts_by_name[j] -> phone_number << endl;
                        
                }
                else 
                {
                        cout << d -> contacts_by_phone_number[j] -> contact_name << ":" << d -> contacts_by_phone_number[j] -> phone_number << endl;
                }   
        }
}

// This function will print all contacts' infomation sorted by their names if by_names is true.
// Otherwise print the contacts by their phone numbers
void show_contacts(const Telephone_Directory* d, bool by_names)
{
        for (int i = 0 ; i < d -> num_of_contacts ; i++)
        {
                if (by_names)
                {
                        cout << d -> contacts_by_name[i] -> contact_name << ":" << d -> contacts_by_name[i] ->phone_number << endl;
                        
                }
                else 
                {
                        cout << d -> contacts_by_phone_number[i] -> contact_name << ":" << d -> contacts_by_phone_number[i] ->phone_number << endl;
                }   
        } 
}

// This function will delete all the Contact objects and the Telephone_Directory object.
void delete_telephone_directory(Telephone_Directory* d) 
{
        for (int i = 0 ; i < d -> num_of_contacts ; i ++)
        {
                delete d -> contacts_by_name[i];
        }
}

// This function will use new_contact() to create object within given contact_name & phone_num,
// and add the pointer (address) to the 2 arrays of pointers in the Telephone_Directory object pointed by d.
// contacts_by_name is to maintain the contacts in sorted order of names,
// contacts_by_phone_number is to maintain the contacts in sorted order of phone numbers.
void add_contact_to_telephone_directory(Telephone_Directory *d, const char contact_name[], const char phone_num[])
{
        Contact* p = new_contact(contact_name, phone_num);
        Contact* names[MAX_CONTACT_NUMBER];
        Contact* numbers[MAX_CONTACT_NUMBER];  
        
        for (int i = 0 ; i < d -> num_of_contacts ; i++)
        {
                names[i] = d -> contacts_by_name[i];
                numbers[i] = d -> contacts_by_phone_number[i];
        }
        d -> num_of_contacts++ ; 

        bool add_name = false; 
        bool add_number = false;

        for (int i = 0 ; i < d -> num_of_contacts ; i++)
        {
                if (add_name)
                {
                        d -> contacts_by_name[i] = names[i-1];
                }
                else if (d -> contacts_by_name[i] == nullptr || strcmp(contact_name, d -> contacts_by_name[i] -> contact_name) < 0)
                {
                        d -> contacts_by_name[i] = p;
                        add_name = true;
                }

                if (add_number)
                {
                        d -> contacts_by_phone_number[i] = names[i-1];
                }
                else if (d -> contacts_by_phone_number[i] == nullptr || strcmp(phone_num, d -> contacts_by_phone_number[i] -> phone_number) < 0)
                {
                        d -> contacts_by_phone_number[i] = p;
                        add_number = true;
                }
        }
}

// This function will search for contacts matching with the substring contact_name_partial, 
// return num of matched contacts and store the indices of the matched contacts 
// in the contacts_by_name array of Telephone_Directory in the array matched_contacts.
int lookup_by_contact_name(const Telephone_Directory* d, const char contact_name_partial[], int matched_contacts[])
{
        int min_contacts = 0;
        int max_contacts = d -> num_of_contacts;
        int i = 0;

        while (contact_name_partial[i] != '\0')
        {
                for (int j = min_contacts ; j < max_contacts ; j++)
                {
                        if (contact_name_partial[i] > d -> contacts_by_name[j] -> contact_name[i])
                        {
                                min_contacts = j + 1;
                        }
                        else if (contact_name_partial[i] < d -> contacts_by_name[j] -> contact_name[i])
                        {
                                max_contacts = j;
                        }
                }
                i++;
        }
        i = 0;

        for (int j = min_contacts ; j < max_contacts ; j++)
        {
                matched_contacts[i] = j;
                i++;
        }

        return max_contacts - min_contacts;
}

// This function will search for contacts matching with the substring phone_number_partial, 
// return num of matched contacts and store the indices of the matched contacts 
// in the contacts_by_phone_number array of Telephone_Directory in the array matched_contacts.
int lookup_by_phone_number(const Telephone_Directory* d, const char phone_number_partial[], int matched_contacts[])
{
        int min_contacts = 0;
        int max_contacts = d -> num_of_contacts;
        int i = 0;

        while (phone_number_partial[i] != '\0')
        {
                for (int j = min_contacts ; j < max_contacts ; j++)
                {
                        if (phone_number_partial[i] > d -> contacts_by_phone_number[j] -> phone_number[i])
                        {
                                min_contacts = j + 1;
                        }
                        else if (phone_number_partial[i] < d -> contacts_by_phone_number[j] -> phone_number[i])
                        {
                                max_contacts = j;
                        }
                }
                i++;
        }
        i = 0;

        for (int j = min_contacts ; j < max_contacts ; j++)
        {
                matched_contacts[i] = j;
                i++;
        }

        return max_contacts - min_contacts;
}

// This function will update a contact's phone number given the contact_name.
// and update the contacts_by_phone_num array in sorted order.
void update_phone_number(Telephone_Directory* d, const char contact_name[], const char phone_number[])
{
        int i = 0;

        while (strcmp(contact_name, d -> contacts_by_phone_number[i] -> contact_name) != 0)
        {
                i++;
        } 

        Contact* update = d -> contacts_by_phone_number[i];
        Contact* numbers[MAX_CONTACT_NUMBER] = {nullptr};

        strcpy(update -> phone_number, phone_number);

        for (int j = 0; j < d -> num_of_contacts; j++)
        {
                if (j < 1)
                {
                        numbers[j] = d -> contacts_by_phone_number[j];
                        d -> contacts_by_phone_number[j] = d -> contacts_by_phone_number[j];
                }
                else 
                {
                        numbers[j] = d -> contacts_by_phone_number[j - 1];
                        d -> contacts_by_phone_number[j] = d -> contacts_by_phone_number[j + 1];
                }
        }

        bool added_number = false;

        for (int i = 0; i < d-> num_of_contacts; i++)
        {
                if (added_number)
                {
                        d -> contacts_by_phone_number[i] = numbers[i-1];
                }
                else if (d -> contacts_by_phone_number[i] == nullptr || strcmp(phone_number, d -> contacts_by_phone_number[i] -> phone_number) < 0)
                {
                        d -> contacts_by_phone_number[i] = update;
                        added_number = true;
                }
        }
}
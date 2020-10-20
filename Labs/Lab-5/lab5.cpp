#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>

using namespace std;

#define N 20

// search for a word in the input file, return true if found
bool lookup(const char filename[], const char word[]){
    ifstream file(filename);
    char line[N];

    while (!file.eof()){
        file.getline(line, N, '\n');
        if (strcmp(word, line) == 0) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// delete a word in the input file
// the result should not contain blank lines
void delete_word(const char filename[], const char word[]){
    
    if (lookup(filename,word)){
        ifstream file(filename);
        char line[N];
        ofstream out("outfile.txt");

        while (!file.eof()){
            file.getline(line, N, '\n');
            if (strcmp(word, line) != 0 && line[0] != 0) {
                out << line << endl;
            }
        }

        file.close();
        out.close();
        remove(filename);
        rename("outfile.txt", filename);
        cout << "The word \"" << word << "\" is deleted!" << endl;
    }
    else {
        cout << "The word \"" << word << "\" is not found!" << endl;
    }
    
}


// insert a word in the input file such that the words are in ascending order
// it should not insert duplicate word
void insert_word(const char filename[], const char word[]){
    if (!lookup(filename, word)) {
        ifstream file(filename);
        char line[N];
        ofstream out("outfile.txt");

        bool found = false;

        while (!file.eof()){
            file.getline(line, N, '\n');
            if (line[0] == 0 && !found){
                out << word << endl;
            }
            if (strcmp(word, line) > 0 && line[0] != 0) {
                out << line << endl;
            }
            else if (strcmp(word, line) < 0 && !found && line[0] != 0) {
                found = true;
                out << word << endl;
                out << line << endl;
            }
            else if (strcmp(word, line) < 0 && found && line[0] != 0){
                out<<line<<endl;
            }
        }

        file.close();
        out.close();
        remove(filename);
        rename("outfile.txt", filename);
        cout << "The word \"" << word << "\" has been insterted" << endl;
    }
    else {
        cout << "The word \"" << word << "\" already exists." << endl;
    }

}

int main(){
	const char filename[] = "words.txt";
	char choice;
	char word[N];

	while (true){
		cout << "1 for lookup; 2 for insertion; 3 for deletion; q for quit: ";
		cin >> choice;

		if (choice == '1'){
			cout << "Please enter the word you want to search for: ";
			cin >> word;
			if (lookup(filename, word)){
				cout << "The word \"" << word << "\" is found!" << endl;
			}else{
				cout << "The word \"" << word << "\" is not found!" << endl;
			}
		}else if (choice == '2'){
			cout << "Please enter the word you want to insert: ";
			cin >> word;
			insert_word(filename, word);
		}else if (choice == '3'){
			cout << "Please enter the word you want to delete: ";
			cin >> word;
			delete_word(filename, word);
		}else if (choice == 'q'){
			break;
		}else{
			cout << "Invalid input. Please input again." << endl;
		}
		cout << endl;
	}

	return 0;
}
//ONLY SUBMIT THIS FILE TO ZINC
#include "given.h"
#include "todo.h"
#include <iostream>
using namespace std;
//be reminded that you should NOT include any additional library, please read "Additional Notes" on the PA3 webpage 

Node*** generateMap(int width, int height)
{
    Node*** map = new Node**[height];
    for(int i = 0; i < height; ++i)
        map[i] = new Node*[width];

    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            map[i][j] = nullptr;
        }
    }
    
    return map; 
}

void printHeroStatus(const HeroStatus& heroStatus)
{
    cout << "Hero status: x=" << heroStatus.x << " y=" << heroStatus.y << " #mace=" << heroStatus.maceCount <<
    " #dagger=" << heroStatus.daggerCount << " #sword=" << heroStatus.swordCount << endl;
}

void printMonsterCount(Node*** map, int width, int height)
{
    int monsters = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] != nullptr) {
                if (map[i][j]->thing == 3||
                map[i][j]->thing == 4||
                map[i][j]->thing == 5) {
                    Node *current = map[i][j];
                    while (current != nullptr) {
                        monsters += current->quantity;
                        current = current->next;
                    }
                }
            }
        }
    }

    if (monsters == 1) {
        cout<< "There is still one more monster left!" << endl;
    }
    else {
        cout << "There are " << monsters << " monsters left in the world!" << endl;
    }
}

int getLinkedListLength(const Node* head)
{
    int count = 0;
    const Node *current = head;
    while (current != nullptr)
    {
        count++;
        current = current->next;
    }
    return count;
}

bool addThing(Node*** map, int width, int height, int x, int y, Thing thing, int quantity)
{
    if (x < width && y < height && x>=0 && y>=0){
        Node *current = map[y][x];
        
        if (current == nullptr){
            Node *n = new Node;
            n->thing = thing;
            n->quantity = quantity;
            map[y][x] = n;
            return true;
        }

        while (current != nullptr){
            if (current->thing == thing) {
                current->quantity += quantity;
                return true;
            }
            if (current->next == nullptr){
                Node *n = new Node;
                n->thing = thing;
                n->quantity = quantity;
                current->next = n;
                return true;
            }
            current = current->next;
        }
    }
    return false;
}

bool removeThing(Node*** map, int width, int height, int x, int y, Thing thing, int quantity)
{
    if (y >= 0 && x >=0 && x < width && y < height) {
        Node *current = map[y][x];
        Node *temp = nullptr;

        if (current == nullptr) {
            return false;
        }

        if (current->thing == thing && current != nullptr) {
            if (current->quantity > quantity) {
                current->quantity -= quantity;
                return true;
            }
            else if (current->quantity == quantity) {
                map[y][x] = current->next;
                delete current;
                return true;
            }
            
        }

        while (current->thing != thing && current != nullptr) {
            temp = current;
            current = current->next;
        }
        if (current == nullptr) {
            return false;
        }
        if (current->quantity > quantity) {
            current->quantity -= quantity;
            return true;
        }
        else if (current->quantity == quantity) {
            temp->next = current->next;
            delete current;
            return true;
        }
    }
    return false;
}

void deleteLinkedList(Node*& head)
{
    Node *current = head;
    Node *next;

    while (current != nullptr) {
        
        next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;
}

void deleteMap(Node*** map, int width, int height)
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] != nullptr) {
                deleteLinkedList(map[i][j]);
            }
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            delete map[i][j];
        }
        delete [] map[i];
    }
    delete [] map;
}

bool moveHero(char move, Node*** map, int width, int height, HeroStatus &heroStatus)
{
    int x = heroStatus.x;
    int y = heroStatus.y;

    switch (move){
    case 'w':
        y -= 1;
        break;
    case 's':
        y += 1;
        break;
    case 'a':
        x -= 1;
        break;
    case 'd':
        x += 1;
        break;
    default:
        break;
    }

    if (x >= 0 && y >= 0 && y < height && x < width) {
        Node *n = new Node;
        n->thing = HERO;
        if (map[y][x]==nullptr){
            map[heroStatus.y][heroStatus.x] = nullptr;
            map[y][x] = n;
            heroStatus.x = x;
            heroStatus.y =y;
            return true;
        }
        else {
            Node *current = map[y][x];
            if (map[y][x]->thing == MACE || map[y][x]->thing == DAGGER || map[y][x]->thing == SWORD){
                while (current != nullptr){
                    if (current->thing == MACE){
                        heroStatus.maceCount += current->quantity;
                    }
                    else if (current->thing == DAGGER) {
                        heroStatus.daggerCount += current->quantity;
                    }
                    else if (current->thing == SWORD) {
                        heroStatus.swordCount += current->quantity;
                    }
                    current = current->next;
                }
                deleteLinkedList(map[y][x]);
                map[heroStatus.y][heroStatus.x] = nullptr;
                map[y][x] = n;
                heroStatus.x = x;
                heroStatus.y =y;
                return true;
            }
            if (map[y][x]->thing == SKELETON || map[y][x]->thing == VAMPIRE || map[y][x]->thing == DRAGON) {
                bool gameOver = false;
                int tempMaceCount = heroStatus.maceCount;
                int tempDaggerCount = heroStatus.daggerCount;
                int tempSwordCount = heroStatus.swordCount;
                while (current != nullptr){
                    if (current->thing == SKELETON){
                        if (current->quantity <= tempMaceCount){
                            tempMaceCount -= current->quantity;
                        }
                        else {
                            gameOver = true;
                            break;
                        }
                    }
                    else if (current->thing == VAMPIRE) {
                        if (current->quantity <= tempDaggerCount){
                            tempDaggerCount -= current->quantity;
                        }
                        else {
                            gameOver = true;
                            break;
                        }
                    }
                    else if (current->thing == DRAGON) {
                        if (current->quantity <= tempSwordCount){
                            tempSwordCount -= current->quantity;
                        }
                        else {
                            gameOver = true;
                            break;
                        }
                    }
                    current = current->next;
                }
                if (!gameOver) {
                    heroStatus.maceCount = tempMaceCount;
                    heroStatus.daggerCount = tempDaggerCount;
                    heroStatus.swordCount = tempSwordCount;
                    deleteLinkedList(map[y][x]);
                    map[heroStatus.y][heroStatus.x] = nullptr;
                    map[y][x] = n;
                    heroStatus.x = x;
                    heroStatus.y =y;
                }
                else {
                    map[heroStatus.y][heroStatus.x] = nullptr;
                    heroStatus.x = x;
                    heroStatus.y =y;
                    heroStatus.alive = false;
                }
                return true;
            }
        }
    }
    return false;
}

int getMonsterCount(Node*** map, int width, int height)
{
    int monsters = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] != nullptr) {
                if (map[i][j]->thing == 3||
                map[i][j]->thing == 4||
                map[i][j]->thing == 5) {
                    Node *current = map[i][j];
                    while (current != nullptr) {
                        monsters += current->quantity;
                        current = current->next;
                    }
                }
            }
        }
    }

    return monsters;
}

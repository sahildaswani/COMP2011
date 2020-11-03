#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <time.h>
using namespace std;


// ************************************************************************
// helper functions (do not change these functions)
// ************************************************************************

// print the maze map
void print_maze(char maze[], int width, int height) {
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            cout << maze[i*width+j] << " ";
        }
        cout << endl;
    }
}

// print the planned path
void print_path(char maze[], bool path[], int width, int height) {
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            if (path[i*width+j]) {
                cout << "x" << " ";
            } else {
                cout << maze[i*width+j] << " ";
            }
        }
        cout << endl;
    }
}

// ************************************************************************
// core functions (you need to complete these functions)
// ************************************************************************

// helper function: test (x,y) is a valid position (within the maze map) or not
// return true if (x, y) is a valid cell
bool is_valid(int x, int y, int width, int height) {
    if ((x <= width-1 && x >= 0) && (y >=0 && y <= height-1)){
        return true;
    }
    return false;
}

// helper function: test (x,y) is the Exit or not 
// return true if (x, y) is the Exit
bool is_exit(int x, int y, int end_x, int end_y) {
    if (x == end_x && y == end_y){
        return true;
    }
    return false;
}

// helper function: test (x,y) is a wall or not
// return true if (x, y) is a dead cell (wall)
bool is_wall(char maze[], int x, int y, int width, int height) {
    int index = width * y + x;

    if (maze[index] == '#') {
        return true;
    }
    return false;
}

void find_pos(char maze[], char symbol, int pos[], int width, int height){
    int mazeSize = width * height;

    int y = 0;
    int x = 0;

    for (int i=0; i < mazeSize; i++){
        if (i % width == 0 && i != 0) {
            y += 1;
            x = 0;
        }
        if (maze[i] == symbol){
            break;
        }
        else{
            x += 1;
        }
    }

    pos[0] = x;
    pos[1] = y;
}

// helper function: test (x,y) is a dangerous position or not
// return true if (x, y) is a dangerous cell
bool is_dangerous(char maze[], int x, int y, int width, int height) {
    int T_pos[2];
    find_pos(maze, 'T', T_pos, width, height);

    if (x >= T_pos[0] - 1 && x <= T_pos[0] + 1 && y >= T_pos[1]-1 && y <= T_pos[1] +1){
        return true;
    }
    return false;

}

/**
    task 1: find a safe path to the Exit 
    description: Given a maze map, the entry (x, y) and the exit (exit_x, exit_y), 
    find a safe path from the entry to the exit, and save the planned path.

    @param maze the maze map: '.' (empty cell), 'x' (dead cell), 'T' (Tom), 'o' (cheese).
    @param path a variable to save the planned path: true (included), false (not included)
    @param x x axis of the entry.
    @param y y axis of the entry.
    @param exit_x x axis of the exit.
    @param exit_y y axis of the exit.
    @param width width of the maze map.
    @param height height of the maze map.
    @return whether find a safe path from (x,y) to (exit_x, exit_y) or not
**/
bool find_safe_path(char maze[], bool path[], int x, int y, int exit_x, int exit_y, int width, int height) {
    if (is_exit(x, y, exit_x, exit_y) && !is_wall(maze, x, y, width, height) && !is_dangerous(maze, x, y, width, height)){
        path[x+width*y] = true;
        return true;
    }
    if (is_valid(x, y, width, height) && !is_wall(maze, x, y, width, height) && !is_dangerous(maze, x, y, width, height)) {
        path[x+width*y] = true;

        if(find_safe_path(maze, path, x+1, y, exit_x, exit_y, width, height)){
            return true;
        }
        else if (find_safe_path(maze, path, x, y+1, exit_x, exit_y, width, height)) {
            return true;
        }
        else {
            path[x+width*y] = false;
            return false;
        }
    }
    return false;
}

/**
    task 2: find a safe path with cheese to the Exit
    description: Given a maze map, find a safe path from the entry to the exit, 
    and save the planned path. Note that the default entry and exit are (0, 0) 
    and (width-1, height-1).

    @param maze the maze map: '.' (empty cell), 'x' (dead cell), 'T' (Tom), 'o' (cheese).
    @param path a variable to save the planned path: true (included), false (not included)
    @param cheese_x x axis of the cheese.
    @param cheese_y y axis of the cheese.
    @param width width of the maze map.
    @param height height of the maze map.
    @return whether find a safe path through (cheese_x, cheese_y) from (x,y) to (exit_x, exit_y) or not
**/
bool find_safe_path_with_cheese(char maze[], bool path[], int x, int y, int exit_x, int exit_y, int cheese_x, int cheese_y, int width, int height) {
    bool start_to_cheese = find_safe_path(maze, path, 0, 0, cheese_x, cheese_y, width, height);
    bool cheese_to_end = find_safe_path(maze, path, cheese_x, cheese_y, exit_x, exit_y, width, height);
    
    if (start_to_cheese && cheese_to_end){
        return true;
    }
    return false;
}


// Maze Game: Tom and Jerry
int main() {
    // game initialization
    unsigned int width;
    unsigned int height;
    unsigned int cheese_x;
    unsigned int cheese_y;

    // Change this paramenter from 0 to 5 to test different cases.
    unsigned int test_case = 5;

    // set width, height and cheese_x, cheese_y
    switch(test_case) {
        case 1:
            width = 11; height = 10; cheese_x = 6; cheese_y = 7;
            break;
        case 2:
            width = 14; height = 10; cheese_x = 3; cheese_y = 7;
            break;
        case 3:
            width = 16; height = 8; cheese_x = 7; cheese_y = 4;
            break;
        case 4:
            width = 15; height = 9; cheese_x = 8; cheese_y = 3;
            break;
        case 5:
            width = 15; height = 9; cheese_x = 3; cheese_y = 5;
            break;
        default:
            width = 7; height = 5; cheese_x = 3; cheese_y = 1;
            break;
    }

    // a char array recording the maze map.
    char maze[140];

    // set maze map
    if (test_case == 0) {
        char tmp[7*5] = {
            '.', '.', '.', '.', '.', '#', '.', 
            '.', '#', '#', 'o', '.', '.', 'T',
            '.', '.', '.', '.', '.', '.', '#', 
            '.', '.', '.', '.', '.', '#', '.', 
            '.', '.', '#', '.', '.', '.', '.', 
        }; 
        copy(tmp, tmp + width*height, maze);
    }
    else if (test_case == 1) {
        char tmp[110] = {
            '.', '.', '#', '.', '#', '.', '.', '.', '.', '#', '.', 
            '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 
            '.', '.', '.', '.', '.', '.', '.', '.', '#', '#', '#', 
            '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
            '.', '#', '#', '.', '.', '.', '.', '#', '.', '#', '.',
            '.', '.', '.', '#', '#', '.', '#', '#', '.', '.', '.',
            '.', 'T', '.', '.', '#', '.', '.', '.', '.', '#', '.',
            '.', '.', '.', '.', '.', '#', 'o', '.', '#', '.', '.',
            '#', '.', '.', '.', '#', '#', '.', '#', '.', '.', '#',
            '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.',
        };
        copy(tmp, tmp + width*height, maze);
    } else if (test_case == 2) {
        char tmp[140] = {
            '.', '.', '.', '.', '.', '.', 'T', '.', '.', '.', '#', '.', '.', '#',
            '.', '#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.',
            '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '#', '.', '.',
            '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
            '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
            '#', '.', '#', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#',
            '.', '.', '#', 'o', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.',
            '.', '.', '.', '.', '.', '.', '.', '#', '.', '#', '.', '.', '.', '#',
            '.', '.', '.', '#', '#', '.', '#', '.', '.', '.', '#', '#', '.', '.',
            '.', '#', '#', '#', '.', '.', '.', '.', '.', '#', '.', '#', '.', '.',
        };
        copy(tmp, tmp + width*height, maze);
    } else if (test_case == 3) {
        char tmp[128] = {
            '.', '.', '#', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.',
            '.', '#', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.',
            '.', '#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', 'T', '#', '.',
            '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '#', '.', '#',
            '.', '#', '.', '#', '.', '.', '.', 'o', '.', '.', '.', '.', '.', '.', '.', '.',
            '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '#', '.', '#', '#',
            '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '#',
            '.', '#', '.', '.', '#', '.', '.', '#', '.', '#', '#', '.', '.', '.', '.', '.',
        }; 
        copy(tmp, tmp + width*height, maze);
    } else if (test_case == 4) {
        char tmp[135] = {
            '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#', '.',
            '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
            '#', '#', '.', '.', '.', '#', '#', '.', '.', '.', '.', '.', '.', '.', '.',
            '.', '#', '.', '.', '.', '.', '#', '.', 'o', '#', '.', '.', '#', '.', '.',
            '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#', '.', '.',
            '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.',
            '.', '#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '#',
            '#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '#', '#', '.', '.', '.',
            '.', '#', '#', '.', '#', '#', '.', '#', '#', 'T', '.', '.', '#', '.', '.',
        }; 
        copy(tmp, tmp + width*height, maze);
    } else if (test_case == 5) {
        char tmp[135] = {
            '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#',
            '.', '#', '.', '.', '#', '#', '#', '.', '.', '.', '.', '.', '#', '.', '.',
            '.', '.', '.', '#', '#', '.', '.', '#', '#', '.', '.', '.', '.', '.', '.',
            '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#',
            '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'T', '.', '#', '.',
            '.', '.', '.', 'o', '.', '.', '.', '#', '.', '.', '#', '#', '.', '.', '.',
            '#', '.', '.', '#', '.', '#', '.', '.', '.', '#', '.', '.', '#', '.', '.',
            '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.',
            '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
        }; 
        copy(tmp, tmp + width*height, maze);
    } else {
        cout << "No more test cases!" << endl;
        return 0;
    }

    // a bool array recording the path, "true" means the planned path goes through the cell.
    bool path[140];
    for (int i=0; i<width * height; i++) {
        path[i] = false;
    }

    cout << "**************************************************" << endl;
    cout << "Maze Game: Tom and Jerry" << endl;
    cout << "Maze Size (Width x Height): " << width << "x" << height << endl;
    cout << "Cheese Location: (" << cheese_x << "," << cheese_y << ")" << endl;
    cout << "**************************************************" << endl;

    print_maze(maze, width, height);
    cout << endl;

    // find a path from the entry to the exit
    bool status;
    status = find_safe_path(maze, path, 0, 0, width-1, height-1, width, height);
    if (status) {
        cout << "Find a path to the Exit: " << endl;
        print_path(maze, path, width, height);
    } else {
        cout << "Cannot find a path to the Exit!" << endl;
    }

    cout << endl;

    // find a path with cheese to the exit
    for (int i=0; i<width*height; i++) {
        path[i] = false;
    }

    status = find_safe_path_with_cheese(maze, path, 0, 0, width-1, height-1, cheese_x, cheese_y, width, height);
    if (status) {
        cout << "Find a path with cheese to the Exit: " << endl;
        print_path(maze, path, width, height);
    } else {
        cout << "Cannot find a path with cheese to the Exit!" << endl;
    }
	return 0;
}
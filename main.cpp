/* 
    First Name: Hossameldin
    Last Name: Abdelmoez
    SID: 230ADB031

    I hereby certify that I have come with the algorithmic solution by myself.

    Explanation:
    the idea is to use dijkstra shortest path algorithm to minimize the total 
    value of coins collected to reach the goal cell.

    Acknowledgement:
    I learnt this implementation of dijkstra at Nile University Competitive
    Programming community. So I want to give them part of the credit : )
*/

#include<bits/stdc++.h>
#include "dijkstra.h"
using namespace std;


// global variables
char file_name[] = "maze_101x101.txt";
pair<int, int> start_coordinates;
pair<int, int> goal_coordinates;


// prototypes
void take_input(vector<string> &maze);
void find_start(vector<string> &maze, int n);
void find_goal(vector<string> &maze, int n);


int main(){
    // a vector to store the maze 
    vector<string> maze;

    // reading the file and initializing the maze
    take_input(maze);

    // get the dimensions of the maze:
    int n = maze.size();

    find_start(maze, n);
    find_goal(maze, n);

    // finding the minimum coins value collected to reach goal cell
    int ans = dijkstra(maze, n, start_coordinates, goal_coordinates);

    cout << ans << "\n";
    return 0;
}



void take_input(vector<string> &maze){    
    // redirecting standard input to be a file instead of keyboard
    // then checking if no file is found, exit with code 404 
    if(freopen(file_name, "rt", stdin) == NULL){
        cout << "Wrong file name\n";
        exit(404);
    }
    // the checking of freopen return is accredited to a stack overflow post
    // https://stackoverflow.com/questions/20908740/check-the-return-value-of-freopen-in-c 

    string line;
    // read next line while it is not EOF
    while(cin >> line){
        // insert the read line to maze 
        maze.push_back(line);
    }
}


void find_start(vector<string> &maze, int n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(maze[i][j] == 'S'){
                start_coordinates = {i, j};
                return ;
            }
        }
    }
}


void find_goal(vector<string> &maze, int n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(maze[i][j] == 'G'){
                goal_coordinates = {i, j};
                return ;
            }
        }
    }
}
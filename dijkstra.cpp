#include<bits/stdc++.h>
using namespace std;


// this variable represents infinity
const int OO = 1e9;

// these two arrays are used to traverse the maze
// (aka to generate edges between the cells)
int dir_r[4] = {1, -1, 0, 0};
int dir_c[4] = {0, 0, 1, -1};



// check if the generated coordinates are in the maze boundaries
bool valid(int r, int c, int n){
    return (r < n && r > -1 && c < n && c > -1);
}


int dijkstra(vector<string> &maze, int n, pair<int, int> start_coordinates, pair<int, int> goal_coordinates){
    // this is an array to keep track of the total
    // coins value up to node with coordinates (i, j)
    int coins_val[n][n];

    // initialize all values with infinity
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j) coins_val[i][j] = OO;
    }

    // initialize the coins at the starting cell with 0
    coins_val[start_coordinates.first][start_coordinates.second] = 0;

    // this priority queue stores the coins collected
    // up to the reached node, and the coordinates of the
    // reached node, while keeping the smallest values first, as follows:
    // priority_queue< pair<coins, pair<row_coordinate, col_coordinate> >>
    priority_queue<pair<int, pair<int, int>>> pq;


    // keep in mind that this is a max heap pq and we want it 
    // to be a min heap, so we can multiply the coin_value with -1
    // to mimic the behaviour of min heap and multiply again by -1 while
    // extracting the value from the pq. If this is not clear  enough,
    // please continue to where the the algorithm pushes data to the pq
    // and it will be much clearer.


    // push the start coordinate with coins value equal to zero
    pq.push({0, start_coordinates});

    // continue looping throw nodes in the pq until it is empty
    while(!pq.empty()){
        // notice that the node coins is pushed to the pq with a negative value 
        // so it should be returned back to a positive value by adding a negative sign.
        int nd_coins = -pq.top().first;

        // these are the row and column coordinates of the node
        int nd_r = pq.top().second.first;
        int nd_c = pq.top().second.second;

        // remove the node from the priority queue
        pq.pop();

        // this is an optimization, which means if this
        // is an old node cost update, skip
        if(nd_coins != coins_val[nd_r][nd_c]) continue;


        // traversing the four adjacent cells of the current cell
        for(int i = 0; i < 4; ++i){
            int ch_r = nd_r + dir_r[i];
            int ch_c = nd_c + dir_c[i];

            // if this cell is out of the maze boundaries, skip
            if(!valid(ch_r, ch_c, n)) continue;
            
            // if this cell is a wall, skip
            if(maze[ch_r][ch_c] == 'X') continue;

            // if this is the goal cell, check if we reached it
            // with a coins less than the previous ones
            if(maze[ch_r][ch_c] == 'G'){
                coins_val[ch_r][ch_c] = min(coins_val[ch_r][ch_c], nd_coins);
                continue;
            }

            // calculating the number of coins to take the child cell
            int new_cell_coins = nd_coins + ((int)(maze[ch_r][ch_c] - '0')); // last part is casting

            // checking if the new collected value of coins to child cell
            // is smaller, then update coins_val and add cell to pq
            if(new_cell_coins < coins_val[ch_r][ch_c]){
                coins_val[ch_r][ch_c] = new_cell_coins;
                // the coins count is pushed as a negative value
                pq.push({-new_cell_coins, {ch_r, ch_c}});
            }
        }
    }


    // return the minimum coins value collected to reach goal cell
    return coins_val[goal_coordinates.first][goal_coordinates.second];
}
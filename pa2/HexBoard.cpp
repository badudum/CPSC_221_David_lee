#include "HexBoard.h"

#include <iostream>
#include <utility>
#include "queue.h"
#include "stack.h"

HexBoard::HexBoard(int radius) {
    this->radius = radius;
    start_coord.first = 0;
    start_coord.second =0;
    this->longest_path_dist =0;
    create_board();
    //br_prob = 0;
}


void HexBoard::create_board() {
    for (int q = -(radius-1); q < radius; q++) {
            int r1 = std::max(-(radius-1), -q - (radius-1));
            int r2 = std::min((radius-1), -q + (radius-1));
            for (int r = r1; r <= r2; r++) {
                pair<int, int> coord;
                coord.first = q;
                coord.second = r;
                this->cells[coord] = new HexCell(q,r);
            }
    }
    configure_cells();
}

void HexBoard::configure_cells() {
    for(auto const& x : cells){
        vector<pair<int,int>> coords = get_neigh_coords(make_pair(x.second->q,x.second->r));
        for(int y = 0; y < 6; y++){
            auto find = this->cells.find(coords[y]);
            if (find == cells.end()){
                x.second->neighbours[y] = NULL;
            }
            else {
                x.second->neighbours[y] = find->second;
                if(y<3){
                    find->second->neighbours[y+3] = x.second;
                }
                else{
                    find->second->neighbours[y%3] = x.second;
                }
                
            }
           
        }
    }

}

void HexBoard::generate_maze(pair<int, int> start_coord, double branch_prob) {
    Stack<HexCell*> cell_stack;
    this->start_coord = start_coord;
    auto it =  this->cells.find(start_coord);
    cell_stack.push(it->second);
    it->second->path_dist_from_start = 0;
    
    map<pair<int,int>, bool> visited;
    visited[start_coord] = true;

    int longpath = 0;

    while(!cell_stack.isEmpty()){
        HexCell *curr_cell = cell_stack.peek();
        HexCell *curr_neighbour = chooseNeighbour(curr_cell, visited, branch_prob);



        if(curr_neighbour != nullptr){
            curr_cell->link(curr_neighbour);
            visited[make_pair(curr_neighbour->q,curr_neighbour->r)] = true;
            curr_neighbour->path_dist_from_start = curr_cell->path_dist_from_start + 1;

            if(curr_neighbour->path_dist_from_start > longpath && curr_neighbour->is_edge()){
                longpath  = curr_neighbour->path_dist_from_start;
                end_coord = {curr_neighbour->q, curr_neighbour->r};
            }

            if(curr_neighbour->path_dist_from_start > longest_path_dist){
                longest_path_dist = curr_neighbour->path_dist_from_start;
            }
            cell_stack.push(curr_neighbour);
        }
        else{
            cell_stack.pop();
        }
        
    }

}

void HexBoard::solve_maze() {
    vector<pair<int,int>> solve;
    //cout << start_coord.first << " " << start_coord.second << endl;
    auto it = this->cells.find(this->start_coord);
    HexCell* start = it->second;
    cout << end_coord.first << " " << end_coord.second << endl;
    solve_maze_help(start, solve);

}

void HexBoard::solve_maze_help(HexCell *curr, vector<pair<int, int>> path){
    if(curr == nullptr){
        return;
    }
    pair<int, int> curr_coord = {curr->q, curr->r};
    
    //cout << curr_coord.first << "   " << curr_coord.second << endl;
    path.push_back(curr_coord);
    visited.push_back(curr_coord);
    HexCell *current_cell = this->cells[curr_coord];

    if(curr_coord == end_coord){
        this->solution = path;
    }

    for(auto &cell : curr->links){ //cells in links 
        if(cell != nullptr){
            pair<int, int> cell_coordinate = {cell->q,cell->r};
            if(std::find(visited.begin(), visited.end(), cell_coordinate) == visited.end()){
                solve_maze_help(cell, path);
            }
        }
    }
}
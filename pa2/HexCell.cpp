#include "HexCell.h"

#include <cmath>
#include <algorithm>
#include <utility>
#include <bits/stdc++.h>
#include <iostream>

using std::pair;
using std::vector;
using namespace std;
HexCell::HexCell(int Q, int R) {
    r = R;
    q = Q;
    for(int x =0; x<6; x++){
        neighbours[x] = nullptr;
        links[x] = nullptr;
    }
    path_dist_from_start = 0;
}

void HexCell::link(HexCell* cell) {
    if(cell == NULL){
        return;
    }
    vector<pair<int,int>>  coords = {{q, r - 1},{q + 1, r - 1},{q + 1, r},{q, r + 1},{q - 1, r + 1},{q - 1, r}};
    auto iterate = find(coords.begin(), coords.end(), make_pair(cell->q,cell->r));
    if( iterate == coords.end()){
        return;
    } 
    else{
        int dir = iterate - coords.begin();
        //cout << "direction " << dir << " pair " << cell->q <<  " " << cell->r << " this pair " << q << " " << r << endl;
        links[dir] = cell;
        neighbours[dir] = cell;
        if(dir <3){
            cell->links[dir+3]= this;
            cell->neighbours[dir+3] = this;
        }
        else{
            cell->links[dir%3] = this;
            cell->neighbours[dir%3] = this;
        }
    }
    //cout << "linked? " << is_linked(cell) << endl;
}

int HexCell::get_neighbour_side(const HexCell* cell) const {
    for(int x=0 ; x < 6; x++){
        if(neighbours[x] == cell){
            if(x>3){
                return x+3;
            }
            else {
                return x%3;
            } 
        }
    }
    return -1;
}

bool HexCell::is_linked(const HexCell* cell) const {
    if(cell == nullptr){return false;}
    for(int x =0; x < 6; x++){
        if(links[x] == cell){
            return true;
        }
    }
    return false;
}

int HexCell::distance(const HexCell* cell) const {
    int distance = (abs(q-cell->q) + abs(r-cell->r) + abs(q+r-cell->q-cell->r))/2;
    return distance;
}

bool HexCell::is_edge() const {
    int count =0;
    for (int x =0 ; x< 6; x++){
        if(neighbours[x] == NULL){
            count ++;
        }
    }
    if (count >= 2){
        return true;
    }
    return false;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "volcano.h"

int main (int argc, char** argv) {
    int N_locs = 8;
    int N_times = 2500000;
    
    // how to interpret volcano information?
    LOC *loc_Northeast_Asia  = init_loc(-1,  1, Northeast_Asia,  0, 0.001, 0, 0, 0);
    LOC *loc_East_Asia       = init_loc( 0,  0, East_Asia,       0, 0.001, 0, 0, 0);
    LOC *loc_Southeast_Asia  = init_loc( 0, -1, Southeast_Asia,  0, 0.001, 0, 0, 0);
    LOC *loc_Oceania         = init_loc( 1, -2, Oceania,         0, 0.001, 0, 0, 0);
    LOC *loc_South_America   = init_loc( 2, -2, South_America,   0, 0.001, 0, 0, 0);
    LOC *loc_Central_America = init_loc( 2, -1, Central_America, 0, 0.001, 0, 0, 0);
    LOC *loc_North_America   = init_loc( 2,  0, North_America,   0, 0.001, 0, 0, 0);
    LOC *loc_Europe          = init_loc(-2,  1, Europe,          0, 0.001, 0, 0, 0);
    
    MAP *map = init_map(N_locs);
    
    map->E[0] = 200;
    map->E[1] = 200;
    map->E[2] = 200;
    map->E[3] = 200;
    map->E[4] = 200;
    map->E[5] = 200;
    map->E[6] = 200;
    map->E[7] = 200;
    
    map->locs[0] = loc_Northeast_Asia;
    map->locs[1] = loc_East_Asia;
    map->locs[2] = loc_Southeast_Asia;
    map->locs[3] = loc_Oceania;
    map->locs[4] = loc_South_America;
    map->locs[5] = loc_Central_America;
    map->locs[6] = loc_North_America;
    map->locs[7] = loc_Europe;
    
    while (map->time < N_times) update_map(map);
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum {
    Northeast_Asia,
    East_Asia,
    Southeast_Asia,
    Oceania,
    South_America,
    Central_America,
    North_America,
    Europe
}LOCATIONS;

typedef struct loc_ {
    int x;
    int y;
    LOCATIONS index;
    int to_erupt;
    float base_energy_self_accumulate_rate;
    float energy_self_accumulate_rate;
    float energy_self_accumulated;
    float energy_received_from_neighbours;
    float energy_released_to_neighbours;
}LOC;

typedef struct map_ {
    float *E;
    int time;
    int number_of_locs;
    LOC **locs;
}MAP;

LOC *init_loc(int x, int y, LOCATIONS index, int to_erupt, float base_energy_self_accumulate_rate, float energy_self_accumulated, float energy_received_from_neighbours, float energy_released_to_neighbours) {
    LOC *loc = (LOC *)malloc(sizeof(struct loc_));
    loc->x = x;
    loc->y = y;
    loc->index = index;
    loc->to_erupt = to_erupt;
    loc->base_energy_self_accumulate_rate = base_energy_self_accumulate_rate;
    loc->energy_self_accumulate_rate = base_energy_self_accumulate_rate;
    loc->energy_self_accumulated = energy_self_accumulated;
    loc->energy_received_from_neighbours = energy_received_from_neighbours;
    loc->energy_released_to_neighbours = energy_released_to_neighbours;
    
    return loc;
};

MAP *init_map(int N) {
    MAP *map = (MAP *)malloc(sizeof(struct map_));
    map->E = (float *)malloc(sizeof(float)*N);
    map->time = 0;
    map->number_of_locs = N;
    map->locs = (LOC **)malloc(sizeof(struct loc_ *)*N);
    
    return map;
}

int if_erupt(float E_test, float E_erupt) {
    int tmp_if_to_erupt = 0;
    if (E_test >= E_erupt) tmp_if_to_erupt = 1;
    
    return tmp_if_to_erupt;
}

int dist(LOC *loc1, LOC *loc2) {
    int dist = (loc1->x-loc2->x)*(loc1->x-loc2->x)+(loc1->y-loc2->y)*(loc1->y-loc2->y);
    
    return dist;
}

void update_self(LOC *loc) {
    if (loc->to_erupt == 1) {
        loc->energy_self_accumulate_rate = 0.90*(loc->energy_self_accumulated + loc->energy_received_from_neighbours - loc->energy_released_to_neighbours);
        loc->to_erupt = 0;
    } else {
        loc->energy_self_accumulate_rate = loc->base_energy_self_accumulate_rate;
    }
    loc->energy_self_accumulated += loc->base_energy_self_accumulate_rate;
}

void update_receive(LOC *loc, LOC **locs, int N) {
    for (int i = 0; i < N; i++) {
        if (dist(loc, locs[i]) != 0) {
            loc->energy_received_from_neighbours += locs[i]->energy_self_accumulate_rate/dist(loc, locs[i])/N;
        }
    }
}

void update_release(LOC *loc, LOC **locs, int N) {
    for (int i = 0; i < N; i++) {
        if (dist(loc, locs[i]) != 0) {
            loc->energy_released_to_neighbours += loc->energy_self_accumulate_rate/N;
        }
    }
}

int printf_loc_info(LOC *loc) {
    printf("x: %d\n", loc->x);
    printf("y: %d\n", loc->y);
    printf("locations: %d\n", loc->index);
    printf("energy_self_accumulated: %f\n", loc->energy_self_accumulated);
    printf("energy_received_from_neighbours: %f\n", loc->energy_received_from_neighbours);
    printf("energy_released_to_neighbours: %f\n", loc->energy_released_to_neighbours);
    printf("energy_total: %f\n", loc->energy_self_accumulated + loc->energy_received_from_neighbours - loc->energy_released_to_neighbours);
    
    return 0;
}

int printf_map_info(MAP *map) {
    for (int i = 0; i < map->number_of_locs; i++) {
        if (map->locs[i]->to_erupt == 1) {
            printf("time: %d\n", map->time);
            printf_loc_info(map->locs[i]);
        }
    }
    
    return 0;
}

int update_map(MAP *map) {
    for (int i = 0; i < map->number_of_locs; i++) update_self(map->locs[i]);
    
    for (int i = 0; i < map->number_of_locs; i++) {
        update_receive(map->locs[i], map->locs, map->number_of_locs);
        update_release(map->locs[i], map->locs, map->number_of_locs);
        
        float total_energy_for_test = map->locs[i]->energy_self_accumulated + map->locs[i]->energy_received_from_neighbours - map->locs[i]->energy_released_to_neighbours;
        
        map->locs[i]->to_erupt = if_erupt(total_energy_for_test, map->E[i]);
        
        if (map->locs[i]->to_erupt == 1) {
            //printf("========\n");
            //printf("time: %d\n", map->time);
            //printf("%d\n", map->time);
            //printf_loc_info(map->locs[i]);
            printf("%d, %d, %f\n", map->time, map->locs[i]->index, map->locs[i]->energy_self_accumulated + map->locs[i]->energy_received_from_neighbours - map->locs[i]->energy_released_to_neighbours);
        }
    }
    
    map->time++;
    
    return 0;
}

#include <iostream>
#include "VectorMap.h"

const float LOG_ODD_OCCUPIED = 0.9,
            LOG_ODD_FREE = 0.7;

const bool OCCUPIED = 1,
           FREE = 0;

const unsigned long X_OCCUPIED_START = 100,
                    X_OCCUPIED_END = 500,
                    Y_OCCUPIED_START = 250,
                    Y_OCCUPIED_END = 500;

const int UP = 90,
          DOWN = 270,
          LEFT = 180,
          RIGHT = 0;

const int POSITIONS = 10;
const unsigned long X_POSITIONS[POSITIONS] = {1, 157, 77, 70, 73, 99, 378, 658, 683, 400},
                    Y_POSITIONS[POSITIONS] = {1, 148, 274, 422, 529, 679, 607, 435, 216, 225};
const int DIRECTIONS[POSITIONS] = {RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, UP, LEFT, UP, DOWN};

int main() {
    VectorMap map;

    for (unsigned long x = X_OCCUPIED_START; x <= X_OCCUPIED_END; ++x){
        for (unsigned long y = Y_OCCUPIED_START; y <= Y_OCCUPIED_END; ++y){
            map.setOccupancy(OCCUPIED, x, y);
        }
    }

    for (unsigned p = 0; p < POSITIONS; ++p){
        map.updateMap(DIRECTIONS[p], LOG_ODD_OCCUPIED, LOG_ODD_FREE, X_POSITIONS[p], Y_POSITIONS[p]);
    }

    std::cout << map(1, 2).getLogOddMean() << std::endl;
    std::cout << map(400, 250).getLogOddMean() << std::endl;

    return 0;
}
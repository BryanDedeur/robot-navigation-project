#include <fstream>
#include <iostream>
#include "VectorMap.h"

const int MAP_WIDTH = 1000, MAP_HEIGHT = 1000;

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

    // // raw occupancy map image generation
    // std::cout << "Generating 'occupancy-map.ppm' file. Please wait..." << std::endl;
    //
    // std::ofstream img ("occupancy-map.ppm");
    // img << "P3" << std::endl; // image format
    // img << MAP_WIDTH << " " << MAP_HEIGHT << std::endl;
    // img << 255 << std::endl; // color range
    //
    // for (int y = 0; y < MAP_HEIGHT; y++){
    //     for (int x = 0; x < MAP_WIDTH; x++){
    //         if ((x >= X_OCCUPIED_START && x <= X_OCCUPIED_END) && (y >= Y_OCCUPIED_START && y <= Y_OCCUPIED_END))
    //             img << "0 0 0" << std::endl; // black pixel
    //         else
    //             img << "255 255 255" << std::endl; // white pixel
    //     }
    // }

    // probability map image generation
    std::cout << "Generating 'probability-map.ppm' file. Please wait..." << std::endl;

    std::ofstream img ("probability-map.ppm");
    img << "P3" << std::endl; // image format
    img << MAP_WIDTH << " " << MAP_HEIGHT << std::endl;
    img << 255 << std::endl; // color range
    float max = 0, min = 0;
    for (int y = 0; y < MAP_HEIGHT; y++){
        for (int x = 0; x < MAP_WIDTH; x++){

            bool isRobotPosition = 0;
            for (int i = 0; i < POSITIONS; i++)
              if (x == X_POSITIONS[i] && y == Y_POSITIONS[i])
                  isRobotPosition = 1;

            if (isRobotPosition) { // define robot position
                img << "255 0 0" << std::endl;
            } else if (map(x, y).getOccupancy()) {
                img << "0 0 0" << std::endl;
            } else if (map(x, y).getLogOddMean() == 0) {
                img << "255 255 255" << std::endl;
            } else { // all other positions
                int scalar = -map(x, y).getLogOddMean();
                int r = 255,
                    g = (3.5 - scalar)/3.5 * 255,
                    b = 255;
                img << r << " " << g << " " << b << std::endl;
            }
        }
    }


    return 0;
}

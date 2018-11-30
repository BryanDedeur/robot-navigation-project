#include <fstream>
#include <iostream>
#include "VectorMap.h"

const int MAP_WIDTH = 1000, MAP_HEIGHT = 1000;

const float LOG_ODD_OCCUPIED = 0.9f,
            LOG_ODD_FREE = -0.7f;

const bool OCCUPIED = true,
           FREE = false;

const unsigned long X_OCCUPIED_START = 100,
                    X_OCCUPIED_END = 500,
                    Y_OCCUPIED_START = 250,
                    Y_OCCUPIED_END = 500;

const int UP = 270,
          DOWN = 90,
          LEFT = 180,
          RIGHT = 0;

const int POSITIONS = 10;
const unsigned long X_POSITIONS[POSITIONS] = {1, 157, 77, 70, 73, 99, 378, 658, 683, 400},
                    Y_POSITIONS[POSITIONS] = {1, 148, 274, 422, 529, 679, 607, 435, 216, 225};
const int DIRECTIONS[POSITIONS] = {RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, UP, LEFT, UP, DOWN};

const float MAGNIFYCOLOR = 100.f;

void clip(int &value){
    if (value > 255){
        value = 255;
    } else if (value < 0){
        value = 0;
    }
}

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

    std::ofstream img2 ("probability-map.ppm");
    img2 << "P3" << std::endl; // image format
    img2 << MAP_WIDTH << " " << MAP_HEIGHT << std::endl;
    img2 << 255 << std::endl; // color range
    float max = 0, min = 0;
    for (unsigned long int y = 0; y < MAP_HEIGHT; y++){
        for (unsigned long int x = 0; x < MAP_WIDTH; x++){
            int r = 255,
                g = 255,
                b = 255;

            if (map(x, y).getOccupancy()) {
                r = 0;
                g = 0;
                b = 0;
            }

            bool isRobotPosition = false;
            for (int i = 0; i < POSITIONS; i++) {
                if (x == X_POSITIONS[i] && y == Y_POSITIONS[i]) {
                    isRobotPosition = true;
                    break;
                }
            }

            int scalar = static_cast<int>(map(x, y).getLogOddMean() * MAGNIFYCOLOR);
            if (scalar > max)
                max = scalar;
            if (scalar < min)
                min = scalar;
            if (scalar < 0){
                r = 255;
                g = 255 + scalar;
                b = 255 + scalar;
            }
                //if (scalar > 0){
            else if (scalar > 0) {
                r = 255 - scalar;
                g = 255 - scalar;
                b = 255;
            }
            clip(r);
            clip(g);
            clip(b);

            if (isRobotPosition) { // define robot position
                r = 0;
                g = 255;
                b = 0;
            } //else if (map(x, y).getLogOddMean() == 0.f) {
                //img2 << "255 255 255" << std::endl;
            //}
            img2 << r << " " << g << " " << b << std::endl;
        }
    }
    std::cout << "The max of the log odd mean is " << max << " the min is " <<  min << std::endl;




    return 0;
}

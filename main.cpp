#include <fstream>
#include <iostream>
#include "VectorMap.h"
#include <time.h>
#include <random>
#include <math.h>

bool RANDOM_MAP = true;

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
                    Y_POSITIONS[POSITIONS] = {1, 148, 274, 422, 500, 679, 607, 435, 216, 225}; //529
const int DIRECTIONS[POSITIONS] = {RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, UP, LEFT, UP, DOWN};

const float MAGNIFYCOLOR = 100.f;

void clipColor(int &value){
    if (value > 255){
        value = 255;
    } else if (value < 0){
        value = 0;
    }
}

std::ofstream definePPM(std::string filename) {
    std::cout << "Generating " << filename << ".ppm file. Please wait..." << std::endl;
    std::ofstream ppm (filename + ".ppm");
    ppm << "P3" << std::endl; // image format
    ppm << MAP_WIDTH << " " << MAP_HEIGHT << std::endl;
    ppm << 255 << std::endl; // color range
    return ppm;
}

void makePath(int lastX, int lastY, int newX, int newY, int pointMap[MAP_WIDTH][MAP_HEIGHT]) {
    int distance = static_cast<int>(round(sqrt(pow(newX-lastX,2)+pow(newY-lastY,2)))); // TODO: tighten gaps between nodes and lines by better rounding (see ppm file)
    int theta = static_cast<int>(round(atan2(newY - lastY, newX - lastX) * (180/M_PI))); //  TODO: prevent dividing by zero
    for (; distance > 1; --distance)
        pointMap[lastX + static_cast<int>(round(cos(theta * (M_PI/180)) * distance))][lastY + static_cast<int>(round(sin(theta * (M_PI/180)) * distance))] = 2;
}

void testRandomPositions(VectorMap &map) {
    for (unsigned p = 0; p < POSITIONS; ++p) {
        std::random_device generator;
        std::uniform_int_distribution<int> randomDirection(1, 360);
        std::uniform_int_distribution<int> randomPlotX(1, MAP_WIDTH-1);
        std::uniform_int_distribution<int> randomPlotY(1, MAP_HEIGHT-1);
        int newX = 0, newY = 0;
        do {
            newX = randomPlotX(generator), newY = randomPlotY(generator);
        } while (map(static_cast<unsigned long>(newX), static_cast<unsigned long>(newY)).getOccupancy());
        map.updateMap(randomDirection(generator), LOG_ODD_OCCUPIED, LOG_ODD_FREE, static_cast<unsigned long>(newX), static_cast<unsigned long>(newY));
    }
}

bool setRandomOccupancy(VectorMap &map, int fromX, int fromY, int quantity) {
    if (quantity == 0) {
        return true;
    } else {
        std::random_device generator;
        std::uniform_int_distribution<int> randomOffset(-2, 2);
        std::uniform_int_distribution<int> randomPlotX(1, MAP_WIDTH-1);
        std::uniform_int_distribution<int> randomPlotY(1, MAP_HEIGHT-1);
        int newX = 0, newY = 0, attempts = 8;
        do {
            --attempts;
            newX = randomOffset(generator) + fromX, newY = randomOffset(generator) + fromY;
            if (newX < 0 || newY < 0) {
                newX = fromX, newY = fromY;
            } else if (attempts <= 0) {
                newX = randomPlotX(generator), newY = randomPlotY(generator);
            }
        } while (map(static_cast<unsigned long>(newX), static_cast<unsigned long>(newY)).getOccupancy());
            map.setOccupancy(OCCUPIED, static_cast<unsigned long>(newX), static_cast<unsigned long>(newY));
            for (int i = 0; i < 8; i++){
                if (cos(i*180/M_PI) + newX > MAP_WIDTH ||
                cos(i*180/M_PI) + newX < 1 ||
                sin(i*180/M_PI) + newY > MAP_HEIGHT ||
                sin(i*180/M_PI) + newY < 1)
                    continue;
                if (!map(static_cast<unsigned long>(cos(i*180/M_PI) + newX), static_cast<unsigned long>(sin(i*180/M_PI) + newY)).getOccupancy()) {
                     map.setOccupancy(OCCUPIED, static_cast<unsigned long>(cos(i * 180 / M_PI) + newX),
                                      static_cast<unsigned long>(sin(i * 180 / M_PI) + newY));
                }
            }
        setRandomOccupancy(map, newX, newY, --quantity);
        return true;
    }
}

int main() {
    VectorMap map;

    int offset = 25;
    const int testPos = 9;

    if (RANDOM_MAP) {
        setRandomOccupancy(map, MAP_WIDTH/2, MAP_HEIGHT/2, 10000);
        testRandomPositions(map);
    } else {
        for (unsigned long x = X_OCCUPIED_START; x <= X_OCCUPIED_END; ++x) {
            for (unsigned long y = Y_OCCUPIED_START; y <= Y_OCCUPIED_END; ++y) {
                map.setOccupancy(OCCUPIED, x, y);
            }
        }

        for (unsigned p = 0; p < POSITIONS; ++p) {
            map.updateMap(DIRECTIONS[p], LOG_ODD_OCCUPIED, LOG_ODD_FREE, X_POSITIONS[p], Y_POSITIONS[p]);
        }

        // loop testing a multiple times over a single position as requested by professor
        std::cout << "At point (" << X_POSITIONS[testPos] << ", " << Y_POSITIONS[testPos] << ")" << std::endl;
        std::cout << "| scan | LOM (occupied) | LOM (unoccupied) |" << std::endl;
        std::cout << "| ---- | -------------- | ---------------- |" << std::endl;
        for (unsigned i = 1; i < 10; ++i) {
            std::cout << "| " << i << "    | " <<
                      map(X_POSITIONS[testPos], Y_POSITIONS[testPos] + offset).getLogOddMean() << "            | " <<
                      map(X_POSITIONS[testPos], Y_POSITIONS[testPos] + offset - 1).getLogOddMean() << "             |"
                      << std::endl;
            map.updateMap(DIRECTIONS[testPos], LOG_ODD_OCCUPIED, LOG_ODD_FREE, X_POSITIONS[testPos],
                          Y_POSITIONS[testPos]);
        }
        std::cout << std::endl;
    }

    // random line generation test
//    int pointMap[MAP_WIDTH][MAP_HEIGHT] = {0};
//
//    std::random_device generator;
//    std::uniform_int_distribution<int> randomPlotX(1, MAP_WIDTH);
//    std::uniform_int_distribution<int> randomPlotY(1, MAP_HEIGHT);

//
//    int lastX = randomPlotX(generator);
//    int lastY = randomPlotY(generator);
//    for (int i = 0; i < 10; i++) { // run 5 tests points
//        int newX = randomOffset(generator);
//        int newY = randomOffset(generator);
//        makePath(lastX, lastY, newX, newY, pointMap);
//        lastX = newX;
//        lastY = newY;
//        pointMap[lastX][lastY] = 1;
//    }
//
//    std::ofstream img = definePPM("random-lines");
//    for (unsigned long int y = 0; y < MAP_HEIGHT; y++) {
//        for (unsigned long int x = 0; x < MAP_WIDTH; x++) {
//            int r = 255,
//                g = 255,
//                b = 255;
//            if ( pointMap[x][y] == 1)
//                r = 0, g = 0, b = 0;
//            else if (pointMap[x][y] == 2)
//                r = 0, g = 100, b = 100;
//
//            img << r << " " << g << " " << b << std::endl;
//        }
//    }

    // probability map image generation
    std::ofstream img2 = definePPM("probability-map");
    float max = 0, min = 0;
    for (unsigned long int y = 0; y < MAP_HEIGHT; y++){
        for (unsigned long int x = 0; x < MAP_WIDTH; x++){
            int r = 255, g = 255, b = 255;

            if (map(x, y).getOccupancy()) {
                r = 0, g = 0, b = 0;
            }

            int scalar = static_cast<int>(map(x, y).getLogOddMean() * MAGNIFYCOLOR);
            if (scalar > max)
                max = scalar;
            if (scalar < min)
                min = scalar;
            if (scalar < 0){
                r = 255, g = 255 + scalar, b = 255 + scalar;
            }

            else if (scalar > 0) {
                r = 255 - scalar, g = 255 - scalar, b = 255;
            }
            clipColor(r), clipColor(g), clipColor(b);

//            if (X_POSITIONS[testPos] == x && Y_POSITIONS[testPos]+offset == y) {
//                r = 255, g = 0, b = 255;
//            }
            img2 << r << " " << g << " " << b << std::endl;
        }
    }
    std::cout << "The max of the log odd mean is " << max << " the min is " <<  min << std::endl;

    return 0;
}

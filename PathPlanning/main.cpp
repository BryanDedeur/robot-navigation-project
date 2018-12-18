#include <iostream>
#include "VectorMap.h"
#include "PathMap.h"
#include "PathNode.h"
#include <memory>
#include <cmath>
#include <random>
#include <time.h>
#include <set>

const int MAP_WIDTH = 1000, MAP_HEIGHT = 1000;

const bool OCCUPIED = true,
           FREE = false;

const unsigned long X_OCCUPIED_START = 250,
                    X_OCCUPIED_END = 500,
                    Y_OCCUPIED_START = 250,
                    Y_OCCUPIED_END = 500;

bool collides(const std::shared_ptr<PathNode> &currVertex, const std::shared_ptr<PathNode> &testVertex, VectorMap map) {
  double distance = 0,
         x_length = 0,
         y_length = 0,
         x_inc = 0,
         y_inc = 0;
  unsigned long x_curr = currVertex->getX(),
                y_curr = currVertex->getY(),
                x_test = testVertex->getX(),
                y_test = testVertex->getY();

  x_length = x_test - x_curr;
  y_length = y_test - y_curr;

  distance = sqrt(x_length * x_length + y_length * y_length);
  x_inc = x_length/distance;
  y_inc = y_length/distance;

  for (double x = x_curr, y = y_curr;
       (x_test > static_cast<unsigned long>(x) ? x_test - static_cast<unsigned long>(x) : static_cast<unsigned long>(x) - x_test) > 10 ||
       (y_test > static_cast<unsigned long>(y) ? y_test - static_cast<unsigned long>(y) : static_cast<unsigned long>(y) - y_test) > 10;
       x += x_inc, y += y_inc){
    std::cout << (x_test > static_cast<unsigned long>(x) ? x_test - static_cast<unsigned long>(x) : static_cast<unsigned long>(x) - x_test) << " ";
    std::cout << (y_test > static_cast<unsigned long>(y) ? y_test - static_cast<unsigned long>(y) : static_cast<unsigned long>(y) - y_test) << std::endl;

    auto x_offset = static_cast<unsigned long>(x);
    auto y_offset = static_cast<unsigned long>(y);
    if (map(x_offset, y_offset).getOccupancy()) return true;
  }
  return false;
}

int main() {
  std::shared_ptr<PathNode> start = std::make_shared<PathNode>(70, 422);
  std::shared_ptr<PathNode> end = std::make_shared<PathNode>(658, 435);
  std::shared_ptr<PathNode> random_vertex = start;
  std::shared_ptr<PathNode> nearest_vertex;

  VectorMap map;

  PathMap path(start);

  std::random_device generator;
  std::uniform_int_distribution<unsigned long> distribution(0, 999);
  std::set<unsigned long> generated_x;
  std::set<unsigned long> generated_y;

  int vertices = 0;

  unsigned long x_coordinate, y_coordinate;

  for (unsigned long x = X_OCCUPIED_START; x <= X_OCCUPIED_END; ++x) {
    for (unsigned long y = Y_OCCUPIED_START; y <= Y_OCCUPIED_END; ++y) {
      map.setOccupancy(OCCUPIED, x, y);
    }
  }

  // TODO: fix logic in while loops, code gets stuck in seemingly infinite loop
  while (!(random_vertex == end)){
    do{
      x_coordinate = distribution(generator);
      y_coordinate = distribution(generator);
      random_vertex = std::make_shared<PathNode>(x_coordinate, y_coordinate);
    } while(path.findNearest(random_vertex) == random_vertex || map(x_coordinate, y_coordinate).getOccupancy());
    nearest_vertex = path.findNearest(random_vertex);
    std::cout << nearest_vertex->getX() << "\t" << nearest_vertex->getY() << std::endl;
    if (!collides(nearest_vertex, random_vertex, map)){
      random_vertex->setPointsTo(nearest_vertex);
      path.addVertex(random_vertex);
    }
  }

  vertices = path.outputPathFound();

  return 0;
}
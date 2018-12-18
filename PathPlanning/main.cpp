#include <iostream>
#include "VectorMap.h"
#include "PathMap.h"
#include "PathNode.h"
#include <memory>
#include <cmath>
#include <random>
#include <time.h>
#include <set>

const int MAP_WIDTH = 1000, MAP_HEIGHT = 1000, MAX_VERTICES = 1000;

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

  if (x_test > x_curr) x_length = x_test - x_curr;
  else x_length = x_curr - x_test;
  if (y_test > y_curr) y_length = y_test - y_curr;
  else y_length = y_curr - y_test;

  distance = sqrt(x_length * x_length + y_length * y_length);
  x_inc = x_length/distance;
  y_inc = y_length/distance;

  for (double x = x_curr, y = y_curr;
       static_cast<unsigned long>(x) < x_test &&
       static_cast<unsigned long>(y) < y_test;
       x += x_inc, y += y_inc){
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

  unsigned long x_vertices[MAX_VERTICES] = {0};
  unsigned long y_vertices[MAX_VERTICES] = {0};
  int vertices = 0;

  unsigned long x_coordinate, y_coordinate;
  bool x_notExisted, y_notExisted;

  for (unsigned long x = X_OCCUPIED_START; x <= X_OCCUPIED_END; ++x) {
    for (unsigned long y = Y_OCCUPIED_START; y <= Y_OCCUPIED_END; ++y) {
      map.setOccupancy(OCCUPIED, x, y);
    }
  }

  while (!(random_vertex == end)){
    do{
      x_coordinate = distribution(generator);
      y_coordinate = distribution(generator);
      x_notExisted = generated_x.find(x_coordinate) != generated_x.end();
      y_notExisted = generated_y.find(y_coordinate) != generated_y.end();
    } while(x_notExisted && y_notExisted && !map(x_coordinate, y_coordinate).getOccupancy());
    if (x_notExisted) generated_x.insert(x_coordinate);
    if (y_notExisted) generated_y.insert(y_coordinate);
    random_vertex->setCoordinate(x_coordinate, y_coordinate);
    nearest_vertex = path.findNearest(random_vertex);
    if (!collides(nearest_vertex, random_vertex, map)){
      random_vertex->setPointsTo(nearest_vertex);
      path.addVertex(random_vertex);
    }
  }

  vertices = path.outputPathFound(x_vertices, y_vertices, MAX_VERTICES);

  std::cout << "x\ty" << std::endl;
  for (int i = 0; i < vertices; ++i){
    std::cout << x_vertices[i] << '\t' << y_vertices[i] << std::endl;
  }

  return 0;
}
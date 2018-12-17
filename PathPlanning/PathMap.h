//
// Created by eric on 12/16/18.
//

#ifndef PATHPLANNING_PATHMAP_H
#define PATHPLANNING_PATHMAP_H

#include "PathList.h"
#include <memory>
#include <float.h>
#include <cmath>
#include <iostream>

class PathMap {
 private:
  std::unique_ptr<PathList> vertices_;
 public:
  explicit PathMap(const std::shared_ptr<PathNode> &start);
  ~PathMap();

  std::shared_ptr<PathNode> findNearest(const std::shared_ptr<PathNode> &vertex) const;
  void addVertex(const std::shared_ptr<PathNode> &newVertex);
  int outputPathFound(unsigned long x_vertices[], unsigned long y_vertices[], int size) const;
};

#endif //PATHPLANNING_PATHMAP_H

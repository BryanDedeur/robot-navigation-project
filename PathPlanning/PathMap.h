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
  explicit PathMap(std::shared_ptr<PathNode> start);
  ~PathMap();

  std::shared_ptr<PathNode> findNearest(std::shared_ptr<PathNode> vertex) const;
  void addVertex(std::shared_ptr<PathNode> newVertex);
  int outputPathFound() const;
};

#endif //PATHPLANNING_PATHMAP_H

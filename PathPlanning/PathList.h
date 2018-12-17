//
// Created by eric on 12/16/18.
//

#ifndef PATHPLANNING_PATHLIST_H
#define PATHPLANNING_PATHLIST_H

#include "PathNode.h"
#include <memory>

class PathList {
 private:
  std::shared_ptr<PathNode> tail_;
 public:
  PathList();
  explicit PathList(const std::shared_ptr<PathNode> &start);
  ~PathList();

  void add(const std::shared_ptr<PathNode> &newVertex);
  std::shared_ptr<PathNode> getTail() const;
};

#endif //PATHPLANNING_PATHLIST_H

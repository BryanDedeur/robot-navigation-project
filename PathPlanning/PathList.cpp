//
// Created by eric on 12/16/18.
//

#include "PathList.h"
PathList::PathList() = default;
PathList::PathList(const std::shared_ptr<PathNode> &start):
  tail_(start) {}
PathList::~PathList() {
  tail_.reset();
}
void PathList::add(const std::shared_ptr<PathNode> &newVertex) {
  newVertex->setNext(tail_);
  tail_->setNext(newVertex);
}
std::shared_ptr<PathNode> PathList::getTail() const {
  return tail_;
}

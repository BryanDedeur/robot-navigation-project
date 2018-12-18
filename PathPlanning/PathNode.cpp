//
// Created by eric on 12/16/18.
//

#include "PathNode.h"

PathNode::PathNode():
  x_(0), y_(0), next_(nullptr), pointsTo_(nullptr) {}

PathNode::PathNode(unsigned long x, unsigned long y):
  x_(x), y_(y), next_(nullptr), pointsTo_(nullptr) {}

unsigned long PathNode::getX() const {
  return x_;
}
unsigned long PathNode::getY() const {
  return y_;
}
std::shared_ptr<PathNode> PathNode::getPointsTo() const {
  return pointsTo_;
}
std::shared_ptr<PathNode> PathNode::getNext() const {
  return next_;
}
void PathNode::setCoordinate(unsigned long x, unsigned long y) {
  x_ = x, y_ = y;
}
void PathNode::setPointsTo(std::shared_ptr<PathNode> pointsTo) {
  pointsTo_ = std::move(pointsTo);
}
void PathNode::setNext(std::shared_ptr<PathNode> next) {
  next_ = std::move(next);
}
bool PathNode::operator==(std::shared_ptr<PathNode> rhsNode) const {
  return rhsNode->getX() == x_ && rhsNode->getY() == y_;
}

//
// Created by eric on 12/16/18.
//

#include "PathMap.h"
PathMap::PathMap(std::shared_ptr<PathNode> start): vertices_(new PathList(start)){
  //vertices_->add(std::move(start));
}
PathMap::~PathMap() {
  vertices_.reset();
}

std::shared_ptr<PathNode> PathMap::findNearest(std::shared_ptr<PathNode> vertex) const {
  double min_distance = DBL_MAX;
  std::shared_ptr<PathNode> nearestVertex;
  std::shared_ptr<PathNode> curr = vertices_->getTail();
  while(curr != nullptr){
    unsigned long x = vertex->getX() - curr->getX();
    unsigned long y = vertex->getY() - curr->getY();
    double distance = sqrt(x*x + y*y);
    if (min_distance >= distance){
      min_distance = distance;
      nearestVertex = curr;
    }
  }
  return nearestVertex;
}
void PathMap::addVertex(std::shared_ptr<PathNode> newVertex) {
  vertices_->add(newVertex);
}
int PathMap::outputPathFound(unsigned long *x_vertices, unsigned long *y_vertices, const int size) const {
  std::shared_ptr<PathNode> pathVertex = vertices_->getTail();
  int i = 0;
  for (; pathVertex != nullptr && i < size; ++i, pathVertex = pathVertex->getPointsTo()){
    x_vertices[i] = pathVertex->getX();
    y_vertices[i] = pathVertex->getY();
  }
  return i;
}

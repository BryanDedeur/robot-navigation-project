//
// Created by eric on 12/16/18.
//

#ifndef PATHPLANNING_VECTORMAP_H
#define PATHPLANNING_VECTORMAP_H

#include "MapNode.h"
#include <vector>

class VectorMap {
 private:
  std::vector<std::vector<MapNode>> map_;
 public:
  VectorMap();

  MapNode& operator()(unsigned long x, unsigned long y);
  const MapNode& operator()(unsigned long x, unsigned long y) const;
  void updateMap(int direction, float logOddOccupied, float logOddFree, unsigned long x, unsigned long y);
  void setOccupancy(bool occupance, unsigned long x, unsigned long y);
};

#endif //PATHPLANNING_VECTORMAP_H

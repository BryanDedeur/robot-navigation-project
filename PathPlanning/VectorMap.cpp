//
// Created by eric on 12/16/18.
//

#include "VectorMap.h"
#include "iostream"
#include <cmath>

VectorMap::VectorMap(): map_(1000, std::vector<MapNode>(1000)){}
MapNode &VectorMap::operator()(unsigned long x, unsigned long y) {
  try {
    return map_.at(x).at(y);
  } catch (...) {
    return map_.at(0).at(0);
  }
}
const MapNode &VectorMap::operator()(unsigned long x, unsigned long y) const {
  try {
    return map_.at(x).at(y);
  } catch (...) {
    return map_.at(0).at(0);
  }
}
void VectorMap::updateMap(int direction, float logOddOccupied, float logOddFree, unsigned long x, unsigned long y) {
  for (int theta = (direction - 90); theta <= direction + 90; theta += 15) {
    long x_offset_old = 0,
        y_offset_old = 0;
    for (int length = 1; length <= 50; ++length) {
      auto x_offset = static_cast<long>((cos(theta * (M_PI/180)) * length));
      auto y_offset = static_cast<long>((sin(theta * (M_PI/180)) * length));
      if (x_offset == x_offset_old && y_offset == y_offset_old)
        continue;
      x_offset_old = x_offset;
      y_offset_old = y_offset;
      long x_new = x + x_offset;
      long y_new = y + y_offset;
      if (x_new < 0 || y_new < 0) // if out of map range
        break;
      if ((*this)(static_cast<unsigned long>(x_new), static_cast<unsigned long>(y_new)).getOccupancy()) {
        (*this)(static_cast<unsigned long>(x_new),
                static_cast<unsigned long>(y_new)).updateLogOddMean(logOddOccupied);
        break;
      }
      (*this)(static_cast<unsigned long>(x_new), static_cast<unsigned long>(y_new)).updateLogOddMean(logOddFree);
    }
  }
}
void VectorMap::setOccupancy(bool occupance, unsigned long x, unsigned long y) {
  try {
    (*this)(x, y).setOccupancy(occupance);
  } catch (...) {
    std::cout << "this point is out of range (" << x << ", " << y << ")." << std::endl;
  }
}
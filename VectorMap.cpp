#include "VectorMap.h"
#include <cmath>

VectorMap::VectorMap(): map_(1000, std::vector<MapNode>(1000)){}

MapNode &VectorMap::operator()(unsigned long x, unsigned long y) {
    return map_.at(x).at(y);
}

const MapNode &VectorMap::operator()(unsigned long x, unsigned long y) const {
    return map_.at(x).at(y);
}

void VectorMap::updateMap(int direction, float logOddOccupied, float logOddFree, unsigned long x, unsigned long y) {
    for (int theta = (direction - 90); theta <= direction + 90; theta += 15){
        for (int length = 1; length <= 50; ++length){
            auto x_offset = static_cast<long>((cos(theta * (M_PI/180)) * length));
            auto y_offset = static_cast<long>((sin(theta * (M_PI/180)) * length));
            long x_new = x + x_offset;
            long y_new = y + y_offset;
            if (x_new < 0 || y_new < 0) // if out of map range
              break;
            if ((*this)(x_new, y_new).getOccupancy()) {
                (*this)(x_new, y_new).updateLogOddMean(logOddOccupied);
                break;
            }
            (*this)(x_new, y_new).updateLogOddMean(-logOddFree);
        }
    }
}

void VectorMap::setOccupancy(bool occupance, unsigned long x, unsigned long y) {
    (*this)(x, y).setOccupancy(occupance);
}

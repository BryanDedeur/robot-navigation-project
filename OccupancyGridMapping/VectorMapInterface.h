#ifndef BONUSPROJECT_VECTORMAPINTERFACE_H
#define BONUSPROJECT_VECTORMAPINTERFACE_H

#include "MapNode.h"

class VectorMapInterface{
public:
    virtual MapNode& operator()(unsigned long x, unsigned long y) = 0;
    virtual const MapNode& operator()(unsigned long x, unsigned long y) const = 0;
    virtual void updateMap(int direction, float logOddOccupied, float logOddFree, unsigned long x, unsigned long y) = 0;
    virtual void setOccupancy(bool occupance, unsigned long x, unsigned long y) = 0;
};

#endif //BONUSPROJECT_VECTORMAPINTERFACE_H

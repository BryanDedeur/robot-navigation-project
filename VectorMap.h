#ifndef BONUSPROJECT_VECTORMAP_H
#define BONUSPROJECT_VECTORMAP_H

#include "MapNode.h"
#include "VectorMapInterface.h"
#include <vector>

class VectorMap : public VectorMapInterface {
private:
    std::vector<std::vector<MapNode>> map_;
public:
    VectorMap();

    MapNode& operator()(unsigned long x, unsigned long y) override;
    const MapNode& operator()(unsigned long x, unsigned long y) const override;
    void updateMap(int direction, float logOddOccupied, float logOddFree, unsigned long x, unsigned long y) override;
    void setOccupancy(bool occupance, unsigned long x, unsigned long y) override;
};


#endif //BONUSPROJECT_VECTORMAP_H

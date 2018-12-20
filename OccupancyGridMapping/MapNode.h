#ifndef BONUSPROJECT_MAPNODE_H
#define BONUSPROJECT_MAPNODE_H

#include "MapNodeInterface.h"


class MapNode : public MapNodeInterface {
private:
    bool occupied_;
    float logOddMean_;
public:
    MapNode();
    explicit MapNode(bool occupance, float logOddMean = 0.f);

    bool getOccupancy() override;
    void setOccupancy(bool occupance) override;
    float getLogOddMean() override;
    void setLogOddMean(float newLogOddMean) override;
    void updateLogOddMean(float logOddMean) override;
};


#endif //BONUSPROJECT_MAPNODE_H

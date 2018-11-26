//
// Created by eric on 11/25/18.
//

#ifndef BONUSPROJECT_MAPNODEINTERFACE_H
#define BONUSPROJECT_MAPNODEINTERFACE_H

class MapNodeInterface {
public:
    virtual bool getOccupancy() = 0;
    virtual void setOccupancy(bool occupance) = 0;
    virtual float getLogOddMean() = 0;
    virtual void setLogOddMean(float newLogOddMean) = 0;
    virtual void updateLogOddMean(float logOddMean) = 0;
};

#endif //BONUSPROJECT_MAPNODEINTERFACE_H

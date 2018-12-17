//
// Created by eric on 12/16/18.
//

#ifndef PATHPLANNING_MAPNODE_H
#define PATHPLANNING_MAPNODE_H

class MapNode {
 private:
  bool occupied_;
  float logOddMean_;
 public:
  MapNode();
  explicit MapNode(bool occupance, float logOddMean = 0.f);

  bool getOccupancy();
  void setOccupancy(bool occupance);
  float getLogOddMean();
  void setLogOddMean(float newLogOddMean);
  void updateLogOddMean(float logOddMean);
};

#endif //PATHPLANNING_MAPNODE_H

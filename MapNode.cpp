#include "MapNode.h"

MapNode::MapNode(): occupied_(false), logOddMean_(0.f){}

MapNode::MapNode(bool occupance, float logOddMean): occupied_(occupance), logOddMean_(logOddMean){}

bool MapNode::getOccupancy() {
    return occupied_;
}

void MapNode::setOccupancy(bool occupance) {
    occupied_ = occupance;
}

float MapNode::getLogOddMean() {
    return logOddMean_;
}

void MapNode::setLogOddMean(float newLogOddMean) {
    logOddMean_ = newLogOddMean;
}

void MapNode::updateLogOddMean(float logOddMean) {
    logOddMean_ += logOddMean;
}
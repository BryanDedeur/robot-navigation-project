//
// Created by eric on 12/16/18.
//

#ifndef PATHPLANNING_PATHNODE_H
#define PATHPLANNING_PATHNODE_H

#include <memory>

class PathNode {
 private:
  unsigned long x_,
                y_;
  std::shared_ptr<PathNode> pointsTo_,
                            next_;
 public:
  PathNode();
  PathNode(unsigned long x, unsigned long y);

  unsigned long getX() const;
  unsigned long getY() const;
  std::shared_ptr<PathNode> getPointsTo() const;
  std::shared_ptr<PathNode> getNext() const;

  void setCoordinate(unsigned long x, unsigned long y);
  void setPointsTo(std::shared_ptr<PathNode> pointsTo);
  void setNext(std::shared_ptr<PathNode> next);

  bool operator==(std::shared_ptr<PathNode> rhsNode) const;
};

#endif //PATHPLANNING_PATHNODE_H

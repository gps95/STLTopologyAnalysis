#ifndef FACET
#define FACET

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include "coord3d.h"

class Facet
{//For each STL Facet
private:
  Coord3d uv, p1, p2, p3;
  bool active;
public:
  //constructors
  Facet();
  Facet(const Coord3d & uv,const Coord3d & p1,const Coord3d & p2,const Coord3d & p3);
  //get the 3d planar equation
  double get3dPLane();
  //get points
  Coord3d getPoint(int pointno);
  //gets unit vector
  Coord3d getUV();
  //operators
  bool operator==(Facet & other);
  //hash function to insert into map
  struct hashFunction
  {
    size_t operator()(const Facet *p) const;
  };
  // dot product of unit vectors
  double dot(Facet other);
  //normalize unit vector
  void norm(double len=1.0);
  //active flag for bfs
  const bool isActive();
  //active flag for bfs
  void setActive(bool b);
  //toString
  std::string toString();
};
#endif
#ifndef COORD3D
#define COORD3D

#include <cmath>

class Coord3d
{//For 3d Points and vectors
private:
  double x, y, z;
public:
  //constructors
  Coord3d();
  Coord3d(double x,double y,double z);
  //constructor copy
  Coord3d(const Coord3d& p);
  //operator overloading
  bool operator==(const Coord3d& other) const;
  Coord3d operator+(const Coord3d &other);
  Coord3d operator-(const Coord3d& other);
  //getters
  double getX();
  double getY();
  double getZ();
  //dot product
  double dot(Coord3d &other);
  //cross product
  Coord3d cross(Coord3d &other);
  //length
  double len();
  //normalize vector to a length
  void norm(double len=1.0);
  //hash function to insert into map
  struct hashFunction
  {
    size_t operator()(const Coord3d& p) const;
  };
};
#endif
#ifndef COORD3D
#define COORD3D

#include "mytypes.h"

class Coord3d
{//For 3d Points and vectors
private:
  ld x, y, z;
public:
  //constructors
  Coord3d()
  {
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
  }

  Coord3d(ld x, ld y, ld z)
  {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  Coord3d(const Coord3d& p)
  {
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
  }

  //operators
  bool operator==(const Coord3d& other) const
  {
    return abs(this->x - other.x) < EPSILON && abs(this->y - other.y) < EPSILON && abs(this->z - other.z) < EPSILON;
  }

  Coord3d operator+(const Coord3d &other)
  {
    return Coord3d(this->x+other.x,this->y+other.y,this->z+other.z);
  }

  Coord3d operator-(const Coord3d& other){
    return Coord3d(this->x-other.x,this->y-other.y,this->z-other.z);
  }

  //getters
  ld getX() { return this->x; }
  ld getY() { return this->y; }
  ld getZ() { return this->z; }

  //dot product
  ld dot(Coord3d &other)
  {
    return this->x*other.x +this->y*other.y +this->z*other.z;
  }

  //cross product
  Coord3d cross(Coord3d &other)
  {
    return Coord3d((this->y*other.z)-(this->z*other.y),(this->z*other.x)-(this->x*other.z),(this->x*other.y)-(this->y*other.x));
  }

  //length
  ld len()
  {
    return sqrtl((this->x*this->x)+(this->y*this->y)+(this->z*this->z));
  }

  //normalize vector to a length
  void norm(ld len=1.0)
  {
    if(len==0)
      return ;
    ld length=this->len();
    this->x=((this->x/length)*len);
    this->y=((this->y/length)*len);
    this->z=((this->z/length)*len);
  }

  //hash function to insert into map
  struct hashFunction
  {
    size_t operator()(const Coord3d& p) const
    {
      size_t p1=73856093,p2=33715219,p3=83492791;
      size_t h1 = std::hash<ld>()(p1*p.x);
      size_t h2 = std::hash<ld>()(p2*p.y);
      size_t h3 = std::hash<ld>()(p3*p.z);
      return h1^h2^h3;
    }
  };
};
#endif
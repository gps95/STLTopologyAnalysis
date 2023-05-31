#include "coord3d.h"

//constructors
Coord3d::Coord3d()
{
  this->x=0.0;
  this->y=0.0;
  this->z=0.0;
}

Coord3d::Coord3d(double x,double y,double z)
{
  this->x=x;
  this->y=y;
  this->z=z;
}

Coord3d::Coord3d(const Coord3d &p)
{
  this->x=p.x;
  this->y=p.y;
  this->z=p.z;
}

//operator overloading
bool Coord3d::operator==(const Coord3d &other) const
{
  const double EPSILON=5.0e-4;
  return abs(this->x-other.x)<EPSILON&&abs(this->y-other.y)<EPSILON&&abs(this->z-other.z)<EPSILON;
}

Coord3d Coord3d::operator+(const Coord3d &other)
{
  return Coord3d(this->x+other.x,this->y+other.y,this->z+other.z);
}

Coord3d Coord3d::operator-(const Coord3d &other)
{
  return Coord3d(this->x-other.x,this->y-other.y,this->z-other.z);
}

//getters
double Coord3d::getX()
{
  return this->x;
}

double Coord3d::getY()
{
  return this->y;
}

double Coord3d::getZ()
{
  return this->z;
}

//dot product
double Coord3d::dot(Coord3d &other)
{
  return this->x*other.x+this->y*other.y+this->z*other.z;
}

//cross product
Coord3d Coord3d::cross(Coord3d &other)
{
  return Coord3d((this->y*other.z)-(this->z*other.y),(this->z*other.x)-(this->x*other.z),(this->x*other.y)-(this->y*other.x));
}

//length
double Coord3d::len()
{
  return sqrtl((this->x*this->x)+(this->y*this->y)+(this->z*this->z));
}

//normalize vector to a length
void Coord3d::norm(double len)
{
  if(len==0)
    return;
  double length=this->len();
  this->x=((this->x/length)*len);
  this->y=((this->y/length)*len);
  this->z=((this->z/length)*len);
}

//hash function to insert into map
size_t Coord3d::hashFunction::operator()(const Coord3d &p) const
{
  size_t p1=73856093,p2=33715219,p3=83492791;
  size_t h1=std::hash<double>()(p1*p.x);
  size_t h2=std::hash<double>()(p2*p.y);
  size_t h3=std::hash<double>()(p3*p.z);
  return h1^h2^h3;
}
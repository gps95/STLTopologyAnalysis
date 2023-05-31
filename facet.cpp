#include "facet.h"

//constructors
Facet::Facet()
{
  this->uv=Coord3d();
  this->p1=Coord3d();
  this->p2=Coord3d();
  this->p3=Coord3d();
  this->active=true;
}

Facet::Facet(const Coord3d &uv,const Coord3d &p1,const Coord3d &p2,const Coord3d &p3)
{
  this->uv=Coord3d(uv);
  this->p1=Coord3d(p1);
  this->p2=Coord3d(p2);
  this->p3=Coord3d(p3);
  this->active=true;
}

//get the 3d planar equation
double Facet::get3dPLane()
{
  return (this->uv.getX()*this->p1.getX())+(this->uv.getY()*this->p1.getY())+(this->uv.getZ()*this->p1.getZ());
}

//get points
Coord3d Facet::getPoint(int pointno)
{
  if(pointno==0) return this->p1;
  if(pointno==1) return this->p2;
  return this->p3;
}

//gets unit vector
Coord3d Facet::getUV()
{
  return this->uv;
}

//operators
bool Facet::operator==(Facet &other)
{
  int eq=0;
  if(this->p1==other.p1||this->p1==other.p2||this->p1==other.p3)eq++;
  if(this->p2==other.p1||this->p2==other.p2||this->p2==other.p3)eq++;
  if(this->p3==other.p1||this->p3==other.p2||this->p3==other.p3)eq++;
  return eq==3;
}

//hash function to insert into map
size_t Facet::hashFunction::operator()(const Facet *p) const
{
  return Coord3d::hashFunction()(p->p1)^Coord3d::hashFunction()(p->p2)^Coord3d::hashFunction()(p->p3);
}

// dot product of unit vectors
double Facet::dot(Facet other)
{
  return this->uv.dot(other.uv);
}

//normalize unit vector
void Facet::norm(double len)
{
  this->uv.norm(len);
}

//active flag for bfs
const bool Facet::isActive()
{
  return this->active;
}

//active flag for bfs
void Facet::setActive(bool b)
{
  this->active=b;
}

//toString
std::string Facet::toString()
{
  const std::string TAB="   ";
  std::stringstream stream;
  stream<<TAB<<"facet normal "<<
    std::to_string(uv.getX())<<" "<<std::to_string(uv.getY())<<" "<<std::to_string(uv.getZ())<<"\n"<<
    TAB<<TAB<<"outer loop\n"<<
    TAB<<TAB<<TAB<<"vertex "<<std::to_string(p1.getX())<<" "<<std::to_string(p1.getY())<<" "<<std::to_string(p1.getZ())<<"\n"<<
    TAB<<TAB<<TAB<<"vertex "<<std::to_string(p2.getX())<<" "<<std::to_string(p2.getY())<<" "<<std::to_string(p2.getZ())<<"\n"<<
    TAB<<TAB<<TAB<<"vertex "<<std::to_string(p3.getX())<<" "<<std::to_string(p3.getY())<<" "<<std::to_string(p3.getZ())<<"\n"<<
    TAB<<TAB<<"endloop\n"<<TAB<<"endfacet";
  return stream.str();
}
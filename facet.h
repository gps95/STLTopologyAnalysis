#ifndef FACET
#define FACET

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

#include "mytypes.h"
#include "coord3d.h"

class Facet
{//For each STL Facet
private:
  Coord3d uv, p1, p2, p3;
  bool active;
public:
  //constructors
  Facet()
  {
    this->uv=Coord3d();
    this->p1=Coord3d();
    this->p2=Coord3d();
    this->p3=Coord3d();
    this->active=true;
  }

  Facet(const Coord3d & uv,const Coord3d & p1,const Coord3d & p2,const Coord3d & p3)
  {
    this->uv=Coord3d(uv);
    this->p1=Coord3d(p1);
    this->p2=Coord3d(p2);
    this->p3=Coord3d(p3);
    this->active=true;
  }
  
  //get the 3d planar equation
  double get3dPLane()
  {
    return (this->uv.getX()*this->p1.getX())+(this->uv.getY()*this->p1.getY())+(this->uv.getZ()*this->p1.getZ());
  }

  //get points
  Coord3d getPoint(int pointno)
  {
    if(pointno==0) return this->p1;
    if(pointno==1) return this->p2;
    return this->p3;
  }

  //gets unit vector
  Coord3d getUV()
  {
    return this->uv;
  }

  //operators
  bool operator==(Facet & other)
  {
    int eq=0;
    if(this->p1==other.p1 || this->p1==other.p2 || this->p1==other.p3)eq++;
    if(this->p2==other.p1 || this->p2==other.p2 || this->p2==other.p3)eq++;
    if(this->p3==other.p1 || this->p3==other.p2 || this->p3==other.p3)eq++;
    return eq==3;
  }

  //hash function to insert into map
  struct hashFunction
  {
    size_t operator()(const Facet *p) const
    {
      return Coord3d::hashFunction()(p->p1)^Coord3d::hashFunction()(p->p2)^Coord3d::hashFunction()(p->p3);
    }
  };

  // dot product of unit vectors
  ld dot(Facet other)
  {
    return this->uv.dot(other.uv);
  }

  //normalize unit vector
  void norm(ld len=1.0)
  {
    this->uv.norm(len);
  }

  //active flag for bfs
  const bool isActive()
  {
    return this->active;
  }

  //active flag for bfs
  void setActive(bool b)
  {
    this->active=b;
  }
  
  //toString
  std::string toString(){
    const std::string TAB="   ";
    std::stringstream stream;
    stream <<TAB<<"facet normal "<<
    std::to_string(uv.getX())<<" "<< std::to_string(uv.getY())<< " " << std::to_string(uv.getZ())<<"\n"<<
    TAB<<TAB<<"outer loop\n"<<
    TAB<<TAB<<TAB<<"vertex "<<std::to_string(p1.getX())<<" "<<std::to_string(p1.getY())<<" "<<std::to_string(p1.getZ())<<"\n"<<
    TAB<<TAB<<TAB<<"vertex "<<std::to_string(p2.getX())<<" "<<std::to_string(p2.getY())<<" "<<std::to_string(p2.getZ())<<"\n"<<
    TAB<<TAB<<TAB<<"vertex "<<std::to_string(p3.getX())<<" "<<std::to_string(p3.getY())<<" "<<std::to_string(p3.getZ())<<"\n"<<
    TAB<<TAB<<"endloop\n"<<TAB<<"endfacet";
    return stream.str();
  }
};
#endif
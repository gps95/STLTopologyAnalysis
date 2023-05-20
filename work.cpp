#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <cmath>
#include <format>

#include "mytypes.h"
#include "coord3d.h"
#include "facet.h"

// settings//TODO: have a config file
const long double ANGLELIMIT=0.2;
const bool INHIBANGLELIMIT=false;
const bool DEBUG=true;
std::string OUTPUTPATH= "D:\\VSPROJECTS\\MyProjects\\STLSeparator\\OUTPUT\\";

//reads file and populates Facet vector
void readFile(std::ifstream &in,std::vector<Facet> &fvec){
  std::string s;
  std::getline(in,s);//ignore first line: solid name ...
  while(in >> s){
    //read facet and normal vector
    // s is "facet" or "endsolid"
    if(s=="endsolid")return;
    ld x,y,z;
    in >> s >> x >> y >> z;// normal + coordinates
    Coord3d uv(x,y,z);
    //read 3 vertex + coordinates:
    in >> s >> s;//reads "outer loop"
    in >> s >> x >> y >> z;
    Coord3d p1(x,y,z);
    in >> s >> x >> y >> z;
    Coord3d p2(x,y,z);
    in >> s >> x >> y >> z;
    Coord3d p3(x,y,z);
    //calculate uv again just in case
    Coord3d p1p2 = p2-p1;//vector from p1 to p2
    Coord3d p1p3 = p3-p1;//vector from p1 to p3
    Coord3d uv2(p1p2.cross(p1p3));
    uv2.norm();
    //debug info
    if(DEBUG && uv!=uv2)
      std::cout << "Bad unit vector detected\n";
    //create Facet
    Facet f(uv2,p1,p2,p3);
    in >> s >> s;//reads "endloop" and "endfacet"
    //add to Facet vector
    fvec.push_back(f);
  }
}

//writes the STL files according to topology
void writeSTL(std::unordered_set<Facet *,Facet::hashFunction> &v,int &partno,std::string &basename,std::string sufix)
{
  //debug info
  if(DEBUG)
    std::cout<<std::format("-------------------------------WRITING FILE {}\n",partno);
  //open file
  std::ofstream out(basename+sufix+std::to_string(partno++)+".stl");
  //write Facets
  out << "solid FacetAssembly\n";
  for(Facet *f : v)
    out<<f->toString()<<"\n";
  out << "endsolid\n";
  //Close
  out.close();
}

//normal bfs
void bfs(int pos,std::unordered_set<Facet*,Facet::hashFunction> &ret,std::vector<Facet> &facets,std::unordered_map<Coord3d,std::vector<Facet*>,Coord3d::hashFunction> &vmap){
  //initialize
  std::queue<Facet*> q;
  q.push(&facets[pos]);
  facets[pos].setActive(false);
  ret.insert(&facets[pos]);
  //bfs
  while(!q.empty())
  {
    Facet *f=q.front();q.pop();
    for(int i=0;i<2;++i)
    {//for each point
      for(auto aux:vmap[f->getPoint(i)])
      {//get list of Facets that have the point as its vertex
        if(!aux->isActive())
          continue;
        {//calculate angle and check with ANGLELIMIT
          f->norm();
          aux->norm();
          ld angle = abs(f->dot(*aux));
          if(INHIBANGLELIMIT || angle>=ANGLELIMIT)
          {
            aux->setActive(false);
            if(!ret.contains(aux))
              ret.insert(aux);
            q.push(aux);
          }
        }
      }
    }
  }
  //debug info
  if(DEBUG)
    std::cout<<ret.begin()._Ptr->_Myval->toString()<<"\n"<<Coord3d::hashFunction()(ret.begin()._Ptr->_Myval->getUV())<<"\n";
}

//Performs the topology analysis
void runAnalysis(std::vector<Facet> &roundT,std::string &name)
{
  int partno=0;
  std::unordered_map<Coord3d,std::vector<Facet *>,Coord3d::hashFunction> vmap;
  //populate vmap
  for(Facet &f:roundT)
  {
    for(int i=0;i<=2;++i)
    {
      vmap[f.getPoint(i)].push_back(&f);
    }
  }
  //bfs
  for(int i=0;i<roundT.size();++i)
  {
    if(roundT[i].isActive())
    {
      std::unordered_set<Facet*,Facet::hashFunction> fvec;
      bfs(i,fvec,roundT,vmap);
      if(fvec.size()==0)
        continue;
      writeSTL(fvec,partno,name,"feature");
    }
  }
}

int main(int argc, char **argv){
    std::ifstream in(argv[1]);
    std::string name=argv[2];
    name=name.substr(0,name.size()-4);//erase .stl from name
    name=OUTPUTPATH+name;//add path
    //TODO check if opened,file is correct,etc...
    //read file and populate facet vector
    std::vector<Facet> fvec;
    readFile(in,fvec);
    //debug info: print all Facet hashes
    int mapentry = 0;
    if(DEBUG)
      for(auto &facet:fvec)
        std::cout<<std::format("{}:HashKey:{}\n",mapentry++,Coord3d::hashFunction()(facet.getUV()));
    //run the analysis
    runAnalysis(fvec,name);
    return 0;
}
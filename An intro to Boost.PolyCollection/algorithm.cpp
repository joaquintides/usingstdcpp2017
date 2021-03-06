/* usingstdcpp2017: microintro to Boost.PolyCollection algorithms.
 *
 * Copyright 2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/poly_collection/algorithm.hpp>
#include <boost/poly_collection/base_collection.hpp>
#include <iostream>
#include <memory>
#include <random>
#include <string>

struct sprite
{
  sprite(int id):id(id){}
  virtual ~sprite()=default;
  virtual void render(std::ostream& os)const=0;

  int id;
};

struct warrior:sprite
{
  using sprite::sprite;
  warrior(std::string rank,int id):sprite{id},rank{std::move(rank)}{}

  void render(std::ostream& os)const override{os<<rank<<" "<<id;}

  std::string rank="warrior";
};

struct juggernaut:warrior
{
  juggernaut(int id):warrior{"juggernaut",id}{}
};

struct goblin:sprite
{
  using sprite::sprite;
  void render(std::ostream& os)const override{os<<"goblin "<<id;}
};

int main()
{
  boost::base_collection<sprite> c;

  std::mt19937                 gen{92748}; // some arbitrary random seed
  std::discrete_distribution<> rnd{{1,1,1}};
  for(int i=0;i<8;++i){        // assign each type with 1/3 probability
    switch(rnd(gen)){
      case 0: c.insert(warrior{i});break;
      case 1: c.insert(juggernaut{i});break;
      case 2: c.insert(goblin{i});break;
    }
  }

  {
    // classical version
    const char* comma="";
    for(const sprite& s:c){
      std::cout<<comma;
      s.render(std::cout);
      comma=",";
    }
    std::cout<<"\n";
  }
  {
    // double loop
    const char* comma="";
    for(const auto& seg_info:c.segment_traversal()){
      for(const sprite& s:seg_info){
        std::cout<<comma;
        s.render(std::cout);
        comma=",";
      }
    }
    std::cout<<"\n";
  }
  {
    // dedicated for_each
    const char* comma="";
    boost::poly_collection::for_each(
      c.begin(),c.end(),[&](const sprite& s){
        std::cout<<comma;
        s.render(std::cout);
        comma=",";
      }
    );
    std::cout<<"\n";
  }
  {
    // with type restitution
    const char* comma="";
    boost::poly_collection::for_each<warrior,juggernaut,goblin>(
      c.begin(),c.end(),[&](const auto& s){
        std::cout<<comma;
        s.render(std::cout);
        comma=",";
      }
    );
    std::cout<<"\n";
  }
}

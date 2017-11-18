/* usingstdcpp2017: populate and traverse a boost::any_collection.
 *
 * Copyright 2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/format.hpp>
#include <boost/poly_collection/any_collection.hpp>
#include <boost/type_erasure/operators.hpp>
#include <iostream>
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

std::ostream& operator<<(std::ostream& os,const sprite& s)
{
  s.render(os);
  return os;
}

int main()
{
  boost::any_collection<boost::type_erasure::ostreamable<>> c;

  std::mt19937                 gen{92748}; // some arbitrary random seed
  std::discrete_distribution<> rnd{{1,1,1,1,1}};
  for(int i=0;i<12;++i){       // assign each type with 1/5 probability
    switch(rnd(gen)){
      case 0: c.insert(warrior{i});break;
      case 1: c.insert(juggernaut{i});break;
      case 2: c.insert(goblin{i});break;
      case 3: c.insert(boost::format{"message %1%"}%i);break;
      case 4: c.insert(i);break;
    }
  }

  const char* comma="";
  for(const auto& x:c){
    std::cout<<comma<<x;
    comma=",";
  }
  std::cout<<"\n";
}

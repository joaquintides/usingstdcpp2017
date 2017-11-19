/* usingstdcpp2017: boost::base_collection interface at a glance.
 *
 * Copyright 2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <algorithm>
#include <array>
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

struct elf:sprite
{
  using sprite::sprite;
  void render(std::ostream& os)const override{os<<"elf "<<id;}
};

struct ghoul:sprite
{
  using sprite::sprite;
  void render(std::ostream& os)const override{os<<"ghoul "<<id;}
};

struct amazon:warrior
{
  amazon(int id):warrior{"amazon",id}{}
};

int main()
{
  boost::base_collection<sprite> c;

  auto print=[&](){
    const char* comma="";
    for(const sprite& s:c){
      std::cout<<comma;
      s.render(std::cout);
      comma=",";
    }
    std::cout<<"\n";
  };  

  std::mt19937                 gen{92748}; // some arbitrary random seed
  std::discrete_distribution<> rnd{{1,1,1}};
  for(int i=0;i<8;++i){        // assign each type with 1/3 probability
    switch(rnd(gen)){
      case 0: c.insert(warrior{i});break;
      case 1: c.insert(juggernaut{i});break;
      case 2: c.insert(goblin{i});break;
    }
  }

  // Segments can be targeted individually

  std::sort( // sort warriors in descending id order
    c.begin<warrior>(),c.end<warrior>(),
    [](const warrior& x,const warrior& y){return x.id>y.id;});

  for(const warrior& w:c.segment<warrior>()) // print warrior ids
    std::cout<<w.id<<"\n";

  c.erase(c.begin(typeid(warrior))); // erase first warrior

  c.clear<warrior>(); // erase all warriors

  print();

  // Insertion interface mimics std::multi_set rather than std::vector

  c.insert(juggernaut{8}); // at the end of juggernaut segment

  c.insert(c.begin(),juggernaut{9}); // hint only useful if
                                     // juggernauts are the first segment
  c.insert(c.begin<juggernaut>(),juggernaut{10}); // 1st of juggernauts

  print();

  // Emplacement requires that type of element be specified

  c.emplace<goblin>(11);

  c.emplace_pos<goblin>(c.begin<goblin>(),12); // 1st of goblins

  print();

  // New segments are created automagically; otherwise, use register_types

  // new assortment of sprites
  std::array<std::unique_ptr<sprite>,3> a{{
    std::make_unique<elf>(13),
    std::make_unique<ghoul>(14),
    std::make_unique<amazon>(15)
  }};

  c.register_types<elf,ghoul,amazon>(); // otherwise exception is thrown below

  for(const auto&p:a)c.insert(*p);

  print();
}

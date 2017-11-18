/* usingstdcpp2017: populate and render a vector of OOP entities.
 *
 * Copyright 2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <iostream>
#include <memory>
#include <random>
#include <vector>
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
  std::vector<std::unique_ptr<sprite>> c;

  std::mt19937                 gen{92748}; // some arbitrary random seed
  std::discrete_distribution<> rnd{{1,1,1}};
  for(int i=0;i<8;++i){        // assign each type with 1/3 probability
    switch(rnd(gen)){
      // watch out: std::make_unique requires C++14
      case 0: c.push_back(std::make_unique<warrior>(i));break;
      case 1: c.push_back(std::make_unique<juggernaut>(i));break;
      case 2: c.push_back(std::make_unique<goblin>(i));break;
    }
  }

  const char* comma="";
  for(const auto& p:c){
    std::cout<<comma;
    p->render(std::cout);
    comma=",";
  }
  std::cout<<"\n";
}

/* usingstdcpp2017: populate and traverse a boost::function_collection.
 *
 * Copyright 2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#include <boost/poly_collection/function_collection.hpp>
#include <iostream>
#include <random>

int foo(int x){return x;}

struct bar
{
  int operator()(int x)const{return 2*x;}
};

int main()
{
  boost::function_collection<int(int)> c;

  std::mt19937                 gen{92748}; // some arbitrary random seed
  std::discrete_distribution<> rnd{{1,1,1}};
  for(int i=0;i<8;++i){        // assign each type with 1/3 probability
    switch(rnd(gen)){
      case 0: c.insert(&foo);break;
      case 1: c.insert(bar{});break;
      case 2: c.insert([](int x){return 3*x;});break;
    }
  }

  int res=0;
  for(const auto& f:c)res+=f(1);
  std::cout<<res<<"\n";
}

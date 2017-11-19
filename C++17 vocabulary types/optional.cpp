/* usingstdcpp2017: microexample of std::optional.
 *
 * Copyright 2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */
 
#include <iostream>
#include <optional>

struct name
{
  std::string                given;
  std::optional<std::string> middle;
  std::string                family;
};

void print(const name& n)
{
  std::cout<<n.given<<" ";
  if(n.middle)std::cout<<n.middle.value()<<" ";
  std::cout<<n.family<<"\n";
}

int main()
{
  print(name{"John","Fitzgerald","Kennedy"});
  print(name{"Bob",{},"Laszlo"});
}

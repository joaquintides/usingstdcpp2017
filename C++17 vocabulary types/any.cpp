/* usingstdcpp2017: microexample of std::any.
 *
 * Copyright 2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */
 
#include <any>
#include <iostream>

void print(const std::any& x)
{
  if(x.type()==typeid(int))
    std::cout<<std::any_cast<int>(x)<<"\n";
  else if(x.type()==typeid(std::string))
    std::cout<<std::any_cast<const std::string>(x)<<"\n";
  else
    std::cout<<"[unknown]"<<"\n";  
}

int main()
{
  print(std::make_any<int>(10)); // prints "10"
  print(std::make_any<std::string>("Hello")); // prints "Hello"
  print(std::make_any<double>(3.14159265));  // prints "[unknown]"
}

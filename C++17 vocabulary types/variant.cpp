/* usingstdcpp2017: microexample of std::variant.
 *
 * Copyright 2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */
 
#include <iostream>
#include <variant>

int main()
{
  using namespace std::string_literals; // for the s literal suffix
  using my_type=std::variant<int,std::string,double>;
  
  auto printer=[](const auto& x){std::cout<<x<<"\n";};
  
  my_type v{10};
  std::visit(printer,v);
  v="Hello"s;
  std::visit(printer,v);
  v=3.14159265;
  std::visit(printer,v);
}

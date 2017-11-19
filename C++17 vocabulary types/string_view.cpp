/* usingstdcpp2017: microexample of std::string_view.
 *
 * Copyright 2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */
 
#include <cstring>
#include <iostream>
#include <string>
#include <string_view>

std::string_view find(const char* what,const std::string& where)
{
  auto s=std::strlen(what);
  auto n=where.find(what,s);
  if(n!=std::string::npos)return {where.data()+n,s};
  else return {};
}

int main()
{
  std::string str{"John feeds the beautiful cat in the kitchen"};
  auto strv=find("feeds",str);
  std::cout<<strv<<"\n"; // print "feeds"
  str[8]='l';
  std::cout<<strv<<"\n"; // print "feels"
}

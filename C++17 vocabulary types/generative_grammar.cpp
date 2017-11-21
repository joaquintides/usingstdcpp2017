/* usingstdcpp2017: some generative grammar with C++17 vocabulary types.
 *
 * Copyright 2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */
 
#include <array>
#include <iostream>
#include <optional>
#include <random>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>

void print(const std::string& str){std::cout<<str<<" ";}

template<typename T>
void print(const std::optional<T>& o){if(o)print(o.value());}

template<typename... Ts>
void print(const std::variant<Ts...>& v)
{std::visit([](const auto& x){print(x);},v);}

template<typename... Ts>
void print(const std::tuple<Ts...>& t)
{std::apply([](const auto&... x){int l[]={0,(print(x),0)...};(void)l;},t);}

struct proper_noun:std::string{using std::string::string;};
struct article:std::string{using std::string::string;};
struct adjective:std::string{using std::string::string;};
struct common_noun:std::string{using std::string::string;};
using  common_noun_phrase=std::tuple<
  article,
  std::optional<adjective>,
  common_noun
>;
using  noun_phrase=std::variant<proper_noun,common_noun_phrase>;
struct verb:std::string{using std::string::string;};
struct preposition:std::string{using std::string::string;};
using  prepositional_phrase=std::tuple<preposition,noun_phrase>;
using  sentence=std::tuple<
  noun_phrase,
  verb,
  noun_phrase,
  std::optional<prepositional_phrase>
>;

// For the random generation example we refine sentence to
// distinguish common from  place names.

struct place_noun:std::string{using std::string::string;};
using  place_noun_phrase=std::tuple<
  article,
  std::optional<adjective>,
  place_noun
>;
using  place_phrase=std::tuple<preposition,place_noun_phrase>;
using  sentence2=std::tuple<
  noun_phrase,
  verb,
  noun_phrase,
  std::optional<place_phrase>
>;

template<typename T,std::size_t N,typename URBG>
T get_from(const std::array<T,N>& a,URBG&& gen)
{
  std::uniform_int_distribution<> rnd(0,a.size()-1);
  return a[rnd(gen)];
}

template<typename URBG>
auto get(std::in_place_type_t<proper_noun>,URBG&& gen)
{
  static const std::array<proper_noun,3> a={{"John","Mary","Bob"}};
  return get_from(a,std::forward<URBG>(gen));
}

template<typename URBG>
auto get(std::in_place_type_t<article>,URBG&& gen)
{
  static const std::array<article,2> a={{"the","a"}};
  return get_from(a,std::forward<URBG>(gen));
}

template<typename URBG>
auto get(std::in_place_type_t<adjective>,URBG&& gen)
{
  static const std::array<adjective,3> a={{"beautiful","big","red"}};
  return get_from(a,std::forward<URBG>(gen));
}

template<typename URBG>
auto get(std::in_place_type_t<common_noun>,URBG&& gen)
{
  static const std::array<common_noun,3> a={{"cat","dog","postman"}};
  return get_from(a,std::forward<URBG>(gen));
}

template<typename URBG>
auto get(std::in_place_type_t<verb>,URBG&& gen)
{
  static const std::array<verb,3> a={{"feeds","kisses","meets"}};
  return get_from(a,std::forward<URBG>(gen));
}

template<typename URBG>
auto get(std::in_place_type_t<preposition>,URBG&& gen)
{
  static const std::array<preposition,2> a={{"in","outside"}};
  return get_from(a,std::forward<URBG>(gen));
}

template<typename URBG>
auto get(std::in_place_type_t<place_noun>,URBG&& gen)
{
  static const std::array<place_noun,2> a={{"kitchen","pool"}};
  return get_from(a,std::forward<URBG>(gen));
}

template<typename T,typename URBG>
std::optional<T> get(std::in_place_type_t<std::optional<T>>,URBG&& gen)
{
  std::uniform_int_distribution<> rnd(0,1);
  if(rnd(gen))return get(std::in_place_type<T>,std::forward<URBG>(gen));
  else return {};
}

template<typename Variant,typename URBG,typename T>
Variant variant_get(URBG&& gen)
{
  return get(std::in_place_type<T>,std::forward<URBG>(gen));
}

template<typename... Ts,typename URBG>
std::variant<Ts...> get(
  std::in_place_type_t<std::variant<Ts...>>,URBG&& gen)
{
  using return_type=std::variant<Ts...>;
  using get_function=return_type(*)(URBG&&);
  static const std::array<get_function,sizeof...(Ts)> a={{
    &variant_get<return_type,URBG,Ts>...
  }};
  return get_from(a,std::forward<URBG>(gen))(std::forward<URBG>(gen));
}

template<typename... Ts,typename URBG>
std::tuple<Ts...> get(
  std::in_place_type_t<std::tuple<Ts...>>,URBG&& gen)
{
  return {get(std::in_place_type<Ts>,std::forward<URBG>(gen))...};
}

int main()
{
  print(sentence{
    proper_noun{"John"},
    verb{"feeds"},
    common_noun_phrase{
      article{"the"},adjective{"beautiful"},common_noun{"cat"}
    },
    prepositional_phrase{
      preposition{"in"},
      common_noun_phrase{
        article{"the"},{},common_noun{"kitchen"}
      }
    }
  });
  std::cout<<"\n";
  
  std::mt19937 gen{92748}; // some arbitrary random seed
  for(int i=0;i<10;++i){
    print(get(std::in_place_type<sentence2>,gen));
    std::cout<<"\n";
  }
}

using std::cpp 2017
-------------------

Presentations from Joaquín Mª López Muñoz at [using std::cpp 2017](http://usingstdcpp.org/using-stdcpp-2017/)
and associated material.

* [An intro to Boost.PolyCollection](https://github.com/joaquintides/usingstdcpp2017/raw/master/An%20intro%20to%20Boost.PolyCollection/An%20intro%20to%20Boost.PolyCollection.pdf)
([video](https://www.youtube.com/watch?v=J1oUXDAJ5RM) in Spanish):
[Boost.PolyCollection](http://boost.org/libs/poly_collection) was released as part of Boost 1.65 in
August 2017. This library implements a novel data structure for polymorphic objects that packs elements
of the same concrete type together, which increases performance dramatically. Added speed can be squeezed
out by using dedicated algorithms with *type restitution* capabilities. Dynamic polymorphism in current
C++ goes beyond classic OOP, and Boost.PolyCollection provides containers for three polymorphism models:

  * `boost::base_collection` for OOP
  * `boost::function_collection` for callable entities in the spirit of `std::function`
  * `boost::any_collection` for *duck typing* as implemented by [Boost.TypeErasure](http://boost.org/libs/type_erasure).

* [C++17 vocabulary types](https://github.com/joaquintides/usingstdcpp2017/raw/master/C%2B%2B17%20vocabulary%20types/C%2B%2B17%20vocabulary%20types.pdf)
([video](https://www.youtube.com/watch?v=IFwdbggHbOE) in Spanish):
Vocabulary types are the basic building blocks of any program and also serve as an effective tool for
communicating the program intent when others read the code. C++17 features four new vocabulary types:

  * `std::string_view`
  * `std::any`
  * `std::optional`
  * `std::variant`
 
   We briefly describe these types and use some of them in an example that shows their power when
combined together.

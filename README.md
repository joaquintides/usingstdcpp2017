using std::cpp 2017
-------------------

Presentations from Joaquín Mª López Muñoz at [using std::cpp 2017](http://usingstdcpp.org/using-stdcpp-2017/)
and associated material.

* An intro to Boost.PolyCollection: [Boost.PolyCollection](http://boost.org/libs/poly_collection) was
released as part of Boost 1.65 in August 2017. This library implements a novel data structure for polymorphic
objects that packs elements of the same concrete type together, which increases performance dramatically.
Added speed can be squeezed out by using dedicated algorithms with *type restitution* capabilities.
Dynamic polymorphism in current C++ goes beyond classic OOP, and Boost.PolyCollection provides containers
for three polymorphism models:

  * `boost::base_collection` for OOP
  * `boost::function_collection` for callable entities in the spirit of `std::function`
  * `boost::any_collection` for *duck typing* as implemented by [Boost.TypeErasure](http://boost.org/libs/type_erasure).

* C++17 vocabulary types: *abstract to come.*
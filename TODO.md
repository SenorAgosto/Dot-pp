# TODO

- add support for vertex attributes 
- write unit test coverage for file:line error reporting.
- change behavior of edge attributes to apply the attribute to all the edges in a chain, 
  e.g. a -> b -> c [weight=2], should call: 
    - applyEdgeAttribute("a", "b", "weight", "2")
    - applyEdgeAttribute("b", "c", "weight", "2")
- change parser to allow multiple edge attributes

- Change parse interface from std::istream& to char* and length, use std::string_view instead of std::string in tokens. 


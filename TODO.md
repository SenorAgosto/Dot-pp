# TODO

- add support for keywords:
    - subgraph, node, edge, strict
    - setting compass settings (n | ne | e | se | s | sw | w | nw | c | _)

- write unit test coverage for file:line error reporting.

- Change parse interface from std::istream& to char* and length, use std::string_view instead of std::string in tokens. 

- Eliminate boost::string_view dependency.

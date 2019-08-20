#  graph_algorithm

[![](https://img.shields.io/badge/commitizen-friendly-brightgreen.svg)](http://commitizen.github.io/cz-cli/)

[中文版本（Chinese version）](./README.zh-CN.md)

Graph algorithm implementation, including storage structure, depth/breadth first traversal, minimum spanning tree creation, based on different languages (pyhon/c++).

## Features

The **adjacency matrix** storage structure implementation function (`c++` implementation) is as follows:

1. breadth-first search(BFS)
2. depth-first search(DFS)
3. Prim algorithm
4. Kruskal algorithm

The **adjacency table** storage structure implementation function (`c++` implementation) is as follows:

1. breadth-first search(BFS)
2. depth-first search(DFS)
3. Prim algorithm
4. Kruskal algorithm

## Catalog

```
.
├── cplusplus
│   ├── CMakeLists.txt
│   ├── common_iostream.h                 # common iostream library function
│   ├── graph.h                           # Graph storage structure: adjacency matrix + adjacency table
│   ├── lena.jpg
│   ├── main.cpp                          # Entry file
│   ├── undigraph.cpp                     # class Undigraph's implementation
│   └── undigraph.h                       # class Undigraph's declare
├── LICENSE
└── README.md
```

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags](https://github.com/zjZSTU/graph_algorithm/releases) on this repository.

## Authors

* zhujian - *Initial work* - [zjZSTU](https://github.com/zjZSTU)

## CHANGELOG

see the [CHANGELOG](./CHANGELOG.md) on this repository.

## License

This project is licensed under the Apache License v2.0 - see the LICENSE file for details

## Acknowledgments

* 《大话数据结构》

# 图算法

图算法实现，包括存储结构、深度/广度优先遍历、最小生成树创建，基于不同语言（`pyhon/c++`）实现

## 功能特性

**邻接矩阵**存储结构实现功能（`c++`实现）如下：

1. 广度优先遍历(BFS)
2. 深度优先遍历(DFS)
3. `Prim`算法
4. `Kruskal`算法

**邻接表**存储结构实现功能（`c++`实现）如下：

1. 广度优先遍历(BFS)
2. 深度优先遍历(DFS)
3. `Prim`算法
4. `Kruskal`算法

## 工程结构

```
.
├── cplusplus
│   ├── CMakeLists.txt
│   ├── common_iostream.h                 # 常用iostream函数
│   ├── graph.h                           # 图存储结构：邻接矩阵 + 邻接表
│   ├── lena.jpg
│   ├── main.cpp                          # 入口文件
│   ├── undigraph.cpp                     # 类Undigraph实现
│   └── undigraph.h                       # 类Undigraph声明
├── LICENSE
└── README.md
```

## 版本化

我们使用[SemVer](http://semver.org/)进行版本控制。 对于可用的版本，请参阅仓库中的[标记](https://github.com/zjZSTU/graph_algorithm/releases)

## 作者

* zhujian - *初始工作* - [zjZSTU](https://github.com/zjZSTU)

## 更改日志

请参阅仓库中的[CHNAGELOG](./CHNAGELOG.md)

## 协议

本工程基于`Apache v2.0`协议 - 具体协议内容参考`LICENSE`文件

## 致谢

* 《大话数据结构》
![](./test_graph.png)

# 图算法

[![](https://img.shields.io/badge/commitizen-friendly-brightgreen.svg)](http://commitizen.github.io/cz-cli/)

图算法实现，包括存储结构、深度/广度优先遍历、最小生成树创建，基于不同语言（`pyhon/c++`）实现

## 内容列表

- [用法](#用法)
- [版本更新日志](#版本更新日志)
- [待办事项](#待办事项)
- [主要维护人员](#主要维护人员)
- [致谢](#致谢)
- [参与贡献方式](#参与贡献方式)
- [许可证](#许可证)

## 用法

### 先决条件

本仓库要求具备以下准备知识

* `c++`
* 数据结构

### 实现

**邻接矩阵**存储结构实现功能（`c++`实现）如下：

1. 广度优先遍历(`BFS`)
2. 深度优先遍历(`DFS`)
3. `Prim`算法
4. `Kruskal`算法

**邻接表**存储结构实现功能（`c++`实现）如下：

1. 广度优先遍历(`BFS`)
2. 深度优先遍历(`DFS`)
3. `Prim`算法
4. `Kruskal`算法

## 版本更新日志

请参阅仓库中的[CHANGELOG](./CHANGELOG.md)

# 待办事项

* `C++11`标准实现
* 最短路径算法实现
* 拓扑排序算法实现

## 主要维护人员

* zhujian - *Initial work* - [zjZSTU](https://github.com/zjZSTU)

## 致谢

感谢以下人员的参与

[![](https://avatars3.githubusercontent.com/u/13742735?s=460&v=4)](https://github.com/zjZSTU)

参考以下资源

* 《大话数据结构》

## 参与贡献方式

欢迎任何人的参与！打开[issue](https://github.com/zjZSTU/graph_algorithm/issues)或提交合并请求

注意:

* `git`提交请遵守[Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0-beta.4/)
* 如果进行版本化，请遵守[Semantic Versioning 2.0.0](https://semver.org)规范
* 如果修改README，请遵守[standard-readme](https://github.com/RichardLitt/standard-readme)规范

## 许可证

[Apache License 2.0](LICENSE) © 2019 zjZSTU
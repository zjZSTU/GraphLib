//
// Created by zj on 19-10-31.
//

#ifndef CPLUSPLUS_DISJOINSET_H
#define CPLUSPLUS_DISJOINSET_H

#include <iostream>
#include <memory>

typedef struct disjoint_set_element {
    int parentPoint;
    int rank;
} ds_element;


class DisjointSet {
public:
    DisjointSet(const int num);

    ~DisjointSet();

    /**
     * 利用路径压缩优化
     * @param x 起始节点
     * @return 根节点
     */
    int find(int x);

    /**
     * 子集合并，利用rank进行优化
     * @param x 根节点
     * @param y 根节点
     * @return 连接成功，返回true；连接失败或者原节点在同一个子集中，返回false
     */
    bool join(int x, int y);

    /**
     * 返回集合数
     */
    int getSetNum() {
        return this->num;
    }

private:
    ds_element *elements;
    // 子集数
    int num;
};


#endif //CPLUSPLUS_DISJOINSET_H

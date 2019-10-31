//
// Created by zj on 19-10-31.
//

#include "DisjointSet.h"

DisjointSet::DisjointSet(const int num) {
    elements = new ds_element[num];
    this->num = num;

    for (int i = 0; i < num; i++) {
        elements[i].rank = 0;
        elements[i].parentPoint = i;
    }
}

DisjointSet::~DisjointSet() {
    delete[] elements;
}

int DisjointSet::find(int x) {
    if (elements[x].parentPoint != x) {
        elements[x].parentPoint = find(elements[x].parentPoint);
    }

    return elements[x].parentPoint;
}

bool DisjointSet::join(int x, int y) {
    if (x == y) {
        return false;
    }

    // 保证节点x的rank大于等于节点y
    if (elements[x].rank < elements[y].rank) {
        int tmp = x;
        x = y;
        y = tmp;
    }

    elements[y].parentPoint = x;
    if (elements[x].rank == elements[y].rank) {
        elements[x].rank += 1;
    }

    this->num--;
    return true;
}

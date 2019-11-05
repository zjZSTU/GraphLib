//
// Created by zj on 19-11-5.
//

#ifndef CPLUSPLUS_POINTSET_H
#define CPLUSPLUS_POINTSET_H

class PointSetElement {
public:
    int p;
    int size;

    PointSetElement() {}

    PointSetElement(int p_) {
        p = p_;
        size = 1;
    }
};

class PointSet {
public:
    PointSet(int nb_elements_);

    ~PointSet();

    int nb_elements;

    // Return the main point of the point's set
    int getBasePoint(int p);

    // Join two sets of points, based on their main point
    void joinPoints(int p_a, int p_b);

    // Return the set size of a set (based on the main point)
    int size(unsigned int p) { return mapping[p].size; }

private:
    PointSetElement *mapping;
};


#endif //CPLUSPLUS_POINTSET_H

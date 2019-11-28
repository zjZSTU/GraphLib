//
// Created by zj on 19-11-28.
//

#include "SelectiveSearchSegmentation.h"
#include "SelectiveSearchSegmentationImpl.h"

std::shared_ptr<SelectiveSearchSegmentation> createSelectiveSearchSegmentation() {
    Ptr<SelectiveSearchSegmentation> s = makePtr<SelectiveSearchSegmentationImpl>();
    return s;
}

std::ostream &operator<<(std::ostream &os, const Neighbour &n) {
    os << "Neighbour[" << n.from << "->" << n.to << "," << n.similarity << "]";
    return os;
}

std::ostream &operator<<(std::ostream &os, const Region &r) {
    os << "Region[WID" << r.id << ", L" << r.level << ", merged to " << r.merged_to << ", R:" << r.rank << ", "
       << r.bounding_box << "]";
    return os;
}
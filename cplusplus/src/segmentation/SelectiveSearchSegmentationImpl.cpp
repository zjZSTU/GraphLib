//
// Created by zj on 19-11-28.
//

#include "SelectiveSearchSegmentationImpl.h"
#include "GraphSegmentation.h"

void SelectiveSearchSegmentationImpl::setBaseImage(InputArray img) {
    base_image = img.getMat();
}

void SelectiveSearchSegmentationImpl::addImage(InputArray img) {
    images.push_back(img.getMat());
}

void SelectiveSearchSegmentationImpl::clearImages() {
    images.clear();
}

void SelectiveSearchSegmentationImpl::addGraphSegmentation(std::shared_ptr<GraphSegmentation> g) {
    segmentations.push_back(g);
}

void SelectiveSearchSegmentationImpl::clearGraphSegmentations() {
    segmentations.clear();
}

void SelectiveSearchSegmentationImpl::addStrategy(std::shared_ptr<SelectiveSearchSegmentationStrategy> s) {
    strategies.push_back(s);
}

void SelectiveSearchSegmentationImpl::clearStrategies() {
    strategies.clear();
}

void SelectiveSearchSegmentationImpl::switchToSingleStrategy(int k, float sigma) {
    clearImages();
    clearGraphSegmentations();
    clearStrategies();

    Mat hsv;
    cvtColor(base_image, hsv, COLOR_BGR2HSV);
    addImage(hsv);

    std::shared_ptr<GraphSegmentation> gs = createGraphSegmentation();
    gs->setK((float) k);
    gs->setSigma(sigma);
    addGraphSegmentation(gs);

    std::shared_ptr<SelectiveSearchSegmentationStrategyColor> color = createSelectiveSearchSegmentationStrategyColor();
    std::shared_ptr<SelectiveSearchSegmentationStrategyFill> fill = createSelectiveSearchSegmentationStrategyFill();
    std::shared_ptr<SelectiveSearchSegmentationStrategyTexture> texture = createSelectiveSearchSegmentationStrategyTexture();
    std::shared_ptr<SelectiveSearchSegmentationStrategySize> size = createSelectiveSearchSegmentationStrategySize();

    std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple> m = createSelectiveSearchSegmentationStrategyMultiple(color, fill,
                                                                                                           texture,
                                                                                                           size);

    addStrategy(m);
}

void SelectiveSearchSegmentationImpl::switchToSelectiveSearchFast(int base_k, int inc_k, float sigma) {
    clearImages();
    clearGraphSegmentations();
    clearStrategies();

    Mat hsv;
    cvtColor(base_image, hsv, COLOR_BGR2HSV);
    addImage(hsv);
    Mat lab;
    cvtColor(base_image, lab, COLOR_BGR2Lab);
    addImage(lab);

    for (int k = base_k; k <= base_k + inc_k * 2; k += inc_k) {
        std::shared_ptr<GraphSegmentation> gs = createGraphSegmentation();
        gs->setK((float) k);
        gs->setSigma(sigma);
        addGraphSegmentation(gs);
    }

    std::shared_ptr<SelectiveSearchSegmentationStrategyColor> color = createSelectiveSearchSegmentationStrategyColor();
    std::shared_ptr<SelectiveSearchSegmentationStrategyFill> fill = createSelectiveSearchSegmentationStrategyFill();
    std::shared_ptr<SelectiveSearchSegmentationStrategyTexture> texture = createSelectiveSearchSegmentationStrategyTexture();
    std::shared_ptr<SelectiveSearchSegmentationStrategySize> size = createSelectiveSearchSegmentationStrategySize();

    std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple> m = createSelectiveSearchSegmentationStrategyMultiple(color, fill,
                                                                                                           texture,
                                                                                                           size);

    addStrategy(m);

    std::shared_ptr<SelectiveSearchSegmentationStrategyFill> fill2 = createSelectiveSearchSegmentationStrategyFill();
    std::shared_ptr<SelectiveSearchSegmentationStrategyTexture> texture2 = createSelectiveSearchSegmentationStrategyTexture();
    std::shared_ptr<SelectiveSearchSegmentationStrategySize> size2 = createSelectiveSearchSegmentationStrategySize();

    std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple> m2 = createSelectiveSearchSegmentationStrategyMultiple(fill2,
                                                                                                            texture2,
                                                                                                            size2);

    addStrategy(m2);

}

void SelectiveSearchSegmentationImpl::switchToSelectiveSearchQuality(int base_k, int inc_k, float sigma) {
    clearImages();
    clearGraphSegmentations();
    clearStrategies();


    Mat hsv;
    cvtColor(base_image, hsv, COLOR_BGR2HSV);
    addImage(hsv);
    Mat lab;
    cvtColor(base_image, lab, COLOR_BGR2Lab);
    addImage(lab);

    Mat I;
    cvtColor(base_image, I, COLOR_BGR2GRAY);
    addImage(I);

    Mat channel[3];
    split(hsv, channel);
    addImage(channel[0]);

    split(base_image, channel);
    std::vector<Mat> channel2 = {channel[2], channel[1], I};

    Mat rgI;
    merge(channel2, rgI);
    addImage(rgI);

    for (int k = base_k; k <= base_k + inc_k * 4; k += inc_k) {
        std::shared_ptr<GraphSegmentation> gs = createGraphSegmentation();
        gs->setK((float) k);
        gs->setSigma(sigma);
        addGraphSegmentation(gs);
    }

    std::shared_ptr<SelectiveSearchSegmentationStrategyColor> color = createSelectiveSearchSegmentationStrategyColor();
    std::shared_ptr<SelectiveSearchSegmentationStrategyFill> fill = createSelectiveSearchSegmentationStrategyFill();
    std::shared_ptr<SelectiveSearchSegmentationStrategyTexture> texture = createSelectiveSearchSegmentationStrategyTexture();
    std::shared_ptr<SelectiveSearchSegmentationStrategySize> size = createSelectiveSearchSegmentationStrategySize();

    std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple> m = createSelectiveSearchSegmentationStrategyMultiple(color, fill,
                                                                                                           texture,
                                                                                                           size);

    addStrategy(m);

    std::shared_ptr<SelectiveSearchSegmentationStrategyFill> fill2 = createSelectiveSearchSegmentationStrategyFill();
    std::shared_ptr<SelectiveSearchSegmentationStrategyTexture> texture2 = createSelectiveSearchSegmentationStrategyTexture();
    std::shared_ptr<SelectiveSearchSegmentationStrategySize> size2 = createSelectiveSearchSegmentationStrategySize();

    std::shared_ptr<SelectiveSearchSegmentationStrategyMultiple> m2 = createSelectiveSearchSegmentationStrategyMultiple(fill2,
                                                                                                            texture2,
                                                                                                            size2);

    addStrategy(m2);

    std::shared_ptr<SelectiveSearchSegmentationStrategyFill> fill3 = createSelectiveSearchSegmentationStrategyFill();
    addStrategy(fill3);

    std::shared_ptr<SelectiveSearchSegmentationStrategySize> size3 = createSelectiveSearchSegmentationStrategySize();
    addStrategy(size3);
}

void SelectiveSearchSegmentationImpl::process(std::vector<Rect> &rects) {

    std::vector<Region> all_regions;

    int image_id = 0;

    for (std::vector<Mat>::iterator image = images.begin(); image != images.end(); ++image) {
        for (std::vector<std::shared_ptr<GraphSegmentation> >::iterator gs = segmentations.begin();
             gs != segmentations.end(); ++gs) {

            Mat img_regions;
            Mat_<char> is_neighbour;
            Mat_<int> sizes;

            // Compute initial segmentation
            // 图分割，得到分割结果
            (*gs)->processImage(*image, img_regions);

            // Get number of regions
            // 图分割结果共得到(max+1)个分割
            double min, max;
            minMaxLoc(img_regions, &min, &max);
            int nb_segs = (int) max + 1;

            // Compute bouding rects and neighbours
            std::vector<Rect> bounding_rects;
            bounding_rects.resize(nb_segs);

            std::vector<std::vector<cv::Point> > points;

            points.resize(nb_segs);

            // 邻接矩阵，不同分割之间是否相邻
            is_neighbour = Mat::zeros(nb_segs, nb_segs, CV_8UC1);
            sizes = Mat::zeros(nb_segs, 1, CV_32SC1);

            const int *previous_p = NULL;

            // 遍历图分割处后的结果图
            for (int i = 0; i < (int) img_regions.rows; i++) {
                const int *p = img_regions.ptr<int>(i);

                for (int j = 0; j < (int) img_regions.cols; j++) {

                    // 保存每个分割的像素坐标
                    points[p[j]].push_back(cv::Point(j, i));
                    // 统计每个分割的像素个数
                    sizes.at<int>(p[j], 0) = sizes.at<int>(p[j], 0) + 1;

                    if (i > 0 && j > 0) {

                        // 计算相邻区域，判断像素点(x,y)是否和(x-1, y)/(x,y-1)/(x-1,y-1)属于同一邻域
                        is_neighbour.at<char>(p[j], p[j - 1]) = 1;
                        is_neighbour.at<char>(p[j], previous_p[j]) = 1;
                        is_neighbour.at<char>(p[j], previous_p[j - 1]) = 1;

                        is_neighbour.at<char>(p[j - 1], p[j]) = 1;
                        is_neighbour.at<char>(previous_p[j], p[j]) = 1;
                        is_neighbour.at<char>(previous_p[j - 1], p[j]) = 1;
                    }
                }
                previous_p = p;
            }

            // 根据每个分割的像素点集合计算边界框
            for (int seg = 0; seg < nb_segs; seg++) {
                bounding_rects[seg] = cv::boundingRect(points[seg]);
            }

            // 通过相似度策略和分层分组方法计算假设区域
            for (std::vector<std::shared_ptr<SelectiveSearchSegmentationStrategy> >::iterator strategy = strategies.begin();
                 strategy != strategies.end(); ++strategy) {
                // 计算基于不同初始图像/图分割算法/相似度策略的假设区域集
                std::vector<Region> regions;
                hierarchicalGrouping(*image, *strategy, img_regions, is_neighbour, sizes, nb_segs, bounding_rects,
                                     regions, image_id);

                for (std::vector<Region>::iterator region = regions.begin(); region != regions.end(); ++region) {
                    all_regions.push_back(*region);
                }
            }

            image_id++;
        }
    }

    // 按照rank进行排序(rank随机）
    std::sort(all_regions.begin(), all_regions.end());

    std::map<Rect, char, rectComparator> processed_rect;

    rects.clear();

    // Remove duplicate in rect list
    for (std::vector<Region>::iterator region = all_regions.begin(); region != all_regions.end(); ++region) {
        if (processed_rect.find((*region).bounding_box) == processed_rect.end()) {
            processed_rect[(*region).bounding_box] = true;
            rects.push_back((*region).bounding_box);
        }
    }
}

void SelectiveSearchSegmentationImpl::hierarchicalGrouping(const Mat &img, std::shared_ptr<SelectiveSearchSegmentationStrategy> &s,
                                                           const Mat &img_regions, const Mat_<char> &is_neighbour,
                                                           const Mat_<int> &sizes_, int &nb_segs,
                                                           const std::vector<Rect> &bounding_rects,
                                                           std::vector<Region> &regions, int image_id) {

    Mat sizes = sizes_.clone();

    std::vector<Neighbour> similarities;
    regions.clear();

    /////////////////////////////////////////

    s->setImage(img, img_regions, sizes, image_id);

    // Compute initial similarities
    for (int i = 0; i < nb_segs; i++) {
        Region r;

        r.id = i;
        r.level = 1;
        r.merged_to = -1;
        r.bounding_box = bounding_rects[i];

        // 获取初始区域（图分割算法得到的分割边界框）
        regions.push_back(r);

        // 遍历所有相邻区域对，保存在对象Neighbour
        for (int j = i + 1; j < nb_segs; j++) {
            if (is_neighbour.at<char>(i, j)) {
                Neighbour n;
                n.from = i;
                n.to = j;
                // 通过相似度策略计算
                n.similarity = s->get(i, j);

                similarities.push_back(n);
            }
        }
    }

    // 遍历相似集
    while (similarities.size() > 0) {

        // 从小到大排序
        std::sort(similarities.begin(), similarities.end());

        // for(std::vector<Neighbour>::iterator similarity = similarities.begin(); similarity != similarities.end(); ++similarity) {
        //     std::cout << *similarity << std::endl;
        // }

        // 提取并移除向量中最后一个对象（最大相似度）
        Neighbour p = similarities.back();
        similarities.pop_back();

        Region region_from = regions[p.from];
        Region region_to = regions[p.to];

        Region new_r;
        new_r.id = std::min(region_from.id, region_to.id); // Should be the smalest, working ID
        // 合并次数，每合并一次加1
        new_r.level = std::max(region_from.level, region_to.level) + 1;
        new_r.merged_to = -1;
        new_r.bounding_box = region_from.bounding_box | region_to.bounding_box;

        regions.push_back(new_r);

        regions[p.from].merged_to = (int) regions.size() - 1;
        regions[p.to].merged_to = (int) regions.size() - 1;

        // Merge
        s->merge(region_from.id, region_to.id);

        // Update size
        sizes.at<int>(region_from.id, 0) += sizes.at<int>(region_to.id, 0);
        sizes.at<int>(region_to.id, 0) = sizes.at<int>(region_from.id, 0);

        std::vector<int> local_neighbours;

        // 遍历所有相似对，找到之前两个相邻区域的相邻区域，得到新建区域的相邻集
        for (std::vector<Neighbour>::iterator similarity = similarities.begin(); similarity != similarities.end();) {
            if ((*similarity).from == p.from || (*similarity).to == p.from || (*similarity).from == p.to ||
                (*similarity).to == p.to) {
                int from = 0;

                if ((*similarity).from == p.from || (*similarity).from == p.to) {
                    from = (*similarity).to;
                } else {
                    from = (*similarity).from;
                }

                bool already_neighboor = false;

                for (std::vector<int>::iterator local_neighbour = local_neighbours.begin();
                     local_neighbour != local_neighbours.end(); local_neighbour++) {
                    if (*local_neighbour == from) {
                        already_neighboor = true;
                    }
                }

                // 保存新建区域的邻域ID
                if (!already_neighboor) {
                    local_neighbours.push_back(from);
                }

                similarity = similarities.erase(similarity);
            } else {
                similarity++;
            }
        }

        // 计算合并后区域与相邻区域之间的相似度
        for (std::vector<int>::iterator local_neighbour = local_neighbours.begin();
             local_neighbour != local_neighbours.end(); local_neighbour++) {

            Neighbour n;
            n.from = (int) regions.size() - 1;
            n.to = *local_neighbour;
            n.similarity = s->get(regions[n.from].id, regions[n.to].id);

            similarities.push_back(n);
        }
    }

    // Compute regions' rank
    // 获取所有假设区域后进行随机排序，相对而言level越大，rank越大
    for (std::vector<Region>::iterator region = regions.begin(); region != regions.end(); ++region) {
        // Note: this is inverted from the paper, but we keep the lover region first so it's works
        (*region).rank = ((double) rand() / (RAND_MAX)) * ((*region).level);
    }

}
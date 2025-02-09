#include <fstream>
#include <iostream>
#include <random>
#include <cstdlib>
#include <map>
#include <vector>

#include "segment/include/segment.hpp"

[[nodiscard]] bool isNonVertOverlap(
    const std::map<Fraction, std::vector<Segment>>& non_vertical_segms,
    const Segment& new_segm) {
    Fraction new_segm_k = new_segm.getIncline();
    auto non_vertical_segms_f_iter = non_vertical_segms.find(new_segm_k);
    if (non_vertical_segms_f_iter == non_vertical_segms.end()) {
        return false;
    }
    const std::vector<Segment>& parallel_segms =
        non_vertical_segms_f_iter->second;
    std::size_t parallel_semgs_size = parallel_segms.size();
    auto new_pair = new_segm.getPoints();
    IntPoint new_segm_left = new_pair.first;
    IntPoint new_segm_right = new_pair.second;
    if (new_segm_left.x_ > new_segm_right.x_) {
        std::swap(new_segm_left, new_segm_right);
    }
    for (std::size_t i = 0; i < parallel_semgs_size; ++i) {
        std::pair<const IntPoint&, const IntPoint&> parallel_pair =
            parallel_segms[i].getPoints();
        IntPoint parallel_segm_left = parallel_pair.first;
        IntPoint parallel_segm_right = parallel_pair.second;
        if (parallel_segm_left.x_ > parallel_segm_right.x_) {
            std::swap(parallel_segm_left, parallel_segm_right);
        }
        if (new_segm_left.x_ != parallel_segm_right.x_) {
            Fraction tmp_segm_k =
                Segment(static_cast<int>(new_segm_left.x_),
                        static_cast<int>(new_segm_left.y_),
                        static_cast<int>(parallel_segm_right.x_),
                        static_cast<int>(parallel_segm_right.y_))
                    .getIncline();
            if (tmp_segm_k == new_segm_k &&
                ((parallel_segm_left.x_ < new_segm_left.x_ &&
                  new_segm_left.x_ < parallel_segm_right.x_) ||
                 (parallel_segm_left.x_ < new_segm_right.x_ &&
                  new_segm_right.x_ < parallel_segm_right.x_) ||
                 (new_segm_left.x_ < parallel_segm_left.x_ &&
                  parallel_segm_left.x_ < new_segm_right.x_) ||
                 (new_segm_left.x_ < parallel_segm_right.x_ &&
                  parallel_segm_right.x_ < new_segm_right.x_))) {
                return true;
            }
        }
    }
    return false;
}

[[nodiscard]] bool isVertOverlap(
    const std::map<int, std::vector<Segment>>& vertical_semgs,
    const Segment& new_segm) {
    auto new_pair = new_segm.getPoints();
    IntPoint new_segm_left = new_pair.first;
    IntPoint new_segm_right = new_pair.second;
    if (new_segm_left.y_ > new_segm_right.y_) {
        std::swap(new_segm_left, new_segm_right);
    }
    auto vertical_semgs_f_iter =
        vertical_semgs.find(static_cast<int>(new_segm_left.x_));
    if (vertical_semgs_f_iter == vertical_semgs.end()) {
        return false;
    }
    const std::vector<Segment>& line_segms = vertical_semgs_f_iter->second;
    std::size_t line_semgs_size = line_segms.size();
    for (std::size_t i = 0; i < line_semgs_size; ++i) {
        std::pair<const IntPoint&, const IntPoint&> line_pair =
            line_segms[i].getPoints();
        IntPoint line_segm_left = line_pair.first;
        IntPoint line_segm_right = line_pair.second;
        if (line_segm_left.y_ > line_segm_right.y_) {
            std::swap(line_segm_left, line_segm_right);
        }
        if ((line_segm_left.y_ < new_segm_left.y_ &&
             new_segm_left.y_ < line_segm_right.y_) ||
            (line_segm_left.y_ < new_segm_right.y_ &&
             new_segm_right.y_ < line_segm_right.y_) ||
            (new_segm_left.y_ < line_segm_left.y_ &&
             line_segm_left.y_ < new_segm_right.y_) ||
            (new_segm_left.y_ < line_segm_right.y_ &&
             line_segm_right.y_ < new_segm_right.y_)) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr
            << "USAGE: <POINTS_RANGE> <SEGMENTS_NUMBER> <OUTPUT_FILE_NAME>\n ";
        return EXIT_FAILURE;
    }
    std::ofstream output_file(argv[3], std::ios::binary);
    if (!output_file.is_open()) {
        std::cerr << "Couldn't open output file\n";
        return EXIT_FAILURE;
    }
    int points_range = std::atoi(argv[1]);
    int segments_number = std::atoi(argv[2]);
    std::random_device rn_dev;
    std::mt19937 gen(rn_dev());
    std::uniform_int_distribution<> unif_dist(-points_range, points_range);
    int x1, y1, x2, y2;
    std::map<Fraction, std::vector<Segment>> non_vertical_segms;
    std::map<int, std::vector<Segment>> vertical_segms;
    int curr_segments_number = 0;
    while (curr_segments_number < segments_number) {
        do {
            x1 = unif_dist(gen);
            y1 = unif_dist(gen);
            x2 = unif_dist(gen);
            y2 = unif_dist(gen);
        } while (x1 == x2 && y1 == y2);
        Segment new_segm(x1, y1, x2, y2);
        if (x1 != x2) {
            if (!isNonVertOverlap(non_vertical_segms, new_segm)) {
                non_vertical_segms[new_segm.getIncline()].push_back(new_segm);
                ++curr_segments_number;
                output_file << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2;
            }
        } else {
            if (!isVertOverlap(vertical_segms, new_segm)) {
                vertical_segms[x1].push_back(new_segm);
                ++curr_segments_number;
                output_file << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2;
            }
        }
        if (curr_segments_number != segments_number) {
            output_file << '\n';
        }
    }
    output_file.close();
    return EXIT_SUCCESS;
}

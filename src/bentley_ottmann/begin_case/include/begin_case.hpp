#ifndef BENTLEY_OTTMANN_SRC_BENTLEY_OTTMANN_BEGIN_CASE
#define BENTLEY_OTTMANN_SRC_BENTLEY_OTTMANN_BEGIN_CASE

#include <vector>
#include <queue>
#include <set>
#include <map>

#include <cassert>

#include "../../../segment/include/segment.hpp"
#include "../../../comparator/include/comparator.hpp"
#include "../../../intersection_info/include/intersection_info.hpp"
#include "../../../find_intersection/include/find_intersection.hpp"

#define assertm(exp, msg) assert((void(msg), exp))

void beginCaseHandler(
    const QueueItem& new_event, int64_t& vert_line_end_y,
    const Segment* const& segm_begin_ptr, const std::vector<Segment>& segments,
    std::vector<const Segment*>& segment_ptrs,
    std::priority_queue<QueueItem, std::vector<QueueItem>, QueueComparator>
        min_heap,
    std::map<RealPoint, IntersectionInfo>& intersections,
    std::set<const Segment**, StatusComparator>& status) {
    const Segment& new_segm = segments[new_event.segment_ind_];
    const auto& [left_point, right_point] = new_segm.getPoints();
    if (left_point.x_ == right_point.x_) {
        vert_line_end_y = right_point.y_;
    } else {
        // Insert non-vertical segment
        const auto& [ins_iter, is_inserted] =
            status.insert(&segment_ptrs[new_event.segment_ind_]);
        assertm(is_inserted, "NO INSERTSION");
        if (status.begin() != ins_iter) {
            const auto& prev_iter = std::prev(ins_iter);
            const auto& inter_point =
                findIntersection(***prev_iter, ***ins_iter);
            int ins_iter_ind = static_cast<int>(**ins_iter - segm_begin_ptr);
            int prev_iter_ind = static_cast<int>(**prev_iter - segm_begin_ptr);
            if (inter_point.has_value()) {
                const auto& f_iter = intersections.find(inter_point.value());
                // The point is already in intersections
                if (f_iter != intersections.end()) {
                    std::unordered_set<int>& unord_set =
                        f_iter->second.intersec_segms_;
                    // Insert ins_iter
                    if (!unord_set.contains(ins_iter_ind)) {
                        unord_set.insert(ins_iter_ind);
                        const Fraction& new_semg_k =
                            segments[ins_iter_ind].getIncline();
                        if (segments[f_iter->second.lower_seg_ind_]
                                .getIncline() < new_semg_k) {
                            f_iter->second.lower_seg_ind_ = ins_iter_ind;
                        }
                    }
                    prev_iter_ind =
                        static_cast<int>(**prev_iter - segm_begin_ptr);
                    if (!unord_set.contains(prev_iter_ind)) {
                        unord_set.insert(prev_iter_ind);
                        const Fraction& new_semg_k =
                            segments[prev_iter_ind].getIncline();
                        if (segments[f_iter->second.lower_seg_ind_]
                                .getIncline() < new_semg_k) {
                            f_iter->second.lower_seg_ind_ = prev_iter_ind;
                        }
                    }
                } else {
                    // No such point in intersections
                    min_heap.push(
                        QueueItem{.segment_ind_ = -1,
                                  .oper_type_ = OperType::INTERSECTION,
                                  .point_ = inter_point.value()});
                    const Fraction& prev_iter_k =
                        segments[prev_iter_ind].getIncline();
                    const Fraction& ins_iter_k =
                        segments[ins_iter_ind].getIncline();
                    int lower_ind = -1;
                    if (prev_iter_k > ins_iter_k) {
                        lower_ind = prev_iter_ind;
                    } else {
                        lower_ind = ins_iter_ind;
                    }
                    intersections.insert(std::pair<RealPoint, IntersectionInfo>{
                        inter_point.value(),
                        IntersectionInfo{
                            .lower_seg_ind_ = lower_ind,
                            .intersec_segms_ =
                                std::unordered_set<int>{prev_iter_ind,
                                                        ins_iter_ind},
                        }});
                }
            }
            // TODO check std::next iter
        }
        if (left_point.y_ < vert_line_end_y) {
            // const auto& f_iter =
            //     intersections.find(static_cast<RealPoint>(left_point));
            // if (f_iter != intersections.end()) {
            // } else {
            // }
            // if (intersections.co)
        }
        // new_event
        // TODO Check if we are in vert line and if so, find
        // intersection point
    }
}

#endif  // BENTLEY_OTTMANN_SRC_BENTLEY_OTTMANN_BEGIN_CASE

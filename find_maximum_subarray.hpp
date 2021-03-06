#ifndef FIND_MAXIMUM_SUBARRAY
#define FIND_MAXIMUM_SUBARRAY

#include <iterator>
#include <tuple>

namespace find {
  namespace detail {
    template<typename InputIt>
    InputIt middle_iterator(InputIt begin, InputIt end) {
      return std::next(begin, std::distance(begin, end) / 2);
    }

    template<typename RandomIt>
    std::tuple<RandomIt, RandomIt, typename RandomIt::value_type>
    find_maximum_crossing_subarray(RandomIt begin, RandomIt mid, RandomIt end) {
      auto max_left = mid - 1;
      auto max_right = mid;
      auto left_sum = *(mid-1);
      auto right_sum = *mid;
      typename RandomIt::value_type total_sum = 0;

      for (auto i = mid - 1; i >= begin; --i) {
        total_sum += *i;
        if (total_sum > left_sum) {
          left_sum = total_sum;
          max_left = i;
        }
      }

      total_sum = 0;
      for (auto i = mid; i < end; ++i) {
        total_sum += *i;
        if (total_sum > right_sum) {
          right_sum = total_sum;
          max_right = i;
        }
      }

      return {max_left, max_right, left_sum + right_sum};
    }
  }
  
  template<typename RandomIt>
  std::tuple<RandomIt, RandomIt, typename RandomIt::value_type>
  find_maximum_subarray(RandomIt begin, RandomIt end) {
    if (end - begin > 1) {
      const auto mid = detail::middle_iterator(begin, end);
      const auto left_subarray = find_maximum_subarray(begin, mid);
      const auto right_subarray = find_maximum_subarray(mid, end);
      const auto cross_subarray = detail::find_maximum_crossing_subarray(begin, mid, end);

      const auto& left_sum = std::get<2>(left_subarray);
      const auto& right_sum = std::get<2>(right_subarray);
      const auto& cross_sum = std::get<2>(cross_subarray);
    
      if (left_sum >= right_sum && left_sum >= cross_sum)
        return left_subarray;
      if (right_sum >= left_sum && right_sum >= cross_sum)
        return right_subarray;
      
      return cross_subarray;
    }
    
    return {begin, end-1, *(end-1)};
  }
}

#endif

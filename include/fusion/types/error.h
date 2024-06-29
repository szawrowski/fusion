// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef FUSION_TYPE_ERROR_H_
#define FUSION_TYPE_ERROR_H_

#include <utility>

namespace fus {

template <typename E>
class error_t {
public:
  explicit error_t(E error) : error_{std::move(error)} {}

  const E& get() const noexcept { return error_; }

private:
  E error_;
};

template <typename E>
bool operator==(const error_t<E>& lhs, const error_t<E>& rhs) {
  return lhs.get() == rhs.get();
}

template <typename E>
bool operator!=(const error_t<E>& lhs, const error_t<E>& rhs) {
  return !(lhs == rhs);
}

}  // namespace fus

#endif  // FUSION_TYPE_ERROR_H_
